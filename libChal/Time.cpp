/**
 * @file Time.cpp
 * @author Adrian Szczepanski
 * @date 07-06-2022
 * @brief 
 * @details
 */

#include "Hal.hpp"

#ifdef __cplusplus
extern "C" {
#endif

clock_t clock()
{
    auto hal = Chal::GetHal();

    if(hal != nullptr)
        return hal->GetClock();
    else
        return -1;
}

time_t time(time_t* timer)
{
    auto hal = Chal::GetHal();
    
    time_t result = -1;

    if(hal != nullptr)
        result = hal->GetTime();

    if(timer != nullptr)
        *timer = result;

    return result;
}

#ifdef __cplusplus
}
#endif