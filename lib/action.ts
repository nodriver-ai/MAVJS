/**
 * The Action class enables simple actions for a drone such as arming, taking off, and landing.
 * 
 * Synchronous and asynchronous variants of the action methods are supplied.
 * 
 * The action methods send their associated MAVLink commands to the vehicle and complete (return synchronously or callback asynchronously) with an [[Action.Result]] value indicating whether the vehicle has accepted or rejected the command, or that there has been some error. If the command is accepted, the vehicle will then start to perform the associated action.
 * 
 * The plugin is typically created as shown below: ```let action = system.action()```
 */
export class Action {
  
  /**
   * Send command to arm the drone (synchronous).
   * 
   * Note: Arming a drone normally causes motors to spin at idle. Before arming take all safety precautions and stand clear of the drone!
   * @returns Result of request.
   */
  arm(): Action.Result {
    return this.arm();
  }

  /**
   * Send command to disarm the drone (synchronous).
   * 
   * This will disarm a drone that considers itself landed. If flying, the drone should reject the disarm command. Disarming means that all motors will stop.
   * @returns Result of request.
   */
  disarm(): Action.Result {
    return this.disarm();
  }

  /**
   * Send command to kill the drone (synchronous).
   * 
   * This will disarm a drone irrespective of whether it is landed or flying. Note that the drone will fall out of the sky if this command is used while flying.
   * @returns Result of request.
   */
  kill(): Action.Result {
    return this.kill();
  }

  /**
   * Send command to reboot the drone components.
   * 
   * This will reboot the autopilot, onboard computer, camera and gimbal.
   * @returns Result of request.
   */
  reboot(): Action.Result {
    return this.reboot();
  }

  /**
   * Send command to take off and hover (synchronous).
   * 
   * This switches the drone into position control mode and commands it to take off and hover at the takeoff altitude (set using [[set_takeoff_altitude()]]).
   * 
   * Note: that the vehicle must be armed before it can take off.
   * @returns Result of request.
   */
  takeoff(): Action.Result {
    return this.takeoff();
  }

  /**
   * Send command to land at the current position (synchronous).
   * 
   * This switches the drone to [Land mode](https://docs.px4.io/v1.9.0/en/flight_modes/land.html).
   * @returns Result of request.
   */
  land(): Action.Result {
    return this.land();
  }

  /**
   * Send command to return to the launch (takeoff) position and land (asynchronous).
   * 
   * This switches the drone into [RTL mode](https://docs.px4.io/en/flight_modes/rtl.html) which generally means it will rise up to a certain altitude to clear any obstacles before heading back to the launch (takeoff) position and land there.
   * @returns Result of request.
   */
  return_to_launch(): Action.Result {
    return this.return_to_launch();
  }

  /**
   * Send command to move the vehicle to a specific global position.
   * 
   * The latitude and longitude are given in degrees (WGS84 frame) and the altitude in meters AMSL (above mean sea level).
   * @param latitude_deg Latitude in degrees.
   * @param longitude_deg Longitude in degrees.
   * @param altitude_amsl_m Altitude AMSL in meters.
   * @param yaw_deg Yaw angle in degrees (Frame is NED, 0 is North, positive is clockwise).
   * @returns Result of request.
   */
  goto_location(latitude_deg: number, longitude_deg: number, altitude_amsl_m: number, yaw_deg: number): Action.Result {
    return this.goto_location(latitude_deg, longitude_deg, altitude_amsl_m, yaw_deg);
  }

  /**
   * Send command to transition the drone to fixedwing.
   * 
   * The associated action will only be executed for VTOL vehicles (on other vehicle types the command will fail with an Result). The command will succeed if called when the vehicle is already in fixedwing mode.
   * @returns Result of request.
   */
  transition_to_fixedwing(): Action.Result {
    return this.transition_to_fixedwing();
  }

  /**
   * Send command to transition the drone to multicopter.
   * 
   * The associated action will only be executed for VTOL vehicles (on other vehicle types the command will fail with an Result). The command will succeed if called when the vehicle is already in multicopter mode.
   * @returns Result of request.
   */
  transition_to_multicopter(): Action.Result {
    return this.transition_to_multicopter();
  }

  /**
   * Send command to arm the drone (asynchronous).
   * Note that arming a drone normally means that the motors will spin at idle. Therefore, before arming take all safety precautions and stand clear of the drone.
   */
  arm_async(): Promise<Action.Result> {
    return this.arm_async();
  }
  
  /**
   * Send command to disarm the drone (asynchronous).
   * 
   * This will disarm a drone that considers itself landed. If flying, the drone should reject the disarm command. Disarming means that all motors will stop.
   */
  disarm_async(): Promise<Action.Result> {
    return this.disarm_async();
  }

