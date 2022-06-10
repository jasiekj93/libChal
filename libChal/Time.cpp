/**
 * @file Time.cpp
 * @author Adrian Szczepanski
 * @date 07-06-2022
 * @brief 
 * @details
 */

#include "Hal.hpp"
#include "Time.hpp"

clock_t Chal::clock()
{
    auto hal = Chal::GetHal();

    if(hal != nullptr)
        return hal->GetClock();
    else
        return -1;
}

time_t Chal::time(time_t* timer)
{
    auto hal = Chal::GetHal();
    
    time_t result = -1;

    if(hal != nullptr)
        result = hal->GetTime();

    if(timer != nullptr)
        *timer = result;

    return result;
}

double Chal::difftime (time_t end, time_t beginning)
{
    return ::difftime(end, beginning);
}

time_t Chal::mktime(struct tm *time)
{
    return ::mktime(time);
}

char * asctime(const struct tm *);
char * ctime(const time_t *);
struct tm * gmtime(const time_t *);
struct tm * localtime(const time_t *);
size_t strftime(char *, size_t, const char *, const struct tm *);










