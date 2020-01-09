#ifndef MISSION_H
#define MISSION_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/mission/mission.h>

namespace mavjs {
    class Mission : public Napi::ObjectWrap<Mission> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Mission(const Napi::CallbackInfo &info);
            static Napi::FunctionReference constructor;

        private:
            std::shared_ptr<mavsdk::Mission> _mission;

            Napi::Value upload_mission_async(const Napi::CallbackInfo &info);
            void upload_mission_cancel(const Napi::CallbackInfo &info);
            Napi::Value download_mission_async(const Napi::CallbackInfo &info);
            void download_mission_cancel(const Napi::CallbackInfo &info);
            void set_return_to_launch_after_mission(const Napi::CallbackInfo &info);
            Napi::Value get_return_to_launch_after_mission(const Napi::CallbackInfo &info);
    };
};

#endif