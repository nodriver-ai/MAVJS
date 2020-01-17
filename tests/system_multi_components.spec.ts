import { expect } from 'chai';

import { Mavsdk } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('Multi systems', function() {
  
  let mavsdk: Mavsdk;
  let uuids: string[];

  before(() => {
    mavsdk = new Mavsdk();
  })

  after(async () => {   
    mavsdk.close();
  })

  it("connect to SITL", (done) => {
    expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
    
    sleep(2000).then(() => {
      uuids = mavsdk.system_uuids();
      expect(uuids).length.greaterThan(0);
      if (uuids.length < 2) {
        uuids.push(uuids[0])
      }
      done();
    }).catch((err) => {
      done(err);
  });
  })

  it('multi systems components', () => {
      for (let uuid of uuids) {
          let system = mavsdk.system(uuid);
          expect(system.has_autopilot()).to.equal(true);
          expect(system.is_standalone()).to.equal(false);
          expect(system.has_camera()).to.equal(false);
          expect(system.has_gimbal()).to.equal(false);
      }
  });
  
});