import { expect } from 'chai';

import { Mavsdk, System, Telemetry } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('telemetry Sync', function() {
  
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
        system = mavsdk.system();
        expect(system.is_connected()).to.equal(true);
        done();
    })
  })

  it('telemetry', async () => {
      let telemetry = system.telemetry();

      expect(telemetry.set_rate_position(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_home_position(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_in_air(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_attitude(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_ground_speed_ned(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_gps_info(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_battery(10)).to.equal(Telemetry.Result.SUCCESS);
      expect(telemetry.set_rate_actuator_control_target(10)).to.equal(Telemetry.Result.SUCCESS);

      for (let i = 0; i < 10; i++) {
          expect(typeof telemetry.position()).not.be.undefined;
          expect(typeof telemetry.home_position()).not.be.undefined;
          expect(typeof telemetry.attitude_quaternion()).not.be.undefined;
          expect(typeof telemetry.attitude_euler_angle()).not.be.undefined;
          expect(typeof telemetry.attitude_angular_velocity_body()).not.be.undefined;
          expect(typeof telemetry.ground_speed_ned()).not.be.undefined;
          expect(typeof telemetry.gps_info()).not.be.undefined;
          expect(typeof telemetry.battery()).not.be.undefined;
          expect(typeof telemetry.actuator_control_target()).not.be.undefined;
          expect(typeof telemetry.flight_mode()).not.be.undefined;
          expect(typeof telemetry.in_air()).not.be.undefined;

          await sleep(500);
      }
  });
  
});