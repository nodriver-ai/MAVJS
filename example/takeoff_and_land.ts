import { Mavsdk, System, Telemetry, Action } from "../lib/addon";

function usage(bin_name: string): void
{
    console.log(`Usage : ${bin_name} <connection_url>
                Connection URL format should be :
                For TCP : tcp://[server_host][:server_port]
                For UDP : udp://[bind_host][:bind_port]
                For Serial : serial:///path/to/serial/dev[:baudrate]
                For example, to connect to the simulator use URL: udp://:14540`);
}

function component_discovered(component_type: System.ComponentType) {
    console.log(`Discovered a component with type ${component_type}`);
}

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

let main = async () => {
    
    const argc = process.argv.length - 2;

    let mavsdk = new Mavsdk();

    let discovered_system: boolean = false;


    let connection_result: Mavsdk.ConnectionResult;
    if (argc == 1) {
        const connection_url: string = process.argv[2];
        connection_result = mavsdk.add_any_connection(connection_url);
    } else {
        usage(process.argv[1]);
        process.exit()
    }

    if (connection_result != Mavsdk.ConnectionResult.SUCCESS) {
        console.log(`Connection failed: ${connection_result.toString()}`);
        process.exit()
    }

    let system = mavsdk.system();

    console.log("Waiting to discover system...");
    mavsdk.register_on_discover((uuid) => {
        console.log(`Discovered system with UUID: ${uuid}`);
        discovered_system = true;
    });
    
    // We usually receive heartbeats at 1Hz, therefore we should find a system after around 2
    // seconds.
    await sleep(2000);

    if (!discovered_system) {
        console.log("No system found, exiting.");
        process.exit();
    }

    system.register_component_discovered_callback(component_discovered);

    let telemetry = system.telemetry();
    let action = system.action();

    // We want to listen to the altitude of the drone at 1 Hz.
    const set_rate_result: Telemetry.Result = telemetry.set_rate_position(1.0);
    if (set_rate_result != Telemetry.Result.SUCCESS) {
        console.log(`Setting rate failed: ${set_rate_result}`)
        process.exit();
    }

    //Monitor altitude while the vehicle is in flight
    setInterval(() => {
        let position = telemetry.position();
        console.log(`Altitude: ${position.relative_altitude_m} m`)
    }, 1000)

    // Check if vehicle is ready to arm
    while (telemetry.health_all_ok() != true) {
        console.log("Vehicle is getting ready to arm")
        await sleep(1000);
    }

    // Arm vehicle
    console.log("Arming...");
    let arm_result: Action.Result = action.arm();

    if (arm_result != Action.Result.SUCCESS) {
        console.log(`Arming failed: ${arm_result}`)
        process.exit();
    }

    // Take off
    console.log("Taking off...");
    let takeoff_result: Action.Result = action.takeoff();
    if (takeoff_result != Action.Result.SUCCESS) {
        console.log(`Takeoff failed: ${takeoff_result}`)
        process.exit();
    }

    // Let it hover for a bit before landing again.
    await sleep(10000);

    console.log("Landing...");
    let land_result: Action.Result = action.land();
    if (land_result != Action.Result.SUCCESS) {
        console.log(`Land failed: ${land_result}`)
    }

    // Check if vehicle is still in air
    while (telemetry.in_air()) {
        console.log("Vehicle is landing...");
        await sleep(1000);
    }
    console.log("Landed!");

    // We are relying on auto-disarming but let's keep watching the telemetry for a bit longer.
    await sleep(3000);
    console.log("Finished...");

    process.exit();
}

main();