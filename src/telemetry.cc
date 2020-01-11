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
    InstanceMethod("actuator_output_status", &Telemetry::actuator_output_status),
    InstanceMethod("position_velocity_ned_async", &Telemetry::position_velocity_ned_async),
    InstanceMethod("position_async", &Telemetry::position_async),
    InstanceMethod("home_position_async", &Telemetry::home_position_async),
    InstanceMethod("in_air_async", &Telemetry::in_air_async),
    InstanceMethod("status_text_async", &Telemetry::status_text_async),
    InstanceMethod("armed_async", &Telemetry::armed_async),
    InstanceMethod("attitude_quaternion_async", &Telemetry::attitude_quaternion_async),
    InstanceMethod("attitude_euler_angle_async", &Telemetry::attitude_euler_angle_async),
    InstanceMethod("attitude_angular_velocity_body_async", &Telemetry::attitude_angular_velocity_body_async),
    InstanceMethod("ground_speed_ned_async", &Telemetry::ground_speed_ned_async),
    InstanceMethod("imu_reading_ned_async", &Telemetry::imu_reading_ned_async), 
    InstanceMethod("gps_info_async", &Telemetry::gps_info_async),
    InstanceMethod("battery_async", &Telemetry::battery_async),
    InstanceMethod("flight_mode_async", &Telemetry::flight_mode_async),
    InstanceMethod("health_async", &Telemetry::health_async),
    InstanceMethod("health_all_ok_async", &Telemetry::health_all_ok_async),
    InstanceMethod("landed_state_async", &Telemetry::landed_state_async),
    InstanceMethod("actuator_control_target_async", &Telemetry::actuator_control_target_async),
    InstanceMethod("actuator_output_status_async", &Telemetry::actuator_output_status_async),
    InstanceMethod("rc_status_async", &Telemetry::rc_status_async)
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
  return Napi::Number::New(info.Env(), double(this->_telemetry->landed_state()));
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
  return Napi::Number::New(info.Env(), double(this->_telemetry->flight_mode()));
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

void Telemetry::position_velocity_ned_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_position_velocity_ned_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "position_velocity_ned_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_position_velocity_ned_async = [ts_position_velocity_ned_async](mavsdk::Telemetry::PositionVelocityNED type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::PositionVelocityNED * position_velocity_ned ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object position = Napi::Object::New(env);
      position.Set(Napi::String::New(env, "down_m"), position_velocity_ned->position.down_m);
      position.Set(Napi::String::New(env, "east_m"), position_velocity_ned->position.east_m);
      position.Set(Napi::String::New(env, "north_m"), position_velocity_ned->position.north_m);

      Napi::Object velocity = Napi::Object::New(env);
      velocity.Set(Napi::String::New(env, "down_m_s"), position_velocity_ned->velocity.down_m_s);
      velocity.Set(Napi::String::New(env, "east_m_s"), position_velocity_ned->velocity.east_m_s);
      velocity.Set(Napi::String::New(env, "north_m_s"), position_velocity_ned->velocity.north_m_s);

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "position"), position);
      obj.Set(Napi::String::New(env, "velocity"), velocity);
      
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete position_velocity_ned;
    };

    mavsdk::Telemetry::PositionVelocityNED * value = new mavsdk::Telemetry::PositionVelocityNED(type);
    
    napi_status status = ts_position_velocity_ned_async.BlockingCall(value, callback);
  };

  this->_telemetry->position_velocity_ned_async(_on_position_velocity_ned_async);
}

void Telemetry::position_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_position_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "position_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_position_async = [ts_position_async](mavsdk::Telemetry::Position type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::Position * position ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "latitude_deg"), position->latitude_deg);
      obj.Set(Napi::String::New(env, "longitude_deg"), position->longitude_deg);
      obj.Set(Napi::String::New(env, "absolute_altitude_m"), position->absolute_altitude_m);
      obj.Set(Napi::String::New(env, "relative_altitude_m"), position->relative_altitude_m);
      
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete position;
    };

    mavsdk::Telemetry::Position * value = new mavsdk::Telemetry::Position(type);
    
    napi_status status = ts_position_async.BlockingCall(value, callback);
  };

  this->_telemetry->position_async(_on_position_async);
}

