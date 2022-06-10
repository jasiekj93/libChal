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

char * Chal::asctime(const struct tm *time)
{
    return ::asctime(time);
}

char * Chal::ctime(const time_t *time)
{
    return ::ctime(time);
}

struct tm * Chal::gmtime(const time_t *time)
{
    return ::gmtime(time);
}

struct tm * Chal::localtime(const time_t *time)
{
    return ::localtime(time);
}

size_t Chal::strftime(char *buffer, size_t max, const char *format, const struct tm *time)
{
    return ::strftime(buffer, max, format, time);
}










