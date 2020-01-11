#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <napi.h>
#include <mavsdk/mavsdk.h>

namespace mavjs {
    
    class Subscriber : public Napi::ObjectWrap<Subscriber> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Subscriber(const Napi::CallbackInfo &info);
            static Napi::FunctionReference constructor;

            void set_param(Napi::Value value);
            void subscribe(const Napi::CallbackInfo &info);
            void unsubscribe(const Napi::CallbackInfo &info);

            Napi::ThreadSafeFunction _thread_safe_function;
    };

    class RegistertOnDiscover: public Subscriber {
        public:
            void set_param(Napi::Value value);
            void subscribe(const Napi::CallbackInfo &info);
        
        private: 
            mavsdk::Mavsdk * _dc;;
    };

};

#endif