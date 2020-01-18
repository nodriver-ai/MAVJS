import { expect } from 'chai';

import { Mavsdk, System, Telemetry } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('telemetry Async', function() {
  let _received_position = false;
  let _received_home_position = false;
  let _received_in_air = false;
  let _received_armed = false;
  let _received_quaternion = false;
  let _received_euler_angle = false;
  let _received_angular_velocity_body = false;
  let _received_ground_speed = false;
  let _received_imu_reading_ned = false;
  let _received_gps_info = false;
  let _received_battery = false;
  let _received_position_velocity_ned = false;
  let _received_actuator_control_target = false;
  
  let mavsdk: Mavsdk;
  let system: System;

  before(() => {
    mavsdk = new Mavsdk();
  })

  after(async () => {   
    mavsdk.close();
  })

  it("connect to SITL", (done) => {
    expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
    
    sleep(2000).then(() => {

        let uuids = mavsdk.system_uuids();
        expect(uuids.length).to.equal(1)

        system = mavsdk.system(uuids[0]);
        done();
    })
  })

  it('telemetry', async () => {
    let telemetry = system.telemetry();
      
    // we have to implement set rate async yet
    expect(telemetry.set_rate_position(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_home_position(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_in_air(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_attitude(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_ground_speed_ned(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_gps_info(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_battery(10)).to.equal(Telemetry.Result.SUCCESS);
    expect(telemetry.set_rate_actuator_control_target(10)).to.equal(Telemetry.Result.SUCCESS);
      
    telemetry.position_async((position) => {
        if (position) {_received_position = true}
    });
    telemetry.home_position_async((home_position) => {
        if (home_position) {_received_home_position = true}
    });
    telemetry.attitude_quaternion_async((attitude) => {
        if (attitude) {_received_quaternion = true}
    });
    telemetry.attitude_euler_angle_async((attitude) => {
        if (attitude) {_received_euler_angle = true}
    });
    telemetry.attitude_angular_velocity_body_async((attitude) => {
        if (attitude) {_received_angular_velocity_body = true}
    });
    telemetry.ground_speed_ned_async((speed) => {
        if (speed) {_received_ground_speed = true}
    });
    telemetry.gps_info_async((gps) => {
        if (gps) {_received_gps_info = true}
    });
    telemetry.battery_async((battery) => {
        if (battery) {_received_battery = true}
    });
    telemetry.imu_reading_ned_async((imu) => {
        if (imu) {_received_imu_reading_ned = true}
    });
    telemetry.actuator_control_target_async((actuator) => {
        if (actuator) {_received_actuator_control_target = true}
    });
    telemetry.in_air_async((in_air) => {
        _received_in_air = true;
    });
    telemetry.armed_async((armed) => {
        _received_armed = true;
    })
    telemetry.position_velocity_ned_async((value) => {
        if (value) {_received_position_velocity_ned = true}
    })

    await sleep(10000)
    expect(_received_armed).to.equal(true);
    expect(_received_battery).to.equal(true);
    expect(_received_euler_angle).to.equal(true);
    expect(_received_gps_info).to.equal(true);
    expect(_received_ground_speed).to.equal(true);
    expect(_received_home_position).to.equal(true);
    expect(_received_imu_reading_ned).to.equal(true);
    expect(_received_in_air).to.equal(true);
    expect(_received_position).to.equal(true);
    expect(_received_angular_velocity_body).to.equal(true);
    expect(_received_position_velocity_ned).to.equal(true);
    expect(_received_quaternion).to.equal(true);
    expect(_received_actuator_control_target).to.equal(true);
    
  });
  
});