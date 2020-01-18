#include <iostream>
#include <future>
#include <utility>

#include "mission.h"
#include "missionItem.h"

using namespace mavjs;

static mavsdk::MissionItem::CameraAction _camera_actions[6] = {
                mavsdk::MissionItem::CameraAction::TAKE_PHOTO,
                mavsdk::MissionItem::CameraAction::START_PHOTO_INTERVAL,
                mavsdk::MissionItem::CameraAction::STOP_PHOTO_INTERVAL,
                mavsdk::MissionItem::CameraAction::START_VIDEO,
                mavsdk::MissionItem::CameraAction::STOP_VIDEO,
                mavsdk::MissionItem::CameraAction::NONE
            };

class UploadMissionWorker : public Napi::AsyncWorker {
    public:
        UploadMissionWorker(Napi::Env &env, std::vector<std::shared_ptr<mavsdk::MissionItem>>& mission_items, mavsdk::Mission* mission, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), mission_items(mission_items), mission(mission), deferred(deferred) {}

        ~UploadMissionWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Mission::Result>>();
        auto future_result = prom->get_future();
        mission->upload_mission_async(
              mission_items, [prom](mavsdk::Mission::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Mission::result_str(result)));
    }

    private:
        std::vector<std::shared_ptr<mavsdk::MissionItem>> mission_items;
        mavsdk::Mission* mission;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Mission::Result result;
};

class DownloadMissionWorker : public Napi::AsyncWorker {
    public:
        DownloadMissionWorker(Napi::Env &env, mavsdk::Mission* mission, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), mission(mission), deferred(deferred) {}

        ~DownloadMissionWorker() {}
    
    void Execute() {
        auto prom_result = std::make_shared<std::promise<mavsdk::Mission::Result>>();
        auto prom_mission_items = std::make_shared<std::promise<std::vector<std::shared_ptr<mavsdk::MissionItem>>>>();

        auto future_result = prom_result->get_future();
        auto future_mission_items = prom_mission_items->get_future();

        mission->download_mission_async(
          [prom_result, prom_mission_items](mavsdk::Mission::Result result, std::vector<std::shared_ptr<mavsdk::MissionItem>> items) {

            prom_result->set_value(result);
            prom_mission_items->set_value(items);
          });

        result = future_result.get();
        mission_items = future_mission_items.get();
    }

    void OnOK() {
      Napi::Array items = Napi::Array::New(Env());

      for(int i = 0; i < mission_items.size(); ++i) {
        Napi::Object obj = Napi::Object::New(Env());

        obj.Set(Napi::String::New(Env(), "longitude_deg"), mission_items[i]->get_longitude_deg());
        obj.Set(Napi::String::New(Env(), "latitude_deg"), mission_items[i]->get_latitude_deg());
        obj.Set(Napi::String::New(Env(), "relative_altitude_m"), mission_items[i]->get_relative_altitude_m());
        obj.Set(Napi::String::New(Env(), "fly_through"), mission_items[i]->get_fly_through());
        obj.Set(Napi::String::New(Env(), "acceptance_radius_m"), mission_items[i]->get_acceptance_radius_m());
        obj.Set(Napi::String::New(Env(), "speed_m_s"), mission_items[i]->get_speed_m_s());
        obj.Set(Napi::String::New(Env(), "loiter_time_s"), mission_items[i]->get_loiter_time_s());
        obj.Set(Napi::String::New(Env(), "gimbal_pitch_deg"), mission_items[i]->get_gimbal_pitch_deg());
        obj.Set(Napi::String::New(Env(), "gimbal_yaw_deg"), mission_items[i]->get_gimbal_yaw_deg());
        auto action = static_cast<typename std::underlying_type<mavsdk::MissionItem::CameraAction>::type>(mission_items[i]->get_camera_action());
        obj.Set(Napi::String::New(Env(), "camera_action"), action);
        obj.Set(Napi::String::New(Env(), "camera_photo_interval_s"), mission_items[i]->get_camera_photo_interval_s());

        items[i] = obj;
      }

      Napi::Object _result = Napi::Object::New(Env());

      _result.Set(Napi::String::New(Env(), "result"), mavsdk::Mission::result_str(result));
      _result.Set(Napi::String::New(Env(), "mission_items"), items);
      deferred.Resolve(_result);
    }

