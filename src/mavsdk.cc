#include <sstream>
#include <iostream>
#include <thread>

#include "mavsdk.h"
#include "system.h"

using namespace mavjs;

Napi::FunctionReference Mavsdk::constructor;

Napi::Object Mavsdk::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Mavsdk", {
    InstanceMethod("version", &Mavsdk::version),
    InstanceMethod("add_any_connection", &Mavsdk::add_any_connection),
    InstanceMethod("add_udp_connection", &Mavsdk::add_udp_connection),
    InstanceMethod("setup_udp_remote", &Mavsdk::setup_udp_remote),
    InstanceMethod("add_tcp_connection", &Mavsdk::add_tcp_connection),
    InstanceMethod("add_serial_connection", &Mavsdk::add_serial_connection),
    InstanceMethod("set_configuration", &Mavsdk::set_configuration),
    InstanceMethod("system_uuids", &Mavsdk::system_uuids),
    InstanceMethod("system", &Mavsdk::system),
    InstanceMethod("is_connected", &Mavsdk::is_connected),
    InstanceMethod("register_on_discover", &Mavsdk::register_on_discover),
    InstanceMethod("unregister_on_discover", &Mavsdk::unregister_on_discover),
    InstanceMethod("register_on_timeout", &Mavsdk::register_on_timeout),
    InstanceMethod("unregister_on_timeout", &Mavsdk::unregister_on_timeout)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Mavsdk", func);
  return exports;
}

Mavsdk::Mavsdk(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Mavsdk>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
}

Napi::Value Mavsdk::version(const Napi::CallbackInfo& info) {
  return Napi::String::New(info.Env(), this->_dc.version());
}

Napi::Value Mavsdk::add_any_connection(const Napi::CallbackInfo& info) {
  mavsdk::ConnectionResult result = this->_dc.add_any_connection(info[0].As<Napi::String>().Utf8Value());
  return Napi::String::New(info.Env(), mavsdk::connection_result_str(result));
}

Napi::Value Mavsdk::add_udp_connection(const Napi::CallbackInfo& info) {
  mavsdk::ConnectionResult result;
  if (info.Length() > 0) {
    if (info.Length() < 2) {
      if (info[0].IsString()) {
        result = this->_dc.add_udp_connection(info[0].As<Napi::String>().Utf8Value());
      } 
      else {
        result = this->_dc.add_udp_connection(info[0].As<Napi::Number>().DoubleValue());
      }
    }
    else {
      result = this->_dc.add_udp_connection(info[0].As<Napi::String>().Utf8Value(), info[1].As<Napi::Number>().DoubleValue());
    }
  }
  else {
    result = this->_dc.add_udp_connection();
  }

  return Napi::String::New(info.Env(), mavsdk::connection_result_str(result));
}

Napi::Value Mavsdk::setup_udp_remote(const Napi::CallbackInfo& info) {
  mavsdk::ConnectionResult result = this->_dc.add_udp_connection(info[0].As<Napi::String>().Utf8Value(), info[1].As<Napi::Number>().DoubleValue());
  return Napi::String::New(info.Env(), mavsdk::connection_result_str(result));
}

Napi::Value Mavsdk::add_tcp_connection(const Napi::CallbackInfo& info) {
  mavsdk::ConnectionResult result;
  if (info.Length() < 2) {
      result = this->_dc.add_tcp_connection(info[0].As<Napi::String>().Utf8Value());
  }
  else {
    result = this->_dc.add_tcp_connection(info[0].As<Napi::String>().Utf8Value(), info[1].As<Napi::Number>().DoubleValue());
  }
  
  return Napi::String::New(info.Env(), mavsdk::connection_result_str(result));
}

Napi::Value Mavsdk::add_serial_connection(const Napi::CallbackInfo& info) {
  mavsdk::ConnectionResult result;
  if (info.Length() < 2) {
      result = this->_dc.add_serial_connection(info[0].As<Napi::String>().Utf8Value());
  }
  else {
    result = this->_dc.add_serial_connection(info[0].As<Napi::String>().Utf8Value(), info[1].As<Napi::Number>().DoubleValue());
  }
  
  return Napi::String::New(info.Env(), mavsdk::connection_result_str(result));
}

void Mavsdk::set_configuration(const Napi::CallbackInfo& info) {
  int index = info[0].As<Napi::Number>().Int32Value();
  this->_dc.set_configuration(this->configuration[index]);
}

Napi::Value Mavsdk::system_uuids(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  std::vector<uint64_t> system_uuids = this->_dc.system_uuids();

  Napi::Array uuids = Napi::Array::New(env);
  for(uint i = 0; i < system_uuids.size(); ++i) {
    uuids.Set(i, Napi::String::New(env, std::to_string(system_uuids[i])));
  }

  return uuids; 
}

Napi::Value Mavsdk::system(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() > 0) {
    std:: string uuid = info[0].As<Napi::String>().Utf8Value();
    uint64_t value;
    std::istringstream iss(uuid);
    iss >> value;
    
    if (!this->_dc.is_connected(value)) {
      return env.Undefined();
    }

    mavsdk::System *sys = &this->_dc.system(value);
    auto arg = Napi::External<mavsdk::System>::New(env, sys);
    auto system = System::constructor.New({ arg });
        
    return system;
  }
  else {
    mavsdk::System *sys = &this->_dc.system();
    
    auto arg = Napi::External<mavsdk::System>::New(env, sys);
    auto system = System::constructor.New({ arg });

    return system;
  }
}

Napi::Value Mavsdk::is_connected(const Napi::CallbackInfo& info) {
  bool isConnected;

  if (info.Length() > 0) {
    std:: string uuid = info[0].As<Napi::String>().Utf8Value();
    uint64_t value;
    std::istringstream iss(uuid);
    iss >> value;    
    isConnected = this->_dc.is_connected(value);
  }
  else {
    isConnected = this->_dc.is_connected();
  }

  return Napi::Boolean::New(info.Env(), isConnected);
}

void Mavsdk::register_on_discover(const Napi::CallbackInfo& info) {
  auto env = info.Env();

  this->ts_register_on_discover = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "register_on_discover",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });

  
  auto _on_discover = [this](uint64_t uuid) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, std::string* value ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( {Napi::String::New( env, *value )} );
    
      // We're finished with the data.
      delete value;
    };

    std::string* value = new std::string(std::to_string(uuid));
    
    napi_status status = this->ts_register_on_discover.BlockingCall(value, callback);
  };

  this->_dc.register_on_discover(_on_discover);
}

void Mavsdk::unregister_on_discover(const Napi::CallbackInfo& info) {
  if (this->ts_register_on_discover) {
    this->ts_register_on_discover.Release();
  }
}

void Mavsdk::register_on_timeout(const Napi::CallbackInfo& info) {
  auto env = info.Env();

  this->ts_register_on_timeout = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "register_on_timeout",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_timeout = [this](uint64_t uuid) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, std::string* value ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( {Napi::String::New( env, *value )} );
    
      // We're finished with the data.
      delete value;
    };

    std::string* value = new std::string(std::to_string(uuid));
    
    napi_status status = this->ts_register_on_discover.BlockingCall(value, callback);
  };

  this->_dc.register_on_timeout(_on_timeout);
}

void Mavsdk::unregister_on_timeout(const Napi::CallbackInfo& info) {
  if (this->ts_register_on_timeout) {
    this->ts_register_on_timeout.Release();
  }
}