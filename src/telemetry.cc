#include <iostream>

#include "telemetry.h"
#include "system.h"

using namespace mavjs;

Napi::FunctionReference Telemetry::constructor;

Napi::Object Telemetry::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "Telemetry", {
    InstanceMethod("set_rate_position_velocity_ned", &Telemetry::set_rate_position_velocity_ned),
    InstanceMethod("set_rate_position", &Telemetry::set_rate_position),
    InstanceMethod("set_rate_home_position", &Telemetry::set_rate_home_position),
    InstanceMethod("set_rate_in_air", &Telemetry::set_rate_in_air),
    InstanceMethod("set_rate_ground_speed_ned", &Telemetry::set_rate_ground_speed_ned),
    InstanceMethod("set_rate_imu_reading_ned", &Telemetry::set_rate_imu_reading_ned),
    InstanceMethod("set_rate_gps_info", &Telemetry::set_rate_gps_info),
    InstanceMethod("set_rate_battery", &Telemetry::set_rate_battery),
    InstanceMethod("set_rate_rc_status", &Telemetry::set_rate_rc_status),
    InstanceMethod("set_rate_actuator_control_target", &Telemetry::set_rate_actuator_control_target),
    InstanceMethod("set_rate_actuator_output_status", &Telemetry::set_rate_actuator_output_status),
    InstanceMethod("position_velocity_ned", &Telemetry::position_velocity_ned),
    InstanceMethod("position", &Telemetry::position),
    InstanceMethod("home_position", &Telemetry::home_position),
    InstanceMethod("status_text", &Telemetry::status_text),
    InstanceMethod("in_air", &Telemetry::in_air),
    InstanceMethod("landed_state", &Telemetry::landed_state),
    InstanceMethod("armed", &Telemetry::armed),
    InstanceMethod("attitude_quaternion", &Telemetry::attitude_quaternion),
    InstanceMethod("attitude_euler_angle", &Telemetry::attitude_euler_angle),
    InstanceMethod("attitude_angular_velocity_body", &Telemetry::attitude_angular_velocity_body),
    InstanceMethod("ground_speed_ned", &Telemetry::ground_speed_ned),
    InstanceMethod("imu_reading_ned", &Telemetry::imu_reading_ned),
    InstanceMethod("gps_info", &Telemetry::gps_info),
    InstanceMethod("battery", &Telemetry::battery),
    InstanceMethod("flight_mode", &Telemetry::flight_mode),
    InstanceMethod("health", &Telemetry::health),
    InstanceMethod("health_all_ok", &Telemetry::health_all_ok),
    InstanceMethod("rc_status", &Telemetry::rc_status),
    InstanceMethod("actuator_control_target", &Telemetry::actuator_control_target),
    InstanceMethod("actuator_output_status", &Telemetry::actuator_output_status)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("Telemetry", func);
  return exports;
}

Telemetry::Telemetry(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Telemetry>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  
  auto system = info[0].As<Napi::External<mavsdk::System>>().Data();
  this->_telemetry = std::make_shared<mavsdk::Telemetry>(*system);
}

