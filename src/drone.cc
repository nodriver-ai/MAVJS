#include <string>
#include <iostream>
//#include <chrono>
#include <cstdint>
//#include <thread>
#include <typeinfo>
#include <sstream>

#include "drone.h"
//#include <mavsdk/mavsdk.h>
//#include <mavsdk/plugins/telemetry/telemetry.h>
//#include <mavsdk/plugins/info/info.h>

//using namespace mavsdk;
//using namespace std::chrono;
//using namespace std::this_thread;

#define ERROR_CONSOLE_TEXT "\033[31m" // Turn text on console red
#define TELEMETRY_CONSOLE_TEXT "\033[34m" // Turn text on console blue
#define NORMAL_CONSOLE_TEXT "\033[0m" // Restore normal console colour

Napi::FunctionReference Drone::constructor;

Napi::Object Drone::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Drone", {
    InstanceAccessor("uuid", &Drone::get_uuid, nullptr),
    InstanceMethod("get_identification", &Drone::get_identification),
    InstanceMethod("get_product", &Drone::get_product),
    InstanceMethod("is_connected", &Drone::is_connected),
    InstanceMethod("has_autopilot", &Drone::has_autopilot),
    InstanceMethod("has_camera", &Drone::has_camera),
    InstanceMethod("has_gimbal", &Drone::has_gimbal),
    InstanceMethod("set_rate_position", &Drone::set_rate_position),
    InstanceMethod("set_rate_home_position", &Drone::set_rate_home_position),
    InstanceMethod("set_rate_attitude", &Drone::set_rate_attitude),
    InstanceMethod("set_rate_battery", &Drone::set_rate_battery),
    InstanceMethod("set_rate_position_velocity_ned", &Drone::set_rate_position_velocity_ned),
    InstanceMethod("set_rate_in_air", &Drone::set_rate_in_air),
    InstanceMethod("set_rate_camera_attitude", &Drone::set_rate_camera_attitude),
    InstanceMethod("set_rate_ground_speed_ned", &Drone::set_rate_ground_speed_ned),
    InstanceMethod("set_rate_gps_info", &Drone::set_rate_gps_info),
    InstanceMethod("set_rate_rc_status", &Drone::set_rate_rc_status),
    InstanceMethod("position", &Drone::position),
    InstanceMethod("health_all_ok", &Drone::health_all_ok),
    InstanceMethod("home_position", &Drone::home_position),
    InstanceMethod("battery", &Drone::battery),
    InstanceMethod("in_air", &Drone::in_air),
    InstanceMethod("armed", &Drone::armed),
    InstanceMethod("attitude_quaternion", &Drone::attitude_quaternion),
    InstanceMethod("attitude_euler_angle", &Drone::attitude_euler_angle),
    InstanceMethod("ground_speed_ned", &Drone::ground_speed_ned),
    InstanceMethod("gps_info", &Drone::gps_info),
    InstanceMethod("flight_mode", &Drone::flight_mode),
    InstanceMethod("health", &Drone::health),
    InstanceMethod("rc_status", &Drone::rc_status)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Drone", func);
  return exports;
}


Drone::Drone(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Drone>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  this->_system = info[0].As<Napi::External<mavsdk::System>>().Data();

  this->_telemetry = std::make_shared<mavsdk::Telemetry>(*this->_system);
  this->_info = std::make_shared<mavsdk::Info>(*this->_system);
}

Napi::Value Drone::get_uuid(const Napi::CallbackInfo& info) {
  uint64_t uuid = this->_system->get_uuid();

  return Napi::String::New(info.Env(), std::to_string(uuid));
}

Napi::Value Drone::get_identification(const Napi::CallbackInfo& info) {
  const std::pair<mavsdk::Info::Result, mavsdk::Info::Identification> result = this->_info->get_identification();

  Napi::Array hardware_uid = Napi::Array::New(info.Env(), 18);
  for (int i = 0; i < 18; i++) {
    hardware_uid[i] = result.second.hardware_uid[i];
	}

  return hardware_uid;
}

Napi::Value Drone::get_product(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  const std::pair<mavsdk::Info::Result, mavsdk::Info::Product> result = this->_info->get_product();

  Napi::Object obj = Napi::Object::New(env);

  obj.Set(Napi::String::New(env, "vendor_id"), result.second.vendor_id);

  std::string vendor_name = result.second.vendor_name;
  obj.Set(Napi::String::New(env, "vendor_name"), vendor_name);

  obj.Set(Napi::String::New(env, "product_id"), result.second.product_id);

  std::string product_name = result.second.product_name;
  obj.Set(Napi::String::New(env, "product_name"), product_name);

  return obj;
}

Napi::Value Drone::is_connected(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->is_connected());
}

Napi::Value Drone::has_autopilot(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_autopilot());
}

Napi::Value Drone::has_camera(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_camera());
}

Napi::Value Drone::has_gimbal(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_system->has_gimbal());
}

void Drone::set_rate_position(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_position(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate position failed: " + msg);
  }
}

void Drone::set_rate_home_position(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_home_position(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate home position failed: " + msg);
  }
}

void Drone::set_rate_attitude(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_attitude(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate attitude failed: " + msg);
  }
}

