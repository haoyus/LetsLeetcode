/**
 * Author: hsun@changanus.com
 */

#pragma once

#include <string>
#include <functional>
#include <deque>
#include "thread_base.h"

/**
 * bitmasking for one publisher - multi subscriber
*/
enum eRepoUpdateFlag
{
    REPO_EMPTY = 0,
    PIN0_UPDATED = 1 << 0,
    PIN1_UPDATED = 1 << 1,
    PIN2_UPDATED = 1 << 2,
    PIN3_UPDATED = 1 << 3,
    PIN4_UPDATED = 1 << 4,
    PIN5_UPDATED = 1 << 5,
    PIN6_UPDATED = 1 << 6,
    PIN7_UPDATED = 1 << 7,
    // add more ...

    PIN_ALL_UPDATED = PIN0_UPDATED + PIN1_UPDATED + PIN2_UPDATED + PIN3_UPDATED 
                    + PIN4_UPDATED + PIN5_UPDATED + PIN6_UPDATED + PIN7_UPDATED
};



/**
 * Single buffer repo
 * Basic repo element that provides buffering, data writing and reading services
 * Currently has 1Pub-1Sub and 1Pub-nSub mode implemented
 * TODO: implement a Write function for data hub mode, i.e. nPub-1Sub and nPub-nSub
*/
template <typename T>
class Repository
{
public:
    Repository() : buf(), updated(false), update_mask(REPO_EMPTY),out_pin_num(0) {}
    ~Repository() {}

public:
    //typedef void (*CbkForWrite)(T &buffer) tCbkForWrite;

protected:
    T buf;
    std::condition_variable cv_updated;
    std::mutex mtx;
    bool updated;
    eRepoUpdateFlag update_mask;
    int out_pin_num;
    std::deque<T> bufQue;
    const size_t bufquesize = 2;

private:
    std::function<void(T &)> mCbkForWrite;
    std::function<void(T &)> mCbkForClear;
    std::function<T(void)> mCbkForPushQue;
    //tCbkForWrite mCbkForWrite;

public:
    void SetCbks(std::function<void(T &)> pW, std::function<void(T &)> pC) { mCbkForWrite = pW;mCbkForClear=pC; };
    void SetCbks(std::function<T(void)> cbk){mCbkForPushQue = cbk;};

    inline void WriteData(const T &indata);
    inline void ClearAndWriteData();
    inline void PushDataQue();

    inline T ReadNextData();
    inline T ReadNextData(const std::string &destname, eRepoUpdateFlag maskpos);
    inline T ReadAvaiData();//for time trigger
    inline T ReadNextDataQue();

    int AddOutPin(){return out_pin_num++;};
};


/**
 * Publish to this repo, all subscribers will be noticed
 */
template <typename T>
void Repository<T>::WriteData(const T &indata)
{
    std::unique_lock<std::mutex> lck(mtx);
    
    //std::cout << "Writing\n";
    buf = indata;
    updated = true;
    update_mask = eRepoUpdateFlag::PIN_ALL_UPDATED;

    cv_updated.notify_all();
}

/**
 * Using cbk funcs to first clear then write buffer
 * NOTICE: caller shall make sure that the callbacks will NOT bring deadlock
*/
template <typename T>
void Repository<T>::ClearAndWriteData()
{
    std::unique_lock<std::mutex> lck(mtx);
    //std::cout << "Writing starts..\n";
    mCbkForClear(buf);
    mCbkForWrite(buf);
    //std::cout << "Writing done!\n";
    updated = true;
    update_mask = eRepoUpdateFlag::PIN_ALL_UPDATED;

    cv_updated.notify_all();
}

/**
 * Using cbk function with return type T, cbk is called in bufQue.push_back()
 * NOTICE: caller shall make sure that the callbacks will NOT bring deadlock
*/
template <typename T>
void Repository<T>::PushDataQue()
{
    std::unique_lock<std::mutex> lck(mtx);
    //std::cout << "Writing starts..\n";
    bufQue.push_back(mCbkForPushQue());
    //std::cout << "Writing done!\n";
    if(bufQue.size()>bufquesize){
        bufQue.pop_front();
    }
    updated = true;
    update_mask = eRepoUpdateFlag::PIN_ALL_UPDATED;

    cv_updated.notify_all();
}

/**
 * Read from this repo. Should be used by time-triggered subscriber
*/
template <typename T>
T Repository<T>::ReadAvaiData()
{
    std::unique_lock<std::mutex> lck(mtx);
    return buf;
}

/**
 * Read from this repo, should be used by event-triggered subscriber, data race between subs
*/
template <typename T>
T Repository<T>::ReadNextData()
{
    std::unique_lock<std::mutex> lck(mtx);
    while (!updated) {
        //already caught up with recent write, need to wait for cv_not_empty
        //std::cout << "Read: waiting...\n";
        cv_updated.wait(lck);
        //std::cout << "Read: noticed!\n";
    }
    updated = false;
    
    return buf;
}

/**
 * read from bufQue
*/
template <typename T>
T Repository<T>::ReadNextDataQue()
{
    std::unique_lock<std::mutex> lck(mtx);
    while (!updated)
    {
        //already caught up with recent write, need to wait for cv_not_empty
        //std::cout << "Read: waiting...\n";
        cv_updated.wait(lck);
        //std::cout << "Read: noticed!\n";
    }
    updated = false;

    return bufQue.back();
}

/**
 * maskpos has to be one of PIN0 to 7
*/
template <typename T>
T Repository<T>::ReadNextData(const std::string &destname, eRepoUpdateFlag maskpos)
{
    std::unique_lock<std::mutex> lck(mtx);
    while (!(maskpos & update_mask)){
        //not updated yet
        std::cout << destname << ": waiting on " << maskpos << " of " << update_mask << "\n";
        cv_updated.wait(lck);
        std::cout << destname << ": noticed on" << maskpos << " of " << update_mask << "\n";
    }
    update_mask = static_cast<eRepoUpdateFlag> (update_mask & (~maskpos) ); //could use ^,diff way but same result in this specific case

    return buf;
}