Napi::Value Telemetry::set_rate_position_velocity_ned(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_position_velocity_ned(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_position(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_position(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_home_position(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_home_position(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_in_air(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_in_air(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_ground_speed_ned(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_ground_speed_ned(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_imu_reading_ned(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_imu_reading_ned(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_gps_info(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_gps_info(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_battery(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_battery(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_rc_status(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_rc_status(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_actuator_control_target(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_actuator_control_target(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::set_rate_actuator_output_status(const Napi::CallbackInfo& info) {
  double rate = info[0].As<Napi::Number>().DoubleValue();
  const mavsdk::Telemetry::Result set_rate_result = this->_telemetry->set_rate_actuator_output_status(rate);
  return Napi::String::New(info.Env(), mavsdk::Telemetry::result_str(set_rate_result));
}

Napi::Value Telemetry::position_velocity_ned(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::PositionVelocityNED position_velocity_ned = this->_telemetry->position_velocity_ned();

  Napi::Object position = Napi::Object::New(env);
  position.Set(Napi::String::New(env, "down_m"), position_velocity_ned.position.down_m);
  position.Set(Napi::String::New(env, "east_m"), position_velocity_ned.position.east_m);
  position.Set(Napi::String::New(env, "north_m"), position_velocity_ned.position.north_m);

  Napi::Object velocity = Napi::Object::New(env);
  velocity.Set(Napi::String::New(env, "down_m_s"), position_velocity_ned.velocity.down_m_s);
  velocity.Set(Napi::String::New(env, "east_m_s"), position_velocity_ned.velocity.east_m_s);
  velocity.Set(Napi::String::New(env, "north_m_s"), position_velocity_ned.velocity.north_m_s);

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "position"), position);
  obj.Set(Napi::String::New(env, "velocity"), velocity);
  return obj;
}

Napi::Value Telemetry::position(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Position position = this->_telemetry->position();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "latitude_deg"), position.latitude_deg);
  obj.Set(Napi::String::New(env, "longitude_deg"), position.longitude_deg);
  obj.Set(Napi::String::New(env, "absolute_altitude_m"), position.absolute_altitude_m);
  obj.Set(Napi::String::New(env, "relative_altitude_m"), position.relative_altitude_m);

  return obj;
}

Napi::Value Telemetry::home_position(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Position home_position = this->_telemetry->home_position();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "latitude_deg"), home_position.latitude_deg);
  obj.Set(Napi::String::New(env, "longitude_deg"), home_position.longitude_deg);
  obj.Set(Napi::String::New(env, "absolute_altitude_m"), home_position.absolute_altitude_m);
  obj.Set(Napi::String::New(env, "relative_altitude_m"), home_position.relative_altitude_m);

  return obj;
}

Napi::Value Telemetry::status_text(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  return Napi::String::New(info.Env(), this->_telemetry->status_text().text);
}

Napi::Value Telemetry::in_air(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_telemetry->in_air());  
}

Napi::Value Telemetry::landed_state(const Napi::CallbackInfo& info) {
  return Napi::String::New(info.Env(), mavsdk::Telemetry::landed_state_str(this->_telemetry->landed_state()));
}

Napi::Value Telemetry::armed(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_telemetry->armed());  
}

Napi::Value Telemetry::attitude_quaternion(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Quaternion attitude_quaternion = this->_telemetry->attitude_quaternion();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "w"), attitude_quaternion.w);
  obj.Set(Napi::String::New(env, "x"), attitude_quaternion.x);
  obj.Set(Napi::String::New(env, "y"), attitude_quaternion.y);
  obj.Set(Napi::String::New(env, "z"), attitude_quaternion.y);

  return obj;
}

Napi::Value Telemetry::attitude_euler_angle(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::EulerAngle attitude_euler_angle = this->_telemetry->attitude_euler_angle();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "roll_deg"), attitude_euler_angle.roll_deg);
  obj.Set(Napi::String::New(env, "pitch_deg"), attitude_euler_angle.pitch_deg);
  obj.Set(Napi::String::New(env, "yaw_deg"), attitude_euler_angle.yaw_deg);

  return obj;
}

Napi::Value Telemetry::attitude_angular_velocity_body(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::AngularVelocityBody attitude_angular_velocity_body = this->_telemetry->attitude_angular_velocity_body();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "roll_rad_s"), attitude_angular_velocity_body.roll_rad_s);
  obj.Set(Napi::String::New(env, "pitch_rad_s"), attitude_angular_velocity_body.pitch_rad_s);
  obj.Set(Napi::String::New(env, "yaw_rad_s"), attitude_angular_velocity_body.yaw_rad_s);

  return obj;
}

Napi::Value Telemetry::ground_speed_ned(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::GroundSpeedNED ground_speed_ned = this->_telemetry->ground_speed_ned();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "velocity_north_m_s"), ground_speed_ned.velocity_north_m_s);
  obj.Set(Napi::String::New(env, "velocity_east_m_s"), ground_speed_ned.velocity_east_m_s);
  obj.Set(Napi::String::New(env, "velocity_down_m_s"), ground_speed_ned.velocity_down_m_s);

  return obj;
}

Napi::Value Telemetry::imu_reading_ned(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::IMUReadingNED imu_reading_ned = this->_telemetry->imu_reading_ned();

  Napi::Object acceleration = Napi::Object::New(env);
  acceleration.Set(Napi::String::New(env, "down_m_s2"), imu_reading_ned.acceleration.down_m_s2);
  acceleration.Set(Napi::String::New(env, "east_m_s2"), imu_reading_ned.acceleration.east_m_s2);
  acceleration.Set(Napi::String::New(env, "north_m_s2"), imu_reading_ned.acceleration.north_m_s2);

  Napi::Object angular_velocity = Napi::Object::New(env);
  angular_velocity.Set(Napi::String::New(env, "down_rad_s"), imu_reading_ned.angular_velocity.down_rad_s);
  angular_velocity.Set(Napi::String::New(env, "east_rad_s"), imu_reading_ned.angular_velocity.east_rad_s);
  angular_velocity.Set(Napi::String::New(env, "north_rad_s"), imu_reading_ned.angular_velocity.north_rad_s);

  Napi::Object magnetic_field = Napi::Object::New(env);
  magnetic_field.Set(Napi::String::New(env, "down_gauss"), imu_reading_ned.magnetic_field.down_gauss);
  magnetic_field.Set(Napi::String::New(env, "east_gauss"), imu_reading_ned.magnetic_field.east_gauss);
  magnetic_field.Set(Napi::String::New(env, "north_gauss"), imu_reading_ned.magnetic_field.north_gauss);

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "acceleration"), acceleration);
  obj.Set(Napi::String::New(env, "angular_velocity"), angular_velocity);
  obj.Set(Napi::String::New(env, "magnetic_field"), magnetic_field);
  obj.Set(Napi::String::New(env, "temperature_degC"), imu_reading_ned.temperature_degC);

  return obj;
}

Napi::Value Telemetry::gps_info(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::GPSInfo gps_info = this->_telemetry->gps_info();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "num_satellites"), gps_info.num_satellites);
  //Fix type (0: no GPS, 1: no fix, 2: 2D fix, 3: 3D fix, 4: DGPS fix, 5: RTK float, 6: RTK fixed).
  obj.Set(Napi::String::New(env, "fix_type"), gps_info.fix_type);

  return obj;
}

