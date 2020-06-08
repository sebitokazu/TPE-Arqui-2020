#include "include/time.h"
#include "include/libasm.h"

const char *weekdayShort[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

/*
    date[0]->seg
    date[1]->min
    date[2]->hor
    date[3]->dia de la semana
    date[4]->dia del mes
    date[5]->mes
    date[6]->año
*/

static int date[7];

int *getCurrentTime()
{
    int ret = time(date);
    if (ret == -1)
    {
        return 0;
    }
    else
    {
        if(date[2]==0)
            date[0] = 24;
        return date;
    }
}

char* getDay(int i){
    return weekdayShort[i-1];
}