#pragma once

#include <iostream>
#include "time_base.h"

/**
 * Provide time service for Modules
 * short time period use only - no overnight
 */
class Timer
{
public:
    Timer()
    {
        gettimeofday(&timebuf_, NULL);
        birthtime_ = 1000000 * static_cast<tTimeUsec>(timebuf_.tv_sec) + static_cast<tTimeUsec>(timebuf_.tv_usec);
        globalInit(this->birthtime_);
    }
    
    virtual ~Timer() {}

public:
    tTimeUsec getTimeOfDayUsec()
    {
        gettimeofday(&timebuf_, NULL);
        return (1000000 * static_cast<tTimeUsec>(timebuf_.tv_sec) + static_cast<tTimeUsec>(timebuf_.tv_usec));
    }

    tTimeSec getTimeOfDaySec()
    {
        gettimeofday(&timebuf_, NULL);
        return (static_cast<tTimeSec>(timebuf_.tv_sec) + static_cast<tTimeSec>(timebuf_.tv_usec) / 1000000.0);
    }

    tTimeUsec getBirthTime() { return birthtime_; }

    tTimeUsec getRelativeTimeUsec()
    {
        gettimeofday(&timebuf_, NULL);
        return (1000000 * static_cast<tTimeUsec>(timebuf_.tv_sec) + static_cast<tTimeUsec>(timebuf_.tv_usec) - global_init_time);
    }

    tTimeSec getRelativeTimeSec()
    {
        gettimeofday(&timebuf_, NULL);
        return (static_cast<tTimeSec>(timebuf_.tv_sec) + static_cast<tTimeSec>(timebuf_.tv_usec)/1000000.0 - static_cast<tTimeSec>(global_init_time)/1000000.0);
    }

    void reset()
    {
        gettimeofday(&timebuf_, NULL);
        birthtime_ = 1000000 * timebuf_.tv_sec + timebuf_.tv_usec;
    }

private:
    void globalInit(tTimeUsec initT);

protected:
    timeval timebuf_;
    tTimeUsec birthtime_;
//public:
    static bool global_initialized;
    static tTimeUsec global_init_time;
};

/******************************************************************************************************/

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
