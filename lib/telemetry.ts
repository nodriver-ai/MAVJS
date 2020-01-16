/**
 * This class allows users to get vehicle telemetry and state information (e.g. battery, GPS, RC connection, flight mode etc.) and set telemetry update rates.
 * 
 * The plugin is typically created as shown below: ```let telemetry = system.telemetry()```
 */
export class Telemetry {
  /**
   * Set rate of kinematic (position and velocity) updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */
  set_rate_position_velocity_ned(rate_hz: number): Telemetry.Result {
    return this.set_rate_position_velocity_ned(rate_hz);
  }

  /**
   * Set rate of position updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */
  set_rate_position(rate_hz: number): Telemetry.Result {
    return this.set_rate_position(rate_hz);
  }

  /**
   * Set rate of home position updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */
  set_rate_home_position(rate_hz: number): Telemetry.Result {
    return this.set_rate_home_position(rate_hz);
  }

  /**
   * Set rate of in-air status updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */
  set_rate_in_air(rate_hz: number): Telemetry.Result {
    return this.set_rate_in_air(rate_hz);
  }

  /**
   * Set rate of attitude updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */
  set_rate_attitude(rate_hz: number): Telemetry.Result {
    return this.set_rate_attitude(rate_hz);
  }

  /**
   * Set rate of ground speed (NED) updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */
  set_rate_ground_speed_ned(rate_hz: number): Telemetry.Result {
    return this.set_rate_ground_speed_ned(rate_hz);
  }

  /**
   * Set rate of IMU reading (NED) updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */  
  set_rate_imu_reading_ned(rate_hz: number): Telemetry.Result {
    return this.set_rate_imu_reading_ned(rate_hz);
  }

  /**
   * Set rate of GPS information updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */  
  set_rate_gps_info(rate_hz: number): Telemetry.Result {
    return this.set_rate_gps_info(rate_hz);
  }

  /**
   * Set rate of battery status updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */ 
  set_rate_battery(rate_hz: number): Telemetry.Result {
    return this.set_rate_battery(rate_hz);
  }

  /**
   * Set rate of RC status updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */ 
  set_rate_rc_status(rate_hz: number): Telemetry.Result {
    return this.set_rate_rc_status(rate_hz);
  }

  /**
   * Set rate of actuator controls updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */ 
  set_rate_actuator_control_target(rate_hz: number): Telemetry.Result {
    return this.set_rate_actuator_control_target(rate_hz);
  }

  /**
   * Set rate of actuator output status updates (synchronous).
   * @param rate_hz Rate in Hz.
   * > To stop sending it completely, use a rate_hz of -1, for default rate use 0.
   * @returns Result of request.
   */ 
  set_rate_actuator_output_status(rate_hz: number): Telemetry.Result {
    return this.set_rate_actuator_output_status(rate_hz);
  }

  /**
   * Get the current kinematic (position and velocity) in NED frame (synchronous).
   */
  position_velocity_ned(): Telemetry.PositionVelocityNED {
    return this.position_velocity_ned();
  }
  
  /**
   * Get the current position (synchronous).
   */
  position(): Telemetry.Position {
    return this.position();
  }

  /**
   * Get the home position (synchronous).
   * @returns Home position.
   */
  home_position(): Telemetry.Position {
    return this.home_position();
  }

  /**
   * Get status text (synchronous).
   * @returns Status text.
   */
  status_text(): string {
    return this.status_text();
  }

  /**
   * Get the in-air status (synchronous).
   * @returns true if in-air (flying) and not on-ground (landed).
   */
  in_air(): boolean {
    return this.in_air();
  }

  /**
   * Get the landed state status (synchronous).
   * @returns Landed state.
   */
  landed_state(): Telemetry.LandedState {
    return this.landed_state();
  }

  /**
   * Get the arming status (synchronous).
   * @returns true if armed (propellers spinning).
   */
  armed(): boolean {
    return this.armed();
  }

  /**
   * Get the current attitude in quaternions (synchronous).
   * @returns Attitude as quaternion.
   */
  attitude_quaternion(): Telemetry.Quaternion {
    return this.attitude_quaternion();
  }

