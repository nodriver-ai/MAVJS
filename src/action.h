#ifndef ACTION_H
#define ACTION_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>

namespace mavjs {
    class Action : public Napi::ObjectWrap<Action> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Action(const Napi::CallbackInfo &info);

            static Napi::FunctionReference constructor;
            
            void dispose();
            
        private:
            mavsdk::Action* _action;

            Napi::Value arm(const Napi::CallbackInfo& info);
            Napi::Value disarm(const Napi::CallbackInfo& info);
            Napi::Value kill(const Napi::CallbackInfo& info);
            Napi::Value reboot(const Napi::CallbackInfo& info);
            Napi::Value takeoff(const Napi::CallbackInfo& info);
            Napi::Value land(const Napi::CallbackInfo& info);
            Napi::Value return_to_launch(const Napi::CallbackInfo& info);
            Napi::Value goto_location(const Napi::CallbackInfo& info);
            Napi::Value transition_to_fixedwing(const Napi::CallbackInfo& info);
            Napi::Value transition_to_multicopter(const Napi::CallbackInfo& info);
            Napi::Value arm_async(const Napi::CallbackInfo& info);
            Napi::Value disarm_async(const Napi::CallbackInfo& info);
            Napi::Value kill_async(const Napi::CallbackInfo& info);
            Napi::Value takeoff_async(const Napi::CallbackInfo& info);
            Napi::Value land_async(const Napi::CallbackInfo& info);
            Napi::Value return_to_launch_async(const Napi::CallbackInfo& info);
            Napi::Value transition_to_fixedwing_async(const Napi::CallbackInfo& info);
            Napi::Value transition_to_multicopter_async(const Napi::CallbackInfo& info);
            Napi::Value set_takeoff_altitude(const Napi::CallbackInfo& info);
            Napi::Value get_takeoff_altitude(const Napi::CallbackInfo& info);
            Napi::Value set_max_speed(const Napi::CallbackInfo& info);
            Napi::Value get_max_speed(const Napi::CallbackInfo& info);
            Napi::Value set_return_to_launch_return_altitude(const Napi::CallbackInfo& info);
            Napi::Value get_return_to_launch_return_altitude(const Napi::CallbackInfo& info);
    };
};

#endif