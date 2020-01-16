#ifndef SYSTEM_H
#define SYSTEM_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include "telemetry.h"
#include "action.h"
#include "info.h"
#include "mission.h"

namespace mavjs {
    class System : public Napi::ObjectWrap<System> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            System(const Napi::CallbackInfo &info);

            static Napi::FunctionReference constructor;

            mavsdk::System* _system;

            void dispose();

        private:
            Telemetry* _telemetry = nullptr;
            Mission* _mission = nullptr;
            Action* _action = nullptr;
            Info* _info = nullptr;

            Napi::ThreadSafeFunction tsfn[1] = {nullptr};

            Napi::Value has_autopilot(const Napi::CallbackInfo &info);
            Napi::Value is_standalone(const Napi::CallbackInfo &info);
            Napi::Value has_camera(const Napi::CallbackInfo &info);
            Napi::Value has_gimbal(const Napi::CallbackInfo &info);
            Napi::Value is_connected(const Napi::CallbackInfo &info);
            Napi::Value get_uuid(const Napi::CallbackInfo &info);
            Napi::Value telemetry(const Napi::CallbackInfo &info);
            Napi::Value action(const Napi::CallbackInfo &info);
            Napi::Value info(const Napi::CallbackInfo &info);
            Napi::Value mission(const Napi::CallbackInfo &info);
            void register_component_discovered_callback(const Napi::CallbackInfo &info);
    };
};

#endif