  /**
   * Get the current attitude in Euler angles (synchronous).
   * @returns Attitude as Euler angle.
   */
  attitude_euler_angle(): Telemetry.EulerAngle {
    return this.attitude_euler_angle();
  }

  /**
   * Get the current angular speed in rad/s (synchronous).
   * @returns Angular speed.
   */
  attitude_angular_velocity_body(): Telemetry.AngularVelocityBody {
    return this.attitude_angular_velocity_body();
  }

  /**
   * Get the current ground speed (NED) (synchronous).
   * @returns Ground speed in NED.
   */
  ground_speed_ned(): Telemetry.GroundSpeedNED {
    return this.ground_speed_ned();
  }

  /**
   * Get the current IMU reading (NED) (synchronous).
   * @returns IMU reading in NED.
   */
  imu_reading_ned(): Telemetry.IMUReadingNED {
    return this.imu_reading_ned();
  }

  /**
   * Get the current GPS information (synchronous).
   * @returns GPS information.
   */
  gps_info(): Telemetry.GPSInfo {
    return this.gps_info();
  }

  /**
   * Get the current battery status (synchronous).
   * @returns Battery status.
   */
  battery(): Telemetry.Battery {
    return this.battery();
  }
  
  /**
   * Get the current flight mode (synchronous).
   * @returns Flight mode.
   */
  flight_mode(): Telemetry.FlightMode {
    return this.flight_mode();
  }

  /**
   * Get the current health status (synchronous).
   * @returns Health status.
   */
  health(): Telemetry.Health {
    return this.health();
  }

  /**
   * Returns true if the overall health is ok (synchronous).
   * @returns True if all health flags are OK.
   */
  health_all_ok(): boolean {
    return this.health_all_ok();
  }

  /**
   * Get the RC status (synchronous).
   * @returns RC status.
   */
  rc_status(): Telemetry.RCStatus {
    return this.rc_status();
  }

  /**
   * Get the actuator control target (synchronous).
   * @returns Actuator control target
   */
  actuator_control_target(): Telemetry.ActuatorControlTarget {
    return this.actuator_control_target();
  }

  /**
   * Get the actuator output status (synchronous).
   *@returns Actuator output status. 
   */
  actuator_output_status(): Telemetry.ActuatorOutputStatus {
    return this.actuator_output_status();
  }

  /**
   * Subscribe to kinematic (position and velocity) updates (asynchronous).
   * @param callback  Function to call with updates.
   */
  position_velocity_ned_async(callback: Telemetry.position_velocity_ned_callback_t): void {
    this.position_velocity_ned_async(callback);
  }

  /**
   * Subscribe to position updates (asynchronous).
   * @param callback  Function to call with updates.
   */
  position_async(callback: Telemetry.position_callback_t): void {
    this.position_async(callback);
  }

  /**
   * Subscribe to home position updates (asynchronous).
   * @param callback  Function to call with updates.
   */
  home_position_async(callback: Telemetry.position_callback_t): void {
    this.home_position_async(callback);
  }

  /**
   * Subscribe to in-air updates (asynchronous).
   * @param callback Function to call with updates.
   */
  in_air_async(callback: Telemetry.in_air_callback_t): void {
    this.in_air_async(callback);
  }

  /**
   * Subscribe to status text updates (asynchronous).
   * @param callback Function to call with updates.
   */
  status_text_async(callback: Telemetry.status_text_callback_t): void {
    this.status_text_async(callback);
  }

  /**
   * Subscribe to armed updates (asynchronous).
   * Note that armed updates are limited to 1Hz.
   * @param callback Function to call with updates.
   */
  armed_async(callback: Telemetry.armed_callback_t): void {
    this.armed_async(callback);
  }

  /**
   * Subscribe to attitude updates in quaternion (asynchronous).
   * @param callback Function to call with updates.
   */
  attitude_quaternion_async(callback: Telemetry.attitude_quaternion_callback_t): void {
    this.attitude_quaternion_async(callback);
  }

