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

 //private:

};

#endif
