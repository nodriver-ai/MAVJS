#ifndef INFO_H
#define INFO_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/info/info.h>

namespace mavjs {
    class Info : public Napi::ObjectWrap<Info> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Info(const Napi::CallbackInfo &info);

            static Napi::FunctionReference constructor;

        private:
            std::shared_ptr<mavsdk::Info> _info;
            
            Napi::Value get_identification(const Napi::CallbackInfo& info);
            Napi::Value get_version(const Napi::CallbackInfo& info);
            Napi::Value get_product(const Napi::CallbackInfo& info);
    };
};

#endif