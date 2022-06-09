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

clock_t clock (void)
{
    return Chal::GetHal()->GetClock();
}

time_t time (time_t* timer)
{
    return Chal::GetHal()->GetTime();
}

#ifdef __cplusplus
}
#endif