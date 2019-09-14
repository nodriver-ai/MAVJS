"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var turf = require("@turf/turf");
var Mission = /** @class */ (function () {
    function Mission(options) {
        this.waypoints = [];
        this.home = options.home;
        this.area = options.area;
        this.camera = options.camera;
        this.compute_camera_model();
        this.compute_indices();
    }
    Mission.prototype.compute_indices = function () {
        var vstart = turf.nearestPoint(this.home, turf.explode(this.area)).properties.featureIndex;
        var escan = this.compute_escan();
        var escan_segment = this.get_segment(escan);
        var vfar = this.compute_vfar(escan_segment);
        var num_nodes = turf.coordAll(this.area).length - 1;
        var mode;
        var vscan = escan;
        if (vstart > vscan) {
            vscan += 1;
            mode = 0;
        }
        else {
            mode = 1;
        }
        this.indices = {
            vstart: vstart,
            vscan: vscan,
            vfar: vfar,
            escan: escan,
            num_nodes: num_nodes,
            mode: mode
        };
    };
    Mission.prototype.compute_camera_model = function () {
        // Aspect ration
        var rho = this.camera.img_resolution.x / this.camera.img_resolution.y;
        // h max
        var hmax = this.camera.img_resolution.x / (2 * this.camera.resolution * Math.tan(this.camera.angle_of_view / 2));
        var altitude = Math.min(this.camera.altitude, hmax);
        // Size of the projection area (Lx, Ly)
        var size_proj = 2 * altitude * Math.tan(this.camera.angle_of_view / 2);
        var projectionArea = {
            x: size_proj,
            y: size_proj / rho
        };
        // Resolution
        var resolution = this.camera.img_resolution.x / projectionArea.x;
        var overlap = {
            x: projectionArea.x * (this.camera.overlap / 100),
            y: projectionArea.y * (this.camera.overlap / 100)
        };
        // Distance between the centers of two adjacent area along the wired direction
        var ds = projectionArea.x - overlap.x;
        // Distance between the centers of two adjacent area along the path direction
        var dw = projectionArea.y - overlap.y;
        // Maximum velocity of the drone
        var vmax = Math.min((projectionArea.y - overlap.y) / this.camera.ts, this.camera.theta / (resolution * this.camera.te));
        this.camera_model = {
            projectionArea: projectionArea,
            overlap: overlap,
            ds: ds,
            dw: dw,
            vmax: vmax,
            altitude: altitude
        };
    };
    Mission.prototype.get_point = function (index) {
        var points = turf.coordAll(turf.polygonToLine(this.area));
        return turf.point(points[index]);
    };
    Mission.prototype.get_segment = function (index) {
        var segments = turf.lineSegment(this.area);
        return segments.features[index];
    };
    Mission.prototype.compute_escan = function () {
        var segmentLenght = [];
        turf.segmentEach(this.area, function (segment) {
            segmentLenght.push(turf.length(segment));
        });
        var maxLenght = Math.max.apply(Math, segmentLenght);
        var segmentMaxLenghtIndex = segmentLenght.indexOf(maxLenght);
        return segmentMaxLenghtIndex;
    };
    Mission.prototype.compute_vfar = function (segment) {
        var vertexDistance = [];
        turf.coordEach(this.area, function (vertex) {
            vertexDistance.push(turf.pointToLineDistance(vertex, segment));
        });
        var minDistance = Math.max.apply(Math, vertexDistance);
        var vertexMinDistanceIndex = vertexDistance.indexOf(minDistance);
        return vertexMinDistanceIndex;
    };
    Mission.prototype.compute_phase_1 = function (point_i, point_j, point_next_i) {
        var d = turf.distance(point_i, point_next_i) * 1000;
        var nw = Math.ceil((d - this.camera_model.overlap.y) / this.camera_model.dw);
        //const ovy_ = ((nw * this.camera_model.projectionArea.y) - d) / (nw - 1)
        var dw_ = (d - this.camera_model.projectionArea.y) / (nw - 1);
        var x = turf.destination(point_i, this.camera_model.projectionArea.y / (2 * 1000), turf.bearing(point_i, point_next_i));
        x = turf.destination(x, this.camera_model.projectionArea.x / (2 * 1000), turf.bearing(point_i, point_next_i) + point_j);
        this.waypoints.push(x);
        var prev_vertex = x;
        for (var j = 1; j < nw; j++) {
            var y = turf.destination(prev_vertex, dw_ / 1000, turf.bearing(point_i, point_next_i));
            this.waypoints.push(y);
            prev_vertex = y;
        }
    };
    Mission.prototype.compute_phase_2 = function (clockwise) {
        var vscan_pre_point = this.get_point(this.indices.vscan);
        var vscan_point;
        if (clockwise) {
            vscan_point = this.get_point(this.indices.vscan - 1);
        }
        else {
            vscan_point = this.get_point(this.indices.vscan + 1);
        }
        var vfar_point = this.get_point(this.indices.vfar);
        var escan_segment = this.get_segment(this.indices.escan);
        var dfs = turf.pointToLineDistance(vfar_point, this.get_segment(this.indices.escan)) * 1000;
        var ns = Math.ceil((dfs - this.camera_model.overlap.x) / this.camera_model.ds);
        if (ns % 2) {
            ns += 1;
        }
        //const ovx_ = ((ns * this.camera_model.projectionArea.x) - dfs) / (ns - 1)
        var ds_ = (dfs - this.camera_model.projectionArea.x) / (ns - 1);
        for (var i = 0; i < ns; i++) {
            var bbox = turf.bboxPolygon(turf.bbox(this.area));
            var len = turf.length(turf.lineSegment(bbox).features[0]);
            var p1 = void 0, p2 = void 0, vleftright = void 0, intersections = void 0, start_point = void 0, d = void 0;
            ;
            if (clockwise) {
                p1 = turf.destination(escan_segment.geometry.coordinates[0], len / 2, turf.bearing(vscan_pre_point, vscan_point));
                p2 = turf.destination(escan_segment.geometry.coordinates[1], -len / 2, turf.bearing(vscan_pre_point, vscan_point));
                vleftright = turf.transformTranslate(turf.lineString([p1.geometry.coordinates, p2.geometry.coordinates]), (i * ds_) / 1000 + (this.camera_model.projectionArea.x / (2 * 1000)), turf.bearing(vscan_pre_point, vscan_point) + 90);
                intersections = turf.lineIntersect(vleftright, turf.polygonToLine(this.area));
                if (turf.distance(intersections.features[1], vscan_pre_point) > turf.distance(intersections.features[0], vscan_pre_point)) {
                    var gamma = turf.bearing(intersections.features[0], intersections.features[1]);
                    start_point = turf.destination(intersections.features[0], this.camera_model.ds / 1000, gamma);
                    d = turf.distance(start_point, intersections.features[1]) * 1000;
                }
                else {
                    var gamma = turf.bearing(intersections.features[1], intersections.features[0]);
                    start_point = turf.destination(intersections.features[1], this.camera_model.ds / 1000, gamma);
                    d = turf.distance(start_point, intersections.features[0]) * 1000;
                }
            }
            else {
                p1 = turf.destination(escan_segment.geometry.coordinates[0], -len / 2, turf.bearing(vscan_pre_point, vscan_point));
                p2 = turf.destination(escan_segment.geometry.coordinates[1], len / 2, turf.bearing(vscan_pre_point, vscan_point));
                vleftright = turf.transformTranslate(turf.lineString([p1.geometry.coordinates, p2.geometry.coordinates]), (i * ds_) / 1000 + (this.camera_model.projectionArea.x / (2 * 1000)), turf.bearing(vscan_pre_point, vscan_point) - 90);
                intersections = turf.lineIntersect(vleftright, turf.polygonToLine(this.area));
                if (turf.distance(intersections.features[0], vscan_pre_point) < turf.distance(intersections.features[1], vscan_pre_point)) {
                    var gamma = turf.bearing(intersections.features[0], intersections.features[1]);
                    start_point = turf.destination(intersections.features[0], this.camera_model.ds / 1000, gamma);
                    d = turf.distance(start_point, intersections.features[1]) * 1000;
                }
                else {
                    var gamma = turf.bearing(intersections.features[1], intersections.features[0]);
                    start_point = turf.destination(intersections.features[1], this.camera_model.ds / 1000, gamma);
                    d = turf.distance(start_point, intersections.features[0]) * 1000;
                }
            }
            var nw = Math.ceil((d - this.camera_model.overlap.y) / this.camera_model.dw);
            var dw_ = (d - this.camera_model.projectionArea.y) / (nw - 1);
            if (dw_ > 0) {
                var x = turf.destination(start_point, this.camera_model.projectionArea.y / (2 * 1000), turf.bearing(vscan_pre_point, vscan_point));
                this.waypoints.push(x);
                var prev_vertex = x;
                for (var j = 1; j < nw; j++) {
                    var y = turf.destination(prev_vertex, dw_ / 1000, turf.bearing(vscan_pre_point, vscan_point));
                    this.waypoints.push(y);
                    prev_vertex = y;
                }
            }
            else {
                this.waypoints.push(start_point);
            }
        }
    };
    Mission.prototype.compute_phase_3 = function (clockwise) {
        if (clockwise) {
            if (this.indices.vfar > this.indices.vstart) {
                for (var i = this.indices.vfar; i > this.indices.vstart; i--) {
                    var point_i = this.get_point(i);
                    var point_j = 90;
                    var point_next_i = this.get_point(i - 1);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
            }
            if (this.indices.vfar < this.indices.vstart) {
                for (var i = this.indices.vfar; i > 0; i--) {
                    var point_i = this.get_point(i);
                    var point_j = 90;
                    var point_next_i = this.get_point(i - 1);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
                for (var i = this.indices.num_nodes; i < this.indices.vstart; i--) {
                    var point_i = this.get_point(i);
                    var point_j = 90;
                    var point_next_i = this.get_point(i - 1);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
            }
        }
        else {
            if (this.indices.vfar < this.indices.vstart) {
                for (var i = this.indices.vfar; i < this.indices.vstart; i++) {
                    var point_i = this.get_point(i);
                    var point_j = -90;
                    var point_next_i = this.get_point(i + 1);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
            }
            if (this.indices.vfar > this.indices.vstart) {
                for (var i = this.indices.vfar; i < this.indices.num_nodes; i++) {
                    var point_i = this.get_point(i);
                    var point_j = -90;
                    var i_ = i + 1;
                    if (i_ === this.indices.num_nodes) {
                        i_ = 0;
                    }
                    var point_next_i = this.get_point(i_);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
            }
            for (var i = 0; i < this.indices.vstart; i++) {
                var point_i = this.get_point(i);
                var point_j = -90;
                var point_next_i = this.get_point(i + 1);
                this.compute_phase_1(point_i, point_j, point_next_i);
            }
        }
    };
    Mission.prototype.generate = function () {
        switch (this.indices.mode) {
            case 0: {
                for (var i = this.indices.vstart; i > this.indices.vscan; i--) {
                    var point_i = this.get_point(i);
                    var point_j = 90;
                    var point_next_i = this.get_point(i - 1);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
                this.compute_phase_2(true);
                this.compute_phase_3(true);
                break;
            }
            case 1: {
                for (var i = this.indices.vstart; i < this.indices.vscan; i++) {
                    var point_i = this.get_point(i);
                    var point_j = -90;
                    var point_next_i = this.get_point(i + 1);
                    this.compute_phase_1(point_i, point_j, point_next_i);
                }
                this.compute_phase_2(false);
                this.compute_phase_3(false);
                break;
            }
        }
        return this.waypoints;
    };
    return Mission;
}());
exports.Mission = Mission;
//# sourceMappingURL=mission.js.map