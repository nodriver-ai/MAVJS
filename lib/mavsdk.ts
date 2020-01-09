import { System } from "./system";

import * as bindings from 'bindings';
const addon = bindings('MAVJS');

export namespace Mavsdk {
    
    export interface event_callback { (uuid: string): void };

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

    export const Init: {
        new(): Mavsdk
    } = addon.Mavsdk
}

export interface Mavsdk {
    version(): string,
    add_any_connection(connection_url: string): Mavsdk.ConnectionResult,
    add_udp_connection(local_ip?: string, local_port?: number): Mavsdk.ConnectionResult,
    add_udp_connection(local_port?: number): Mavsdk.ConnectionResult,
    setup_udp_remote(remote_ip: string, remote_port: number): Mavsdk.ConnectionResult,
    add_tcp_connection(remote_ip: string, remote_port?: number): Mavsdk.ConnectionResult,
    add_serial_connection(dev_path: string, baudrate?: number): Mavsdk.ConnectionResult,
    set_configuration(configuration: Mavsdk.Configuration): void,
    system_uuids(): string[],
    system(uuid?: string): System,
    is_connected(uuid?: string): boolean,
    register_on_discover(callback: Mavsdk.event_callback): void,
    unregister_on_discover(): void,
    register_on_timeout(callback: Mavsdk.event_callback): void,
    unregister_on_timeout(): void,
}