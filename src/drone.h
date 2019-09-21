#ifndef DRONE_H
#define DRONE_H

#include <string>

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/info/info.h>

class Drone : public Napi::ObjectWrap<Drone> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 Drone(const Napi::CallbackInfo &info);
 static Napi::FunctionReference constructor;

 private:
   mavsdk::System * _system;
   std::shared_ptr<mavsdk::Telemetry> _telemetry;
   std::shared_ptr<mavsdk::Action> _action;
   std::shared_ptr<mavsdk::Info> _info;

   std::string _uuid;
   Napi::Value get_uuid(const Napi::CallbackInfo &info);

   Napi::Value get_product_info(const Napi::CallbackInfo &info);
   Napi::Value is_connected(const Napi::CallbackInfo &info);
   Napi::Value has_autopilot(const Napi::CallbackInfo &info);
   Napi::Value has_camera(const Napi::CallbackInfo &info);
   Napi::Value has_gimbal(const Napi::CallbackInfo &info);

   void set_rate_position(const Napi::CallbackInfo &info);
   void set_rate_home_position(const Napi::CallbackInfo &info);
   void set_rate_attitude(const Napi::CallbackInfo &info);
   void set_rate_battery(const Napi::CallbackInfo &info);
   void set_rate_position_velocity_ned(const Napi::CallbackInfo &info);
   void set_rate_in_air(const Napi::CallbackInfo &info);
   void set_rate_camera_attitude(const Napi::CallbackInfo &info);
   void set_rate_ground_speed_ned(const Napi::CallbackInfo &info);
   void set_rate_gps_info(const Napi::CallbackInfo &info);
   void set_rate_rc_status(const Napi::CallbackInfo &info);

   Napi::Value position(const Napi::CallbackInfo &info);
   Napi::Value health_all_ok(const Napi::CallbackInfo &info);
   Napi::Value home_position(const Napi::CallbackInfo &info);
   Napi::Value battery(const Napi::CallbackInfo &info);
   Napi::Value in_air(const Napi::CallbackInfo &info);
   Napi::Value armed(const Napi::CallbackInfo &info);
   Napi::Value attitude_quaternion(const Napi::CallbackInfo &info);
   Napi::Value attitude_euler_angle(const Napi::CallbackInfo &info);
   Napi::Value ground_speed_ned(const Napi::CallbackInfo &info);
   Napi::Value gps_info(const Napi::CallbackInfo &info);
   Napi::Value flight_mode(const Napi::CallbackInfo &info);
   Napi::Value health(const Napi::CallbackInfo &info);
   Napi::Value rc_status(const Napi::CallbackInfo &info);

   Napi::Value telemetry(const Napi::CallbackInfo &info);

   Napi::Value arm(const Napi::CallbackInfo &info);
   Napi::Value disarm(const Napi::CallbackInfo &info);
   Napi::Value takeoff(const Napi::CallbackInfo &info);
   Napi::Value land(const Napi::CallbackInfo &info);
};

#endif
