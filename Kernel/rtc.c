#include <RTC.h>

extern int cpuHours();
extern int cpuMins();
extern int cpuSecs();

int getRTCHours(){
    int hoursBCD = cpuHours();
    return bcdToDec(hoursBCD);
}

int getRTCMinutes(){
    int minBCD = cpuMins();
    return bcdToDec(minBCD);
}

int getRTCSeconds(){
    int minBCD = cpuSecs();
    return bcdToDec(minBCD);
}


int bcdToDec(int bcd){
    return  ((bcd & 0xF0) >> 4)*10 + (bcd & 0x0F);
}