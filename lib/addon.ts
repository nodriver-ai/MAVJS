import * as bindings from 'bindings';
import * as turf from '@turf/turf';

const addon = bindings('ndbox');

export interface Position {
  latitude: number,
  longitude: number,
  altitude: number
}

export interface Battery {
  voltage: number;
  remaining_percent: number;
}

export interface Quaternion {
  w: number;
  x: number;
  y: number;
  z: number;
}

export interface EulerAngle {
  roll: number;
  pitch: number;
  yaw: number;
}

export interface GroundSpeedNED {
  velocity_north: number;
  velocity_east: number;
  velocity_down: number;
}

export interface GPSInfo {
  num_satellites: number;
  fix_type: number;
}

export interface Health {
  gyrometer_calibration_ok: boolean;
  accelerometer_calibration_ok: boolean;
  magnetometer_calibration_ok: boolean;
  level_calibration_ok: boolean;
  local_position_ok: boolean;
  global_position_ok: boolean;
  home_position_ok: boolean;
}

export interface RCStatus {
  available_once: boolean;
  available: boolean;
  signal_strength_percent: number;
}

export interface ProductInfo {
  hardware_uid: number[];
  vendor_id: number;
  vendor_name: string;
  product_id: number;
  product_name: string;
}

export interface Telemetry {
  flight_mode: string,
  battery: Battery,
  gps_info: GPSInfo,
  has_autopilot: boolean;
  has_camera: boolean;
  has_gimbal: boolean;
  in_air: boolean;
  armed: boolean;
  ground_speed_ned : GroundSpeedNED;
  attitude_quaternion: Quaternion;
  attitude_euler_angle: EulerAngle;
}

export interface Drone {
  uuid: string;
  get_product_info(): ProductInfo;
  is_connected(): boolean;
  has_autopilot(): boolean;
  has_camera(): boolean;
  has_gimbal(): boolean;
  set_rate_position(rate_hz: number): void;
  set_rate_home_position(rate_hz: number): void;
  set_rate_attitude(rate_hz: number): void;
  set_rate_battery(rate_hz: number): void;
  set_rate_position_velocity_ned(rate_hz: number): void;
  set_rate_in_air(rate_hz: number): void;
  set_rate_camera_attitude(rate_hz: number): void;
  set_rate_ground_speed_ned(rate_hz: number): void;
  set_rate_gps_info(rate_hz: number): void;
  set_rate_rc_status(rate_hz: number): void;
  position(): Position;
  health_all_ok(): boolean;
  home_position(): Position;
  battery(): Battery;
  in_air(): boolean;
  armed(): boolean;
  attitude_quaternion(): Quaternion;
  attitude_euler_angle(): EulerAngle;
  ground_speed_ned(): GroundSpeedNED;
  gps_info(): GPSInfo;
  flight_mode(): string;
  health(): Health;
  rc_status(): RCStatus;
  telemetry(): Telemetry;
}

export interface Ndbox {
  connection_url: string;
  is_connected(uuid: string | null): boolean;
  discover_uuids(): string[];
  connect_to_drone(uuid: string): Drone | null;
}

export const Ndbox: {
    new(url: string): Ndbox
} = addon.Ndbox

export interface ImgResolution {
  x?: number,
  y?: number
}

export interface Camera {
  id: number,
  name: string,
  resolution: number,
  angle_of_view: number,
  img_resolution: ImgResolution,
  ts: number,
  te: number,
  overlap: number,
  theta: number,
  altitude: number
}

export interface MissionOptions {
  home_position: turf.Feature<turf.Point>,
  area_of_interest: turf.Feature<turf.Polygon>,
  camera: Camera;
}


function compute_vstart(home_position:turf.Feature<turf.Point>, polygon: turf.Feature<turf.Polygon>): number {
  return turf.nearestPoint(home_position, turf.explode(polygon)).properties.featureIndex;
}

function get_segment(index: number, polygon: turf.Feature<turf.Polygon>): turf.Feature<turf.LineString> {
  const segments = turf.lineSegment(polygon);
  return segments.features[index];
}

