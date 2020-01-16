#include <iostream>

#include "system.h"

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

  this->_telemetry = Telemetry::Unwrap(telemetry);

  return telemetry;
}

Napi::Value System::action(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto action = Action::constructor.New({ arg });
  
  this->_action = Action::Unwrap(action);

  return action;
}

Napi::Value System::info(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto info_ = Info::constructor.New({ arg });
  
  this->_info = Info::Unwrap(info_);
  
  return info_;
}

Napi::Value System::mission(const Napi::CallbackInfo& info) {
  auto arg = Napi::External<mavsdk::System>::New(info.Env(), this->_system);
  auto mission = Mission::constructor.New({ arg });

  this->_mission = Mission::Unwrap(mission);
        
  return mission;
}

void System::register_component_discovered_callback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  this->tsfn[0] = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "register_component_discovered_callback",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_component_discovered = [this](mavsdk::ComponentType type) -> void {


    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::ComponentType * type ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( {Napi::Number::New( env, *type )} );
    };
    
    this->tsfn[0].BlockingCall(&type, callback);
  };

  this->_system->register_component_discovered_callback(_on_component_discovered);
}

void System::dispose() {

  if (this->_mission != nullptr) {
    this->_mission->dispose();
  }
  
  if (this->_telemetry != nullptr) {
    this->_telemetry->dispose();
  }

  if (this->_action != nullptr) {
    this->_action->dispose();
  }

  if (this->_info != nullptr) {
    this->_info->dispose();
  }

  for (int i = 0; i < 1; i++) {
    if (this->tsfn[i] != nullptr) {
      this->tsfn[i].Release();
      this->tsfn[i] = nullptr;
    }
  }
}