  /**
   * Send command to kill the drone (asynchronous).
   * 
   * This will disarm a drone irrespective of whether it is landed or flying. Note that the drone will fall out of the sky if you use this command while flying.
   */
  kill_async(): Promise<Action.Result> {
    return this.kill_async();
  }

  /**
   * Send command to take off and hover (asynchronous).
   * 
   * This switches the drone into position control mode and commands it to take off and hover at the takeoff altitude set using [[set_takeoff_altitude()]].
   * 
   * Note that the vehicle must be armed before it can take off.
   */
  takeoff_async(): Promise<Action.Result> {
    return this.takeoff_async();
  }

  /**
   * Send command to land at the current position (asynchronous).
   * 
   * This switches the drone to [Land mode](https://docs.px4.io/v1.9.0/en/flight_modes/land.html).
   */
  land_async(): Promise<Action.Result> {
    return this.land_async();
  }

  /**
   * Send command to return to the launch (takeoff) position and land (asynchronous).
   * 
   * This switches the drone into [RTL mode](https://docs.px4.io/en/flight_modes/rtl.html) which generally means it will rise up to a certain altitude to clear any obstacles before heading back to the launch (takeoff) position and land there.
   */
  return_to_launch_async(): Promise<Action.Result> {
    return this.return_to_launch_async();
  }

  /**
   * Send command to transition the drone to fixedwing (asynchronous).
   * 
   * The associated action will only be executed for VTOL vehicles (on other vehicle types the command will fail with an Result). The command will succeed if called when the vehicle is already in fixedwing mode.
   */
  transition_to_fixedwing_async(): Promise<Action.Result> {
    return this.transition_to_fixedwing_async();
  }

  /**
   * Send command to transition the drone to multicopter (asynchronous).
   * 
   * The associated action will only be executed for VTOL vehicles (on other vehicle types the command will fail with an Result). The command will succeed if called when the vehicle is already in multicopter mode.
   */
  transition_to_multicopter_async(): Promise<Action.Result> {
    return this.transition_to_multicopter_async();
  }
  
  /**
   * Set takeoff altitude above ground.
   * @param relative_altitude_m 
   * @returns Result of request.
   */
  set_takeoff_altitude(relative_altitude_m: number): Action.Result {
    return this.set_takeoff_altitude(relative_altitude_m);
  }

  /**
   * Get the takeoff altitude.
   * @returns A pair containing the result of request and if successful, the takeoff altitude relative to ground/takeoff location, in meters.
   */
  get_takeoff_altitude(): Action.pair_result {
    return this.get_takeoff_altitude();
  }

  /**
   * Set vehicle maximum speed.
   * @param speed_m_s Maximum speed in metres/second.
   * @returns Result of request.
   */
  set_max_speed(speed_m_s: number): Action.Result {
    return this.set_max_speed(speed_m_s);
  }
  
  /**
   * Get the vehicle maximum speed.
   * @returns A pair containing the result of the request and if successful, the maximum speed in metres/second.
   */
  get_max_speed(): Action.pair_result {
    return this.get_max_speed();
  }

  /**
   * Set the return to launch minimum return altitude.
   * 
   * When return to launch is initiated, the vehicle climbs to the return altitude if it is lower and stays at the current altitude if higher than the return altitude. Then it returns to the home location and lands there.
   * @param relative_altitude_m Return altitude relative to takeoff location, in meters.
   * @returns Result of request.
   */
  set_return_to_launch_return_altitude(relative_altitude_m: number): Action.Result {
    return this.set_return_to_launch_return_altitude(relative_altitude_m);
  }

  /**
   * Get the return to launch minimum return altitude.
   * @returns A pair containing the result of the request and if successful, the return altitude relative to takeoff location, in meters.
   */
  get_return_to_launch_return_altitude(): Action.pair_result {
    return this.get_return_to_launch_return_altitude();
  }
}


export namespace Action {

    export enum Result {
      UNKNOWN = "Unknown",
      SUCCESS = "Success",
      NO_SYSTEM = "No system",
      CONNECTION_ERROR = "Connection error",
      BUSY = "Busy",
      COMMAND_DENIED = "Command denied",
      COMMAND_DENIED_LANDED_STATE_UNKNOWN = "Command denied landed_state unknown",
      COMMAND_DENIED_NOT_LANDED = "Command denied not landed",
      TIMEOUT = "Timeout",
      VTOL_TRANSITION_SUPPORT_UNKNOWN = "VTOL transistion support unknown",
      NO_VTOL_TRANSITION_SUPPORT = "No VTOL transition support",
      PARAMETER_ERROR = "Parameter error"
    }
    
    export interface pair_result{
      result: string,
      value: number | string
    }
}
