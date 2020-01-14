/**
 * @file fly_mission.ts
 *
 * @brief Demonstrates how to Add & Fly Waypoint missions using the MAVJS.
 * The example is summarised below:
 * 1. Adds mission items.
 * 2. Starts mission from first mission item.
 * 3. Illustrates Pause/Resume mission item.
 * 4. Exits after the mission is accomplished.
 *
 * @author Andrea Pomente <andrea.pomente@nodriver.ai>,
 * @date 2020-
 * */
import { Mavsdk, MissionItem, Mission, Action } from "../lib/addon";

function usage(bin_name: string): void
{
    console.log(`Usage : ${bin_name} <connection_url>
                Connection URL format should be :
                For TCP : tcp://[server_host][:server_port]
                For UDP : udp://[bind_host][:bind_port]
                For Serial : serial:///path/to/serial/dev[:baudrate]
                For example, to connect to the simulator use URL: udp://:14540`);
}

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

function make_mission_item(
    latitude_deg: number,
    longitude_deg: number,
    relative_altitude_m: number,
    speed_m_s: number,
    is_fly_through: boolean,
    gimbal_pitch_deg: number,
    gimbal_yaw_deg: number,
    camera_action: MissionItem.CameraAction)
{
    let new_item = new MissionItem();
    new_item.set_position(latitude_deg, longitude_deg);
    new_item.set_relative_altitude(relative_altitude_m);
    new_item.set_speed(speed_m_s);
    new_item.set_fly_through(is_fly_through);
    new_item.set_gimbal_pitch_and_yaw(gimbal_pitch_deg, gimbal_yaw_deg);
    new_item.set_camera_action(camera_action);
    return new_item.to_object();
}


let main = async () => {
    
    const argc = process.argv.length - 2;

    let mavsdk = new Mavsdk();

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

    console.log("Waiting to discover system...");
    {
        let prom = function() {
            return new Promise((resolve) => {
                    mavsdk.register_on_discover((uuid) => {
                    console.log(`Discovered system with UUID: ${uuid}`);
                    resolve();
                });
            });
        }

        await prom();
    }
    
    mavsdk.register_on_timeout((uuid) => {
        console.log(`System with UUID timed out: ${uuid}`);
        process.exit();
    })

    // We don't need to specifiy the UUID if it's only one system anyway.
    // If there were multiple, we could specify it with:
    // mavsdk.system(uuid: number);
    let system = mavsdk.system();
    
    let telemetry = system.telemetry();
    let action = system.action();
    let mission = system.mission();

    // Check if vehicle is ready to arm
    while (telemetry.health_all_ok() != true) {
        console.log("Vehicle is getting ready to arm")
        await sleep(1000);
    }

    console.log("System ready");
    console.log("Creating and uploading mission");

    let mission_items = [];

    mission_items.push(make_mission_item(
        47.398170327054473,
        8.5456490218639658,
        10.0,
        5.0,
        false,
        20.0,
        60.0,
        MissionItem.CameraAction.NONE));

    mission_items.push(make_mission_item(
        47.398241338125118,
        8.5455360114574432,
        10.0,
        2.0,
        true,
        0.0,
        -60.0,
        MissionItem.CameraAction.TAKE_PHOTO));

    mission_items.push(make_mission_item(
        47.398139363821485,
        8.5453846156597137,
        10.0,
        5.0,
        true,
        -45.0,
        0.0,
        MissionItem.CameraAction.START_VIDEO));

    mission_items.push(make_mission_item(
        47.398058617228855,
        8.5454618036746979,
        10.0,
        2.0,
        false,
        -90.0,
        30.0,
        MissionItem.CameraAction.STOP_VIDEO));

    mission_items.push(make_mission_item(
        47.398100366082858,
        8.5456969141960144,
        10.0,
        5.0,
        false,
        -45.0,
        -30.0,
        MissionItem.CameraAction.START_PHOTO_INTERVAL));

    mission_items.push(make_mission_item(
        47.398001890458097,
        8.5455576181411743,
        10.0,
        5.0,
        false,
        0.0,
        0.0,
        MissionItem.CameraAction.STOP_PHOTO_INTERVAL));

    console.log("Uploading mission...");
    {
        let result = await mission.upload_mission_async(mission_items)
        
        if (result != Mission.Result.SUCCESS) {
            console.log(`Mission upload failed ${result}, exiting.`)
            process.exit();
        }
    }   
    console.log("Mission uploaded.");

    // Arm vehicle
    console.log("Arming...");
    let arm_result: Action.Result = action.arm();

    if (arm_result != Action.Result.SUCCESS) {
        console.log(`Arming failed: ${arm_result}`)
        process.exit();
    }

    let want_to_pause: boolean = false;
    // Before starting the mission, we want to be sure to subscribe to the mission progress.
    mission.subscribe_progress((progress) => {
        console.log(`Mission status update: ${progress.current} / ${progress.total}`);

        if (progress.current >= 2) {
            // We can only set a flag here. If we do more request inside the callback,
            // we risk blocking the system.
            want_to_pause = true;
        }
    });

    {
        console.log("Starting mission.");
        let result = await mission.start_mission_async();

        if (result != Mission.Result.SUCCESS) {
            console.log(`Mission start failed: ${result}`);
            process.exit();
        } else {
            console.log("Started mission.");
        }
    }

    while (!want_to_pause) {
        await sleep(1000);
    }

    {
        console.log("Pausing mission...");
        let result = await mission.pause_mission_async();

        if (result != Mission.Result.SUCCESS) {
            console.log(`Failed to pause mission: ${result}`);
            process.exit();
        } else {
            console.log("Mission paused.");
        }
    }

    // Pause for 5 seconds.
    await sleep(5000);

    // Then continue.
    {
        console.log("Resuming mission...");
        let result = await mission.start_mission_async();

        if (result != Mission.Result.SUCCESS) {
            console.log(`Failed to resume mission: ${result}`);
            process.exit();
        } else {
            console.log("Resumed mission.");
        }
    }

    while (!mission.mission_finished()) {
        await sleep(1000);
    }

    {
        // We are done, and can do RTL to go home.
        console.log("Commanding RTL...");
        let result = action.return_to_launch();

        if (result != Action.Result.SUCCESS) {
            console.log(`Failed to command RTL: ${result}`);
            process.exit();
        } else {
            console.log("Commanded RTL.");
        }
    }

    // We need to wait a bit, otherwise the armed state might not be correct yet.
    await sleep(2000);

    while (telemetry.armed()) {
        // Wait until we're done.
        await sleep(1000);
    }


    console.log("Disarmed, exiting.");
   
    process.exit();
}

main();