  /**
   * Subscribe to attitude updates in Euler angles (asynchronous).
   * @param callback Function to call with updates.
   */
  attitude_euler_angle_async(callback: Telemetry.attitude_euler_angle_callback_t): void {
    this.attitude_euler_angle_async(callback);
  }

  /**
   * Subscribe to attitude updates in angular velocity (asynchronous).
   * @param callback Function to call with updates.
   */
  attitude_angular_velocity_body_async(callback: Telemetry.attitude_angular_velocity_body_callback_t): void {
    this.attitude_angular_velocity_body_async(callback)
  }

  /**
   * Subscribe to ground speed (NED) updates (asynchronous).
   * @param callback Function to call with updates.
   */
  ground_speed_ned_async(callback: Telemetry.ground_speed_ned_callback_t): void {
    this.ground_speed_ned_async(callback);
  }

  /**
   * Subscribe to IMU reading (NED) updates (asynchronous).
   * @param callback Function to call with updates.
   */
  imu_reading_ned_async(callback: Telemetry.imu_reading_ned_callback_t): void {
    this.imu_reading_ned_async(callback)
  }

  /**
   * Subscribe to GPS information updates (asynchronous).
   * @param callback Function to call with updates.
   */
  gps_info_async(callback: Telemetry.gps_info_callback_t): void {
    this.gps_info_async(callback)
  }

  /**
   * Subscribe to battery status updates (asynchronous).
   * @param callback Function to call with updates.
   */
  battery_async(callback: Telemetry.battery_callback_t): void {
    this.battery_async(callback)
  }
  
  /**
   * Subscribe to flight mode updates (asynchronous).
   * Note that flight mode updates are limited to 1Hz.
   * @param callback Function to call with updates.
   */
  flight_mode_async(callback: Telemetry.flight_mode_callback_t): void {
    this.flight_mode_async(callback);
  }

  /**
   * Subscribe to health status updates (asynchronous).
   * Note that health status updates are limited to 1Hz.
   * @param callback Function to call with updates.
   */
  health_async(callback: Telemetry.health_callback_t): void {
    this.health_async(callback);
  }

  /**
   * Subscribe to overall health status updates (asynchronous).
   * Note that overall health status updates are limited to 1Hz.
   * @param callback Function to call with updates.
   */
  health_all_ok_async(callback: Telemetry.health_all_ok_callback_t): void {
    this.health_all_ok_async(callback);
  }

  /**
   * Subscribe to Landed state updates (asynchronous).
   * @param callback Function to call with updates.
   */
  landed_state_async(callback: Telemetry.landed_state_callback_t): void {
    this.landed_state_async(callback);
  }

  /**
   * Subscribe to actuator control target updates (asynchronous).
   * @param callback Function to call with updates.
   */
  actuator_control_target_async(callback: Telemetry.actuator_control_target_callback_t): void {
    this.actuator_control_target_async(callback);
  }

  /**
   * Subscribe to actuator output status updates (asynchronous).
   * @param callback Function to call with updates.
   */
  actuator_output_status_async(callback: Telemetry.actuator_output_status_callback_t): void {
    this.actuator_output_status_async(callback);
  }

  /**
   * Subscribe to RC status updates (asynchronous).
   * @param callback Function to call with updates.
   */
  rc_status_async(callback: Telemetry.rc_status_callback_t): void {
    this.rc_status_async(callback);
  }
  
}


export namespace Telemetry {

    export type position_velocity_ned_callback_t = 
    /**
     * Callback type for kinematic (position and velocity) updates.
     * @param {position_velocity_ned_callback_t} position_velocity_ned
     */
    (position_velocity_ned: PositionVelocityNED) => void;

    export type position_callback_t = 
    /**
     * Callback type for position updates.
     * @param {position_callback_t} position
     */
    (position: Position) => void;

    export type in_air_callback_t=
    /**
     * Callback type for in-air updates.
     * @param {in_air_callback_t} in_air
     */
    (in_air: boolean) => void;

    export type status_text_callback_t=
    /**
     * Callback for mavlink status text updates.
     * @param {status_text_callback_t} status_text
     */
    (status_text: StatusType) => void;