    private:
        mavsdk::Mission* mission;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Mission::Result result;
        std::vector<std::shared_ptr<mavsdk::MissionItem>> mission_items;
};

class StartMissionWorker : public Napi::AsyncWorker {
    public:
        StartMissionWorker(Napi::Env &env, mavsdk::Mission* mission, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), mission(mission), deferred(deferred) {}

        ~StartMissionWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Mission::Result>>();
        auto future_result = prom->get_future();
        mission->start_mission_async(
              [prom](mavsdk::Mission::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Mission::result_str(result)));
    }

    private:
        mavsdk::Mission* mission;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Mission::Result result;
};

class PauseMissionWorker : public Napi::AsyncWorker {
    public:
        PauseMissionWorker(Napi::Env &env, mavsdk::Mission* mission, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), mission(mission), deferred(deferred) {}

        ~PauseMissionWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Mission::Result>>();
        auto future_result = prom->get_future();
        mission->pause_mission_async(
              [prom](mavsdk::Mission::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Mission::result_str(result)));
    }

    private:
        mavsdk::Mission* mission;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Mission::Result result;
};

class ClearMissionWorker : public Napi::AsyncWorker {
    public:
        ClearMissionWorker(Napi::Env &env, mavsdk::Mission* mission, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), mission(mission), deferred(deferred) {}

        ~ClearMissionWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Mission::Result>>();
        auto future_result = prom->get_future();
        mission->clear_mission_async(
              [prom](mavsdk::Mission::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Mission::result_str(result)));
    }

    private:
        mavsdk::Mission* mission;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Mission::Result result;
};

class SetCurrentMissionItemWorker : public Napi::AsyncWorker {
    public:
        SetCurrentMissionItemWorker(Napi::Env &env, int current, mavsdk::Mission* mission, Napi::Promise::Deferred& deferred)
        : Napi::AsyncWorker(env), current(current), mission(mission), deferred(deferred) {}

        ~SetCurrentMissionItemWorker() {}
    
    void Execute() {
        auto prom = std::make_shared<std::promise<mavsdk::Mission::Result>>();
        auto future_result = prom->get_future();
        mission->set_current_mission_item_async(
          current, [prom](mavsdk::Mission::Result result) { prom->set_value(result); });

        result = future_result.get();
    }

    void OnOK() {
        deferred.Resolve(Napi::String::New(Env(), mavsdk::Mission::result_str(result)));
    }

    private:
        int current;
        mavsdk::Mission* mission;
        Napi::Promise::Deferred deferred;
        
        mavsdk::Mission::Result result;
};

Napi::FunctionReference Mission::constructor;

Napi::Object Mission::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Mission", {
    InstanceMethod("upload_mission_async", &Mission::upload_mission_async),
    InstanceMethod("upload_mission_cancel", &Mission::upload_mission_cancel),
    InstanceMethod("download_mission_async", &Mission::download_mission_async),
    InstanceMethod("download_mission_cancel", &Mission::download_mission_cancel),
    InstanceMethod("set_return_to_launch_after_mission", &Mission::set_return_to_launch_after_mission),
    InstanceMethod("get_return_to_launch_after_mission", &Mission::get_return_to_launch_after_mission),
    InstanceMethod("start_mission_async", &Mission::start_mission_async),
    InstanceMethod("pause_mission_async", &Mission::pause_mission_async),
    InstanceMethod("clear_mission_async", &Mission::clear_mission_async),
    InstanceMethod("set_current_mission_item_async", &Mission::set_current_mission_item_async),
    InstanceMethod("mission_finished", &Mission::mission_finished),
    InstanceMethod("current_mission_item", &Mission::current_mission_item),
    InstanceMethod("total_mission_items", &Mission::total_mission_items),
    InstanceMethod("subscribe_progress", &Mission::subscribe_progress),
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Mission", func);
  return exports;
}

Mission::Mission(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Mission>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  auto system = info[0].As<Napi::External<mavsdk::System>>().Data();
  this->_mission = new mavsdk::Mission(*system);
}

