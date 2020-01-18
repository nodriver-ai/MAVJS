import { expect } from 'chai';

import { Mavsdk, System, Telemetry, Action } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('takeoff and kill', function() {

  let _flight_mode: Telemetry.FlightMode = Telemetry.FlightMode.UNKNOWN;
  
  let mavsdk: Mavsdk;
  let system: System;
  let telemetry: Telemetry;
  let action: Action

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

    system = mavsdk.system();
    telemetry = system.telemetry();
    action = system.action();

    {
        let prom = function() {
            return new Promise((resolve) => {
                    telemetry.health_all_ok_async((all_ok) => {
                    if (all_ok) {
                        telemetry.health_all_ok_async(null);
                        resolve();
                    }
                });
            });
        }
    
        await prom();
        console.log("fatto")
    }

    action.set_takeoff_altitude(1.5);
  })

  it('arm async', async () => {
    let result = await action.arm_async();
    expect(result).to.equal(Action.Result.SUCCESS);
  });

  it('takeoff async', async () => {
    let result = await action.takeoff_async();
    expect(result).to.equal(Action.Result.SUCCESS);

    await sleep(8000);

    expect(telemetry.position().relative_altitude_m).to.greaterThan(0.2);
  });

  it('kill async', async () => {
    let result = await action.kill_async();
    expect(result).to.equal(Action.Result.SUCCESS);

    await sleep(2000);
    expect(telemetry.armed()).to.equal(false);
    await sleep(2000);
    expect(telemetry.in_air()).to.equal(false);
  });
  
});