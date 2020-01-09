#include <iostream>

#include "system.h"
#include "telemetry.h"
#include "action.h"
#include "info.h"
#include "mission.h"

using namespace mavjs;

Napi::FunctionReference System::constructor;

Napi::Object System::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "System", {
      InstanceMethod("has_autopilot", &System::has_autopilot),
      InstanceMethod("is_standalone", &System::is_standalone),
      InstanceMethod("has_camera", &System::has_camera),
      InstanceMethod("has_gimbal", &System::has_gimbal),
      InstanceMethod("is_connected", &System::is_connected),
      InstanceMethod("get_uuid", &System::get_uuid),
      InstanceMethod("telemetry", &System::telemetry),
      InstanceMethod("action", &System::action),
      InstanceMethod("info", &System::info),
      InstanceMethod("mission", &System::mission),
      InstanceMethod("register_component_discovered_callback", &System::register_component_discovered_callback),
      InstanceMethod("unregister_component_discovered_callback", &System::unregister_component_discovered_callback)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("System", func);
  return exports;
}

System::System(const Napi::CallbackInfo& info) : Napi::ObjectWrap<System>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->_system = info[0].As<Napi::External<mavsdk::System>>().Data();
}

Napi::Value System::has_autopilot(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_autopilot());
}

Napi::Value System::is_standalone(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->is_standalone());
}

Napi::Value System::has_camera(const Napi::CallbackInfo& info) {
  if (info.Length() > 0) {
    return Napi::Boolean::New(info.Env(), this->_system->has_camera(info[0].As<Napi::Number>().Int32Value()));
  }
  else {
    return Napi::Boolean::New(info.Env(), this->_system->has_camera());
  }
}

Napi::Value System::has_gimbal(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_gimbal());
}

Napi::Value System::is_connected(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->is_connected());
}

Napi::Value System::get_uuid(const Napi::CallbackInfo& info) {
  uint64_t uuid = this->_system->get_uuid();

  return Napi::String::New(info.Env(), std::to_string(uuid));
}

Napi::Value System::telemetry(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto telemetry = Telemetry::constructor.New({ arg });
        
  return telemetry;
}

Napi::Value System::action(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto action = Action::constructor.New({ arg });
        
  return action;
}

Napi::Value System::info(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto _info = Info::constructor.New({ arg });
        
  return _info;
}

Napi::Value System::mission(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto _mission = Mission::constructor.New({ arg });
        
  return _mission;
}

void System::register_component_discovered_callback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->ts_register_component_discovered_callback = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "register_component_discovered_callback",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_component_discovered = [this](mavsdk::ComponentType type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::ComponentType * value ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( {Napi::Number::New( env, *value )} );
    
      // We're finished with the data.
      delete value;
    };

    mavsdk::ComponentType * value = new mavsdk::ComponentType(type);
    
    napi_status status = this->ts_register_component_discovered_callback.BlockingCall(value, callback);
  };

  this->_system->register_component_discovered_callback(_on_component_discovered);
}

void System::unregister_component_discovered_callback(const Napi::CallbackInfo& info) {
  if (this->ts_register_component_discovered_callback) {
    this->ts_register_component_discovered_callback.Release();
  }
}

