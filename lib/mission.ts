import { IMissionItem } from "./missionItem";

/**
 * The Mission class enables waypoint missions.
 * 
 * The plugin is typically created as shown below: ```let mission = system.mission()```
 */
export class Mission {

    /**
     * Uploads a vector of mission items to the system (asynchronous).
     * 
     * The mission items are uploaded to a drone. Once uploaded the mission can be started and executed even if a connection is lost.
     * @param mission_items Reference to vector of mission items
     * @returns Result of request.
     */
    upload_mission_async(mission_items: IMissionItem[]): Promise<Mission.Result> {
        return this.upload_mission_async(mission_items);
    }

    /**
     * Cancel a mission upload (asynchronous).
     * 
     * This cancels an ongoing mission upload. The mission upload will fail with the result [[Result.CANCELLED]].
     */
    upload_mission_cancel(): void {
        this.upload_mission_cancel();
    }

    /**
     * Downloads a vector of mission items from the system (asynchronous).
     * 
     * The method will fail if any of the downloaded mission items are not supported by the MAVSDK API.
     * @returns Result of request.
     */
    download_mission_async(): Promise<Mission.MissionItems_and_Result> {
        return this.download_mission_async();
    }

    /**
     * Cancel a mission download (asynchronous).
     * 
     * This cancels an ongoing mission download. The mission download will fail with the result [[Result.CANCELLED]].
     */
    download_mission_cancel(): void {
        this.download_mission_cancel();
    }

    /**
     * Set whether to trigger Return-to-Launch (RTL) after mission is complete.
     * 
     * This enables/disables to command RTL at the end of a mission.
     * 
     * Note: After setting this option, the mission needs to be re-uploaded.
     * @param enable Enables RTL after mission is complete.
     */
    set_return_to_launch_after_mission(enable: boolean): void {
        this.set_return_to_launch_after_mission(enable);
    }

    /**
     * Get whether to trigger Return-to-Launch (RTL) after mission is complete.
     * 
     * Note: Before getting this option, it needs to be set, or a mission needs to be downloaded.
     * @returns True if RTL after mission is complete is enabled.
     */
    get_return_to_launch_after_mission(): boolean {
        return this.get_return_to_launch_after_mission();
    }

    /**
     * Starts the mission (asynchronous).
     * 
     * Note that the mission must be uploaded to the vehicle using [[upload_mission_async()]] before this method is called.
     * @returns Result of request.
     */
    start_mission_async(): Promise<Mission.Result> {
        return this.start_mission_async();
    }

    /**
     * Pauses the mission (asynchronous).
     * 
     * Pausing the mission puts the vehicle into [HOLD mode](https://docs.px4.io/v1.9.0/en/flight_modes/hold.html). A multicopter should just hover at the spot while a fixedwing vehicle should loiter around the location where it paused.
     * @returns Result of request.
     */
    pause_mission_async(): Promise<Mission.Result> {
        return this.pause_mission_async();
    }

    /**
     * Clears the mission saved on the vehicle (asynchronous).
     * @returns Result of request.
     */
    clear_mission_async(): Promise<Mission.Result> {
        return this.clear_mission_async();
    }

    /**
     * Sets the mission item index to go to (asynchronous).
     * 
     * By setting the current index to 0, the mission is restarted from the beginning. If it is set to a specific index of a mission item, the mission will be set to this item.
     * 
     * Note that this is not necessarily true for general missions using MAVLink if loop counters are used.
     * @param current Index for mission index to go to next (0 based).
     * @returns Result of request.
     */
    set_current_mission_item_async(current: number): Promise<Mission.Result> {
        return this.set_current_mission_item_async(current);
    }

    /**
     * Checks if mission has been finished (synchronous).
     * @returns true if mission is finished and the last mission item has been reached.
     */
    mission_finished(): boolean {
        return this.mission_finished();
    }

    /**
     * Returns the current mission item index (synchronous).
     * 
     * If the mission is finished, the current mission item will be the total number of mission items (so the last mission item index + 1).
     * @returns current mission item index (0 based).
     */
    current_mission_item(): number {
        return this.current_mission_item();
    }

    /**
     * Returns the total number of mission items (synchronous).
     * @returns total number of mission items
     */
    total_mission_items(): number {
        return this.total_mission_items();
    }

    /**
     * Subscribes to mission progress (asynchronous).
     * @param callback Callback to receive mission progress.
     */
    subscribe_progress(callback?: Mission.progress_callback_t): void {
        this.subscribe_progress(callback);
    }
}

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

   export interface missionProgress {
       /** Current mission item index (0 based). */
       current: number,
       /** Total number of mission items. */
       total: number
   }

   export type progress_callback_t = 
    /**
     * Callback type to receive mission progress.
     * 
     * The mission is finished if current == total.
     * @param {progress_callback_t} progress
     */
    (progress: missionProgress) => void;

}