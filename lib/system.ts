import { Telemetry } from "./telemetry";
import { Action } from "./action";
import { Info } from "./info";
import { Mission } from "./mission";

/**
 * This class represents a system, made up of one or more components (e.g. autopilot, cameras, servos, gimbals, etc).

    [[System]] objects are used to interact with UAVs (including their components) and standalone cameras. They are not created directly by application code, but are returned by the [[Mavsdk]] class.
*/
export class System {

  /**
   * Checks whether the system has an autopilot.
   * @returns ```true``` if it has an autopilot, ```false``` otherwise.
   */
  has_autopilot(): boolean {
    return this.has_autopilot();
  }

  /**
   * Checks whether the system is a standalone (non-autopilot).
   * @returns ```true``` if stand alone, ```false``` otherwise.
   */
  is_standalone(): boolean {
    return this.is_standalone();
  }

  /**
   * Checks whether the system has a camera with the given camera ID.

    A [[System]] may have several cameras, with IDs starting from 0. When called without passing a camera ID, it checks whether the system has any camera.
   * @param camera_id ID of the camera starting from 0 onwards.
   * @returns ```true``` if camera with the given camera ID is found, ```false``` otherwise.
   */
  has_camera(camera_id: number = 1): boolean {
    return this.has_camera(camera_id);
  }

  /**
   * Checks whether the system has a gimbal.
   * @returns ```true``` if the system has a gimbal, ```false``` otherwise.
   */
  has_gimbal(): boolean {
    return this.has_gimbal();
  }

  /**
   * Checks if the system is connected.

     A system is connected when heartbeats are arriving (discovered and not timed out).
   * @returns  ```true```  if the system is connected.
   */
  is_connected(): boolean {
    return this.is_connected();
  }

  /**
   * Get the UUID of the system. 
   * @returns  UUID of system.
   */
  get_uuid(): string {
    return this.get_uuid();
  }

  /**
   * Get the telemetry plugin instance of the system
   * @returns A reference to the telemetry instance
   */
  telemetry(): Telemetry {
    return this.telemetry();
  }

  /**
   * Get the action plugin instance of the system
   * @returns A reference to the action instance
   */
  action(): Action {
    return this.action();
  }

  /**
   * Get the info plugin instance of the system
   * @returns A reference to the info instance
   */
  info(): Info {
    return this.info();
  }

  /**
   * Get the mission plugin instance of the system
   * @returns A reference to the mission instance
   */
  mission(): Mission {
    return this.mission();
  }

  /**
   * Register a callback to be called when a component is discovered.
   * @param callback a function of type void(ComponentType) which will be called with the component type of the new component.
   */
  register_component_discovered_callback(callback: System.discover_callback_t): void {
    return this.register_component_discovered_callback(callback);
  }
  
}

export namespace System {
  export enum ComponentType {
    UNKNOWN = 0, 
    AUTOPILOT = 1, 
    CAMERA = 2, 
    GIMBAL = 3 
  };
  
  export type discover_callback_t = 
    /**
     * Callback type for discover components notifications.
     * @param {discover_callback_t} component_type component type found.
     */
    (component_type: ComponentType) => void;
}