void Telemetry::home_position_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_home_position_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "home_position_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_home_position_async = [ts_home_position_async](mavsdk::Telemetry::Position type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::Position * home_position ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "latitude_deg"), home_position->latitude_deg);
      obj.Set(Napi::String::New(env, "longitude_deg"), home_position->longitude_deg);
      obj.Set(Napi::String::New(env, "absolute_altitude_m"), home_position->absolute_altitude_m);
      obj.Set(Napi::String::New(env, "relative_altitude_m"), home_position->relative_altitude_m);
      
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete home_position;
    };

    mavsdk::Telemetry::Position * value = new mavsdk::Telemetry::Position(type);
    
    napi_status status = ts_home_position_async.BlockingCall(value, callback);
  };

  this->_telemetry->home_position_async(_on_home_position_async);
}

void Telemetry::in_air_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_in_air_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "in_air_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_in_air_async = [ts_in_air_async](bool type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, bool * in_air ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( { Napi::Boolean::New(env, in_air) } );
    
      // We're finished with the data.
      delete in_air;
    };

    bool * value = new bool(type);
    
    napi_status status = ts_in_air_async.BlockingCall(value, callback);
  };

  this->_telemetry->in_air_async(_on_in_air_async);
}

void Telemetry::status_text_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_status_text_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "status_text_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_status_text_async = [ts_status_text_async](mavsdk::Telemetry::StatusText type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::StatusText * status_text ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( { Napi::String::New(env, status_text->text) } );
    
      // We're finished with the data.
      delete status_text;
    };

    mavsdk::Telemetry::StatusText * value = new mavsdk::Telemetry::StatusText(type);
    
    napi_status status = ts_status_text_async.BlockingCall(value, callback);
  };

  this->_telemetry->status_text_async(_on_status_text_async);
}

void Telemetry::armed_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_armed_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "armed_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_armed_async = [ts_armed_async](bool type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, bool * armed ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( { Napi::Boolean::New(env, armed) } );
    
      // We're finished with the data.
      delete armed;
    };

    bool * value = new bool(type);
    
    napi_status status = ts_armed_async.BlockingCall(value, callback);
  };

  this->_telemetry->armed_async(_on_armed_async);
}

void Telemetry::attitude_quaternion_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_attitude_quaternion_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "attitude_quaternion_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_attitude_quaternion_async = [ts_attitude_quaternion_async](mavsdk::Telemetry::Quaternion type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::Quaternion * attitude_quaternion ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "w"), attitude_quaternion->w);
      obj.Set(Napi::String::New(env, "x"), attitude_quaternion->x);
      obj.Set(Napi::String::New(env, "y"), attitude_quaternion->y);
      obj.Set(Napi::String::New(env, "z"), attitude_quaternion->y);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete attitude_quaternion;
    };

    mavsdk::Telemetry::Quaternion * value = new mavsdk::Telemetry::Quaternion(type);
    
    napi_status status = ts_attitude_quaternion_async.BlockingCall(value, callback);
  };

  this->_telemetry->attitude_quaternion_async(_on_attitude_quaternion_async);
}

void Telemetry::attitude_euler_angle_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_attitude_euler_angle_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "attitude_euler_angle_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_attitude_euler_angle_async = [ts_attitude_euler_angle_async](mavsdk::Telemetry::EulerAngle type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::EulerAngle * attitude_euler_angle ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "roll_deg"), attitude_euler_angle->roll_deg);
      obj.Set(Napi::String::New(env, "pitch_deg"), attitude_euler_angle->pitch_deg);
      obj.Set(Napi::String::New(env, "yaw_deg"), attitude_euler_angle->yaw_deg);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete attitude_euler_angle;
    };

    mavsdk::Telemetry::EulerAngle * value = new mavsdk::Telemetry::EulerAngle(type);
    
    napi_status status = ts_attitude_euler_angle_async.BlockingCall(value, callback);
  };

  this->_telemetry->attitude_euler_angle_async(_on_attitude_euler_angle_async);
}

