import { IMissionItem } from "./missionItem";

export namespace Mission {

    export enum Result {
        UNKNOWN = "Unknown",
        SUCCESS = "Success",
        ERROR = "Error",
        TOO_MANY_MISSION_ITEMS = "Too many mission items",
        BUSY = "Busy",
        TIMEOUT = "Timeout",
        UNSUPPORTED = "Unsupported",
        NO_MISSION_AVAILABLE = "No mission available",
        FAILED_TO_OPEN_QGC_PLAN = "Failed to open qgc plan",
        FAILED_TO_PARSE_QGC_PLAN = "Failed to parse qgc plan",
        UNSUPPORTED_MISSION_CMD = "Unsupported mission cmd",
        CANCELLED = "Cancelled"
    }

   export interface MissionItems_and_Result {
       result: Result,
       mission_items: IMissionItem[]
   }

}

export interface Mission {
    upload_mission_async(mission_items: IMissionItem[]): Promise<Mission.Result>,
    upload_mission_cancel(): void,
    download_mission_async(): Promise<Mission.MissionItems_and_Result>,
    download_mission_cancel(): void,
    set_return_to_launch_after_mission(enable: boolean): void,
    get_return_to_launch_after_mission(): boolean
}