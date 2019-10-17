#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/ndcamera/ndcamera.h>

class Camera : public Napi::ObjectWrap<Camera> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 Camera(const Napi::CallbackInfo &info);
 static Napi::FunctionReference constructor;

 private:
   mavsdk::System * _system;
   std::shared_ptr<mavsdk::NdCamera> _camera;

   std::string _uuid;
   Napi::Value get_uuid(const Napi::CallbackInfo &info);

   Napi::Value is_connected(const Napi::CallbackInfo &info);
   Napi::Value information(const Napi::CallbackInfo &info);
 };

 #endif
