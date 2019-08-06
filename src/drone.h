#ifndef DRONE_H
#define DRONE_H

#include <string>

#include <napi.h>
#include <mavsdk/mavsdk.h>

using namespace mavsdk;

class Drone : public Napi::ObjectWrap<Drone> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 Drone(const Napi::CallbackInfo &info);
 static Napi::FunctionReference constructor;

 private:
   System * _system;

   std::string _uuid;
   Napi::Value get_uuid(const Napi::CallbackInfo &info);

   Napi::Value is_connected(const Napi::CallbackInfo &info);

   Napi::Value has_autopilot(const Napi::CallbackInfo &info);

   Napi::Value has_camera(const Napi::CallbackInfo &info);

   Napi::Value has_gimbal(const Napi::CallbackInfo &info);

};

#endif
