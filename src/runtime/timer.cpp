/* 
 * Author: haoyu
 */

#include "timer.h"

bool Timer::global_initialized = false;
tTimeUsec Timer::global_init_time = 0;

void Timer::globalInit(tTimeUsec initT)
{
    if (!Timer::global_initialized)
    {
        std::cout<<"Global Time Service Init with "<<initT<<"usec!\n";
        Timer::global_initialized = true;
        Timer::global_init_time = initT;
    }
}