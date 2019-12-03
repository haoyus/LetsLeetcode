/* 
 * Author: hsun@changanus.com
 */

#pragma once

#include <string>
#include <functional>
#include <map>
#include <memory>
#include <iostream>

#include "Repository.h"
#include "timer.h"

class Module;
typedef std::shared_ptr<Module> ModulePtr;


/**
 * Defined Module interfaces
*/
class Module : public Timer
{
public:
    Module() : Timer(), name_("unknown") { std::cout << "Module " << name_ << " created.\n"; };
    Module(const char *arg) : Timer(), name_(arg) { std::cout << "Module " << name_ << " created.\n"; };
    Module(const std::string str) : Timer(), name_(str) { std::cout << "Module " << name_ << " created.\n"; };
    virtual ~Module() { std::cout << "Module " << name_ << " destroyed.\n"; };

protected:
    std::string name_;

    ModulePtr prim_pub_;//To obtain data from and get triggered by.

    //TODO: change prim key to enum
    std::map<std::string, ModulePtr> secondary_pubs_;//To obtain data from their repo.

    std::map<std::string, ModulePtr> receivers_; //To send data to their repo, in a N-1 pub-sub pattern. Recommended for 1-1

    tTimeMSec cycleT_;


public:
    void ConnectPrimPub(ModulePtr pm)
    {
        prim_pub_ = pm;
        if(prim_pub_ == nullptr || prim_pub_.use_count()==0)
            throw std::runtime_error("Bad primary connection for "+getName()); 
    };

    void ConnectScndPub(ModulePtr pm) 
    {
        if(pm == nullptr || pm.use_count()==0)
            throw std::runtime_error("Bad secondary connection for "+getName());
        secondary_pubs_[pm->getName()]=pm;
    };

    void ConnectDown(ModulePtr pm)
    {
        if(pm == nullptr || pm.use_count()==0)
            throw std::runtime_error("Bad down connection for "+getName());
        receivers_[pm->getName()] = pm;
    };

    virtual void SetConnections(){};

    virtual void Run() = 0;
    
    std::string getName() const {return name_;};
};