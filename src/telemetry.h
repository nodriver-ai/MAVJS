#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <napi.h>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>

namespace mavjs {
    class Telemetry : public Napi::ObjectWrap<Telemetry> {
        public:
            static Napi::Object Init(Napi::Env env, Napi::Object exports);
            Telemetry(const Napi::CallbackInfo &info);
            static Napi::FunctionReference constructor;

        private:
            std::shared_ptr<mavsdk::Telemetry> _telemetry;
                        
            Napi::Value set_rate_position_velocity_ned(const Napi::CallbackInfo& info);
            Napi::Value set_rate_position(const Napi::CallbackInfo& info);
            Napi::Value set_rate_home_position(const Napi::CallbackInfo& info);
            Napi::Value set_rate_in_air(const Napi::CallbackInfo& info);
            Napi::Value set_rate_attitude(const Napi::CallbackInfo& info);
            Napi::Value set_rate_ground_speed_ned(const Napi::CallbackInfo& info);
            Napi::Value set_rate_imu_reading_ned(const Napi::CallbackInfo& info);
            Napi::Value set_rate_gps_info(const Napi::CallbackInfo& info);
            Napi::Value set_rate_battery(const Napi::CallbackInfo& info);
            Napi::Value set_rate_rc_status(const Napi::CallbackInfo& info);
            Napi::Value set_rate_actuator_control_target(const Napi::CallbackInfo& info);
            Napi::Value set_rate_actuator_output_status(const Napi::CallbackInfo& info);

            Napi::Value position_velocity_ned(const Napi::CallbackInfo& info);
            Napi::Value position(const Napi::CallbackInfo& info);
            Napi::Value home_position(const Napi::CallbackInfo& info);
            Napi::Value status_text(const Napi::CallbackInfo& info);
            Napi::Value in_air(const Napi::CallbackInfo& info);
            Napi::Value landed_state(const Napi::CallbackInfo& info);
            Napi::Value armed(const Napi::CallbackInfo& info);
            Napi::Value attitude_quaternion(const Napi::CallbackInfo& info);
            Napi::Value attitude_euler_angle(const Napi::CallbackInfo& info);
            Napi::Value attitude_angular_velocity_body(const Napi::CallbackInfo& info);
            Napi::Value ground_speed_ned(const Napi::CallbackInfo& info);
            Napi::Value imu_reading_ned(const Napi::CallbackInfo& info);
            Napi::Value gps_info(const Napi::CallbackInfo& info);
            Napi::Value battery(const Napi::CallbackInfo& info);
            Napi::Value flight_mode(const Napi::CallbackInfo& info);
            Napi::Value health(const Napi::CallbackInfo& info);
            Napi::Value health_all_ok(const Napi::CallbackInfo& info);
            Napi::Value rc_status(const Napi::CallbackInfo& info);
            Napi::Value actuator_control_target(const Napi::CallbackInfo& info);
            Napi::Value actuator_output_status(const Napi::CallbackInfo& info);

            void position_velocity_ned_async(const Napi::CallbackInfo& info);
            void position_async(const Napi::CallbackInfo& info);
            void home_position_async(const Napi::CallbackInfo& info);
            void in_air_async(const Napi::CallbackInfo& info);
            void status_text_async(const Napi::CallbackInfo& info);
            void armed_async(const Napi::CallbackInfo& info);
            void attitude_quaternion_async(const Napi::CallbackInfo& info);
            void attitude_euler_angle_async(const Napi::CallbackInfo& info);
            void attitude_angular_velocity_body_async(const Napi::CallbackInfo& info);
            void camera_attitude_quaternion_async(const Napi::CallbackInfo& info);
            void camera_attitude_euler_angle_async(const Napi::CallbackInfo& info);
            void ground_speed_ned_async(const Napi::CallbackInfo& info);
            void imu_reading_ned_async(const Napi::CallbackInfo& info);
            void gps_info_async(const Napi::CallbackInfo& info);
            void battery_async(const Napi::CallbackInfo& info);
            void flight_mode_async(const Napi::CallbackInfo& info);
            void health_async(const Napi::CallbackInfo& info);
            void health_all_ok_async(const Napi::CallbackInfo& info);
            void landed_state_async(const Napi::CallbackInfo& info);
            void actuator_control_target_async(const Napi::CallbackInfo& info);
            void actuator_output_status_async(const Napi::CallbackInfo& info);
            void rc_status_async(const Napi::CallbackInfo& info);
    };
};

#endif