    export type armed_callback_t=
    /**
     * Callback type for armed updates (asynchronous).
     * @param {armed_callback_t} armed
     */
    (armed: boolean) => void;

    export type attitude_quaternion_callback_t=
    /**
     * Callback type for attitude updates in quaternion.
     * @param {attitude_quaternion_callback_t} attitude_quaternion
     */
    (attitude_quaternion: Quaternion) => void;

    export type attitude_euler_angle_callback_t=
    /**
     * Callback type for attitude updates in Euler angles.
     * @param {attitude_euler_angle_callback_t} attitude_euler_angle
     */
    (attitude_euler_angle: EulerAngle) => void;

    export type attitude_angular_velocity_body_callback_t=
    /**
     * Callback type for angular velocity updates in quaternion.
     * @param {attitude_angular_velocity_body_callback_t} attitude_angular_velocity_body
     */
    (attitude_angular_velocity_body: AngularVelocityBody) => void;

    export type ground_speed_ned_callback_t=
    /**
     * Callback type for ground speed (NED) updates.
     * @param {ground_speed_ned_callback_t} ground_speed_ned
     */
    (ground_speed_ned: GroundSpeedNED) => void;

    export type imu_reading_ned_callback_t=
    /**
     * Callback type for IMU (NED) updates.
     * @param {imu_reading_ned_callback_t} imu_reading_ned
     */
    (imu_reading_ned: IMUReadingNED) => void;

    export type gps_info_callback_t=
    /**
     * Callback type for GPS information updates.
     * @param {gps_info_callback_t} gps_info
     */
    (gps_info: GPSInfo) => void;
    
    export type battery_callback_t=
    /**
     * Callback type for Battery status updates.
     * @param {battery_callback_t} battery
     */
    (battery: Battery) => void;

    export type flight_mode_callback_t= 
    /**
     * Callback type for Flight mode updates.
     * @param {flight_mode_callback_t} flight_mode
     */
    (flight_mode: FlightMode) => void;

    export type health_callback_t= 
    /**
     * Callback type for Health status updates.
     * @param {health_callback_t} health
     */
    (health: Health) => void;

    export type health_all_ok_callback_t= 
    /**
     * Callback type for Health status updates.
     * @param {health_all_ok_callback_t} health_all_ok
     */
    (health_all_ok: boolean) => void;

    export type landed_state_callback_t= 
    /**
     * Callback type for Landed state updates.
     * @param {landed_state_callback_t} landed_state
     */
    (landed_state: LandedState) => void;

    export type actuator_control_target_callback_t= 
    /**
     * Callback type for Actuator control target updates.
     * @param {actuator_control_target_callback_t} actuator_control_target
     */
    (actuator_control_target: ActuatorControlTarget) => void;   
    
    export type actuator_output_status_callback_t= 
    /**
     * Callback type for Actuator output status updates.
     * @param {actuator_output_status_callback_t} actuator_output_status
     */
    (actuator_output_status: ActuatorOutputStatus) => void;   

    export type rc_status_callback_t= 
    /**
     * Callback type for RC status updates.
     * @param {rc_status_callback_t} rc_status
     */
    (rc_status: RCStatus) => void;  
    
    export enum Result {
      SUCCESS = "Success",
      NO_SYSTEM = "No system",
      CONNECTION_ERROR = "Connection error",
      BUSY = "Busy",
      COMMAND_DENIED = "Command denied",
      TIMEOUT = "Timeout",
      UNKNOWN = "Unknown"
    }

    export enum FlightMode {
      READY = "Ready",
      TAKEOFF = "Takeoff",
      HOLD = "Hold",
      MISSION = "Mission",
      RETURN_TO_LAUNCH = "Return to launch",
      LAND = "Land",
      OFFBOARD = "Offboard",
      FOLLOW_ME = "Follow me",
      UNKNOWN = "Unknown"
    }
  
    /**
     * Position type in local coordinates.
     * 
     * Position is represented in the NED (North East Down) frame in local coordinate system.
     */
    export interface PositionNED {
      /**
       * Position along north-direction in meters.
       */
      north_m: number,
      /**
       * Position along east-direction in meters.
       */
      east_m: number,
      /**
       * Position along down-direction in meters.
       */
      down_m: number
    }
    
