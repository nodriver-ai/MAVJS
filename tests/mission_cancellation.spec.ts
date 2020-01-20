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
    take_photo: boolean)
{
    let new_item = new MissionItem();
    new_item.set_position(latitude_deg, longitude_deg);
    new_item.set_relative_altitude(relative_altitude_m);
    new_item.set_speed(speed_m_s);
    new_item.set_fly_through(is_fly_through);
    new_item.set_gimbal_pitch_and_yaw(gimbal_pitch_deg, gimbal_yaw_deg);
    if (take_photo) {
        new_item.set_camera_action(MissionItem.CameraAction.TAKE_PHOTO);
    }
    return new_item.to_object();
}

describe('mission cancellation', function() {
  
    let mavsdk: Mavsdk;
    let system: System;
    let mission: Mission;

    before(() => {
        mavsdk = new Mavsdk();
    })

    after(async () => {   
        mavsdk.close();
    })

    it("connect to SITL", async () => {
        expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
        
        await sleep(2000);

        expect(mavsdk.is_connected()).to.equal(true);

        system = mavsdk.system();
        expect(system.has_autopilot()).to.equal(true);

        mission = system.mission();
    })

    
    it('upload mission and cancel', (done) => {
        let mission_items = [];

        for (let i = 0; i < 1000; ++i) {
            mission_items.push(
                make_mission_item(47.3981703270545, 8.54564902186397, 20.0, 3.0, true, -90.0, 0.0, false));
        }

        
        mission.upload_mission_async(mission_items).then((result) => {
            expect(result).to.equal(Mission.Result.CANCELLED);
        }).catch((err) => {
            done(err);
        })

        sleep(1000).then(async () => {
            mission.upload_mission_cancel();
            await sleep(8000);
            done();
        })
        
    })

    it('upload mission', async () => {
        let mission_items = [];

        for (let i = 0; i < 500; ++i) {
            mission_items.push(
                make_mission_item(47.3981703270545, 8.54564902186397, 20.0, 3.0, true, -90.0, 0.0, false));
        }

        let result = await mission.upload_mission_async(mission_items);
        expect(result).to.equal(Mission.Result.SUCCESS);
    })

    it('download mission and cancel', (done) => {
        mission.download_mission_async().then((result) => {
            expect(result.result).to.equal(Mission.Result.CANCELLED);
            done()
        }).catch((err) => {
            done(err);
        })

        sleep(1000).then(async () => {
            mission.download_mission_cancel();
        })
        
    });

});