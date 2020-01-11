import * as bindings from 'bindings';
const addon = bindings('MAVJS');

export class MissionItem {
    private missionItem = new addon.MissionItem();

    constructor() {}

    /**
     * Set the position of a mission item.
     * @param latitude_deg Latitude of the waypoint in degrees.
     * @param longitude_deg Longitude of the waypoint in degrees.
     */
    set_position(latitude_deg: number, longitude_deg: number): void {
        this.missionItem.set_position(latitude_deg, longitude_deg);
    }
    
    /**
     * Set the relative altitude of a mission item.
     * @param altitude_m Altitude relative to takeoff position in metres.
     */
    set_relative_altitude(altitude_m: number): void {
        this.missionItem.set_relative_altitude(altitude_m);
    }

    /**
     * Set the fly-through property of a mission item.
     * @param fly_through If ```true``` the drone will fly through the waypoint without stopping. If ```false``` the drone will come to a stop at the waypoint before continuing.
     */
    set_fly_through(fly_through: boolean): void {
        this.missionItem.set_fly_through(fly_through);
    }

    /**
     * Set the acceptance radius property of a mission item.
     * @param radius_m Radius in meters around the mission_item where it will be considered as reached.
     */
    set_acceptance_radius(radius_m: number): void {
        this.missionItem.set_acceptance_radius(radius_m);
    }

    /**
     * Set the speed to use after a mission item.
     * @param speed_m_s Speed to use after this mission item in metres/second.
     */
    set_speed(speed_m_s: number): void {
        this.missionItem.set_speed(speed_m_s);
    }

    /**
     * Set the pitch and yaw angle of a gimbal at that mission item.
     * @param pitch_deg The new pitch angle of the gimbal in degrees (0: horizontal, positive up, -90: vertical downward facing).
     * @param yaw_deg The new yaw angle of the gimbal in degrees (0: forward, positive clock-wise, 90: to the right).
     */
    set_gimbal_pitch_and_yaw(pitch_deg: number, yaw_deg: number): void {
        this.missionItem.set_gimbal_pitch_and_yaw(pitch_deg, yaw_deg);
    }

    /**
     * Set loiter time in seconds.
     * 
     * This specifies the delay at a waypoint before executing next mission item. It can be used to wait for vehicle to slow down or a gimbal to arrive at the set orientation.
     * @param loiter_time_s The time to wait (loiter), in seconds.
     */
    set_loiter_time(loiter_time_s: number): void {
        this.missionItem.set_loiter_time(loiter_time_s);
    }

    /**
     * Set the camera action for a mission item.
     * @param action The camera action.
     */
    set_camera_action(action: MissionItem.CameraAction): void {
        this.missionItem.set_camera_action(action);
    }

    /**
     * Set the camera photo interval.
     * 
     * This only has an effect if used together with [[CameraAction.START_PHOTO_INTERVAL]].
     * @param interval_s Interval between photo captures in seconds.
     */
    set_camera_photo_interval(interval_s: number): void {
        this.missionItem(interval_s);
    }

    /**
     * Get the latitude of a mission item.
     * @returns Latitude in degrees.
     */
    get_latitude_deg(): number {
        return this.missionItem.get_latitude_deg();
    }

    /**
     * Get the longitude of a mission item.
     * @returns Longitude in degrees.
     */
    get_longitude_deg(): number {
        return this.missionItem.get_longitude_deg();
    }

    /**
     * Reports whether position info (Lat, Lon) was set for this mission item.
     * @returns true if Lat, Lon is set for this mission item.
     */
    has_position_set(): boolean {
        return this.missionItem.has_position_set();
    }

    /**
     * Get the relative altitude of a mission item.
     * @returns The altitude relative to the takeoff position in metres.
     */
    get_relative_altitude_m(): number {
        return this.missionItem.get_relative_altitude_m();
    }

    /**
     * Get the fly-through property of a mission item.
     * @returns  true if the drone will fly through the waypoint without stopping. false if the drone will come to a stop at the waypoint before continuing.
     */
    get_fly_through(): boolean {
        return this.missionItem.get_fly_through();
    }

    /**
     * Get the acceptance radius of a mission item.
     * @returns Acceptance radius in meters.
     */
    get_acceptance_radius_m(): number {
        return this.missionItem.get_acceptance_radius_m();
    }

    /**
     * Get the speed to be used after this mission item.
     * @returns Speed in metres/second.
     */
    get_speed_m_s(): number {
        return this.missionItem.get_speed_m_s();
    }

    /**
     * Get the gimbal pitch of a mission item.
     * @returns Gimbal pitch in degrees.
     */
    get_gimbal_pitch_deg(): number {
        return this.get_gimbal_pitch_deg();
    }

    /**
     * Get the gimbal yaw of a mission item.
     * @returns Gimbal yaw in degrees.
     */
    get_gimbal_yaw_deg(): number {
        return this.missionItem.get_gimbal_yaw_deg();
    }

    /**
     * Get loiter time in seconds.
     * @returns Loiter time in seconds.
     */
    get_loiter_time_s(): number {
        return this.missionItem.get_loiter_time_s();
    }

    /**
     * Get the camera action set for this mission item.
     * @returns Camera action enum value.
     */
    get_camera_action(): MissionItem.CameraAction {
        return this.missionItem.get_camera_action();
    }

    /**
     * Get the camera photo interval that was set for this mission item.
     * 
     * This only has an effect if used together with [[CameraAction.START_PHOTO_INTERVAL]].
     * @returns Camera photo interval in seconds.
     */
    get_camera_photo_interval_s(): number {
        return this.missionItem.get_camera_photo_interval_s();
    }

    /**
     * Get JSON object
     * @returns JSON object of instance.
     */
    to_object(): IMissionItem {
        return this.missionItem.to_object();
    }
}

export namespace MissionItem {
    export enum CameraAction {
        TAKE_PHOTO,
        START_PHOTO_INTERVAL,
        STOP_PHOTO_INTERVAL,
        START_VIDEO,
        STOP_VIDEO,
        NONE 
    }
}

/**
 * @ignore
 */
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

