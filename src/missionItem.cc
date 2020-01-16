#include <iostream>

#include "missionItem.h"

using namespace mavjs;

static mavsdk::MissionItem::CameraAction _camera_actions[6] = {
                mavsdk::MissionItem::CameraAction::TAKE_PHOTO,
                mavsdk::MissionItem::CameraAction::START_PHOTO_INTERVAL,
                mavsdk::MissionItem::CameraAction::STOP_PHOTO_INTERVAL,
                mavsdk::MissionItem::CameraAction::START_VIDEO,
                mavsdk::MissionItem::CameraAction::STOP_VIDEO,
                mavsdk::MissionItem::CameraAction::NONE
            };

Napi::FunctionReference MissionItem::constructor;

Napi::Object MissionItem::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  Napi::Function func = DefineClass(env, "MissionItem", {
    InstanceMethod("set_position", &MissionItem::set_position),
    InstanceMethod("set_relative_altitude", &MissionItem::set_relative_altitude),
    InstanceMethod("set_fly_through", &MissionItem::set_fly_through),
    InstanceMethod("set_acceptance_radius", &MissionItem::set_acceptance_radius),
    InstanceMethod("set_speed", &MissionItem::set_speed),
    InstanceMethod("set_gimbal_pitch_and_yaw", &MissionItem::set_gimbal_pitch_and_yaw),
    InstanceMethod("set_loiter_time", &MissionItem::set_loiter_time),
    InstanceMethod("set_camera_action", &MissionItem::set_camera_action),
    InstanceMethod("set_camera_photo_interval", &MissionItem::set_camera_photo_interval),
    InstanceMethod("get_latitude_deg", &MissionItem::get_latitude_deg),
    InstanceMethod("get_longitude_deg", &MissionItem::get_longitude_deg),
    InstanceMethod("has_position_set", &MissionItem::has_position_set),
    InstanceMethod("get_relative_altitude_m", &MissionItem::get_relative_altitude_m),
    InstanceMethod("get_fly_through", &MissionItem::get_fly_through),
    InstanceMethod("get_acceptance_radius_m", &MissionItem::get_acceptance_radius_m),
    InstanceMethod("get_speed_m_s", &MissionItem::get_speed_m_s),
    InstanceMethod("get_gimbal_pitch_deg", &MissionItem::get_gimbal_pitch_deg),
    InstanceMethod("get_gimbal_yaw_deg", &MissionItem::get_gimbal_yaw_deg),
    InstanceMethod("get_loiter_time_s", &MissionItem::get_loiter_time_s),
    InstanceMethod("get_camera_action", &MissionItem::get_camera_action),
    InstanceMethod("get_camera_photo_interval_s", &MissionItem::get_camera_photo_interval_s),
    InstanceMethod("to_object", &MissionItem::to_object)
  });

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("MissionItem", func);
  return exports;
}

MissionItem::MissionItem(const Napi::CallbackInfo& info) : Napi::ObjectWrap<MissionItem>(info)  {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  std::shared_ptr<mavsdk::MissionItem> new_item(new mavsdk::MissionItem());
  this->_mission_item = new_item;
}

void MissionItem::set_position(const Napi::CallbackInfo& info) {
  double latitude_deg = info[0].As<Napi::Number>().DoubleValue();
  double longitude_deg = info[1].As<Napi::Number>().DoubleValue();
  this->_mission_item->set_position(latitude_deg, longitude_deg);
}

void MissionItem::set_relative_altitude(const Napi::CallbackInfo& info) {
  float altitude_m = info[0].As<Napi::Number>().FloatValue();
  this->_mission_item->set_relative_altitude(altitude_m);
}

void MissionItem::set_fly_through(const Napi::CallbackInfo& info) {
  bool fly_through = info[0].As<Napi::Boolean>();
  this->_mission_item->set_fly_through(fly_through);
}

void MissionItem::set_acceptance_radius(const Napi::CallbackInfo& info) {
  float radius_m = info[0].As<Napi::Number>().FloatValue();
  this->_mission_item->set_acceptance_radius(radius_m);
}

void MissionItem::set_speed(const Napi::CallbackInfo& info) {
  float speed_m_s = info[0].As<Napi::Number>().FloatValue();
  this->_mission_item->set_speed(speed_m_s);
}

void MissionItem::set_gimbal_pitch_and_yaw(const Napi::CallbackInfo& info) {
  float pitch_deg = info[0].As<Napi::Number>().FloatValue();
  float yaw_deg = info[1].As<Napi::Number>().FloatValue();
  this->_mission_item->set_gimbal_pitch_and_yaw(pitch_deg, yaw_deg);
}

