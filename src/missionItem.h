#ifndef MISSIONITEM_H
#define MISSIONITEM_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/mission/mission_item.h>

namespace mavjs {
            
    class MissionItem : public Napi::ObjectWrap<MissionItem> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            MissionItem(const Napi::CallbackInfo &info);
            static Napi::FunctionReference constructor;

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
                mavsdk::MissionItem::CameraAction camera_action,
                double camera_photo_interval_s);

        private:
            std::shared_ptr<mavsdk::MissionItem> _mission_item;

            void set_position(const Napi::CallbackInfo &info);
            void set_relative_altitude(const Napi::CallbackInfo &info);
            void set_fly_through(const Napi::CallbackInfo &info);
            void set_acceptance_radius(const Napi::CallbackInfo &info);
            void set_speed(const Napi::CallbackInfo &info);
            void set_gimbal_pitch_and_yaw(const Napi::CallbackInfo &info);
            void set_loiter_time(const Napi::CallbackInfo &info);
            void set_camera_action(const Napi::CallbackInfo &info);
            void set_camera_photo_interval(const Napi::CallbackInfo &info);

            Napi::Value get_latitude_deg(const Napi::CallbackInfo &info);
            Napi::Value get_longitude_deg(const Napi::CallbackInfo &info);
            Napi::Value has_position_set(const Napi::CallbackInfo &info);
            Napi::Value get_relative_altitude_m(const Napi::CallbackInfo &info);
            Napi::Value get_fly_through(const Napi::CallbackInfo &info);
            Napi::Value get_acceptance_radius_m(const Napi::CallbackInfo &info);
            Napi::Value get_speed_m_s(const Napi::CallbackInfo &info);
            Napi::Value get_gimbal_pitch_deg(const Napi::CallbackInfo &info);
            Napi::Value get_gimbal_yaw_deg(const Napi::CallbackInfo &info);
            Napi::Value get_loiter_time_s(const Napi::CallbackInfo &info);
            Napi::Value get_camera_action(const Napi::CallbackInfo &info);
            Napi::Value get_camera_photo_interval_s(const Napi::CallbackInfo &info);
            Napi::Value to_object(const Napi::CallbackInfo &info);
    };
};

#endif