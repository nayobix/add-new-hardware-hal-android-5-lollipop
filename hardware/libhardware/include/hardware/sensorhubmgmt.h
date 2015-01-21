#ifndef ANDROID_SENSORHUBMGMT_INTERFACE_H
#define ANDROID_SENSORHUBMGMT_INTERFACE_H

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <hardware/hardware.h>

__BEGIN_DECLS

#define SENSORHUBMGMT_MODULE_API_VERSION_1_0 HARDWARE_MODULE_API_VERSION(1, 0)
#define SENSORHUBMGMT_HARDWARE_MODULE_ID "sensorhubmgmt"


struct sensorhubmgmt_device_t {

    struct hw_device_t common;

    int (*read)(char* buffer, int length);
    int (*write)(char* buffer, int length);
    int (*test)(int value);

};

/**                                                                             
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM   
 * and the fields of this data structure must begin with hw_module_t            
 * followed by module specific information.                                     
 */                                                                             
struct sensorhubmgmt_module_t {                                                       
    struct hw_module_t common;                                                  
};

__END_DECLS

#endif // ANDROID_SENSORHUBMGMT_INTERFACE_H
