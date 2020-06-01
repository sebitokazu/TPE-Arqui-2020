#include "include/time.h"
#include "include/libasm.h"


date_tm *getCurrentTime()
{
    date_tm *date = 0;
    int ret = time(date);
    if (ret == -1)
    {
        return 0;
    }
    else
    {
        date->tm[3]--; //corrijo para que Weekday sea 0-6 donde SUN = 0
        return date;
    }
}