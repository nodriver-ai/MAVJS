import { expect } from 'chai';

import { Mavsdk, System } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('telemetry health', function() {
  
  let mavsdk: Mavsdk;
  let system: System;

  before(() => {
    mavsdk = new Mavsdk();
  })

  after(async () => {   
    mavsdk.close();
  })

  it("connect to SITL", async () => {
    expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
    
    await sleep(2000)

    system = mavsdk.system();
  })

  it('flight health', (done) => {
      let telemetry = system.telemetry();

      telemetry.health_async((health) => {
        expect(health.accelerometer_calibration_ok).to.equal(true);
        expect(health.global_position_ok).to.equal(true);
        expect(health.gyrometer_calibration_ok).to.equal(true);
        expect(health.home_position_ok).to.equal(true);
        expect(health.level_calibration_ok).to.equal(true);
        expect(health.local_position_ok).to.equal(true);
        expect(health.magnetometer_calibration_ok).to.equal(true);
      })

      sleep(3000).then(() => done());
  });
  
});