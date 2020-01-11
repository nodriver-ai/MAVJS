#include <sstream>
#include <iostream>
#include <thread>

#include "observable.h"

using namespace mavjs;

Napi::FunctionReference Subscriber::constructor;

Napi::Object Subscriber::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Subscriber", {
    InstanceMethod("subscribe", &Subscriber::subscribe),
    InstanceMethod("unsubscribe", &Subscriber::unsubscribe)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Subscriber", func);
  return exports;
}

Subscriber::Subscriber(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Subscriber>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->_thread_safe_function = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      info[1].As<Napi::String>().Utf8Value(),        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  this->set_param(info[2].As<Napi::Value>());
}

void Subscriber::set_param(Napi::Value value) {}

void Subscriber::subscribe(const Napi::CallbackInfo& info) {
    Napi::Error::New(info.Env(), "Not implemented!").ThrowAsJavaScriptException();
}

void Subscriber::unsubscribe(const Napi::CallbackInfo& info) {
    this->_thread_safe_function.Release();
}

void RegistertOnDiscover::set_param(Napi::Value value) {
    this->_dc = value.As<Napi::External<mavsdk::Mavsdk>>().Data();
}

void RegistertOnDiscover::subscribe(const Napi::CallbackInfo& info) {
    auto _on_discover = [this](uint64_t uuid) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, std::string* value ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( {Napi::String::New( env, *value )} );
    
      // We're finished with the data.
      delete value;
    };

    std::string* value = new std::string(std::to_string(uuid));
    
    napi_status status = this->_thread_safe_function.BlockingCall(value, callback);
  };

  this->_dc->register_on_discover(_on_discover);
}

