#include <iostream>
#include <utility>

#include "info.h"
#include "system.h"

using namespace mavjs;

Napi::FunctionReference Info::constructor;

Napi::Object Info::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Info", {
    InstanceMethod("get_identification", &Info::get_identification),
    InstanceMethod("get_version", &Info::get_version),
    InstanceMethod("get_product", &Info::get_product)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Info", func);
  return exports;
}

Info::Info(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Info>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  
  auto system = info[0].As<Napi::External<mavsdk::System>>().Data();
  this->_info = new mavsdk::Info(*system);
}

Napi::Value Info::get_identification(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  const std::pair<mavsdk::Info::Result, mavsdk::Info::Identification> get_identification_result = this->_info->get_identification();
  
  Napi::Object identification = Napi::Object::New(env);
  Napi::Array hardware_uid = Napi::Array::New(info.Env(), 18);
  for (int i = 0; i < 18; i++) {
      hardware_uid[i] = get_identification_result.second.hardware_uid[i];
  }

  identification.Set(Napi::String::New(env, "hardware_uid"), hardware_uid);
  mavsdk::Info::Result result = get_identification_result.first;

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "result"), mavsdk::Info::result_str(result));
  obj.Set(Napi::String::New(env, "value"), identification);

  return obj;
}

Napi::Value Info::get_version(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  const std::pair<mavsdk::Info::Result, mavsdk::Info::Version> get_version_result = this->_info->get_version();
  
  mavsdk::Info::Result result = get_version_result.first;
  mavsdk::Info::Version _version = get_version_result.second;
  
  Napi::Object version = Napi::Object::New(env);
  version.Set(Napi::String::New(env, "flight_sw_major"), _version.flight_sw_major);
  version.Set(Napi::String::New(env, "flight_sw_minor"), _version.flight_sw_minor);
  version.Set(Napi::String::New(env, "flight_sw_patch"), _version.flight_sw_patch);
  version.Set(Napi::String::New(env, "flight_sw_vendor_major"), _version.flight_sw_vendor_major);
  version.Set(Napi::String::New(env, "flight_sw_vendor_minor"), _version.flight_sw_vendor_minor);
  version.Set(Napi::String::New(env, "flight_sw_vendor_patch"), _version.flight_sw_vendor_patch);
  
  std::string flight_sw_git_hash = _version.flight_sw_git_hash;
  version.Set(Napi::String::New(env, "flight_sw_git_hash"), flight_sw_git_hash);
  
  version.Set(Napi::String::New(env, "os_sw_major"), _version.os_sw_major);
  version.Set(Napi::String::New(env, "os_sw_minor"), _version.os_sw_minor);
  version.Set(Napi::String::New(env, "os_sw_patch"), _version.os_sw_patch);
  
  std::string os_sw_git_hash = _version.os_sw_git_hash;
  version.Set(Napi::String::New(env, "os_sw_git_hash"), os_sw_git_hash);
  
  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "result"), mavsdk::Info::result_str(result));
  obj.Set(Napi::String::New(env, "value"), version);

  return obj;
}

Napi::Value Info::get_product(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  const std::pair<mavsdk::Info::Result, mavsdk::Info::Product> get_product_result = this->_info->get_product();

  mavsdk::Info::Result result = get_product_result.first;
  mavsdk::Info::Product _product = get_product_result.second;
  
  Napi::Object product = Napi::Object::New(env);
  product.Set(Napi::String::New(env, "vendor_id"), _product.vendor_id);

  std::string vendor_name = _product.vendor_name;
  product.Set(Napi::String::New(env, "vendor_name"), vendor_name);

  product.Set(Napi::String::New(env, "product_id"), _product.product_id);

  std::string product_name = _product.product_name;
  product.Set(Napi::String::New(env, "product_name"), product_name);

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "result"), mavsdk::Info::result_str(result));
  obj.Set(Napi::String::New(env, "value"), product);

  return obj;
}

void Info::dispose() {
  delete this->_info;
}