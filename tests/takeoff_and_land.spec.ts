import { expect } from 'chai';

import { Mavsdk, System, Telemetry, Action } from "../lib/addon";

function component_discovered(component_type: System.ComponentType) {
    console.log(`Discovered a component with type ${component_type}`);
}

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

after(function (done) {
  process.exit();
});


describe('Takeoff and land', async () => { 
  let mavsdk = new Mavsdk();
  
  const connection_url: string = "udp://:14540";

  it('connection', () => {
    let connection_result: Mavsdk.ConnectionResult = mavsdk.add_any_connection(connection_url);
    expect(connection_result).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
  });

  let system = mavsdk.system();

  it('discover system', async () => {
    let discovered_system: boolean = false;

    mavsdk.register_on_discover((uuid) => {
      discovered_system = true;
    });

    // We usually receive heartbeats at 1Hz, therefore we should find a system after around 2
    // seconds.
    await sleep(2000);

    expect(discovered_system).to.equal(true);
  });

  let telemetry = system.telemetry();
  let action = system.action();

  it('set rate position', async () => {
    // We want to listen to the altitude of the drone at 1 Hz.
    const set_rate_result: Telemetry.Result = telemetry.set_rate_position(1.0);
    expect(set_rate_result).to.equal(Telemetry.Result.SUCCESS); 
  })

  it('position telemetry', async () => {
    // We want to listen to the altitude of the drone at 1 Hz.
    let position = telemetry.position();
    expect(position).to.be.an('object');
  })

  it('arm', async () => {
    // Check if vehicle is ready to arm
    while (telemetry.health_all_ok() != true) {
      await sleep(1000);
    }
    // We want to listen to the altitude of the drone at 1 Hz.
    // Arm vehicle
    let arm_result: Action.Result = action.arm();
    expect(arm_result).to.equal(Action.Result.SUCCESS); 
  })

  it('takeoff', async () => {
    // Take off
    let takeoff_result: Action.Result = action.takeoff();
    expect(takeoff_result).to.equal(Action.Result.SUCCESS); 
  })

  it('land', async() => {
    // Let it hover for a bit before landing again.
    await sleep(10000);
    let land_result: Action.Result = action.land();
    expect(land_result).to.equal(Action.Result.SUCCESS); 
  })
    
});