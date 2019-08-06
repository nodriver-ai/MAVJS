#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdint>
#include <sstream>
#include <algorithm>

#include "ndbox.h"
#include "drone.h"
#include <mavsdk/mavsdk.h>

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

Napi::FunctionReference Ndbox::constructor;

Napi::Object Ndbox::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Ndbox", {
    InstanceAccessor("connection_url", &Ndbox::get_connection_url, nullptr),
    InstanceMethod("is_connected", &Ndbox::is_connected),
    InstanceMethod("discover_uuids", &Ndbox::discover_uuids),
    InstanceMethod("connect_to_drone", &Ndbox::connect_to_drone),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Ndbox", func);
  return exports;
}

Ndbox::Ndbox(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Ndbox>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  ConnectionResult connection_result;

  std::string connection_url = info[0].As<Napi::String>().Utf8Value();
  connection_result = this->_dc.add_any_connection(connection_url);

  if (connection_result != ConnectionResult::SUCCESS) {
    std::string msg = connection_result_str(connection_result);
    throw Napi::Error::New(env, "Connection failed: " + msg);
  }

  this->_connection_url = connection_url;

  auto _on_discover = [this](uint64_t uuid) -> void {
    this->uuids_mutex.lock();
    if (std::find(this->uuids.begin(), this->uuids.end(), uuid) == this->uuids.end()) {
      this->uuids.push_back(uuid);
    }
    this->uuids_mutex.unlock();
  };

  this->_dc.register_on_discover(_on_discover);

  auto _on_timeout = [this](uint64_t uuid) -> void {
    this->uuids_mutex.lock();
    if (std::find(this->uuids.begin(), this->uuids.end(), uuid) != this->uuids.end()) {
      this->uuids.erase(std::remove(this->uuids.begin(), this->uuids.end(), uuid), this->uuids.end());
    }
    this->uuids_mutex.unlock();
  };

  this->_dc.register_on_timeout(_on_timeout);

}

Napi::Value Ndbox::get_connection_url(const Napi::CallbackInfo& info) {
  std::string connection_url = this->_connection_url;

  return Napi::String::New(info.Env(), connection_url);
}


Napi::Value Ndbox::is_connected(const Napi::CallbackInfo& info) {
  bool isConnected;
  std:: string uuid = info[0].As<Napi::String>().Utf8Value();
  uint64_t value;
  std::istringstream iss(uuid);
  iss >> value;
  isConnected = this->_dc.is_connected(value);

  return Napi::Boolean::New(info.Env(), isConnected);
}

Napi::Value Ndbox::discover_uuids(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->uuids_mutex.lock();
  Napi::Array arr = Napi::Array::New(info.Env(), this->uuids.size());
  for (int i = 0; i < this->uuids.size(); i++) {
    arr[i] = std::to_string(this->uuids.at(i));
	}
  this->uuids_mutex.unlock();

  return arr;
}

Napi::Value Ndbox::connect_to_drone(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std:: string uuid = info[0].As<Napi::String>().Utf8Value();
  uint64_t value;
  std::istringstream iss(uuid);
  iss >> value;
  auto sys = Napi::External<mavsdk::System>::New(env, &this->_dc.system(value));
  auto drone = Drone::constructor.New({ sys });

  return drone;
}
