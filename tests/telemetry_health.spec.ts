import { expect } from 'chai';

import { Mavsdk, System, Telemetry } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('telemetry health', function() {
  
  let mavsdk: Mavsdk;
  let system: System;
  let _health: Telemetry.Health;

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

  it('flight health', async () => {
      let telemetry = system.telemetry();
      
      telemetry.health_async((health) => {
        _health = health;
      });

      await sleep(3000);
      expect(_health).not.be.undefined;
      expect(_health.accelerometer_calibration_ok).to.equal(true);
      expect(_health.global_position_ok).to.equal(true);
      expect(_health.gyrometer_calibration_ok).to.equal(true);
      expect(_health.home_position_ok).to.equal(true);
      expect(_health.level_calibration_ok).to.equal(true);
      expect(_health.local_position_ok).to.equal(true);
      expect(_health.magnetometer_calibration_ok).to.equal(true);

  });
  
});