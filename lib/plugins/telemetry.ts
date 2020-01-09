export namespace Telemetry {
    
    export interface position_velocity_ned_callback_t{ (position_velocity_ned: PositionVelocityNED): void};

    export enum Result {
      SUCCESS = "Success",
      NO_SYSTEM = "No system",
      CONNECTION_ERROR = "Connection error",
      BUSY = "Busy",
      COMMAND_DENIED = "Command denied",
      TIMEOUT = "Timeout",
      UNKNOWN = "Unknown"
    }
  
  
    export interface PositionNED {
      north_m: number,
      east_m: number,
      down_m: number
    }
  
    export interface VelocityNED {
      north_m_s: number,
      east_m_s: number,
      down_m_s: number
    }
  
    export interface PositionVelocityNED {
      position: PositionNED,
      velocity: VelocityNED
    }
  
    export interface Position {
      latitude_deg: number,
      longitude_deg: number,
      absolute_altitude_m: number,
      relative_altitude_m: number
    }
  
    export enum StatusType {
      INFO = "Info",
      WARNING = "Warning",
      CRITICAL = "Critical"
    }
  
    export enum LandedState {
      UNKNOWN = "Unknown",
      ON_GROUND = "On_ground",
      IN_AIR = "In_air",
      TAKING_OFF = "Taking_off",
      LANDING = "Landing"
    }
  
    export interface Battery {
      voltage: number,
      remaining_percent: number
    }
  
    export interface Quaternion {
      w: number,
      x: number,
      y: number,
      z: number
    }
  
    export interface EulerAngle {
      roll_deg: number,
      pitch_deg: number,
      yaw_deg: number,
    }
  
    export interface AngularVelocityBody {
      roll_rad_s: number,
      pitch_rad_s: number,
      yaw_rad_s: number
    }
  
    export interface GroundSpeedNED {
      velocity_north_m_s: number;
      velocity_east_m_s: number;
      velocity_down_m_s: number;
    }
  
    export interface AccelerationNED {
      north_m_s2: number,
      east_m_s2: number,
      down_m_s2: number
    }
  
    export interface AngularVelocityNED {
      north_rad_s: number,
      east_rad_s: number,
      down_rad_s: number
    }
  
    export interface MagneticFieldNED {
      north_gauss: number,
      east_gauss: number,
      down_gauss: number
    }
  
    export interface IMUReadingNED {
      acceleration: AccelerationNED,
      angular_velocity: AngularVelocityNED,
      magnetic_field: MagneticFieldNED,
      temperature_degC: number
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
  
    export interface ActuatorControlTarget {
      group: number,
      controls: number[]
    }
  
    export interface ActuatorOutputStatus {
      active: number,
      actuator: number[]
    }
  }

  export interface Telemetry {
    set_rate_position_velocity_ned(rate_hz: number): Telemetry.Result,
    set_rate_position(rate_hz: number): Telemetry.Result,
    set_rate_home_position(rate_hz: number): Telemetry.Result,
    set_rate_in_air(rate_hz: number): Telemetry.Result,
    set_rate_attitude(rate_hz: number): Telemetry.Result,
    set_rate_ground_speed_ned(rate_hz: number): Telemetry.Result,
    set_rate_imu_reading_ned(rate_hz: number): Telemetry.Result,
    set_rate_gps_info(rate_hz: number): Telemetry.Result,
    set_rate_battery(rate_hz: number): Telemetry.Result,
    set_rate_rc_status(rate_hz: number): Telemetry.Result,
    set_rate_actuator_control_target(rate_hz: number): Telemetry.Result,
    set_rate_actuator_output_status(rate_hz: number): Telemetry.Result,
    position_velocity_ned(): Telemetry.PositionVelocityNED,
    position(): Telemetry.Position,
    home_position(): Telemetry.Position,
    status_text(): string,
    in_air(): boolean,
    landed_state(): Telemetry.LandedState,
    armed(): boolean,
    attitude_quaternion(): Telemetry.Quaternion,
    attitude_euler_angle(): Telemetry.EulerAngle,
    attitude_angular_velocity_body(): Telemetry.AngularVelocityBody,
    ground_speed_ned(): Telemetry.GroundSpeedNED,
    imu_reading_ned(): Telemetry.IMUReadingNED,
    gps_info(): Telemetry.GPSInfo,
    battery(): Telemetry.Battery,
    flight_mode(): string,
    health(): Telemetry.Health,
    health_all_ok(): boolean,
    rc_status(): Telemetry.RCStatus,
    actuator_control_target(): Telemetry.ActuatorControlTarget,
    actuator_output_status(): Telemetry.ActuatorOutputStatus,
  }
  