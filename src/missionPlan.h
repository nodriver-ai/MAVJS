#ifndef MISSIONPLAN_H
#define MISSIONPLAN_H

#include <string>

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/mission/mission.h>

class MissionPlan : public Napi::ObjectWrap<MissionPlan> {
public:
 static Napi::Object Init(Napi::Env env, Napi::Object exports);
 MissionPlan(const Napi::CallbackInfo &info);
 static Napi::FunctionReference constructor;

 private:
   static std::shared_ptr<mavsdk::MissionItem> make_mission_item(
    double latitude_deg,
    double longitude_deg,
    float relative_altitude_m,
    float speed_m_s,
    bool is_fly_through,
    float gimbal_pitch_deg,
    float gimbal_yaw_deg,
    mavsdk::MissionItem::CameraAction camera_action);

   std::vector<std::shared_ptr<mavsdk::MissionItem>> _mission_items;

};

#endif
