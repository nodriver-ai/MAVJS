var addon = require("../lib/addon")
var assert = require('assert');

var UDP_PATH = "udp://:14540";

describe('Ndbox', function() {

  ndbox = new addon.Ndbox(UDP_PATH)

  it('params', function() {
    assert.equal(ndbox.is_connected(), false)
    assert.equal(ndbox.connection_url, UDP_PATH)
  });

  it('discover_uuids', function(done) {
    ndbox.discover_uuids(function(uuids) {
      assert.equal(uuids.length, 1)
      assert.equal(ndbox.is_connected(uuids[0]), true)
      done()
    });
  });

});
