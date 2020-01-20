import { expect } from 'chai';

import { Mavsdk, System, Telemetry, Action } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('go to location', function() {
  
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
    
    await sleep(1000);

    expect(mavsdk.is_connected()).to.equal(true);

    system = mavsdk.system();
    telemetry = system.telemetry();
    action = system.action();

    let iteration = 0;
    while (!telemetry.health_all_ok()) {
        await sleep(1000);
        expect(++iteration).to.be.lessThan(10);
    }
  })

  it('arm', async () => {
    let result = action.arm();
    expect(result).to.equal(Action.Result.SUCCESS);
    await sleep(1000);
  });

  it('takeoff', async () => {
    let result = action.takeoff();
    expect(result).to.equal(Action.Result.SUCCESS);
    await sleep(2000);
  });

  it('go somewhere, back and land', async () => {
    action.goto_location(47.398000, 8.545592, null, null);
    await sleep(10000);

    action.goto_location(47.3977233, 8.545592, null, null);
    await sleep(10000);

    const action_ret = action.land();
    expect(action_ret).to.equal(Action.Result.SUCCESS);
  });

  it('disarm', async () => {
    let iteration = 0;
    while (telemetry.in_air()) {
        await sleep(1000);

        // TODO: currently we need to wait a long time until landed is detected.
        expect(++iteration).to.be.lessThan(20);
    }

    const action_ret = action.disarm();
    expect(action_ret).to.equal(Action.Result.SUCCESS);
    
  });
  
});