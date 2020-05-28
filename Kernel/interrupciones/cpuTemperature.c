#include <cpuTemp.h>
#include <naiveConsole.h>

const uint64_t* IA32_THERM_STATUS_MSR = 0x019B;

unsigned int getCPUTemperature(){
    uint32_t status_reg = *IA32_THERM_STATUS_MSR >> 32;
    int degrees = 0;
    if (status_reg >> 31 == 1)
    {
        degrees = status_reg >> 16;
        degrees = degrees & 0b0000000001111111;
    }
    return degrees;
}