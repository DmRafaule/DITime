#include "time.hpp"
#include "DIDebuger/debuger.hpp"
#include "DIDebuger/log.hpp"
#include <iostream>
#include <unordered_map>

namespace DI{

TimeData* eg_timeData;

void TimeHandler::Start(const char* name){
  // Because of implementation of stl emplace in map,
  // We will insert only unique pairs
  // So for CoreTime timer starting time point will be the same
  // Changes only gonna happend in end time point
  eg_timeData->clocks.emplace(name, std::chrono::steady_clock::now());
}
void TimeHandler::Stop(const char* name){
  auto res = eg_timeData->clocks.find(name);
  char* time_dur;
  switch(eg_timeData->timer_types.find(name)->second){
    case IN_SEC:{
      // Find differance
      std::chrono::duration<float> dur = std::chrono::steady_clock::now() - res->second;
      // For Log function output
      time_dur = "sec";
      // Set value
      eg_timeData->timers.find(name)->second = dur.count();
      break;
    }
    case IN_MILLI:{
      std::chrono::duration<float,std::milli> dur = std::chrono::steady_clock::now() - res->second;
      time_dur = "millisec";
      eg_timeData->timers.find(name)->second = dur.count();
      break;
    }
    case IN_MICRO:{
      std::chrono::duration<float,std::micro> dur = std::chrono::steady_clock::now() - res->second;
      time_dur = "microsec";
      eg_timeData->timers.find(name)->second = dur.count();
      break;
    }
    case IN_NANO:{
      std::chrono::duration<float,std::nano> dur = std::chrono::steady_clock::now() - res->second;
      time_dur = "nanosec";
      eg_timeData->timers.find(name)->second = dur.count();
      break;
    }
  }
  // If it is timer for check speed of some code place execution
  // it will be destroid
  if (eg_timeData->isOneTimers.find(name)->second){
    Log(name,time_dur);
    UnSet(name);
  }
}
void TimeHandler::Log(const char* name, const char* time_dur){
  DI_LOG_INFO("TimerHandler say: {0} : {1} {2}",name,eg_timeData->timers.find(name)->second,time_dur);
}
float* TimeHandler::Get(const char* name){
  return &eg_timeData->timers.find(name)->second; 
}

void TimeHandler::Init(){
  DI_LOG_TRACE("TimeHandler say: Init Time");
  eg_timeData = new TimeData();
  // Set default global engine timer
  Set("CoreTime",IN_SEC,false);
}
void TimeHandler::Kill(){
  DI_LOG_TRACE("TimeHandler say: Kill Time");
  Clear();
  delete eg_timeData;
}
void TimeHandler::Set(const char* name, TimeType type, bool isOneTime){
  // Set everything exept clock wich have to be temporary created objects
  // when mesure a time 
  eg_timeData->timers.emplace(name,0);
  eg_timeData->timer_types.emplace(name,type);
  eg_timeData->isOneTimers.emplace(name,isOneTime);
}
void TimeHandler::UnSet(const char* name){
  eg_timeData->isOneTimers.erase(name);
  eg_timeData->timers.erase(name);
  eg_timeData->clocks.erase(name);
  eg_timeData->timer_types.erase(name);
}
void TimeHandler::Clear(){
  eg_timeData->isOneTimers.clear();
  eg_timeData->timers.clear();
  eg_timeData->clocks.clear();
  eg_timeData->timer_types.clear();
}

}
