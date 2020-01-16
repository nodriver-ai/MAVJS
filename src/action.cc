#include <iostream>
#include <future>
#include <utility>

#include "action.h"
#include "system.h"

using namespace mavjs;

class ArmWorker : public Napi::AsyncWorker {
    public:
        ArmWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~ArmWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->arm_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:     
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class DisarmWorker : public Napi::AsyncWorker {
    public:
        DisarmWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~DisarmWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->disarm_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class KillWorker : public Napi::AsyncWorker {
    public:
        KillWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~KillWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->kill_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class TakeoffWorker : public Napi::AsyncWorker {
    public:
        TakeoffWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~TakeoffWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->takeoff_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class LandWorker : public Napi::AsyncWorker {
    public:
        LandWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~LandWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->land_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class ReturnToLaunchWorker : public Napi::AsyncWorker {
    public:
        ReturnToLaunchWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~ReturnToLaunchWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->return_to_launch_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class TransitionToFixedwingWorker : public Napi::AsyncWorker {
    public:
        TransitionToFixedwingWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~TransitionToFixedwingWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->transition_to_fixedwing_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

class TransitionToMulticopterWorker : public Napi::AsyncWorker {
    public:
        TransitionToMulticopterWorker(Napi::Env &env, mavsdk::Action* action, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), action(action), deferred(deferred) {}

        ~TransitionToMulticopterWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Action::Result>>();
        auto future_result = prom->get_future();
        action->transition_to_multicopter_async(
              [prom](mavsdk::Action::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Action::result_str(result)));
    }

    private:
        mavsdk::Action* action;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Action::Result result;
};

Napi::FunctionReference Action::constructor;

Napi::Object Action::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Action", {
    InstanceMethod("arm", &Action::arm),
    InstanceMethod("disarm", &Action::disarm),
    InstanceMethod("kill", &Action::kill),
    InstanceMethod("reboot", &Action::reboot),
    InstanceMethod("takeoff", &Action::takeoff),
    InstanceMethod("land", &Action::land),
    InstanceMethod("return_to_launch", &Action::return_to_launch),
    InstanceMethod("goto_location", &Action::goto_location),
    InstanceMethod("transition_to_fixedwing", &Action::transition_to_fixedwing),
    InstanceMethod("transition_to_multicopter", &Action::transition_to_multicopter),
    InstanceMethod("arm_async", &Action::arm_async),
    InstanceMethod("disarm_async", &Action::disarm_async),
    InstanceMethod("kill_async", &Action::kill_async),
    InstanceMethod("takeoff_async", &Action::takeoff_async),
    InstanceMethod("land_async", &Action::land_async),
    InstanceMethod("return_to_launch_async", &Action::return_to_launch_async),
    InstanceMethod("transition_to_fixedwing_async", &Action::transition_to_fixedwing_async),
    InstanceMethod("transition_to_multicopter_async", &Action::transition_to_multicopter_async),
    InstanceMethod("set_takeoff_altitude", &Action::set_takeoff_altitude),
    InstanceMethod("get_takeoff_altitude", &Action::get_takeoff_altitude),
    InstanceMethod("set_max_speed", &Action::set_max_speed),
    InstanceMethod("set_return_to_launch_return_altitude", &Action::set_return_to_launch_return_altitude),
    InstanceMethod("get_return_to_launch_return_altitude", &Action::get_return_to_launch_return_altitude)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Action", func);
  return exports;
}

Action::Action(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Action>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  
  auto system = info[0].As<Napi::External<mavsdk::System>>().Data();
  this->_action = new mavsdk::Action(*system);
}

Napi::Value Action::arm(const Napi::CallbackInfo& info) {
    const mavsdk::Action::Result arm_result = this->_action->arm();
    return Napi::String::New(info.Env(), mavsdk::Action::result_str(arm_result));
}

Napi::Value Action::disarm(const Napi::CallbackInfo& info) {
    const mavsdk::Action::Result disarm_result = this->_action->disarm();
    return Napi::String::New(info.Env(), mavsdk::Action::result_str(disarm_result));
}

Napi::Value Action::kill(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result kill_result = this->_action->kill();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(kill_result));
}

Napi::Value Action::reboot(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result reboot_result = this->_action->reboot();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(reboot_result));
}

Napi::Value Action::takeoff(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result takeoff_result = this->_action->takeoff();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(takeoff_result));
}

Napi::Value Action::land(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result land_result = this->_action->land();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(land_result));
}

Napi::Value Action::return_to_launch(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result return_to_launch_result = this->_action->return_to_launch();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(return_to_launch_result));
}

