import { expect } from 'chai';

import { Mavsdk, Configuration } from "../lib/addon";

let mavsdk = new Mavsdk();

describe('Mavsdk', 
  () => { 

    it('version', () => { 
      expect(mavsdk.version()).to.equal("0.21.4-19-g9c625dae-dirty"); 
    }); 

    it('add_any_connection', () => { 
      expect(mavsdk.add_any_connection("udp://127.0.0.1:14540")).to.equal("Success"); 
    }); 

    it('add_udp_connection', () => { 
      expect(mavsdk.add_udp_connection(14540)).to.equal("Bind error"); 
    }); 

    it('setup_udp_remote', () => { 
      expect(mavsdk.setup_udp_remote("1.1.1.1", 5678)).to.equal("Bind error"); 
    });

    it('add_tcp_connection', () => { 
      expect(mavsdk.add_tcp_connection("127.0.0.1", 5678)).to.equal("Socket connection error"); 
    }); 

    it('add_serial_connectrion', () => {
      expect(mavsdk.add_serial_connection("utty0")).to.equal("Connection error");
    });

    it('set_configuration', () => {
      expect(mavsdk.set_configuration(Configuration.GroundStation)).to.be.undefined;
    });

    it('system_uuids', () => {
      expect(mavsdk.system_uuids()).instanceOf(Array);
    })

    it('system', () => {
      expect(mavsdk.system(0)).to.be.undefined;
    })

    it('is_connected', () => {
      expect(mavsdk.is_connected()).to.be.false;
    })
});