Napi::Value Telemetry::battery(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::Battery battery = this->_telemetry->battery();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "voltage"), battery.voltage_v);
  obj.Set(Napi::String::New(env, "remaining_percent"), battery.remaining_percent);

  return obj;
}

Napi::Value Telemetry::flight_mode(const Napi::CallbackInfo& info) {
  return Napi::String::New(info.Env(), this->_telemetry->flight_mode_str(this->_telemetry->flight_mode()));
}

Napi::Value Telemetry::health(const Napi::CallbackInfo& info) {
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

Napi::Value Telemetry::health_all_ok(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_telemetry->health_all_ok());
}

Napi::Value Telemetry::rc_status(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::RCStatus rc_status = this->_telemetry->rc_status();

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "available_once"), rc_status.available_once);
  obj.Set(Napi::String::New(env, "available"), rc_status.available);
  obj.Set(Napi::String::New(env, "signal_strength_percent"), rc_status.signal_strength_percent);

  return obj;
}

Napi::Value Telemetry::actuator_control_target(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::ActuatorControlTarget actuator_control_target = this->_telemetry->actuator_control_target();

  Napi::Array controls = Napi::Array::New(info.Env(), 8);
  for (int i = 0; i < 8; i++) {
    controls[i] = actuator_control_target.controls[i];
	}

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "group"), actuator_control_target.group);
  obj.Set(Napi::String::New(env, "controls"), controls);

  return obj;
}

Napi::Value Telemetry::actuator_output_status(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  mavsdk::Telemetry::ActuatorOutputStatus actuator_output_status = this->_telemetry->actuator_output_status();

  Napi::Array actuator = Napi::Array::New(info.Env(), 32);
  for (int i = 0; i < 32; i++) {
    actuator[i] = actuator_output_status.actuator[i];
	}

  Napi::Object obj = Napi::Object::New(env);
  obj.Set(Napi::String::New(env, "active"), actuator_output_status.active);
  obj.Set(Napi::String::New(env, "actuator"), actuator);

  return obj;
}