Napi::Value Mission::upload_mission_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Array mission_items = info[0].As<Napi::Array>();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  std::vector<std::shared_ptr<mavsdk::MissionItem>> _mission_items;

  for(uint i = 0; i < mission_items.Length(); ++i) {
      auto item = mission_items.Get(i).As<Napi::Object>();
      _mission_items.push_back(MissionItem::make_mission_item(
        item.Get("longitude_deg").As<Napi::Number>().DoubleValue(),
        item.Get("latitude_deg").As<Napi::Number>().DoubleValue(),
        item.Get("relative_altitude_m").As<Napi::Number>().FloatValue(),
        item.Get("fly_through").As<Napi::Boolean>(),
        item.Get("acceptance_radius_m").As<Napi::Number>().FloatValue(),
        item.Get("speed_m_s").As<Napi::Number>().FloatValue(),
        item.Get("gimbal_pitch_deg").As<Napi::Number>().FloatValue(),
        item.Get("gimbal_yaw_deg").As<Napi::Number>().FloatValue(),
        item.Get("loiter_time_s").As<Napi::Number>().FloatValue(),
        _camera_actions[item.Get("camera_action").As<Napi::Number>().Uint32Value()],
        item.Get("camera_photo_interval_s").As<Napi::Number>().FloatValue()
      ));      
  }
  
  UploadMissionWorker* wk = new UploadMissionWorker(env, _mission_items, this->_mission, deferred);
  wk->Queue();
  return deferred.Promise();
}

void Mission::upload_mission_cancel(const Napi::CallbackInfo& info) {
  this->_mission->upload_mission_cancel();
}

Napi::Value Mission::download_mission_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  DownloadMissionWorker* wk = new DownloadMissionWorker(env, this->_mission, deferred);
  wk->Queue();
  return deferred.Promise();
}

void Mission::download_mission_cancel(const Napi::CallbackInfo& info) {
  this->_mission->download_mission_cancel();
}

void Mission::set_return_to_launch_after_mission(const Napi::CallbackInfo& info) {
  this->_mission->set_return_to_launch_after_mission(info[0].As<Napi::Boolean>());
}

Napi::Value Mission::get_return_to_launch_after_mission(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_mission->get_return_to_launch_after_mission());
}

Napi::Value Mission::start_mission_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  StartMissionWorker* wk = new StartMissionWorker(env, this->_mission, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Mission::pause_mission_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  PauseMissionWorker* wk = new PauseMissionWorker(env, this->_mission, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Mission::clear_mission_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  ClearMissionWorker* wk = new ClearMissionWorker(env, this->_mission, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Mission::set_current_mission_item_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  int current = info[0].As<Napi::Number>().Int32Value();
  Napi::Promise::Deferred deferred = Napi::Promise::Deferred::New(env);

  SetCurrentMissionItemWorker* wk = new SetCurrentMissionItemWorker(env, current, this->_mission, deferred);
  wk->Queue();
  return deferred.Promise();
}

Napi::Value Mission::mission_finished(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_mission->mission_finished());
}

Napi::Value Mission::current_mission_item(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission->current_mission_item());
}

Napi::Value Mission::total_mission_items(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission->total_mission_items());
}

struct missionProgress {
  int current;
  int total;
};

void Mission::subscribe_progress(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  this->tsfn_release(0);

  if (info[0].IsFunction()) {
    this->tsfn[0] = Napi::ThreadSafeFunction::New(
        env,
        info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
        "subscribe_progress",        // Name
        0,                             // Unlimited queue
        1,                             // Only one thread will use this initially
        []( Napi::Env ) {  
                // Finalizer used to clean threads up
        });
    
    auto _on_subscribe_progress = [this](int current, int total) -> void {

      auto callback = []( Napi::Env env, Napi::Function jsCallback, missionProgress * progress ) {
        // Transform native data into JS data, passing it to the provided 
        // `jsCallback` -- the TSFN's JavaScript function.

        Napi::Object obj = Napi::Object::New(env);
        obj.Set(Napi::String::New(env, "current"), progress->current);
        obj.Set(Napi::String::New(env, "total"), progress->total);
        jsCallback.Call( { obj } );
      
      };

      missionProgress progress;
      progress.current = current;
      progress.total = total;

      this->tsfn[0].BlockingCall(&progress, callback);
    };

    this->_mission->subscribe_progress(_on_subscribe_progress);
  }
  else {
    this->_mission->subscribe_progress(nullptr);
  }
}

void Mission::dispose() {
  delete this->_mission;

  for (int i = 0; i < 1; i++) {
    this->tsfn_release(i);
  }
}

void Mission::tsfn_release(int k) {
  if (this->tsfn[k] != nullptr) {
      this->tsfn[k].Release();
      this->tsfn[k] = nullptr;
    }
}
