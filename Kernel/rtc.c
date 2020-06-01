#include <RTC.h>

extern int cpuHours();
extern int cpuMins();
extern int cpuSecs();
extern int cpuWeekday();
extern int cpuDay();
extern int cpuMonth();
extern int cpuYear();

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

int getRTCWeekday(){
    return cpuWeekday();
}

int getRTCDay(){
    return cpuDay();
}

int getRTCMonth(){
    return cpuMonth();
}

int getRTCYear(){
    int yearBCD = cpuYear();
    return bcdToDec(yearBCD);
}

int bcdToDec(int bcd){
    return  ((bcd & 0xF0) >> 4)*10 + (bcd & 0x0F);
}