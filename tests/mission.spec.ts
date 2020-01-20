import { expect } from 'chai';

import { Mavsdk, System, Telemetry, Action, Mission, MissionItem } from "../lib/addon";

let pause_already_done = false;

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

function make_mission_item(
    latitude_deg: number,
    longitude_deg: number,
    relative_altitude_m: number,
    speed_m_s: number,
    is_fly_through: boolean,
    gimbal_pitch_deg: number,
    gimbal_yaw_deg: number,
    camera_action: MissionItem.CameraAction)
{
    let new_item = new MissionItem();
    new_item.set_position(latitude_deg, longitude_deg);
    new_item.set_relative_altitude(relative_altitude_m);
    new_item.set_speed(speed_m_s);
    new_item.set_fly_through(is_fly_through);
    new_item.set_gimbal_pitch_and_yaw(gimbal_pitch_deg, gimbal_yaw_deg);
    new_item.set_camera_action(camera_action);
    return new_item.to_object();
}

describe('takeoff and hover Async', function() {
  
    let mavsdk: Mavsdk;
    let system: System;
    let telemetry: Telemetry;
    let action: Action;
    let mission: Mission;

    let mission_items = [];

    before(() => {
        mavsdk = new Mavsdk();
    })

    after(async () => {   
        mavsdk.close();
    })

    it("connect to SITL", async () => {
        expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
        {
            let prom = function() {
                return new Promise((resolve) => {
                        mavsdk.register_on_discover((uuid) => {
                            resolve();
                    });
                });
            }

            await prom();
        }

        mavsdk.register_on_discover(null);
    })

    it('system has autopilot', async () => {
        system = mavsdk.system();
        expect(system.has_autopilot()).to.equal(true);

        telemetry = system.telemetry();
        action = system.action();
        mission = system.mission();
    });
    
    it('set return to launch', async () => {
        let result = action.set_return_to_launch_return_altitude(10);
        expect(result).to.equal(Action.Result.SUCCESS);

        mission.set_return_to_launch_after_mission(true);
        expect(mission.get_return_to_launch_after_mission()).equal(true);
    })
    
    it('upload mission', async () => {
        while (!telemetry.health_all_ok()) {
            await sleep(1000);
        }

        mission_items.push(make_mission_item(
            47.398170327054473,
            8.5456490218639658,
            10.0,
            5.0,
            false,
            20.0,
            60.0,
            MissionItem.CameraAction.NONE));

        mission_items.push(make_mission_item(
            47.398241338125118,
            8.5455360114574432,
            10.0,
            2.0,
            true,
            0.0,
            -60.0,
            MissionItem.CameraAction.TAKE_PHOTO));

        mission_items.push(make_mission_item(
            47.398139363821485,
            8.5453846156597137,
            10.0,
            5.0,
            true,
            -45.0,
            0.0,
            MissionItem.CameraAction.START_VIDEO));

        mission_items.push(make_mission_item(
            47.398058617228855,
            8.5454618036746979,
            10.0,
            2.0,
            false,
            -90.0,
            30.0,
            MissionItem.CameraAction.STOP_VIDEO));

        mission_items.push(make_mission_item(
            47.398100366082858,
            8.5456969141960144,
            10.0,
            5.0,
            false,
            -45.0,
            -30.0,
            MissionItem.CameraAction.START_PHOTO_INTERVAL));

        mission_items.push(make_mission_item(
            47.398001890458097,
            8.5455576181411743,
            10.0,
            5.0,
            false,
            0.0,
            0.0,
            MissionItem.CameraAction.STOP_PHOTO_INTERVAL));
        
        let result = await mission.upload_mission_async(mission_items)
        expect(result).to.equal(Mission.Result.SUCCESS);
         
    })

    it('download mission', async () => {
        let result = await mission.download_mission_async()
        expect(result.result).to.equal(Mission.Result.SUCCESS);

        expect(result.mission_items.length).to.equal(mission_items.length);

        for (let i=0; i < result.mission_items.length; i++) {
            result.mission_items[i].latitude_deg = Math.round(result.mission_items[i].latitude_deg *100) / 100
            result.mission_items[i].longitude_deg = Math.round(result.mission_items[i].longitude_deg *100) / 100

            mission_items[i].latitude_deg = Math.round(mission_items[i].latitude_deg *100) / 100
            mission_items[i].longitude_deg = Math.round(mission_items[i].longitude_deg *100) / 100

            expect(result.mission_items[i]).to.deep.equal(mission_items[i])
        }
        
        expect(mission.get_return_to_launch_after_mission()).to.equal(true);
    });

    it('start mission', async () => {
        let arm_result = action.arm();
        expect(arm_result).to.equal(Action.Result.SUCCESS);

        
        let result = await mission.start_mission_async()
        expect(result).to.equal(Mission.Result.SUCCESS);
    });

    it('pause and resume mission', async () => {
        mission.subscribe_progress(async (result) => {
            if (result.current >= 2 && !pause_already_done) {
                pause_already_done = true;
                {
                    let result = await mission.pause_mission_async()
                    expect(result).to.equal(Mission.Result.SUCCESS);
                }  
            
                await sleep(5000);
                {
                    let result = await mission.start_mission_async()
                    expect(result).to.equal(Mission.Result.SUCCESS);
                }  
            }
        });
    })
        
    it('clear mission', async () => {
        while (!mission.mission_finished()) {
            await sleep(1000);
        }

        while (telemetry.armed()) {
            // Wait until we're done.
            await sleep(1000);
        }

        let result = await mission.clear_mission_async()
        expect(result).to.equal(Mission.Result.SUCCESS);
    })

});