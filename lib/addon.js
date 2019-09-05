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
function move_point(point, distance, bearing) {
    var point_x_moved = turf.destination(point, distance.x, bearing.x);
    return turf.destination(point_x_moved, distance.y, bearing.y);
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
    var vscan = escan + 1;
    var vfar = compute_vfar(get_segment(escan, options.area_of_interest), options.area_of_interest);
    console.log(vstart, vscan, vfar);
    var waypoints = [];
    for (var i = vstart; i < vscan; i++) {
        var point_i = get_point(i, options.area_of_interest);
        var point_next_i = get_point(i + 1, options.area_of_interest);
        var d = turf.distance(point_i, point_next_i) * 1000;
        var nw = Math.ceil((d - overlap.y) / dw);
        var ovy_ = ((nw * projectionArea.y) - d) / (nw - 1);
        var dw_ = (d - (dw + projectionArea.y)) / (nw - 1);
        waypoints.push(move_point(point_i, { x: projectionArea.y / (2 * 1000), y: projectionArea.x / (2 * 1000) }, { x: turf.bearing(point_i, point_next_i), y: 0 }));
        for (var j = 1; j < nw; j++) {
            waypoints.push(move_point(point_i, { x: (projectionArea.y / (2 * 1000)) + ((j * dw_) / 1000), y: projectionArea.x / (2 * 1000) }, { x: turf.bearing(point_i, point_next_i), y: 0 }));
        }
    }
    console.log(JSON.stringify(turf.featureCollection(waypoints)));
}
exports.mission_plan_generate = mission_plan_generate;
var area_of_interest = turf.polygon([[
        [
            12.662944793701172,
            41.734621540876404
        ],
        [
            12.662301063537598,
            41.73311634927409
        ],
        [
            12.666077613830566,
            41.732988246232416
        ],
        [
            12.665305137634277,
            41.73446141578682
        ],
        [
            12.662944793701172,
            41.734621540876404
        ]
    ]]);
var home_position = turf.point([12.661314010620117,
    41.73212354401866]);
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