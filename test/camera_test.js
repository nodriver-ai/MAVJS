var addon = require("../lib/addon")
var assert = require('assert');
var path = require('path');
var fs = require('fs');

var TEST_PATH = "./test";

describe('Camera', function() {
  var img_resolution = {
    "x": 4008,
    "y": 6428
  }

  var overlap = {
    "x": 0,
    "y": 0
  }

  camera = new addon.Camera("testCam", 1.6, 1.6476,
                            img_resolution, 1., 0.001724138,
                            overlap, 4.2844)

  it('params', function() {
    assert.equal(camera.name, "testCam")
    assert.equal(camera.resolution, 1.6)
    assert.equal(camera.angle_of_view, 1.6476)
    assert.equal(camera.img_resolution.x, 4008)
    assert.equal(camera.img_resolution.y, 6428)
    assert.equal(camera.ts, 1.)
    assert.equal(camera.te, 0.001724138)
    assert.equal(camera.overlap.x, 0)
    assert.equal(camera.overlap.y, 0)
    assert.equal(camera.theta, 4.2844)
    assert.equal(camera.aspect_ratio, 0.6235220908525202)
  })

  it('setterParams', function() {
    camera.resolution = 2.84
    camera.img_resolution = {
      "x": 1080,
      "y": 1024
    }
    assert.equal(camera.resolution, 2.84)
    assert.equal(camera.img_resolution.x, 1080)
    assert.equal(camera.img_resolution.y, 1024)
  })

  it('save', function() {
    var json_path = path.join(TEST_PATH, "camera.json")
    camera.save(json_path)
    var rawdata = fs.readFileSync(json_path);
    var cameraJson = JSON.parse(rawdata);
    assert.equal(cameraJson.name, "testCam")
    assert.equal(cameraJson.resolution, 2.84)
    assert.equal(cameraJson.angle_of_view, 1.6476)
    assert.equal(cameraJson.img_resolution.x, 1080)
    assert.equal(cameraJson.img_resolution.y, 1024)
    assert.equal(cameraJson.ts, 1.)
    assert.equal(cameraJson.te, 0.001724138)
    assert.equal(cameraJson.overlap.x, 0)
    assert.equal(cameraJson.overlap.y, 0)
    assert.equal(cameraJson.theta, 4.2844)
  })

  it('from_json', function() {
    var json_path = path.join(TEST_PATH, "camera.json")
    var cameraFromJson = addon.Camera.from_json(json_path)
    assert.equal(cameraFromJson instanceof addon.Camera, true)
    assert.equal(cameraFromJson.name, "testCam")
    assert.equal(cameraFromJson.resolution, 2.84)
    assert.equal(cameraFromJson.angle_of_view, 1.6476)
    assert.equal(cameraFromJson.img_resolution.x, 1080)
    assert.equal(cameraFromJson.img_resolution.y, 1024)
    assert.equal(cameraFromJson.ts, 1.)
    assert.equal(cameraFromJson.te, 0.001724138)
    assert.equal(cameraFromJson.overlap.x, 0)
    assert.equal(cameraFromJson.overlap.y, 0)
    assert.equal(cameraFromJson.theta, 4.2844)
    assert.equal(cameraFromJson.aspect_ratio, 1.0546875)
  })

});
