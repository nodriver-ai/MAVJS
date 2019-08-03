var addon = require("../lib/addon")
var assert = require('assert');
var path = require('path');
var fs = require('fs');

var TEST_PATH = "./test";
var UDP_PATH = "udp://:14540";

describe('Connection', function() {

  conn = new addon.Connection(UDP_PATH)

  it('params', function() {
    assert.equal(conn.isConnected(), false)
    assert.equal(conn.address, UDP_PATH)
  });

  it('getUUIDs', function(done) {
    conn.getUUIDs(function(uuids) {
      assert.equal(uuids.length, 1)
      assert.equal(conn.isConnected(uuids[0]), true)
      done()
    });
  });

});
