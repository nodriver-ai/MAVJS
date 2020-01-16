import { expect } from 'chai';

import { Mavsdk } from "../lib/addon";

function sleep(millis: number) {
    return new Promise(resolve => setTimeout(resolve, millis));
}

describe('Connection Sync', function() {
  
  let mavsdk: Mavsdk;
  let _uuid: string;

  before(() => {
    mavsdk = new Mavsdk();
  })

  after(async () => {   
    mavsdk.close();
  })

  it("connect to SITL", (done) => {
    expect(mavsdk.add_udp_connection("localhost", 14540)).to.equal(Mavsdk.ConnectionResult.SUCCESS); 
    
    expect(mavsdk.add_udp_connection("localhost", 14550)).to.equal(Mavsdk.ConnectionResult.SUCCESS); 

    sleep(2000).then(() => {
      done();
    })
  })

  it('system uuids', () => {
    let uuids = mavsdk.system_uuids();
    
    expect(uuids.length).to.equal(1);

    _uuid = uuids[0];
  });

  it('drop connections', () => {
    mavsdk.close();
  });

  it('new mavsdk instance', (done) => {
    mavsdk = new Mavsdk();

    expect(mavsdk.add_udp_connection("localhost", 14540)).to.equal(Mavsdk.ConnectionResult.SUCCESS); 

    sleep(2000).then(() => {
      let uuids = mavsdk.system_uuids();
      expect(uuids.length).to.equal(1);
      expect(uuids[0]).to.equal(_uuid);
      done();
    })
    
  });
  
});