void Telemetry::attitude_angular_velocity_body_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_attitude_angular_velocity_body_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "attitude_angular_velocity_body_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_attitude_angular_velocity_body_async = [ts_attitude_angular_velocity_body_async](mavsdk::Telemetry::AngularVelocityBody type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::AngularVelocityBody * attitude_angular_velocity_body ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "roll_rad_s"), attitude_angular_velocity_body->roll_rad_s);
      obj.Set(Napi::String::New(env, "pitch_rad_s"), attitude_angular_velocity_body->pitch_rad_s);
      obj.Set(Napi::String::New(env, "yaw_rad_s"), attitude_angular_velocity_body->yaw_rad_s);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete attitude_angular_velocity_body;
    };

    mavsdk::Telemetry::AngularVelocityBody * value = new mavsdk::Telemetry::AngularVelocityBody(type);
    
    napi_status status = ts_attitude_angular_velocity_body_async.BlockingCall(value, callback);
  };

  this->_telemetry->attitude_angular_velocity_body_async(_on_attitude_angular_velocity_body_async);
}

void Telemetry::ground_speed_ned_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_ground_speed_ned_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "ground_speed_ned_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_ground_speed_ned_async = [ts_ground_speed_ned_async](mavsdk::Telemetry::GroundSpeedNED type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::GroundSpeedNED * ground_speed_ned ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "velocity_north_m_s"), ground_speed_ned->velocity_north_m_s);
      obj.Set(Napi::String::New(env, "velocity_east_m_s"), ground_speed_ned->velocity_east_m_s);
      obj.Set(Napi::String::New(env, "velocity_down_m_s"), ground_speed_ned->velocity_down_m_s);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete ground_speed_ned;
    };

    mavsdk::Telemetry::GroundSpeedNED * value = new mavsdk::Telemetry::GroundSpeedNED(type);
    
    napi_status status = ts_ground_speed_ned_async.BlockingCall(value, callback);
  };

  this->_telemetry->ground_speed_ned_async(_on_ground_speed_ned_async);
}

void Telemetry::imu_reading_ned_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_imu_reading_ned_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "imu_reading_ned_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_imu_reading_ned_async = [ts_imu_reading_ned_async](mavsdk::Telemetry::IMUReadingNED type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::IMUReadingNED * imu_reading_ned ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object acceleration = Napi::Object::New(env);
      acceleration.Set(Napi::String::New(env, "down_m_s2"), imu_reading_ned->acceleration.down_m_s2);
      acceleration.Set(Napi::String::New(env, "east_m_s2"), imu_reading_ned->acceleration.east_m_s2);
      acceleration.Set(Napi::String::New(env, "north_m_s2"), imu_reading_ned->acceleration.north_m_s2);

      Napi::Object angular_velocity = Napi::Object::New(env);
      angular_velocity.Set(Napi::String::New(env, "down_rad_s"), imu_reading_ned->angular_velocity.down_rad_s);
      angular_velocity.Set(Napi::String::New(env, "east_rad_s"), imu_reading_ned->angular_velocity.east_rad_s);
      angular_velocity.Set(Napi::String::New(env, "north_rad_s"), imu_reading_ned->angular_velocity.north_rad_s);

      Napi::Object magnetic_field = Napi::Object::New(env);
      magnetic_field.Set(Napi::String::New(env, "down_gauss"), imu_reading_ned->magnetic_field.down_gauss);
      magnetic_field.Set(Napi::String::New(env, "east_gauss"), imu_reading_ned->magnetic_field.east_gauss);
      magnetic_field.Set(Napi::String::New(env, "north_gauss"), imu_reading_ned->magnetic_field.north_gauss);

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "acceleration"), acceleration);
      obj.Set(Napi::String::New(env, "angular_velocity"), angular_velocity);
      obj.Set(Napi::String::New(env, "magnetic_field"), magnetic_field);
      obj.Set(Napi::String::New(env, "temperature_degC"), imu_reading_ned->temperature_degC);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete imu_reading_ned;
    };

    mavsdk::Telemetry::IMUReadingNED * value = new mavsdk::Telemetry::IMUReadingNED(type);
    
    napi_status status = ts_imu_reading_ned_async.BlockingCall(value, callback);
  };

  this->_telemetry->imu_reading_ned_async(_on_imu_reading_ned_async);
}

