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

            void dispose();

        private:
            mavsdk::Mission* _mission;

            Napi::ThreadSafeFunction tsfn[1] = {nullptr};

            Napi::Value upload_mission_async(const Napi::CallbackInfo &info);
            void upload_mission_cancel(const Napi::CallbackInfo &info);
            Napi::Value download_mission_async(const Napi::CallbackInfo &info);
            void download_mission_cancel(const Napi::CallbackInfo &info);
            void set_return_to_launch_after_mission(const Napi::CallbackInfo &info);
            Napi::Value get_return_to_launch_after_mission(const Napi::CallbackInfo &info);
            Napi::Value start_mission_async(const Napi::CallbackInfo &info);
            Napi::Value pause_mission_async(const Napi::CallbackInfo &info);
            Napi::Value clear_mission_async(const Napi::CallbackInfo &info);
            Napi::Value set_current_mission_item_async(const Napi::CallbackInfo &info);
            Napi::Value mission_finished(const Napi::CallbackInfo &info);
            Napi::Value current_mission_item(const Napi::CallbackInfo &info);
            Napi::Value total_mission_items(const Napi::CallbackInfo &info);
            void subscribe_progress(const Napi::CallbackInfo &info);

            void tsfn_release(int k);
    };
};

#endif