#ifndef SYSTEM_H
#define SYSTEM_H

#include <napi.h>
#include <mavsdk/mavsdk.h>

namespace mavjs {
    class System : public Napi::ObjectWrap<System> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            System(const Napi::CallbackInfo &info);
            static Napi::FunctionReference constructor;

            mavsdk::System * _system;

        private:

            Napi::ThreadSafeFunction ts_register_component_discovered_callback;

            Napi::Value has_autopilot(const Napi::CallbackInfo &info);
            Napi::Value is_standalone(const Napi::CallbackInfo &info);
            Napi::Value has_camera(const Napi::CallbackInfo &info);
            Napi::Value has_gimbal(const Napi::CallbackInfo &info);
            Napi::Value is_connected(const Napi::CallbackInfo &info);
            Napi::Value get_uuid(const Napi::CallbackInfo &info);
            Napi::Value telemetry(const Napi::CallbackInfo &info);
            Napi::Value action(const Napi::CallbackInfo &info);
            Napi::Value info(const Napi::CallbackInfo &info);
            void register_component_discovered_callback(const Napi::CallbackInfo &info);
            void unregister_component_discovered_callback(const Napi::CallbackInfo &info);
    };
};

#endif