function get_point(index: number, polygon: turf.Feature<turf.Polygon>): turf.Feature<turf.Point> {
  const points = turf.coordAll(turf.polygonToLine(polygon))
  return turf.point(points[index]);
}

function compute_escan(polygon: turf.Feature<turf.Polygon>): number {
  let segmentLenght = []
  turf.segmentEach(polygon, function (segment) {
    segmentLenght.push(turf.length(segment))
  });

  const maxLenght = Math.max(...segmentLenght);
  const segmentMaxLenghtIndex = segmentLenght.indexOf(maxLenght);
  return segmentMaxLenghtIndex;
}

function compute_vfar(segment: turf.Feature<turf.LineString>, polygon: turf.Feature<turf.Polygon>): number {
  let vertexDistance = [];
  turf.coordEach(polygon, function(vertex) {
    vertexDistance.push(turf.pointToLineDistance(vertex, segment))
  })

  const minDistance = Math.max(...vertexDistance);
  const vertexMinDistanceIndex = vertexDistance.indexOf(minDistance);

  return vertexMinDistanceIndex;
}

export function mission_plan_generate(options: MissionOptions) {

  const camera: Camera = options.camera;
  const home_position: turf.Feature<turf.Point> = options.home_position;
  const area_of_interest: turf.Feature<turf.Polygon> = options.area_of_interest;

  // Aspect ration
  const rho: number = camera.img_resolution.x / camera.img_resolution.y

  // h max
  const hmax: number = camera.img_resolution.x / (2 * camera.resolution * Math.tan(camera.angle_of_view / 2))
  const altitude = Math.min(camera.altitude, hmax)

  // Size of the projection area (Lx, Ly)
  let projectionArea: ImgResolution = {};
  projectionArea.x = 2 * altitude * Math.tan(camera.angle_of_view / 2);
  projectionArea.y = projectionArea.x / rho

  // Resolution
  const resolution: number = camera.img_resolution.x / projectionArea.x

  const overlap: ImgResolution = {
    x: projectionArea.x * (camera.overlap / 100),
    y: projectionArea.y * (camera.overlap / 100),
  }
  // Distance between the centers of two adjacent area along the wired direction
  const ds: number = projectionArea.x - overlap.x

  // Distance between the centers of two adjacent area along the path direction
  const dw: number = projectionArea.y - overlap.y

  // Maximum velocity of the drone
  const vmax = Math.min((projectionArea.y - overlap.y) / camera.ts, camera.theta / (resolution * camera.te))

  // vstart, escan, vscan, vfar
  const vstart = compute_vstart(options.home_position, options.area_of_interest);

  const escan = compute_escan(options.area_of_interest);

  const vscan = escan + 1

  const vfar = compute_vfar(get_segment(escan, options.area_of_interest), options.area_of_interest);


  /*for (let i = vstart; i < vscan + 1; i++) {
    console.log(i)
    console.log(get_point(i, options.area_of_interest))
  }*/
  /*console.log("vstart", vstart)
  console.log(turf.coordAll(turf.polygonToLine(options.area_of_interest))[vstart.properties.featureIndex])
  console.log("vscan", vscan)
  console.log("escan", escan)*/

}

const area_of_interest = turf.polygon([[
  [
              12.777786254882812,
              41.66521798508633
            ],
            [
              12.735214233398438,
              41.57847058443442
            ],
            [
              12.9913330078125,
              41.58360681482734
            ],
            [
              12.913742065429688,
              41.66521798508633
            ],
            [
              12.777786254882812,
              41.66521798508633
            ]
]]);

const home_position = turf.point([13.00575256347656,
          41.5419916023209])

const camera = {
  "id": 0,
  "name": "parrot sequoia RGB",
  "angle_of_view": 1.6476,
  "img_resolution": {
      "x": 1080.0,
      "y": 1024.0
  },
  "overlap": 70.0,
  "resolution": 2.70,
  "te": 0.001724138,
  "theta": 4.2844,
  "ts": 1.0,
  "altitude": 5
};

mission_plan_generate({
  camera: camera,
  area_of_interest: area_of_interest,
  home_position: home_position
})
