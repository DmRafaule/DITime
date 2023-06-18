#pragma once

#include <chrono>
#include <map>

namespace DI{

enum TimeType{
  IN_SEC,
  IN_MILLI,
  IN_MICRO,
  IN_NANO,
};

struct TimeData{
  std::map<const char*, TimeType> timer_types;
  std::map<const char*, bool> isOneTimers;
  std::map<const char*, float> timers;
  std::map<const char*, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration>> clocks; 
};

namespace TimeHandler{
  // Init TimeData
  void Init();
  // Destroy TimeData
  void Kill();
  // Set new timer
  void Set(const char* name, TimeType type, bool isOneTime = true);
  // UnSet timer
  void UnSet(const char* name);
  // Print out debug message
  void Log(const char* name,const char* time_dur);
  // Get timer pointer(for data access)
  float* Get(const char* name);
  // Clear all data in TimeData
  void Clear();
  // Create a clock
  void Start(const char* name);
  // Delete a clock and calculate diff
  void Stop(const char* name);
}

#define DI_GetTime(func, name, type)\
  DI::TimeHandler::Set(name,type);\
  DI::TimeHandler::Start(name);\
  func;\
  DI::TimeHandler::Stop(name);
}