void Telemetry::gps_info_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_gps_info_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "gps_info_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_gps_info_async = [ts_gps_info_async](mavsdk::Telemetry::GPSInfo type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::GPSInfo * gps_info ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "num_satellites"), gps_info->num_satellites);
      //Fix type (0: no GPS, 1: no fix, 2: 2D fix, 3: 3D fix, 4: DGPS fix, 5: RTK float, 6: RTK fixed).
      obj.Set(Napi::String::New(env, "fix_type"), gps_info->fix_type);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete gps_info;
    };

    mavsdk::Telemetry::GPSInfo * value = new mavsdk::Telemetry::GPSInfo(type);
    
    napi_status status = ts_gps_info_async.BlockingCall(value, callback);
  };

  this->_telemetry->gps_info_async(_on_gps_info_async);
}

void Telemetry::battery_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_battery_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "battery_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_battery_async = [ts_battery_async](mavsdk::Telemetry::Battery type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::Battery * battery ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "voltage"), battery->voltage_v);
      obj.Set(Napi::String::New(env, "remaining_percent"), battery->remaining_percent);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete battery;
    };

    mavsdk::Telemetry::Battery * value = new mavsdk::Telemetry::Battery(type);
    
    napi_status status = ts_battery_async.BlockingCall(value, callback);
  };

  this->_telemetry->battery_async(_on_battery_async);
}

void Telemetry::flight_mode_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_flight_mode_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "flight_mode_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_flight_mode_async = [ts_flight_mode_async](mavsdk::Telemetry::FlightMode type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, double * flight_mode ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      jsCallback.Call( { Napi::Number::New(env, *flight_mode) } );
    
      // We're finished with the data.
      delete flight_mode;
    };

    auto idx = double(type);
    double * value = new double(idx);    
    
    napi_status status = ts_flight_mode_async.BlockingCall(value, callback);
  };

  this->_telemetry->flight_mode_async(_on_flight_mode_async);
}

void Telemetry::health_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_health_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "health_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_health_async = [ts_health_async](mavsdk::Telemetry::Health type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::Health * health ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "gyrometer_calibration_ok"), health->gyrometer_calibration_ok);
      obj.Set(Napi::String::New(env, "accelerometer_calibration_ok"), health->accelerometer_calibration_ok);
      obj.Set(Napi::String::New(env, "magnetometer_calibration_ok"), health->magnetometer_calibration_ok);
      obj.Set(Napi::String::New(env, "level_calibration_ok"), health->level_calibration_ok);
      obj.Set(Napi::String::New(env, "local_position_ok"), health->local_position_ok);
      obj.Set(Napi::String::New(env, "global_position_ok"), health->global_position_ok);
      obj.Set(Napi::String::New(env, "home_position_ok"), health->home_position_ok);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete health;
    };

    mavsdk::Telemetry::Health * value = new mavsdk::Telemetry::Health(type);
    
    napi_status status = ts_health_async.BlockingCall(value, callback);
  };

  this->_telemetry->health_async(_on_health_async);
}

void Telemetry::health_all_ok_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_health_all_ok_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "health_all_ok_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_health_all_ok_async = [ts_health_all_ok_async](bool type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, bool * health_all_ok ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.
      jsCallback.Call( { Napi::Boolean::New(env, health_all_ok) } );
    
      // We're finished with the data.
      delete health_all_ok;
    };

    bool * value = new bool(type);
    
    napi_status status = ts_health_all_ok_async.BlockingCall(value, callback);
  };

  this->_telemetry->health_all_ok_async(_on_health_all_ok_async);
}

