/**
 * The Info class provides basic infomation about the hardware and/or software of a system.
 */
export class Info {
  /**
   * Gets the identification of the system.
   * 
   * If possible this will be a unique identifier provided by hardware.
   * @returns a pair containing the result of the request and if successful, the identification information of the system.
   */
  get_identification(): Info.pair_result<Info.Identification> {
    return this.get_identification();
  }

  /**
   * Get system version information.
   * @returns a pair containing the result of the request and if successful, the version information about the system.
   */
  get_version(): Info.pair_result<Info.Version> {
    return this.get_version();
  }
  
  /**
   * Get system product information.
   * @returns a pair containing the result of the request and if successful, the product information about the system.
   */
  get_product(): Info.pair_result<Info.Product> {
    return this.get_product();
  }
}

export namespace Info {

    export enum Result {
      UNKNOWN = "Unknown",
      SUCCESS = "Success",
      INFORMATION_NOT_RECEIVED_YET = "Information_not_received_yet"
    }
    
    /** Type containing identification. */
    export interface Identification {
      /**
       * UID of hardware. This refers to uid2 of MAVLink. If the system does not support uid2 yet, this will be all zero.
      */
      hardware_uid: number[]
    }
    
    /**
     * Type containing system version information.
     */
    export interface Version {
      /** Flight software major version. */
      flight_sw_major: number,
      /** Flight software minor version. */
      flight_sw_minor: number,
      /** Flight software patch version. */
      flight_sw_patch: number,
      /** Flight software vendor major version. */
      flight_sw_vendor_major: number,
      /** Flight software vendor minor version. */
      flight_sw_vendor_minor: number,
      /** Flight software vendor patch version. */
      flight_sw_vendor_patch: number,
      /** Flight software git hash as string. */
      flight_sw_git_hash: string,
      /** Operating system software major version. */
      os_sw_major: number,
      /** Operating system software minor version. */
      os_sw_minor: number,
      /** Operating system software patch version. */
      os_sw_patch: number,
      /** Operating system software git hash as string. */
      os_sw_git_hash: string
    }
    
    /** Type containing system product information. */
    export interface Product {
      /** ID of board vendor. */
      vendor_id: number,
      /** Name of vendor. */
      vendor_name: string,
      /** ID of product. */
      product_id: number,
      /** Name of product. */
      product_name: string
    }
  
    export interface pair_result<T>{
      result: string,
      value: T
    }
  
  }