    /**
     * Velocity type in local coordinates.
     * 
     * Velocity is represented in NED (North East Down) frame in local coordinate system.
     */
    export interface VelocityNED {
      /**
       * Velocity along north-direction in meters.
       */
      north_m_s: number,
      /**
       * Velocity along east-direction in meters.
       */
      east_m_s: number,
      /**
       * Velocity along down-direction in meters.
       */
      down_m_s: number
    }
    
    /**
     * Kinematic type in local coordinates.
     * 
     * Position and Velocity are represented in NED (North East Down) frame in local coordinate system.
     */
    export interface PositionVelocityNED {
      position: PositionNED,
      velocity: VelocityNED
    }

    /**
     * Position type in global coordinates.
     */   
    export interface Position {
      /**
       * Latitude in degrees (range: -90 to +90).
       */
      latitude_deg: number,
      /**
       * Longitude in degrees (range: -180 to 180).
       */
      longitude_deg: number,
      /**
       * Altitude AMSL (above mean sea level) in metres..
       */
      absolute_altitude_m: number,
      /**
       * Altitude relative to takeoff altitude in metres..
       */
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
    
    /**
     * Battery type.
     */
    export interface Battery {
      /**
       * Voltage in volts.
       */
      voltage: number,
      /**
       * Estimated battery percentage remaining (range: 0.0 to 1.0).
       */
      remaining_percent: number
    }
    
    /**
     * Quaternion type.
     * 
     * All rotations and axis systems follow the right-hand rule. The Hamilton quaternion product definition is used. A zero-rotation quaternion is represented by (1,0,0,0). The quaternion could also be written as w + xi + yj + zk.
     * For more info see: [https://en.wikipedia.org/wiki/Quaternion](https://en.wikipedia.org/wiki/Quaternion)
     */
    export interface Quaternion {
      /**
       * entry 0 also denoted as a.
       */
      w: number,
      /**
       * entry 1 also denoted as b.
       */
      x: number,
      /**
       * entry 2 also denoted as c.
       */
      y: number,
      /**
       * entry 3 also denoted as d.
       */
      z: number
    }
    
    /**
     * Euler angle type.
     * 
     * All rotations and axis systems follow the right-hand rule. The Euler angles follow the convention of a 3-2-1 intrinsic Tait-Bryan rotation sequence.
     * For more info see [https://en.wikipedia.org/wiki/Euler_angles](https://en.wikipedia.org/wiki/Euler_angles)
     */
    export interface EulerAngle {
      /**
       * Roll angle in degrees, positive is banking to the right.
       */
      roll_deg: number,
      /**
       * Pitch angle in degrees, positive is pitching nose up.
       */
      pitch_deg: number,
      /**
       * Yaw angle in degrees, positive is clock-wise seen from above.
       */
      yaw_deg: number,
    }
    
    /**
     * Angular velocity type.
     * 
     * The angular velocity of vehicle body in radians/second.
     */
    export interface AngularVelocityBody {
      /**
       * Roll angular velocity.
       */
      roll_rad_s: number,
      /**
       * Pitch angular velocity.
       */
      pitch_rad_s: number,
      /**
       * Yaw angular velocity.
       */
      yaw_rad_s: number
    }
    
    /**
     * Ground speed type.
     * 
     * The ground speed is represented in the NED (North East Down) frame and in metres/second.
     */
    export interface GroundSpeedNED {
      /**
       * Velocity in North direction in metres/second.
       */
      velocity_north_m_s: number;
      /**
       * Velocity in East direction in metres/second.
       */
      velocity_east_m_s: number;
      /**
       * Velocity in Down direction in metres/second.
       */
      velocity_down_m_s: number;
    }
    
    /**
     * Acceleration type in local coordinates.
     * 
     * The acceleration is represented in the NED (North East Down) frame and in metres/second^2.
     */
    export interface AccelerationNED {
      /**
       * Acceleration in North direction in metres/second^2.
       */
      north_m_s2: number,
      /**
       * Acceleration in East direction in metres/second^2.
       */
      east_m_s2: number,
      /**
       * Acceleration in Down direction in metres/second^2.
       */
      down_m_s2: number
    }
    
