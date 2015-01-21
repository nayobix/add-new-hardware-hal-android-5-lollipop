#define LOG_TAG "SensorHubMgmtServiceJNI"                                           
#include "utils/Log.h"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"
#include <utils/misc.h>
#include <hardware/hardware.h>
#include <hardware/sensorhubmgmt.h>
#include <stdio.h>

namespace android
{
    sensorhubmgmt_device_t* sensorhubmgmt_dev;

    static jint init_native(JNIEnv *env, jobject clazz)
    {
        int err;
        hw_module_t* module;
        sensorhubmgmt_device_t* dev = NULL;
        err = hw_get_module(SENSORHUBMGMT_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
        if (err == 0) {
            if (module->methods->open(module, "", ((hw_device_t**) &dev)) != 0) {
                ALOGE("Couldn't load %s module (%s)", SENSORHUBMGMT_HARDWARE_MODULE_ID, strerror(-err));
                return 0;
            }
        } else {
                ALOGE("Couldn't hw_get_module %s module. Error (%s)", SENSORHUBMGMT_HARDWARE_MODULE_ID, strerror(-err));
        }
        return (jint)dev;
    }
    static void finalize_native(JNIEnv *env, jobject clazz, int ptr)
    {
        sensorhubmgmt_device_t* dev = (sensorhubmgmt_device_t*)ptr;
        if (dev == NULL) {
            ALOGE("Error in finalize_native. dev == NULL\n");
            return;
        }
        free(dev);
    }
    static int read_native(JNIEnv *env, jobject clazz, int ptr, jbyteArray buffer)
    {
        sensorhubmgmt_device_t* dev = (sensorhubmgmt_device_t*)ptr;
        jbyte* real_byte_array;
        int length;
        real_byte_array = env->GetByteArrayElements(buffer, NULL);
        if (dev == NULL) {
            ALOGE("Error in read_native. dev == NULL\n");
            return 0;
        }
        length = dev->read((char*) real_byte_array, env->GetArrayLength(buffer));
        env->ReleaseByteArrayElements(buffer, real_byte_array, 0);
        return length;
    }
    static int write_native(JNIEnv *env, jobject clazz, int ptr, jbyteArray buffer)
    {
        sensorhubmgmt_device_t* dev = (sensorhubmgmt_device_t*)ptr;
        jbyte* real_byte_array;
        int length;
        real_byte_array = env->GetByteArrayElements(buffer, NULL);
        if (dev == NULL) {
            ALOGE("Error in write_native. dev == NULL\n");
            return 0;
        }
        length = dev->write((char*) real_byte_array, env->GetArrayLength(buffer));
        env->ReleaseByteArrayElements(buffer, real_byte_array, 0);
        return length;
    }
    static int test_native(JNIEnv *env, jobject clazz, int ptr, int value)
    {
        sensorhubmgmt_device_t* dev = (sensorhubmgmt_device_t*)ptr;
        if (dev == NULL) {
            ALOGE("Error in test_native. dev == NULL\n");
            return 0;
        }
        return dev->test(value);
    }
    static JNINativeMethod method_table[] = {
        { "init_native", "()I", (void*)init_native },
        { "finalize_native", "(I)V", (void*)finalize_native },
        { "read_native", "(I[B)I", (void*)read_native },
        { "write_native", "(I[B)I", (void*)write_native },
        { "test_native", "(II)I", (void*)test_native},
    };
    int register_android_server_SensorHubMgmtService(JNIEnv *env)
    {
        return jniRegisterNativeMethods(env, "com/android/server/sensorhubmgmt/SensorHubMgmtService",
        method_table, NELEM(method_table));
    };
};
