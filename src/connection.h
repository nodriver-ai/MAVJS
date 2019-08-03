#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>

#include <napi.h>
#include <mavsdk/mavsdk.h>

using namespace mavsdk;


/**
  # Class Connection
  # connection with one or more drones.
  # discover available drones.
  # each drone is identified by a UUID.
  @params address: string -> UDP path for the connection
  */
class Connection : public Napi::ObjectWrap<Connection> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 Connection(const Napi::CallbackInfo &info);

private:
 static Napi::FunctionReference constructor;

 Mavsdk _dc;

 std::string _address;
 Napi::Value GetAddress(const Napi::CallbackInfo &info);

 /*
 # IsConnected method
 # Returns true if exactly one system is currently connected.
 # Connected means we are receiving heartbeats from this system
 # If multiple systems have connected, this will return false
 @param uuid: string
 @return Boolean
 */
 Napi::Value IsConnected(const Napi::CallbackInfo& info);

 /*
 */
 void GetUUIDs(const Napi::CallbackInfo& info);

};

#endif
