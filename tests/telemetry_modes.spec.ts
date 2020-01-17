import { expect } from 'chai';

import { Mavsdk, System, Telemetry } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('telemetry modes', function() {

  let _flight_mode: Telemetry.FlightMode = Telemetry.FlightMode.UNKNOWN;
  
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

  it('flight mode', (done) => {
      let telemetry = system.telemetry();
      let action = system.action();

      telemetry.flight_mode_async((flight_mode) => {
        _flight_mode = flight_mode;
      })

      while (!telemetry.health_all_ok()) {
         sleep(1000).then(() => {});
      }

      action.arm();
      sleep(2000).then(() => {
        action.takeoff();

        sleep(2000).then(() => {
            expect(_flight_mode).to.equal(Telemetry.FlightMode.TAKEOFF);
            action.land();

            sleep(2000).then(() => {
                expect(_flight_mode).to.equal(Telemetry.FlightMode.LAND);

                done();
              }).catch((err) => {
                done(err);
            });;
          }).catch((err) => {
            done(err);
        });;
      }).catch((err) => {
        done(err);
    });;
  });
  
});