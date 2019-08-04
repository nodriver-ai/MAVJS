#ifndef NDBOX_H
#define NDBOX_H

#include <string>

#include <napi.h>
#include <mavsdk/mavsdk.h>

/**
  # Class System
  # connection with one or more drones.
  # discover available drones.
  # each drone is identified by a UUID.
  @params address: string -> UDP path for the connection
  */
class Ndbox : public Napi::ObjectWrap<Ndbox> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 Ndbox(const Napi::CallbackInfo &info);

private:
 static Napi::FunctionReference constructor;

 mavsdk::Mavsdk _dc;

 std::string _connection_url;
 Napi::Value get_connection_url(const Napi::CallbackInfo &info);

 /*
 # is_connected method
 # Returns true if exactly one system is currently connected.
 # Connected means we are receiving heartbeats from this system
 # If multiple systems have connected, this will return false
 @param uuid: string
 @return Boolean
 */
 Napi::Value is_connected(const Napi::CallbackInfo& info);

 /*
 */
 void discover_uuids(const Napi::CallbackInfo& info);

 Napi::Value connect_to_drone(const Napi::CallbackInfo& info);

};

#endif