void Telemetry::landed_state_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_landed_state_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "landed_state_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_landed_state_async = [ts_landed_state_async](mavsdk::Telemetry::LandedState type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, double * landed_state ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      jsCallback.Call( { Napi::Number::New(env, *landed_state) } );
    
      // We're finished with the data.
      delete landed_state;
    };

    auto idx = double(type);
    double * value = new double(idx);    
    
    napi_status status = ts_landed_state_async.BlockingCall(value, callback);
  };

  this->_telemetry->landed_state_async(_on_landed_state_async);
}

void Telemetry::actuator_control_target_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_actuator_control_target_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "actuator_control_target_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_actuator_control_target_async = [ts_actuator_control_target_async](mavsdk::Telemetry::ActuatorControlTarget type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::ActuatorControlTarget * actuator_control_target ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Array controls = Napi::Array::New(env, 8);
      for (int i = 0; i < 8; i++) {
        controls[i] = actuator_control_target->controls[i];
      }

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "group"), actuator_control_target->group);
      obj.Set(Napi::String::New(env, "controls"), controls);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete actuator_control_target;
    };

    mavsdk::Telemetry::ActuatorControlTarget * value = new mavsdk::Telemetry::ActuatorControlTarget(type);
    
    napi_status status = ts_actuator_control_target_async.BlockingCall(value, callback);
  };

  this->_telemetry->actuator_control_target_async(_on_actuator_control_target_async);
}

void Telemetry::actuator_output_status_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_actuator_output_status_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "actuator_output_status_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_actuator_output_status_async = [ts_actuator_output_status_async](mavsdk::Telemetry::ActuatorOutputStatus type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::ActuatorOutputStatus * actuator_output_status ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Array actuator = Napi::Array::New(env, 32);
      for (int i = 0; i < 32; i++) {
        actuator[i] = actuator_output_status->actuator[i];
      }

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "active"), actuator_output_status->active);
      obj.Set(Napi::String::New(env, "actuator"), actuator);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete actuator_output_status;
    };

    mavsdk::Telemetry::ActuatorOutputStatus * value = new mavsdk::Telemetry::ActuatorOutputStatus(type);
    
    napi_status status = ts_actuator_output_status_async.BlockingCall(value, callback);
  };

  this->_telemetry->actuator_output_status_async(_on_actuator_output_status_async);
}

void Telemetry::rc_status_async(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  auto ts_rc_status_async = Napi::ThreadSafeFunction::New(
      env,
      info[0].As<Napi::Function>(),  // JavaScript function called asynchronously
      "rc_status_async",        // Name
      0,                             // Unlimited queue
      1,                             // Only one thread will use this initially
      []( Napi::Env ) {  
              // Finalizer used to clean threads up
      });
  
  auto _on_rc_status_async = [ts_rc_status_async](mavsdk::Telemetry::RCStatus type) -> void {
    auto callback = []( Napi::Env env, Napi::Function jsCallback, mavsdk::Telemetry::RCStatus * rc_status ) {
      // Transform native data into JS data, passing it to the provided 
      // `jsCallback` -- the TSFN's JavaScript function.

      Napi::Object obj = Napi::Object::New(env);
      obj.Set(Napi::String::New(env, "available_once"), rc_status->available_once);
      obj.Set(Napi::String::New(env, "available"), rc_status->available);
      obj.Set(Napi::String::New(env, "signal_strength_percent"), rc_status->signal_strength_percent);
      jsCallback.Call( { obj } );
    
      // We're finished with the data.
      delete rc_status;
    };

    mavsdk::Telemetry::RCStatus * value = new mavsdk::Telemetry::RCStatus(type);
    
    napi_status status = ts_rc_status_async.BlockingCall(value, callback);
  };

  this->_telemetry->rc_status_async(_on_rc_status_async);
}