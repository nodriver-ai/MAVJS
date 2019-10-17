#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <sstream>
#include <algorithm>

#include "mavsdk.h"
#include "drone.h"
#include "camera.h"
#include <mavsdk/mavsdk.h>

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

Napi::Value ThrowErrorMessage(Napi::Env env, std::string msg)
{
  Napi::TypeError::New(env, msg).ThrowAsJavaScriptException();
  return env.Null();
}

Napi::FunctionReference MavSDK::constructor;

Napi::Object MavSDK::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "MavSDK", {
    InstanceAccessor("connection_url", &MavSDK::get_connection_url, nullptr),
    InstanceMethod("is_connected", &MavSDK::is_connected),
    InstanceMethod("discover_drones", &MavSDK::discover_drones),
    InstanceMethod("discover_cameras", &MavSDK::discover_cameras),
    InstanceMethod("connect_to_drone", &MavSDK::connect_to_drone),
    InstanceMethod("connect_to_camera", &MavSDK::connect_to_camera)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("MavSDK", func);
  return exports;
}

MavSDK::MavSDK(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MavSDK>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  mavsdk::ConnectionResult connection_result;

  std::string connection_url = info[0].As<Napi::String>().Utf8Value();
  connection_result = this->_dc.add_any_connection(connection_url);

  if (connection_result != mavsdk::ConnectionResult::SUCCESS) {
    std::string msg = connection_result_str(connection_result);
    throw Napi::Error::New(env, "Connection failed: " + msg);
  }

  this->_connection_url = connection_url;

  auto _on_discover = [this](uint64_t uuid) -> void {
    if (uuid >= 200 && uuid <= 205) {
      this->uuid_cameras_mutex.lock();
      if (std::find(this->uuid_cameras.begin(), this->uuid_cameras.end(), uuid) == this->uuid_cameras.end()) {
        this->uuid_cameras.push_back(uuid);
      }
      this->uuid_cameras_mutex.unlock();
    }
    else {
      this->uuid_drones_mutex.lock();
      if (std::find(this->uuid_drones.begin(), this->uuid_drones.end(), uuid) == this->uuid_drones.end()) {
        this->uuid_drones.push_back(uuid);
      }
      this->uuid_drones_mutex.unlock();
    }
  };

  this->_dc.register_on_discover(_on_discover);

  auto _on_timeout = [this](uint64_t uuid) -> void {
    if (uuid >= 200 && uuid <= 205) {
      this->uuid_cameras_mutex.lock();
      if (std::find(this->uuid_cameras.begin(), this->uuid_cameras.end(), uuid) != this->uuid_cameras.end()) {
        this->uuid_cameras.erase(std::remove(this->uuid_cameras.begin(), this->uuid_cameras.end(), uuid), this->uuid_cameras.end());
      }
      this->uuid_cameras_mutex.unlock();
    }
    else {
      this->uuid_drones_mutex.lock();
      if (std::find(this->uuid_drones.begin(), this->uuid_drones.end(), uuid) != this->uuid_drones.end()) {
        this->uuid_drones.erase(std::remove(this->uuid_drones.begin(), this->uuid_drones.end(), uuid), this->uuid_drones.end());
      }
      this->uuid_drones_mutex.unlock();
    }
  };

  this->_dc.register_on_timeout(_on_timeout);
}

Napi::Value MavSDK::get_connection_url(const Napi::CallbackInfo& info) {
  std::string connection_url = this->_connection_url;

  return Napi::String::New(info.Env(), connection_url);
}


Napi::Value MavSDK::is_connected(const Napi::CallbackInfo& info) {
  bool isConnected;
  std:: string uuid = info[0].As<Napi::String>().Utf8Value();
  uint64_t value;
  std::istringstream iss(uuid);
  iss >> value;
  isConnected = this->_dc.is_connected(value);

  return Napi::Boolean::New(info.Env(), isConnected);
}

Napi::Value MavSDK::discover_drones(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->uuid_drones_mutex.lock();
  Napi::Array arr = Napi::Array::New(info.Env(), this->uuid_drones.size());
  for (int i = 0; i < this->uuid_drones.size(); i++) {
    arr[i] = std::to_string(this->uuid_drones.at(i));
	}
  this->uuid_drones_mutex.unlock();

  return arr;
}

Napi::Value MavSDK::discover_cameras(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->uuid_cameras_mutex.lock();
  Napi::Array arr = Napi::Array::New(info.Env(), this->uuid_cameras.size());
  for (int i = 0; i < this->uuid_cameras.size(); i++) {
    arr[i] = std::to_string(this->uuid_cameras.at(i));
	}
  this->uuid_cameras_mutex.unlock();

  return arr;
}

Napi::Value MavSDK::connect_to_drone(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std:: string uuid = info[0].As<Napi::String>().Utf8Value();
  uint64_t value;
  std::istringstream iss(uuid);
  iss >> value;

  if (!this->_dc.is_connected(value)) {
    return env.Undefined();
  }

  auto sys = Napi::External<mavsdk::System>::New(env, &this->_dc.system(value));
  auto drone = Drone::constructor.New({ sys });
  return drone;
}

Napi::Value MavSDK::connect_to_camera(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std:: string uuid = info[0].As<Napi::String>().Utf8Value();
  uint64_t value;
  std::istringstream iss(uuid);
  iss >> value;

  if (!this->_dc.is_connected(value)) {
    return env.Undefined();
  }

  auto id = Napi::Number::New(env, value - 200);
  auto sys = Napi::External<mavsdk::System>::New(env, &this->_dc.system(value));

  auto camera = Camera::constructor.New({ sys, id });
  return camera;
}
