#ifndef MAVSDK_H
#define MAVSDK_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include "system.h"

namespace mavjs {
    
    class Mavsdk : public Napi::ObjectWrap<Mavsdk> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Mavsdk(const Napi::CallbackInfo &info);

        private:
            static Napi::FunctionReference constructor;

            mavsdk::Mavsdk* _dc;
            System* _system = nullptr;

            Napi::ThreadSafeFunction tsfn[2] = {nullptr};
            
            std::vector<mavsdk::Mavsdk::Configuration> configuration = {
                mavsdk::Mavsdk::Configuration::GroundStation, mavsdk::Mavsdk::Configuration::CompanionComputer };

            Napi::Value version(const Napi::CallbackInfo &info);
            Napi::Value add_any_connection(const Napi::CallbackInfo &info);
            Napi::Value add_udp_connection(const Napi::CallbackInfo &info);
            Napi::Value setup_udp_remote(const Napi::CallbackInfo &info);
            Napi::Value add_tcp_connection(const Napi::CallbackInfo &info);
            Napi::Value add_serial_connection(const Napi::CallbackInfo &info);
            void set_configuration(const Napi::CallbackInfo &info);
            Napi::Value system_uuids(const Napi::CallbackInfo &info);
            Napi::Value system(const Napi::CallbackInfo &info);
            Napi::Value is_connected(const Napi::CallbackInfo &info);
            Napi::Value register_on_discover(const Napi::CallbackInfo &info);
            void register_on_timeout(const Napi::CallbackInfo &info);
            void close(const Napi::CallbackInfo &info);
    };

};

#endif
