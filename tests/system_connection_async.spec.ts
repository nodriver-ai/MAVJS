import { expect } from 'chai';

import { Mavsdk } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('Connection Async', function() {
  
  let mavsdk: Mavsdk;
  let _discovered_system: boolean = false
  let _uuid: string;

  before(() => {
    mavsdk = new Mavsdk();
  })

  after(async () => {   
    mavsdk.close();
  })

  it("connect to SITL", (done) => {
    expect(mavsdk.add_udp_connection("localhost")).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
    
    mavsdk.register_on_discover((uuid) => {
      _discovered_system = true;
      _uuid = uuid;
      
    })

    sleep(2000).then(() => {
      expect(_uuid).to.not.equal(0);
      expect(_discovered_system).to.equal(true)
      done();
    }).catch((err) => {
      done(err);
  });

  })
  
});