export namespace Info {

    export enum Result {
      UNKNOWN = "Unknown",
      SUCCESS = "Success",
      INFORMATION_NOT_RECEIVED_YET = "Information_not_received_yet"
    }
  
    export interface Identification {
      hardware_uid: number[]
    }
  
    export interface Version {
      flight_sw_major: number,
      flight_sw_minor: number,
      flight_sw_patch: number,
      flight_sw_vendor_major: number,
      flight_sw_vendor_minor: number,
      flight_sw_vendor_patch: number,
      flight_sw_git_hash: string,
      os_sw_major: number,
      os_sw_minor: number,
      os_sw_patch: number,
      os_sw_git_hash: string
    }
  
    export interface Product {
      vendor_id: number,
      vendor_name: string,
      product_id: number,
      product_name: string
    }
  
    export interface pair_result<T>{
      result: string,
      value: T
    }
  
    export interface Info {
      get_identification(): pair_result<Identification>,
      get_version(): pair_result<Version>,
      get_product(): pair_result<Product>
    }
  
  }