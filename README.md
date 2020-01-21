# MAVJS

[![Build Status](https://travis-ci.com/nodriver-ai/MAVJS.svg?branch=master)](https://travis-ci.com/nodriver-ai/MAVJS)

Node.js wrapper for [mavlink/MAVSDK](https://github.com/mavlink/MAVSDK) C++ library using [node-addon-api](https://github.com/nodejs/node-addon-api). 

MAVJS is a Node.js addon, written in C++, that can be loaded into Node.js using the require() function, and used just as if they were an ordinary Node.js module.

The aim of the project is to provide an interface between JavaScript running in Node.js and MAVSDK C/C++ library.

> The library also provides types definition to use Typescript.

documentation: https://nodriver-ai.github.io/MAVJS/

## Prerequisites

Before starting to use MAVJS you need to assure you have the following prerequisites:

- **Node.js**: see [download and install Node.js](https://nodejs.org/en/download/) Node.js 10.0 or higher is required.
- **CMake**: see [CMake download](https://cmake.org/download/)
> Cmake needs because we use [CMake.js](https://github.com/cmake-js/cmake-js) to build the addon
- A proper C/C++ compiler toolchain of the given platform
    - **Windows**:
        - [Visual C++ Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
        or a recent version of Visual C++ will do ([the free Community](https://www.visualstudio.com/products/visual-studio-community-vs) version works well)
    - **Unix/Posix**:
        - Clang or GCC
        - Ninja or Make (Ninja will be picked if both present)
- **MAVSDK** **C++**: see installation guide [building SDK from Source](https://mavsdk.mavlink.io/develop/en/contributing/build.html) or Ubuntu and Fedora users can install the SDK from *.deb or *.rpm packages in the [Github release page](https://github.com/mavlink/MAVSDK/releases).
> MAVJS requires MAVSDK System-wide Install.

## Installation

This is a Node.js module available through the npm registry.

installation is done using the npm install command:
```bash
$ npm install MAVJS
```

## Getting started

```typescript
import { Mavsdk, System, Telemetry, Action } from "MAVJS";

//Create a Mavsdk instance
let mavsdk = new Mavsdk();

//Add connection
const connection_result = mavsdk.add_any_connection("udp://14540");

if (connection_result != Mavsdk.ConnectionResult.SUCCESS) {
    console.log(`Connection failed: ${connection_result.toString()}`);
    process.exit()
}

//Get the first system discovered
let system = mavsdk.system();

//Initialize telemtery and action objects
let telemetry = system.telemetry();
let action = system.action();

//Monitor altitude while the vehicle is in flight
telemetry.position_async((position) => {
    console.log(`Altitude: ${position.relative_altitude_m} m`)
})

// Arm vehicle
let arm_result: Action.Result = action.arm();

if (arm_result != Action.Result.SUCCESS) {
    console.log(`Arming failed: ${arm_result}`)
    process.exit();
}

// Take off
let takeoff_result: Action.Result = action.takeoff();
if (takeoff_result != Action.Result.SUCCESS) {
    console.log(`Takeoff failed: ${takeoff_result}`)
    process.exit();
}

//close all connections
mavsdk.close();
```

## Examples
To view the examples, clone the Express repo and install the dependencies:
```bash
$ git clone https://github.com/nodriver-ai/MAVJS.git
$ cd MAVJS
$ npm install
```

Then run whichever example you want:
```bash
$ node examples/takeoff_and_land.js udp:://14540
```
## Project Status
Plugins implementation:

- [x] Action
- [x] Info
- [x] Telemetry
- [x] Mission
- [x] MissionItem
- [ ] Offboard
- [ ] Geofence
- [ ] Gimbal
- [ ] Camera
- [ ] LogFiles
- [ ] MavlinkPasstrough
- [ ] MavlinkFTP
- [ ] MissionRaw
- [ ] Mocap
- [ ] Param
- [ ] Shell
- [ ] Tune

## Tests
To run the test suite, first install the dependencies, then run ```npm test```:
```bash
$ npm install
$ npm test
```
> You need also a PX4 SITL running and accessible via UDP in localhost. You can use docker to run a gazebo PX4 SITL simulator.
```bash
$ docker run -d -it --net=host jonasvautherin/px4-gazebo-headless:v1.9.2
```
## License

This project is licensed under the permissive BSD 3-clause, see [LICENSE.md](LICENSE.md).