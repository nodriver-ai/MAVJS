import * as bindings from 'bindings';
const addon = bindings('MAVJS');

export namespace MissionItem {
    export enum CameraAction {
        TAKE_PHOTO,
        START_PHOTO_INTERVAL,
        STOP_PHOTO_INTERVAL,
        START_VIDEO,
        STOP_VIDEO,
        NONE 
    }

    export const Init: {
        new(): MissionItem
    } = addon.MissionItem
}

export interface IMissionItem {
    latitude_deg: number,
    longitude_deg: number,
    relative_altitude_m: number,
    fly_through: boolean,
    acceptance_radius_m: number,
    speed_m_s: number,
    gimbal_pitch_deg: number,
    gimbal_yaw_deg: number,
    loiter_time_s: number,
    camera_action: MissionItem.CameraAction,
    camera_photo_interval_s: number
}

export interface MissionItem {
    set_position(latitude_deg: number, longitude_deg: number): void,
    set_relative_altitude(altitude_m: number): void,
    set_fly_through(fly_through: boolean): void,
    set_acceptance_radius(radius_m: number): void,
    set_speed(speed_m_s: number): void,
    set_gimbal_pitch_and_yaw(pitch_deg: number, yaw_deg: number): void,
    set_loiter_time(loiter_time_s: number): void,
    set_camera_action(action: MissionItem.CameraAction): void,
    set_camera_photo_interval(interval_s: number): void
    get_latitude_deg(): number,
    get_longitude_deg(): number,
    has_position_set(): boolean,
    get_relative_altitude_m(): number,
    get_fly_through(): boolean,
    get_acceptance_radius_m(): number,
    get_speed_m_s(): number,
    get_gimbal_pitch_deg(): number,
    get_gimbal_yaw_deg(): number,
    get_loiter_time_s(): number,
    get_camera_action(): MissionItem.CameraAction,
    get_camera_photo_interval_s(): number,
    to_object(): IMissionItem
}

