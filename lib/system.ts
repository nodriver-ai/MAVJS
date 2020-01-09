import { Telemetry } from "./plugins/telemetry";
import { Action } from "./plugins/action";
import { Info } from "./plugins/info";
import { Mission } from "./plugins/mission";

export namespace System {
  export enum ComponentType {
    UNKNOWN = 0, 
    AUTOPILOT, 
    CAMERA, 
    GIMBAL 
  };
      
  export interface discover_callback_t { (component_type: ComponentType): void };
}

export interface System {
  has_autopilot(): boolean,
  is_standalone(): boolean,
  has_camera(camera_id?: number): boolean,
  has_gimbal(): boolean,
  is_connected(): boolean,
  get_uuid(): string,
  telemetry(): Telemetry,
  action(): Action,
  info(): Info,
  mission(): Mission,
  register_component_discovered_callback(callback: System.discover_callback_t): void,
  unregister_component_discovered_callback(): void,
}
  