void Drone::set_rate_battery(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_battery(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate battery failed: " + msg);
  }
}

void Drone::set_rate_position_velocity_ned(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_position_velocity_ned(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate position velocity NED failed: " + msg);
  }
}

void Drone::set_rate_in_air(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_in_air(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate in air failed: " + msg);
  }
}

void Drone::set_rate_camera_attitude(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_camera_attitude(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate camera attitude failed: " + msg);
  }
}

void Drone::set_rate_ground_speed_ned(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_ground_speed_ned(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate ground speed NED failed: " + msg);
  }
}

void Drone::set_rate_gps_info(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_gps_info(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate GPS info failed: " + msg);
  }
}

void Drone::set_rate_rc_status(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_rc_status(rate);
  if (set_rate_result != mavsdk::Telemetry::Result::SUCCESS) {
    std::string msg = mavsdk::Telemetry::result_str(set_rate_result);
    throw Napi::TypeError::New(info.Env(), "Setting rate RC status failed: " + msg);
  }
}

Napi::Value Drone::position(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Position position = this->_telemetry->position();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "latitude"), position.latitude_deg);
  obj.Set(Napi::String::New(env, "longitude"), position.longitude_deg);
  obj.Set(Napi::String::New(env, "altitude"), position.relative_altitude_m);

  return obj;
}

Napi::Value Drone::health_all_ok(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_telemetry->health_all_ok());
}

Napi::Value Drone::home_position(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Position home_position = this->_telemetry->home_position();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "latitude"), home_position.latitude_deg);
  obj.Set(Napi::String::New(env, "longitude"), home_position.longitude_deg);
  obj.Set(Napi::String::New(env, "altitude"), home_position.relative_altitude_m);

  return obj;
}

Napi::Value Drone::battery(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Battery battery = this->_telemetry->battery();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "voltage"), battery.voltage_v);
  obj.Set(Napi::String::New(env, "remaining_percent"), battery.remaining_percent);

  return obj;
}

Napi::Value Drone::in_air(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_telemetry->in_air());
}

Napi::Value Drone::armed(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_telemetry->armed());
}

Napi::Value Drone::attitude_quaternion(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Quaternion attitude_quaternion = this->_telemetry->attitude_quaternion();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "w"), attitude_quaternion.w);
  obj.Set(Napi::String::New(env, "x"), attitude_quaternion.x);
  obj.Set(Napi::String::New(env, "y"), attitude_quaternion.y);
  obj.Set(Napi::String::New(env, "z"), attitude_quaternion.y);

  return obj;
}

Napi::Value Drone::attitude_euler_angle(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::EulerAngle attitude_euler_angle = this->_telemetry->attitude_euler_angle();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "roll"), attitude_euler_angle.roll_deg);
  obj.Set(Napi::String::New(env, "pitch"), attitude_euler_angle.pitch_deg);
  obj.Set(Napi::String::New(env, "yaw"), attitude_euler_angle.yaw_deg);

  return obj;
}

Napi::Value Drone::ground_speed_ned(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::GroundSpeedNED ground_speed_ned = this->_telemetry->ground_speed_ned();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "velocity_north"), ground_speed_ned.velocity_north_m_s);
  obj.Set(Napi::String::New(env, "velocity_east"), ground_speed_ned.velocity_east_m_s);
  obj.Set(Napi::String::New(env, "velocity_down"), ground_speed_ned.velocity_down_m_s);

  return obj;
}

Napi::Value Drone::gps_info(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::GPSInfo gps_info = this->_telemetry->gps_info();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "num_satellites"), gps_info.num_satellites);
  //Fix type (0: no GPS, 1: no fix, 2: 2D fix, 3: 3D fix, 4: DGPS fix, 5: RTK float, 6: RTK fixed).
  obj.Set(Napi::String::New(env, "fix_type"), gps_info.fix_type);

  return obj;
}

Napi::Value Drone::flight_mode(const Napi::CallbackInfo& info) {
  return Napi::String::New(info.Env(), this->_telemetry->flight_mode_str(this->_telemetry->flight_mode()));
}

Napi::Value Drone::health(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Health health = this->_telemetry->health();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "gyrometer_calibration_ok"), health.gyrometer_calibration_ok);
  obj.Set(Napi::String::New(env, "accelerometer_calibration_ok"), health.accelerometer_calibration_ok);
  obj.Set(Napi::String::New(env, "magnetometer_calibration_ok"), health.magnetometer_calibration_ok);
  obj.Set(Napi::String::New(env, "level_calibration_ok"), health.level_calibration_ok);
  obj.Set(Napi::String::New(env, "local_position_ok"), health.local_position_ok);
  obj.Set(Napi::String::New(env, "global_position_ok"), health.global_position_ok);
  obj.Set(Napi::String::New(env, "home_position_ok"), health.home_position_ok);

  return obj;
}

Napi::Value Drone::rc_status(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::RCStatus rc_status = this->_telemetry->rc_status();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "available_once"), rc_status.available_once);
  obj.Set(Napi::String::New(env, "available"), rc_status.available);
  obj.Set(Napi::String::New(env, "signal_strength_percent"), rc_status.signal_strength_percent);

  return obj;
}
