const addon = require('bindings')('ndbox');

exports.Camera = addon.Camera;
exports.Ndbox = addon.Ndbox;
exports.Drone = addon.Drone;

/*const UDP_PATH = "udp://:14540";

ndbox = new addon.Ndbox(UDP_PATH)

let uuids = []

const uuidsInterval = setInterval(() => {
  uuids = ndbox.discover_uuids()
  console.log(uuids)
}, 1000);

setTimeout(() => {
  if (uuids.length > 0) {
    drone = ndbox.connect_to_drone(uuids[0])
    drone.set_rate_battery(0.2)
    const positionInterval = setInterval(() => {
      //battery = drone.battery()
      //console.log(battery)
      console.log(drone.flight_mode())
    }, 1000)
  }

}, 2000)*/
