import { expect } from 'chai';

import { Mavsdk, System, Telemetry, Action } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('takeoff and hover Async', function() {
  
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
    }

    action.set_takeoff_altitude(5);
  })

  it('arm async', async () => {
    let result = await action.arm_async();
    expect(result).to.equal(Action.Result.SUCCESS);
  });

  it('takeoff async', async () => {
    let result = await action.takeoff_async();
    expect(result).to.equal(Action.Result.SUCCESS);

    await sleep(8000);
  });

  it('land async', async () => {
    let result = await action.land_async();
    expect(result).to.equal(Action.Result.SUCCESS);
  });

  it('disarm async', async () => {
    let prom = function() {
        return new Promise((resolve) => {
                telemetry.in_air_async((in_air) => {
                    if (!in_air) {
                        telemetry.in_air_async(null);
                        resolve();
                    }
                    
            });
        });
    }

    await prom();

    let result = await action.disarm_async();
    expect(result).to.equal(Action.Result.SUCCESS);
  });
  
});