Napi::Value Action::goto_location(const Napi::CallbackInfo& info) {
  double latitude_deg = info[0].As<Napi::Number>().DoubleValue();
  double longitude_deg = info[1].As<Napi::Number>().DoubleValue();
  float altitude_amsl_m = info[2].As<Napi::Number>().FloatValue();
  float yaw_deg = info[3].As<Napi::Number>().FloatValue();
  const mavsdk::Action::Result goto_location_result = this->_action->goto_location(latitude_deg, longitude_deg, altitude_amsl_m, yaw_deg);
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(goto_location_result));
}

Napi::Value Action::transition_to_fixedwing(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result transition_to_fixedwing_result = this->_action->transition_to_fixedwing();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(transition_to_fixedwing_result));
}

Napi::Value Action::transition_to_multicopter(const Napi::CallbackInfo& info) {
  const mavsdk::Action::Result transition_to_multicopter_result = this->_action->transition_to_multicopter();
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(transition_to_multicopter_result));
}

Napi::Value Action::arm_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  ArmWorker* wk = new ArmWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::disarm_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  DisarmWorker* wk = new DisarmWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::kill_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  KillWorker* wk = new KillWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::takeoff_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  TakeoffWorker* wk = new TakeoffWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::land_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  LandWorker* wk = new LandWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::return_to_launch_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  ReturnToLaunchWorker* wk = new ReturnToLaunchWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::transition_to_fixedwing_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  TransitionToFixedwingWorker* wk = new TransitionToFixedwingWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::transition_to_multicopter_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  TransitionToMulticopterWorker* wk = new TransitionToMulticopterWorker(env, this->_action, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Action::set_takeoff_altitude(const Napi::CallbackInfo& info) {
  float relative_altitude_m = info[0].As<Napi::Number>().FloatValue();
  const mavsdk::Action::Result set_takeoff_altitude_result = this->_action->set_takeoff_altitude(relative_altitude_m);
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(set_takeoff_altitude_result));
}

Napi::Value Action::get_takeoff_altitude(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::pair<mavsdk::Action::Result, float> get_takeoff_altitude_result = this->_action->get_takeoff_altitude();
  
  mavsdk::Action::Result result = get_takeoff_altitude_result.first;
  float value = get_takeoff_altitude_result.second;

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "result"), mavsdk::Action::result_str(result));
  obj.Set(Napi::String::New(env, "value"), value);

  return obj;
}

Napi::Value Action::set_max_speed(const Napi::CallbackInfo& info) {
  float speed_m_s = info[0].As<Napi::Number>().FloatValue();
  const mavsdk::Action::Result set_max_speed_result = this->_action->set_max_speed(speed_m_s);
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(set_max_speed_result));
}

Napi::Value Action::get_max_speed(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::pair<mavsdk::Action::Result, float> get_max_speed_result = this->_action->get_max_speed();
  
  mavsdk::Action::Result result = get_max_speed_result.first;
  float value = get_max_speed_result.second;

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "result"), mavsdk::Action::result_str(result));
  obj.Set(Napi::String::New(env, "value"), value);

  return obj;
}

Napi::Value Action::set_return_to_launch_return_altitude(const Napi::CallbackInfo& info) {
  float relative_altitude_m = info[0].As<Napi::Number>().FloatValue();
  const mavsdk::Action::Result set_return_to_launch_return_altitude_result = this->_action->set_return_to_launch_return_altitude(relative_altitude_m);
  return Napi::String::New(info.Env(), mavsdk::Action::result_str(set_return_to_launch_return_altitude_result));
}

Napi::Value Action::get_return_to_launch_return_altitude(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  std::pair<mavsdk::Action::Result, float> get_return_to_launch_return_altitude_result = this->_action->get_return_to_launch_return_altitude();
  
  mavsdk::Action::Result result = get_return_to_launch_return_altitude_result.first;
  float value = get_return_to_launch_return_altitude_result.second;

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "result"), mavsdk::Action::result_str(result));
  obj.Set(Napi::String::New(env, "value"), value);

  return obj;
}

void Action::dispose() {
  delete this->_action;
}