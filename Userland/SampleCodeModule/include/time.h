#ifndef _TIME_H_
#define _TIME_H_

enum weekday{SUN,MON,TUE,WED,THU,FRI,SAT};

//const char* weekday[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

typedef struct date_tm
{
    unsigned int tm[7];
} date_tm;

date_tm *getCurrentTime();

#endif