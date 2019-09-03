#include <string>
#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <sstream>

#include "missionPlan.h"

Napi::FunctionReference MissionPlan::constructor;

Napi::Object MissionPlan::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "MissionPlan", {
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("MissionPlan", func);
  return exports;
}


MissionPlan::MissionPlan(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MissionPlan>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
}
