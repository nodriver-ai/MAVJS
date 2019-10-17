import * as bindings from 'bindings';
const addon = bindings('MAVJS');

export interface Position {
  latitude: number,
  longitude: number,
  altitude: number
}

export interface Battery {
  voltage: number;
  remaining_percent: number;
}

export interface Quaternion {
  w: number;
  x: number;
  y: number;
  z: number;
}

export interface EulerAngle {
  roll: number;
  pitch: number;
  yaw: number;
}

export interface GroundSpeedNED {
  velocity_north: number;
  velocity_east: number;
  velocity_down: number;
}

export interface GPSInfo {
  num_satellites: number;
  fix_type: number;
}

export interface Health {
  gyrometer_calibration_ok: boolean;
  accelerometer_calibration_ok: boolean;
  magnetometer_calibration_ok: boolean;
  level_calibration_ok: boolean;
  local_position_ok: boolean;
  global_position_ok: boolean;
  home_position_ok: boolean;
}

export interface RCStatus {
  available_once: boolean;
  available: boolean;
  signal_strength_percent: number;
}

export interface ProductInfo {
  hardware_uid: number[];
  vendor_id: number;
  vendor_name: string;
  product_id: number;
  product_name: string;
}

export interface Telemetry {
  flight_mode: string,
  battery: Battery,
  gps_info: GPSInfo,
  has_autopilot: boolean;
  has_camera: boolean;
  has_gimbal: boolean;
  in_air: boolean;
  armed: boolean;
  ground_speed_ned : GroundSpeedNED;
  attitude_quaternion: Quaternion;
  attitude_euler_angle: EulerAngle;
}

export interface CameraInformation {
  vendor_name: string,
  model_name: string,
  resolution_h: number,
  resolution_v: number,
  angle_of_view: number,
  spatial_resolution: number,
  te: number,
  ts: number,
  theta: number,
  overlap_high: number,
  overlap_medium: number,
  overlap_low: number
}

export interface MissionItem {
  latitude_deg: number,
  longitude_deg: number,
  relative_altitude_m: number,
  speed_m_s: number,
  gimbal_pitch_deg: number,
  gimbal_yaw_deg: number,
  camera_action: number
}

export interface Drone {
  uuid: string;
  get_product_info(): ProductInfo;
  is_connected(): boolean;
  has_autopilot(): boolean;
  has_camera(): boolean;
  has_gimbal(): boolean;
  set_rate_position(rate_hz: number): void;
  set_rate_home_position(rate_hz: number): void;
  set_rate_attitude(rate_hz: number): void;
  set_rate_battery(rate_hz: number): void;
  set_rate_position_velocity_ned(rate_hz: number): void;
  set_rate_in_air(rate_hz: number): void;
  set_rate_camera_attitude(rate_hz: number): void;
  set_rate_ground_speed_ned(rate_hz: number): void;
  set_rate_gps_info(rate_hz: number): void;
  set_rate_rc_status(rate_hz: number): void;
  position(): Position;
  health_all_ok(): boolean;
  home_position(): Position;
  battery(): Battery;
  in_air(): boolean;
  armed(): boolean;
  attitude_quaternion(): Quaternion;
  attitude_euler_angle(): EulerAngle;
  ground_speed_ned(): GroundSpeedNED;
  gps_info(): GPSInfo;
  flight_mode(): string;
  health(): Health;
  rc_status(): RCStatus;
  telemetry(): Telemetry;
  arm(): Promise<string>;
  disarm(): Promise<string>;
  takeoff(): Promise<string>;
  land(): Promise<string>;
  upload_mission(mission_items: MissionItem[]): Promise<string>;
  start_mission(): Promise<string>;
  stop_mission(): Promise<string>;
  pause_mission(): Promise<string>;
  mission_finished(): boolean;
}

export interface Camera {
  uuid: string;
  is_connected(): boolean;
  information(): CameraInformation
}

export interface MavSDK {
  connection_url: string;
  is_connected(uuid: string | null): boolean;
  discover_drones(): string[];
  discover_cameras(): string[];
  connect_to_drone(uuid: string): Drone | null;
  connect_to_camera(uuid: string): Camera | null;
}

export const MavSDK: {
  new(url: string): MavSDK
} = addon.MavSDK