void MissionItem::set_loiter_time(const Napi::CallbackInfo& info) {
  float loiter_time_s = info[0].As<Napi::Number>().FloatValue();
  this->_mission_item->set_loiter_time(loiter_time_s);
}

void MissionItem::set_camera_action(const Napi::CallbackInfo& info) {
  mavsdk::MissionItem::CameraAction action = _camera_actions[info[0].As<Napi::Number>().Uint32Value()];
  this->_mission_item->set_camera_action(action);
}

void MissionItem::set_camera_photo_interval(const Napi::CallbackInfo& info) {
  double interval_s = info[0].As<Napi::Number>().DoubleValue();
  this->_mission_item->set_camera_photo_interval(interval_s);
}

Napi::Value MissionItem::get_latitude_deg(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_latitude_deg());
}

Napi::Value MissionItem::get_longitude_deg(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_longitude_deg());
}

Napi::Value MissionItem::has_position_set(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_mission_item->has_position_set());
}

Napi::Value MissionItem::get_relative_altitude_m(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_relative_altitude_m());
}

Napi::Value MissionItem::get_fly_through(const Napi::CallbackInfo& info) {
  return Napi::Boolean::New(info.Env(), this->_mission_item->get_fly_through());
}

Napi::Value MissionItem::get_acceptance_radius_m(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_acceptance_radius_m());
}

Napi::Value MissionItem::get_speed_m_s(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_speed_m_s());
}

Napi::Value MissionItem::get_gimbal_pitch_deg(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_gimbal_pitch_deg());
}

Napi::Value MissionItem::get_gimbal_yaw_deg(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_gimbal_yaw_deg());
}

Napi::Value MissionItem::get_loiter_time_s(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_loiter_time_s());
}

Napi::Value MissionItem::get_camera_action(const Napi::CallbackInfo& info) {
  mavsdk::MissionItem::CameraAction action = this->_mission_item->get_camera_action();
  auto n = static_cast<typename std::underlying_type<mavsdk::MissionItem::CameraAction>::type>(action);
  return Napi::Number::New(info.Env(), n);
}

Napi::Value MissionItem::get_camera_photo_interval_s(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->_mission_item->get_camera_photo_interval_s());
}

Napi::Value MissionItem::to_object(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    Napi::Object obj = Napi::Object::New(env);
    obj.Set("latitude_deg", this->_mission_item->get_latitude_deg());
    obj.Set("longitude_deg", this->_mission_item->get_longitude_deg());
    obj.Set("relative_altitude_m", this->_mission_item->get_relative_altitude_m());
    obj.Set("fly_through", this->_mission_item->get_fly_through());
    obj.Set("acceptance_radius_m", this->_mission_item->get_acceptance_radius_m());
    obj.Set("speed_m_s", this->_mission_item->get_speed_m_s());
    obj.Set("gimbal_pitch_deg", this->_mission_item->get_gimbal_pitch_deg());
    obj.Set("gimbal_yaw_deg", this->_mission_item->get_gimbal_yaw_deg());
    obj.Set("loiter_time_s", this->_mission_item->get_loiter_time_s());
    auto action = static_cast<typename std::underlying_type<mavsdk::MissionItem::CameraAction>::type>(this->_mission_item->get_camera_action());
    obj.Set("camera_action", action);
    obj.Set("camera_photo_interval_s", this->_mission_item->get_camera_photo_interval_s());
    
    return obj;
}

std::shared_ptr<mavsdk::MissionItem> MissionItem::make_mission_item(
    double longitude_deg,
    double latitude_deg,
    float relative_altitude_m,
    bool fly_through,
    float acceptance_radius_m,
    float speed_m_s,
    float gimbal_pitch_deg,
    float gimbal_yaw_deg,
    float loiter_time_s,
    mavsdk::MissionItem::CameraAction camera_action,
    double camera_photo_interval_s)
{
    std::shared_ptr<mavsdk::MissionItem> new_item(new mavsdk::MissionItem());
    new_item->set_position(latitude_deg, longitude_deg);
    new_item->set_relative_altitude(relative_altitude_m);
    new_item->set_fly_through(fly_through);
    new_item->set_acceptance_radius(acceptance_radius_m);
    new_item->set_speed(speed_m_s);
    new_item->set_gimbal_pitch_and_yaw(gimbal_pitch_deg, gimbal_yaw_deg);
    new_item->set_loiter_time(loiter_time_s);
    new_item->set_camera_action(camera_action);
    new_item->set_camera_photo_interval(camera_photo_interval_s);
    return new_item;
}