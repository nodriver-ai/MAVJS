import { Mavsdk, System, Telemetry, MissionItem, Info, Action } from "./addon";

let mavsdk = new Mavsdk.Init();

mavsdk.add_udp_connection();

/*setInterval(() => {
    console.log(mavsdk.system_uuids())
}, 1000)*/

//console.log(mavsdk.system().get_uuid())
let uuids: string[] = [];

/*setTimeout(function() {
    console.log(uuids)
    //system = mavsdk.system()

    //console.log(system.get_uuid())
    console.log("okkkkkkkkkkk")
    //mavsdk = null;

}, 5000);*/


mavsdk.register_on_discover((uuid) => {
    uuids.push(uuid)
    console.log("Ok")
})

let system: System;
let telemetry: Telemetry;
let action: Action

setTimeout(() => {
    system = mavsdk.system(uuids[0])
    console.log(system.has_camera())
    telemetry = system.telemetry()
    telemetry.set_rate_position_velocity_ned(1);
    console.log(telemetry.gps_info())
}, 5000);


setTimeout(() => {
    action = system.action();
    action.kill_async((arg) => {

    })
}, 8000);

setTimeout(() => {
    mavsdk.unregister_on_discover();
}, 10000);


