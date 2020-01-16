import { expect } from 'chai';

import { Mavsdk, MissionItem, Mission, Action, Telemetry } from "../lib/addon";

const connection_url: string = "udp://:14540";

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


describe('Connection', function() {
  
  let mavsdk: Mavsdk, mavsdk_, system, telemetry, action, mission;

  after(async () => {   
    mavsdk.close();
  })

  it("connect to SITL", () => {
    mavsdk_ = new Mavsdk();

    const connection_result = mavsdk_.add_any_connection(connection_url);
    expect(connection_result).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
  })

  it('discover system', async () => {
    let discovered_system: boolean = false;

    mavsdk_.register_on_discover((uuid) => {
      discovered_system = true;
    });

    // We usually receive heartbeats at 1Hz, therefore we should find a system after around 2
    // seconds.
    await sleep(2000);

    expect(discovered_system).to.equal(true);

    system = mavsdk_.system();
    
    telemetry = system.telemetry();
    action = system.action(); 
    mission = system.mission();
  });

  it('stop connection', async () => {
    let discovered_system: boolean = false;

    mavsdk_.close();
  });

  it("connect to SITL 2", () => {
    mavsdk = new Mavsdk();

    const connection_result = mavsdk.add_any_connection(connection_url);
    expect(connection_result).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
  })

  it('discover system 2', async () => {
    let discovered_system: boolean = false;

    mavsdk.register_on_discover((uuid) => {
      discovered_system = true;
    });

    // We usually receive heartbeats at 1Hz, therefore we should find a system after around 2
    // seconds.
    await sleep(2000);

    expect(discovered_system).to.equal(true);

    system = mavsdk.system();
    
    telemetry = system.telemetry();
    action = system.action(); 
    mission= system.mission();
  });


  

  /*describe('Fly mission', function() {
    after(async () => {
      while (telemetry.armed()) {
        // Wait until we're done.
        await sleep(1000);
      }
    })
    
    it('upload mission', async () => {
      // We want to listen to the altitude of the drone at 1 Hz.
      // Check if vehicle is ready to arm
      while (telemetry.health_all_ok() != true) {
          await sleep(1000);
      }
      let mission_items = [];
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
      
      let result = await mission.upload_mission_async(mission_items);
      expect(result).to.equal(Mission.Result.SUCCESS); 
    })
    
    it('arm', async () => {
      // We want to listen to the altitude of the drone at 1 Hz.
      // Arm vehicle
      await sleep(2000);
      
      let arm_result: Action.Result = action.arm();
      expect(arm_result).to.equal(Action.Result.SUCCESS); 
    })
    it('start mission', async () => {
      let result = await mission.start_mission_async();
      expect(result).to.equal(Mission.Result.SUCCESS); 
    })
    it('pause mission', async() => {
      await sleep(5000);
      let result = await mission.pause_mission_async();
      expect(result).to.equal(Mission.Result.SUCCESS); 
    })
    it('resume mission', async() => {
      await sleep(5000);
      let result = await mission.start_mission_async();
      expect(result).to.equal(Mission.Result.SUCCESS); 
    })
    it('RTL command', async() => {
      await sleep(5000);
      let result = action.return_to_launch();
      expect(result).to.equal(Action.Result.SUCCESS); 
    })
  });*/

});