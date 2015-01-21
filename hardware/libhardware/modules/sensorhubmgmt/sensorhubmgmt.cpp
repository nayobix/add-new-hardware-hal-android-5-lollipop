#include <errno.h>

#include <cutils/sockets.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <hardware/sensorhubmgmt.h>

#define LOG_NDEBUG 1
#include <cutils/log.h>

//static const char THE_DEVICE[] = "/sys/fs/entry";
static const char THE_DEVICE[] = "/data/sensorhubmgmt.txt";

int sensorhubmgmt__read(char* buffer, int length)
{
    int retval, fd;
    ALOGV("read()for %d bytes called", length);
    fd = open(THE_DEVICE, O_RDWR|O_CREAT, 777);
    
    if (fd < 0) {
        ALOGE("Error open file: %s - %s", THE_DEVICE, strerror(errno));
        return errno;
    }

    retval = read(fd, buffer, length);

    close(fd);

    return retval;
}
int sensorhubmgmt__write(char* buffer, int length)
{
    int retval, fd;
    ALOGV("write()for %d bytes called", length);
    fd = open(THE_DEVICE, O_RDWR|O_CREAT, 777);

    if (fd < 0) {
        ALOGE("Error open file: %s - %s", THE_DEVICE, strerror(errno));
        return errno;
    }

    retval = write(fd, buffer, length);

    close(fd);

    return retval;
}
int sensorhubmgmt__test(int value)
{
    ALOGV("test()for %d", value);
    return value;
}
static int open_sensorhubmgmt(const struct hw_module_t* module, char const* name,
struct hw_device_t** device)
{
    struct sensorhubmgmt_device_t *dev = (sensorhubmgmt_device_t*) malloc(sizeof(struct sensorhubmgmt_device_t));
    memset(dev, 0, sizeof(*dev));
    dev->common.tag = HARDWARE_DEVICE_TAG;
    dev->common.version = HARDWARE_DEVICE_API_VERSION(1,0);
    dev->common.module = (struct hw_module_t*)module;
    dev->read = sensorhubmgmt__read;
    dev->write = sensorhubmgmt__write;
    dev->test = sensorhubmgmt__test;
    *device = (struct hw_device_t*) dev;
    ALOGI("[%s] has been initialized", LOG_TAG);
    return 0;
}
static struct hw_module_methods_t sensorhubmgmt_module_methods = {
    .open = open_sensorhubmgmt
};

struct sensorhubmgmt_module_t HAL_MODULE_INFO_SYM = {                                 
        common: {                                                               
                tag: HARDWARE_MODULE_TAG,                                       
                module_api_version: SENSORHUBMGMT_MODULE_API_VERSION_1_0,                                               
                hal_api_version: HARDWARE_HAL_API_VERSION,                                               
                id: SENSORHUBMGMT_HARDWARE_MODULE_ID,                                 
                name: "Sensor Hub Management Module",                                      
                author: "nayobix.org",                                   
                methods: &sensorhubmgmt_module_methods,                               
                dso: 0,                                                         
                reserved: {},                                                   
        },                                                                      
}; 
