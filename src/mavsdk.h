#ifndef MAVSDK_H
#define MAVSDK_H

#include <string>
#include <mutex>
#include <napi.h>
#include <mavsdk/mavsdk.h>

class MavSDK : public Napi::ObjectWrap<MavSDK> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 MavSDK(const Napi::CallbackInfo &info);

private:
 static Napi::FunctionReference constructor;

 mavsdk::Mavsdk _dc;
 std::vector<uint64_t> uuids;
 std::mutex uuids_mutex;

 std::string _connection_url;
 Napi::Value get_connection_url(const Napi::CallbackInfo &info);

 Napi::Value is_connected(const Napi::CallbackInfo& info);
 Napi::Value discover_uuids(const Napi::CallbackInfo& info);
 Napi::Value connect_to_drone(const Napi::CallbackInfo& info);

};

#endif
