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
  
    export interface result_callback_t{ (result: Result): void };
    export interface pair_result{
      result: string,
      value: number | string
    }
  
    export interface Action {
      arm(): Result,
      disarm(): Result,
      kill(): Result,
      reboot(): Result,
      takeoff(): Result,
      land(): Result,
      return_to_launch(): Result,
      goto_location(latitude_deg: number, longitude_deg: number, altitude_amsl_m: number, yaw_deg: number): Result,
      transition_to_fixedwing(): Result,
      transition_to_multicopter(): Result,
      arm_async(result_callback_t): void,
      disarm_async(result_callback_t): void,
      kill_async(result_callback_t): void,
      takeoff_async(result_callback_t): void,
      land_async(result_callback_t): void,
      return_to_launch_async(result_callback_t): void,
      transition_to_fixedwing_async(result_callback_t): void,
      transition_to_multicopter_async(result_callback_t): void,
      set_takeoff_altitude(relative_altitude_m: number): Result 
      get_takeoff_altitude(): pair_result,
      set_max_speed(speed_m_s: number): Result
      get_max_speed(): pair_result,
      set_return_to_launch_return_altitude(relative_altitude_m: number): Result,
      get_return_to_launch_return_altitude(): pair_result
    }
  }