#pragma once

#include <chrono>
#include <ctime>
#include <sys/time.h>
#include <iostream>


typedef long long tTimeUsec;
typedef long tTimeMSec;
typedef double tTimeSec;

/**
 * RAII way for time profiling
 */
struct SimpleTimer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> startPoint,endPoint;
    std::chrono::duration<double> elapsed;

    SimpleTimer() {startPoint = std::chrono::high_resolution_clock::now();}

    ~SimpleTimer()
    {
        endPoint = std::chrono::high_resolution_clock::now();
        elapsed = endPoint-startPoint;
        //auto dur = endPoint-startPoint;
        //long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();
        double ms = elapsed.count()*1000.0f;
        //double ms_dur = double(microseconds)/1000.0f;
        std::cout<<ms<<"ms\n";
    } 
};