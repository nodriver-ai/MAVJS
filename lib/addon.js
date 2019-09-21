"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var bindings = require("bindings");
var addon = bindings('MAVJS');
var CameraAction;
(function (CameraAction) {
    CameraAction[CameraAction["TAKE_PHOTO"] = 0] = "TAKE_PHOTO";
    CameraAction[CameraAction["START_PHOTO_INTERVAL"] = 1] = "START_PHOTO_INTERVAL";
    CameraAction[CameraAction["STOP_PHOTO_INTERVAL"] = 2] = "STOP_PHOTO_INTERVAL";
    CameraAction[CameraAction["START_VIDEO"] = 3] = "START_VIDEO";
    CameraAction[CameraAction["STOP_VIDEO"] = 4] = "STOP_VIDEO";
    CameraAction[CameraAction["NONE"] = 5] = "NONE";
})(CameraAction = exports.CameraAction || (exports.CameraAction = {}));
exports.MavSDK = addon.MavSDK;
//# sourceMappingURL=addon.js.map