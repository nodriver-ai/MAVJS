import { expect } from 'chai';

import { Mavsdk, System, Telemetry, Action } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

async function takeoff_and_hover_at_altitude(altitude_m: number) {
    let mavsdk = new Mavsdk();

    expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS);

    await sleep(1000);

    expect(mavsdk.is_connected()).to.equal(true);

    let system = mavsdk.system();
    let telemetry = system.telemetry();

    await sleep(2000);
    
    expect(telemetry.health_all_ok()).to.equal(true);

    

    mavsdk.close();
}

describe('takeoff and hover Sync', function() {
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

    await sleep(2000);

    expect(mavsdk.is_connected()).to.equal(true);

    system = mavsdk.system();
    telemetry = system.telemetry();
    action = system.action();

    await sleep(2000);
  })

  it("altitude 2.5", async () => {
    const altitude_m = 2.5;

    expect(action.arm()).to.equal(Action.Result.SUCCESS);
    
    expect(action.set_takeoff_altitude(altitude_m)).to.equal(Action.Result.SUCCESS);

    const takeoff_altitude_result = action.get_takeoff_altitude();
    expect(takeoff_altitude_result.result).to.equal(Action.Result.SUCCESS);
    expect(takeoff_altitude_result.value).to.equal(altitude_m);

    const action_ret = action.takeoff();
    expect(action_ret).to.equal(Action.Result.SUCCESS);

    const wait_time_s = ((altitude_m * 2) + 8)*1000;
    
    await sleep(wait_time_s);
    
    expect(telemetry.position().relative_altitude_m).to.be.greaterThan(altitude_m - 0.25);
    expect(telemetry.position().relative_altitude_m).to.be.lessThan(altitude_m + 0.25);

    const action_ret_land = action.land();
    expect(action_ret_land).to.equal(Action.Result.SUCCESS);

    await sleep(wait_time_s);
    expect(telemetry.in_air()).to.equal(false);

    const action_ret_disarm = action.disarm();
    expect(action_ret_disarm).to.equal(Action.Result.SUCCESS);
  })
  
});