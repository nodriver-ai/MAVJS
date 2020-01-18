import { System } from "./system";

import * as bindings from 'bindings';
const addon = bindings('MAVJS');

/**
 * This is the main class of MAVJS (a MAVLink API Library for NodeJS).

   It is used to discover vehicles and manage active connections.

   An instance of this class must be created (first) in order to use the library. The instance must be destroyed after use in order to break connections and release all resources.
*/
export class Mavsdk {
    private mavsdk = new addon.Mavsdk();

    constructor() {}

    /**
     * Returns the version of MAVSDK.

       Note, you're not supposed to request the version too many times.

     * @returns  A string containing the version.
     */
    version(): string {
        return this.mavsdk.version();
    }

    /**
     * Adds Connection via URL.

        Supports connection: Serial, TCP or UDP. Connection URL format should be:

        UDP - udp://[Bind_host][:Bind_port]

        TCP - tcp://[Remote_host][:Remote_port]

        Serial - serial://Dev_Node[:Baudrate]
        
      * @param connection_url connection URL string.
      * @returns The result of adding the connection.
     */
    add_any_connection(connection_url: string): Mavsdk.ConnectionResult {
        return this.mavsdk.add_any_connection(connection_url);
    }

    /**
     * Adds a UDP connection to the specified port number and local interface.

       To accept only local connections of the machine, use 127.0.0.1. For any incoming connections, use 0.0.0.0.

     * @param local_ip The local UDP IP address to listen to.
     * @param local_port The local UDP port to listen to (defaults to 14540, the same as MAVROS).
     * @returns The result of adding the connection.
     */
    add_udp_connection(local_ip: string, local_port: number = 14540): Mavsdk.ConnectionResult {
        return this.mavsdk.add_udp_connection(local_ip, local_port);
    }

    /**
     * Sets up instance to send heartbeats to the specified remote interface and port number.
     
     * @param remote_ip The remote UDP IP address to report to.
     * @param remote_port The local UDP port to report to.
     * @returns The result of adding the connection.
     */
    setup_udp_remote(remote_ip: string, remote_port: number): Mavsdk.ConnectionResult {
        return this.mavsdk.setup_udp_remote(remote_ip, remote_port);
    }

    /**
     * Adds a TCP connection with a specific IP address and port number.
     
     * @param remote_ip Remote IP address to connect to.
     * @param remote_port The TCP port to connect to (defaults to 5760).
     * @returns The result of adding the connection.
     */
    add_tcp_connection(remote_ip: string, remote_port: number = 5760): Mavsdk.ConnectionResult {
        return this.mavsdk.add_tcp_connection(remote_ip, remote_port);
    }

    /**
     * Adds a serial connection with a specific port (COM or UART dev node) and baudrate as specified.

     * @param dev_path COM or UART dev node name/path (e.g. "/dev/ttyS0", or "COM3" on Windows).
     * @param baudrate Baudrate of the serial port (defaults to 57600).
     * @returns The result of adding the connection.
     */
    add_serial_connection(dev_path: string, baudrate: number= 57600): Mavsdk.ConnectionResult {
        return this.mavsdk.add_serial_connection(dev_path, baudrate);
    }

    /**
     * Set Configuration of SDK.

       The default configuration is [[Configuration.GroundStation]] The configuration is used in order to set the MAVLink system ID, the component ID, as well as the MAV_TYPE accordingly.
     
     * @param configuration Configuration chosen.
     */
    set_configuration(configuration: Mavsdk.Configuration): void {
        this.mavsdk.set_configuration(configuration);
    }

    /**
     * Get vector of system UUIDs.

       This returns a vector of the UUIDs of all systems that have been discovered. If a system doesn't have a UUID then [[Mavsdk]] will instead use its MAVLink system ID (range: 0..255).
     
     * @returns A vector containing the UUIDs.
     */
    system_uuids(): string[] {
        return this.mavsdk.system_uuids();
    }
    
    /**
     * Get the system with the specified UUID.

       This returns a system for a given UUID if such a system has been discovered and a null system otherwise.
     
     * @param uuid UUID of system to get. (If not provided the method return the first discovered system.)
     * @returns A reference to the specified system.
     */
    system(uuid?: string): System {
        if (uuid) {
            return this.mavsdk.system(uuid);
        } else {
            return this.mavsdk.system();
        }
    }

    /**
     * Returns true if exactly one system is currently connected.

       Connected means we are receiving heartbeats from this system. It means the same as "discovered" and "not timed out".

       If multiple systems have connected, this will return false.
     
     * @param uuid UUID of system to check.
     * @returns ```true``` if system is connected.
     */
    is_connected(uuid?: string): boolean {
        return this.mavsdk.is_connected(uuid);
    }

    /**
     * Register callback for system discovery.

       This sets a callback that will be notified if a new system is discovered.

       If systems have been discovered before this callback is registered, they will be notified at the time this callback is registered.

       > Note: Only one callback can be registered at a time. If this function is called several times, previous callbacks will be overwritten.
     
     * @param callback Callback to register.
     */
    register_on_discover(callback?: Mavsdk.event_callback): any {
        return this.mavsdk.register_on_discover(callback);
    }

    /**
     * Register callback for system timeout.

       This sets a callback that will be notified if no heartbeat of the system has been received in 3 seconds.

       > Note: Only one callback can be registered at a time. If this function is called several times, previous callbacks will be overwritten.
     
    * @param callback Callback to register.
    */
    register_on_timeout(callback?: Mavsdk.event_callback): void {
        this.mavsdk.register_on_timeout(callback)
    }

    /**
     * Destructor.
     * 
     * Disconnects all connected vehicles and releases all resources.
     * 
     * You must call this method if you want release all resources and close the program.
     */
    close(): void {
        this.mavsdk.close();
    }

}


export namespace Mavsdk {
    
    export type event_callback = 
    /**
     * Callback type for discover and timeout notifications.
     * @param {event_callback} uuid UUID of system (or MAVLink system ID for systems that don't have a UUID).
     */
    (uuid: string) => void;
    
    export enum ConnectionResult {
        SUCCESS = "Success",
        TIMEOUT = "Timeout",
        SOCKET_ERROR	= "Socket_error",
        BIND_ERROR = "Bind error",
        SOCKET_CONNECTION_ERROR = "Socket connection error",
        CONNECTION_ERROR = "Connection error",
        NOT_IMPLEMENTED = "Not implemented",
        SYSTEM_NOT_CONNECTED = "System not connected",
        SYSTEM_BUSY = "System busy",
        COMMAND_DENIED = "Command denied",
        DESTINATION_IP_UNKNOWN = "Destination ip unknown",
        CONNECTIONS_EXHAUSTED = "Connections exhausted",
        CONNECTION_URL_INVALID = "Invalid connection URL",
        BAUDRATE_UNKNOWN = "Baudrate_unknown"
    }

    export enum Configuration {
        GroundStation,
        CompanionComputer
    }
}