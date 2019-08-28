const addon = require("../lib/addon");
const shell = require('shelljs');
const assert = require('assert');

const UDP_PATH = "udp://:14540";

/* DA FARE AUTOMATICO INTERGANGENDO CON IL SIMULATORE DIRETTAMENTE DA QUI */

describe('Ndbox', function() {

  ndbox = new addon.Ndbox(UDP_PATH)
  uuid = 0;

  it('params', function() {
    assert.equal(ndbox.is_connected(), false)
    assert.equal(ndbox.connection_url, UDP_PATH)
  });

  it('discover_uuids', function(done) {
    ndbox.discover_uuids(function(uuids) {
      assert.equal(uuids.length, 1)

      uuid = uuids[0]
      assert.equal(ndbox.is_connected(uuid), true)
      done()
    });
  });

  it('connect_to_drone', function() {
    drone = ndbox.connect_to_drone(uuid)
    assert.equal(drone.uuid, uuid)
    assert.equal(drone.is_connected(), true)
    assert.equal(drone.has_autopilot(), true)
    assert.equal(drone.has_camera(), false)
    assert.equal(drone.has_gimbal(), false)
  })

});
