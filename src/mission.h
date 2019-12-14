#ifndef MISSION_H
#define MISSION_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/mission/mission.h>

namespace mavjs {
    class Mission : public Napi::ObjectWrap<Mission> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Mission(const Napi::CallbackInfo &info);
            static Napi::FunctionReference constructor;

        private:
            std::shared_ptr<mavsdk::Mission> _mission;

            static std::shared_ptr<mavsdk::MissionItem> make_mission_item(
            double latitude_deg,
            double longitude_deg,
            float relative_altitude_m,
            bool fly_through,
            float acceptance_radius_m,
            float speed_m_s,
            float gimbal_pitch_deg,
            float gimbal_yaw_deg,
            float loiter_time_s,
            double camera_photo_interval_s,
            mavsdk::MissionItem::CameraAction camera_action);

            Napi::Value upload_mission(const Napi::CallbackInfo &info);
    };
};

#endif