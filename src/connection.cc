#include <string>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <thread>
#include <typeinfo>
#include <sstream>

#include "connection.h"
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

using namespace mavsdk;
using namespace std::chrono;
using namespace std::this_thread;

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

Napi::FunctionReference Connection::constructor;

Napi::Object Connection::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Connection", {
    InstanceAccessor("address", &Connection::GetAddress, nullptr),
    InstanceMethod("isConnected", &Connection::IsConnected),
    InstanceMethod("getUUIDs", &Connection::GetUUIDs)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Connection", func);
  return exports;
}

void component_discovered(ComponentType component_type)
{
    std::cout << NORMAL_CONSOLE_TEXT << "Discovered a component with type "
              << unsigned(component_type) << std::endl;
}

Connection::Connection(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Connection>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  ConnectionResult connection_result;

  std::string connection_url = info[0].As<Napi::String>().Utf8Value();
  connection_result = this->_dc.add_any_connection(connection_url);

  if (connection_result != ConnectionResult::SUCCESS) {
    std::string msg = connection_result_str(connection_result);
    throw Napi::Error::New(env, "Connection failed: " + msg);
  }

  this->_address = connection_url;

}

Napi::Value Connection::GetAddress(const Napi::CallbackInfo& info) {
  std::string address = this->_address;

  return Napi::String::New(info.Env(), address);
}


Napi::Value Connection::IsConnected(const Napi::CallbackInfo& info) {
  bool isConnected;
  if (info.Length() > 0 && info[0].IsNumber()) {
    std:: string uuid = info[0].As<Napi::String>().Utf8Value();
    uint64_t value;
    std::istringstream iss("uuid");
    iss >> value;
    std::cout << "isConn " << value << '\n';
    isConnected = this->_dc.is_connected(value);
  } else {
    isConnected = this->_dc.is_connected();
  }

  return Napi::Boolean::New(info.Env(), isConnected);
}

void Connection::GetUUIDs(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function cb = info[0].As<Napi::Function>();
  // We usually receive heartbeats at 1Hz, therefore we should find a system after around 2
  // seconds.
  sleep_for(seconds(2));

  std::vector<uint64_t> uuids = this->_dc.system_uuids();

  Napi::Array arr = Napi::Array::New(info.Env(), uuids.size());
  for (int i = 0; i < uuids.size(); i++) {
    arr[i] = std::to_string(uuids.at(i));
	}

  cb.Call(env.Global(), { arr });
}