    /**
     * Angular velocity type in local coordinates.
     * 
     * The angular velocity is represented in NED (North East Down) frame and in radians/second.
     */
    export interface AngularVelocityNED {
      /**
       * Angular velocity in North direction in radians/second.
       */
      north_rad_s: number,
      /**
       * Angular velocity in East direction in radians/second.
       */
      east_rad_s: number,
      /**
       * Angular velocity in Down direction in radians/second.
       */
      down_rad_s: number
    }
    
    /**
     * Magnetic field type in local coordinates.
     * 
     * The magnetic field is represented in NED (North East Down) frame and is measured in Gauss.
     */
    export interface MagneticFieldNED {
      /**
       * Magnetic field in North direction measured in Gauss.
       */
      north_gauss: number,
      /**
       * Magnetic field in East direction measured in Gauss.
       */
      east_gauss: number,
      /**
       * Magnetic field in Down direction measured in Gauss.
       */
      down_gauss: number
    }
    
    /**
     * Inertial measurement unit type in local coordinates.
     * 
     * Acceleration, angular velocity and magnetic field are represented in NED (North East Down) frame in local coordinate system. Temperature is measured in degrees Celsius.
     */
    export interface IMUReadingNED {
      acceleration: AccelerationNED,
      angular_velocity: AngularVelocityNED,
      magnetic_field: MagneticFieldNED,
      /**
       * Temperature measured in degrees Celsius.
       */
      temperature_degC: number
    }
    
    /**
     * GPS information type.
     */
    export interface GPSInfo {
      /**
       * Number of visible satellites used for solution.
       */
      num_satellites: number;
      /**
       * Fix type (0: no GPS, 1: no fix, 2: 2D fix, 3: 3D fix, 4: DGPS fix, 5: RTK float, 6: RTK fixed).
       */
      fix_type: number;
    }
    
    /**
     * Various health flags.
     */
    export interface Health {
      /**
       * true if the gyrometer is calibrated.
       */
      gyrometer_calibration_ok: boolean;
      /**
       * true if the accelerometer is calibrated.
       */
      accelerometer_calibration_ok: boolean;
      /**
       * true if the magnetometer is calibrated.
       */
      magnetometer_calibration_ok: boolean;
      /**
       * true if the vehicle has a valid level calibration.
       */
      level_calibration_ok: boolean;
      /**
       * true if the local position estimate is good enough to fly in a position control mode.
       */
      local_position_ok: boolean;
      /**
       * true if the global position estimate is good enough to fly in a position controlled mode.
       */
      global_position_ok: boolean;
      /**
       * true if the home position has been initialized properly.
       */
      home_position_ok: boolean;
    }
    
    /**
     * Remote control status type.
     */
    export interface RCStatus {
      /** true if an RC signal has been available once. */
      available_once: boolean;
      /** true if the RC signal is available now. */
      available: boolean;
      /** Signal strength as a percentage (range: 0 to 100). */
      signal_strength_percent: number;
    }
    
    /**
     * The vehicle actuator's rate control type.
     * An actuator's control group is e.g. attitude, for the core flight controls, or gimbal for payload. 
     * 
     * For more information about PX4 groups, check out [https://dev.px4.io/v1.9.0/en/concept/mixing.html#control-pipeline](https://dev.px4.io/v1.9.0/en/concept/mixing.html#control-pipeline)
     * 
     * Actuator controls normed to -1..+1 where 0 is neutral position. Throttle for single rotation direction motors is 0..1, negative range for reverse direction.
     * 
     * For more information about controls, check out [https://mavlink.io/en/messages/common.html#SET_ACTUATOR_CONTROL_TARGET]
     */
    export interface ActuatorControlTarget {
      /** Actuator group. */
      group: number,
      /** Actuator controls. */
      controls: number[]
    }
    
    /**
     * The raw values of the actuator outputs type.
     */
    export interface ActuatorOutputStatus {
      /** Active outputs. */
      active: number,
      /** Servo / motor output array values. */
      actuator: number[]
    }
  }

  
  