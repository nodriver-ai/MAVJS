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

  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Drone", func);
  return exports;
}


Drone::Drone(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Drone>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

}
