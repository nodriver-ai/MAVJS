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
  
    export interface result_callback_t { 
      (result: Result): void 
    };
    
    export interface pair_result{
      result: string,
      value: number | string
    }
}

export interface Action {
    arm(): Action.Result,
    disarm(): Action.Result,
    kill(): Action.Result,
    reboot(): Action.Result,
    takeoff(): Action.Result,
    land(): Action.Result,
    return_to_launch(): Action.Result,
    goto_location(latitude_deg: number, longitude_deg: number, altitude_amsl_m: number, yaw_deg: number): Action.Result,
    transition_to_fixedwing(): Action.Result,
    transition_to_multicopter(): Action.Result,
    arm_async(callback: Action.result_callback_t): void,
    disarm_async(callback: Action.result_callback_t): void,
    kill_async(callback: Action.result_callback_t): void,
    takeoff_async(callback: Action.result_callback_t): void,
    land_async(callback: Action.result_callback_t): void,
    return_to_launch_async(callback: Action.result_callback_t): void,
    transition_to_fixedwing_async(callback: Action.result_callback_t): void,
    transition_to_multicopter_async(callback: Action.result_callback_t): void,
    set_takeoff_altitude(relative_altitude_m: number): Action.Result 
    get_takeoff_altitude(): Action.pair_result,
    set_max_speed(speed_m_s: number): Action.Result
    get_max_speed(): Action.pair_result,
    set_return_to_launch_return_altitude(relative_altitude_m: number): Action.Result,
    get_return_to_launch_return_altitude(): Action.pair_result
}

