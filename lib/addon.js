"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var bindings = require("bindings");
var turf = require("@turf/turf");
var addon = bindings('ndbox');
exports.Ndbox = addon.Ndbox;
function compute_vstart(home_position, polygon) {
    return turf.nearestPoint(home_position, turf.explode(polygon)).properties.featureIndex;
}
function get_segment(index, polygon) {
    var segments = turf.lineSegment(polygon);
    return segments.features[index];
}
function get_point(index, polygon) {
    var points = turf.coordAll(turf.polygonToLine(polygon));
    return turf.point(points[index]);
}
function compute_escan(polygon) {
    var segmentLenght = [];
    turf.segmentEach(polygon, function (segment) {
        segmentLenght.push(turf.length(segment));
    });
    var maxLenght = Math.max.apply(Math, segmentLenght);
    var segmentMaxLenghtIndex = segmentLenght.indexOf(maxLenght);
    return segmentMaxLenghtIndex;
}
/*function compute_vscan(vstart: turf.Feature<turf.Point>, polygon: turf.Feature<turf.Polygon>): number {
  const segments = turf.lineSegment(polygon);

  let vertexDistance = [];
  turf.coordEach(segments, function(vertex) {
    vertexDistance.push(turf.distance(vertex, vstart))
  })

  const minDistance = Math.min(...vertexDistance);
  const vertexMinDistanceIndex = vertexDistance.indexOf(minDistance);

  return vertexMinDistanceIndex + 1;
}*/
function compute_vfar(segment, polygon) {
    var vertexDistance = [];
    turf.coordEach(polygon, function (vertex) {
        vertexDistance.push(turf.pointToLineDistance(vertex, segment));
    });
    var minDistance = Math.max.apply(Math, vertexDistance);
    var vertexMinDistanceIndex = vertexDistance.indexOf(minDistance);
    return vertexMinDistanceIndex;
}
function mission_plan_generate(options) {
    var camera = options.camera;
    var home_position = options.home_position;
    var area_of_interest = options.area_of_interest;
    // Aspect ration
    var rho = camera.img_resolution.x / camera.img_resolution.y;
    // h max
    var hmax = camera.img_resolution.x / (2 * camera.resolution * Math.tan(camera.angle_of_view / 2));
    var altitude = Math.min(camera.altitude, hmax);
    // Size of the projection area (Lx, Ly)
    var projectionArea = {};
    projectionArea.x = 2 * altitude * Math.tan(camera.angle_of_view / 2);
    projectionArea.y = projectionArea.x / rho;
    // Resolution
    var resolution = camera.img_resolution.x / projectionArea.x;
    var overlap = {
        x: projectionArea.x * (camera.overlap / 100),
        y: projectionArea.y * (camera.overlap / 100),
    };
    // Distance between the centers of two adjacent area along the wired direction
    var ds = projectionArea.x - overlap.x;
    // Distance between the centers of two adjacent area along the path direction
    var dw = projectionArea.y - overlap.y;
    // Maximum velocity of the drone
    var vmax = Math.min((projectionArea.y - overlap.y) / camera.ts, camera.theta / (resolution * camera.te));
    // vstart, escan, vscan, vfar
    var vstart = compute_vstart(options.home_position, options.area_of_interest);
    var escan = compute_escan(options.area_of_interest);
    /*const vscan = compute_vscan(get_point(vstart, options.area_of_interest), options.area_of_interest);*/
    var vfar = compute_vfar(get_segment(escan, options.area_of_interest), options.area_of_interest);
    console.log(vstart, escan, vfar);
    console.log(turf.coordAll(turf.polygonToLine(options.area_of_interest)));
    console.log(turf.coordAll(turf.lineSegment(options.area_of_interest)));
    console.log(turf.booleanClockwise(turf.polygonToLine(options.area_of_interest)));
    /*for (let i = vstart; i < vscan + 1; i++) {
      console.log(i)
      console.log(get_point(i, options.area_of_interest))
    }*/
    /*console.log("vstart", vstart)
    console.log(turf.coordAll(turf.polygonToLine(options.area_of_interest))[vstart.properties.featureIndex])
    console.log("vscan", vscan)
    console.log("escan", escan)*/
}
exports.mission_plan_generate = mission_plan_generate;
var area_of_interest = turf.polygon([[
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
var home_position = turf.point([13.00575256347656,
    41.5419916023209]);
var camera = {
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
});
//# sourceMappingURL=addon.js.map