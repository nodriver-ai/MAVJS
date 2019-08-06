#include <string>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <thread>
#include <typeinfo>
#include <sstream>

#include "drone.h"
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

using namespace mavsdk;
using namespace std::chrono;
using namespace std::this_thread;

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

Napi::FunctionReference Drone::constructor;

Napi::Object Drone::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Drone", {
    InstanceAccessor("uuid", &Drone::get_uuid, nullptr),
    InstanceMethod("is_connected", &Drone::is_connected),
    InstanceMethod("has_autopilot", &Drone::has_autopilot),
    InstanceMethod("has_camera", &Drone::has_camera),
    InstanceMethod("has_gimbal", &Drone::has_gimbal)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Drone", func);
  return exports;
}


Drone::Drone(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Drone>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->_system = info[0].As<Napi::External<mavsdk::System>>().Data();
}

Napi::Value Drone::get_uuid(const Napi::CallbackInfo& info) {
  uint64_t uuid = this->_system->get_uuid();

  return Napi::String::New(info.Env(), std::to_string(uuid));
}

Napi::Value Drone::is_connected(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->is_connected());
}

Napi::Value Drone::has_autopilot(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_autopilot());
}

Napi::Value Drone::has_camera(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_camera());
}

Napi::Value Drone::has_gimbal(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_gimbal());
}
