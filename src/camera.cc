#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "camera.h"
#include "json.h"

// for convenience
using json = nlohmann::json;

Napi::FunctionReference Camera::constructor;

Napi::Object Camera::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Camera", {
    InstanceAccessor("name", &Camera::GetName, nullptr),
    InstanceAccessor("resolution", &Camera::GetResolution, &Camera::SetResolution),
    InstanceAccessor("angleOfView", &Camera::GetAngleOfView, &Camera::SetAngleOfView),
    InstanceAccessor("imageResolution", &Camera::GetImageResolution, &Camera::SetImageResolution),
    InstanceAccessor("ts", &Camera::GetTS, &Camera::SetTS),
    InstanceAccessor("te", &Camera::GetTE, &Camera::SetTE),
    InstanceAccessor("overlap", &Camera::GetOverlap, &Camera::SetOverlap),
    InstanceAccessor("theta", &Camera::GetTheta, &Camera::SetTheta),
    InstanceAccessor("aspectRatio", &Camera::GetAspectRatio, nullptr),
    StaticMethod("fromJson", &Camera::FromJson),
    InstanceMethod("save", &Camera::Save)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Camera", func);
  return exports;
}

Camera::Camera(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Camera>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::String name = info[0].As<Napi::String>();
  this->_name = name.Utf8Value();

  Napi::Number resolution = info[1].As<Napi::Number>();
  this->_resolution = resolution.DoubleValue();

  Napi::Number angleOfView = info[2].As<Napi::Number>();
  this->_angleOfView = angleOfView.DoubleValue();

  Napi::Object imageResolution = info[3].As<Napi::Object>();
  this->_imageResolution.x = imageResolution.Get("x").ToNumber().DoubleValue();
  this->_imageResolution.y = imageResolution.Get("y").ToNumber().DoubleValue();

  Napi::Number ts = info[4].As<Napi::Number>();
  this->_ts = ts.DoubleValue();

  Napi::Number te = info[5].As<Napi::Number>();
  this->_te = te.DoubleValue();

  Napi::Object overlap = info[6].As<Napi::Object>();
  this->_overlap.x = overlap.Get("x").ToNumber().DoubleValue();
  this->_overlap.y = overlap.Get("y").ToNumber().DoubleValue();

  Napi::Number theta = info[7].As<Napi::Number>();
  this->_theta = theta.DoubleValue();

  this->_aspectRatio = this->_imageResolution.x / this->_imageResolution.y;

}

Napi::Value Camera::GetName(const Napi::CallbackInfo& info) {
  std::string name = this->_name;

  return Napi::String::New(info.Env(), name);
}

Napi::Value Camera::GetResolution(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_resolution);
}

void Camera::SetResolution(const Napi::CallbackInfo &info, const Napi::Value &resolution) {
    Napi::Number arg = resolution.As<Napi::Number>();
    this->_resolution = arg.DoubleValue();
}

Napi::Value Camera::GetAngleOfView(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_angleOfView);
}

void Camera::SetAngleOfView(const Napi::CallbackInfo &info, const Napi::Value &aov) {
    Napi::Number arg = aov.As<Napi::Number>();
    this->_angleOfView = arg.DoubleValue();
}

Napi::Value Camera::GetImageResolution(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "x"), this->_imageResolution.x);
    obj.Set(Napi::String::New(env, "y"), this->_imageResolution.y);
    return obj;
}

void Camera::SetImageResolution(const Napi::CallbackInfo &info, const Napi::Value &ixy) {
    Napi::Object obj = ixy.As<Napi::Object>();
    this->_imageResolution.x = obj.Get("x").ToNumber().DoubleValue();
    this->_imageResolution.y = obj.Get("y").ToNumber().DoubleValue();
}

Napi::Value Camera::GetTS(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_ts);
}

void Camera::SetTS(const Napi::CallbackInfo &info, const Napi::Value &ts) {
    Napi::Number arg = ts.As<Napi::Number>();
    this->_ts = arg.DoubleValue();
}

Napi::Value Camera::GetTE(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_te);
}

void Camera::SetTE(const Napi::CallbackInfo &info, const Napi::Value &te) {
    Napi::Number arg = te.As<Napi::Number>();
    this->_te = arg.DoubleValue();
}

Napi::Value Camera::GetOverlap(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(Napi::String::New(env, "x"), this->_overlap.x);
    obj.Set(Napi::String::New(env, "y"), this->_overlap.y);
    return obj;
}

void Camera::SetOverlap(const Napi::CallbackInfo &info, const Napi::Value &ovxy) {
    Napi::Object obj = ovxy.As<Napi::Object>();
    this->_overlap.x = obj.Get("x").ToNumber().DoubleValue();
    this->_overlap.y = obj.Get("y").ToNumber().DoubleValue();
}

Napi::Value Camera::GetTheta(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Number::New(env, this->_theta);
}

void Camera::SetTheta(const Napi::CallbackInfo &info, const Napi::Value &theta) {
    Napi::Number arg = theta.As<Napi::Number>();
    this->_theta = arg.DoubleValue();
}


Napi::Value Camera::GetAspectRatio(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();
  return Napi::Number::New(env, this->_aspectRatio);
}

Napi::Value Camera::FromJson(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString()) {
    throw Napi::TypeError::New(env, "Camera.fromJson static method require one argument(`json file path`) as `String`");
  }

  Napi::String json_path = info[0].As<Napi::String>();

  std::ifstream i(json_path.Utf8Value());
  json j;
  i >> j;

  Napi::String name = Napi::String::New(info.Env(), j["name"].get<std::string>());
  Napi::Number resolution = Napi::Number::New(info.Env(), j["resolution"].get<double>());
  Napi::Number angleOfView = Napi::Number::New(info.Env(), j["angleOfView"].get<double>());

  Napi::Object imageResolution = Napi::Object::New(env);
  imageResolution.Set(Napi::String::New(env, "x"), j["imageResolution"]["x"].get<double>());
  imageResolution.Set(Napi::String::New(env, "y"), j["imageResolution"]["y"].get<double>());

  Napi::Number ts = Napi::Number::New(info.Env(), j["ts"].get<double>());
  Napi::Number te = Napi::Number::New(info.Env(), j["te"].get<double>());

  Napi::Object overlap = Napi::Object::New(env);
  overlap.Set(Napi::String::New(env, "x"), j["overlap"]["x"].get<double>());
  overlap.Set(Napi::String::New(env, "y"), j["overlap"]["y"].get<double>());

  Napi::Number theta = Napi::Number::New(info.Env(), j["theta"].get<double>());

  Napi::Object obj = constructor.New({ name, resolution, angleOfView, imageResolution, ts, te, overlap, theta });

  return obj;
}

void Camera::Save(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString()) {
    throw Napi::TypeError::New(env, "Camera save method require one argument(`json file path`) as `String`");
  }

  json j;

  j["name"] = this->_name;
  j["resolution"] = this->_resolution;
  j["angleOfView"] = this->_angleOfView;
  j["imageResolution"] = { {"x", this->_imageResolution.x}, {"y", this->_imageResolution.y} };
  j["ts"] = this->_ts;
  j["te"] = this->_te;
  j["overlap"] = { {"x", this->_overlap.x}, {"y", this->_overlap.y} };
  j["theta"] = this->_theta;

  Napi::String json_path = info[0].As<Napi::String>();
  std::ofstream o(json_path);
  o << std::setw(4) << j << std::endl;
}
