#include <string>
#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <sstream>
#include <future>

#include "camera.h"

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

Napi::FunctionReference Camera::constructor;

Napi::Object Camera::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Camera", {
    InstanceAccessor("uuid", &Camera::get_uuid, nullptr),
    InstanceMethod("is_connected", &Camera::is_connected),
    InstanceMethod("information", &Camera::information),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Camera", func);
  return exports;
}

Camera::Camera(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Camera>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->_system = info[0].As<Napi::External<mavsdk::System>>().Data();
  this->_camera = std::make_shared<mavsdk::NdCamera>(*this->_system);

  this->_camera->select_camera(info[1].As<Napi::Number>().Uint32Value());
}

Napi::Value Camera::get_uuid(const Napi::CallbackInfo& info) {
  uint64_t uuid = this->_system->get_uuid();

  return Napi::String::New(info.Env(), std::to_string(uuid));
}

Napi::Value Camera::is_connected(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->is_connected());
}

Napi::Value Camera::information(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::NdCamera::Information information = this->_camera->get_information();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "vendor_name"), information.vendor_name);
  obj.Set(Napi::String::New(env, "model_name"), information.model_name);
  obj.Set(Napi::String::New(env, "resolution_h"), information.resolution_h);
  obj.Set(Napi::String::New(env, "resolution_v"), information.resolution_v);
  obj.Set(Napi::String::New(env, "angle_of_view"), information.angle_of_view);
  obj.Set(Napi::String::New(env, "spatial_resolution"), information.spatial_resolution);
  obj.Set(Napi::String::New(env, "te"), information.te);
  obj.Set(Napi::String::New(env, "ts"), information.ts);
  obj.Set(Napi::String::New(env, "theta"), information.theta);
  obj.Set(Napi::String::New(env, "overlap_high"), information.overlap_high);
  obj.Set(Napi::String::New(env, "overlap_medium"), information.overlap_medium);
  obj.Set(Napi::String::New(env, "overlap_low"), information.overlap_low);

  return obj;
}
