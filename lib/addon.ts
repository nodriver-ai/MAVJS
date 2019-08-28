const addon = require('bindings')('ndbox');

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

export interface Product {
  vendor_id: number;
  vendor_name: string;
  product_id: number;
  product_name: string;
}

export interface Drone {
  uuid: string;
  get_identification(): number[];
  get_product(): Product;
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
}

export interface Ndbox {
  connection_url: string;
  is_connected(uuid: string | null): boolean;
  discover_uuids(): string[];
  connect_to_drone(uuid: string): Drone | null;
}

export var Ndbox: {
    new(url: string): Ndbox
} = addon.Ndbox
/*const UDP_PATH = "udp://:14540";

ndbox = new addon.Ndbox(UDP_PATH)

let uuids = []

const uuidsInterval = setInterval(() => {
  uuids = ndbox.discover_uuids()
  console.log(uuids)
}, 1000);

setTimeout(() => {
  if (uuids.length > 0) {
    drone = ndbox.connect_to_drone(uuids[0])
    drone.set_rate_battery(0.2)
    const positionInterval = setInterval(() => {
      //battery = drone.battery()
      //console.log(battery)
      console.log(drone.flight_mode())
    }, 1000)
  }

}, 2000)*/
