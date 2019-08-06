#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <napi.h>

/**
  # Struct objectXY
  @param x: double
  @param y: double
  */
struct objectXY {
  double x;
  double y;
};

/**
  # Class Camera
  @param name: string -> camera name
  @param resolution: double -> spatial resolution in `pixels/cm`
  @param angle_of_view: double -> Angle of View in `radians`
  @param img_resolution: objectXY -> image resolution in `pixels`
  @param ts: double -> camera sampling period in `seconds`
  @param te: double -> camera exposure time in `seconds`
  @param overlap: objectXY -> overlap in `meters`
  @param theta: double -> maximum allowed amount of blur in `pixels`
  @param aspect_ratio: double -> imageResolution.x / imageResolution.y
  */
class Camera : public Napi::ObjectWrap<Camera> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Camera(const Napi::CallbackInfo &info);

 private:
  static Napi::FunctionReference constructor;

  std::string _name;
  Napi::Value get_name(const Napi::CallbackInfo &info);

  double _resolution;
  Napi::Value get_resolution(const Napi::CallbackInfo &info);
  void set_resolution(const Napi::CallbackInfo &info, const Napi::Value &resolution);

  double _angle_of_view;
  Napi::Value get_angle_of_view(const Napi::CallbackInfo &info);
  void set_angle_of_view(const Napi::CallbackInfo &info, const Napi::Value &aov);

  objectXY _img_resolution;
  Napi::Value get_img_resolution(const Napi::CallbackInfo &info);
  void set_img_resolution(const Napi::CallbackInfo &info, const Napi::Value &ixy);

  double _ts;
  Napi::Value get_ts(const Napi::CallbackInfo &info);
  void set_ts(const Napi::CallbackInfo &info, const Napi::Value &ts);

  double _te;
  Napi::Value get_te(const Napi::CallbackInfo &info);
  void set_te(const Napi::CallbackInfo &info, const Napi::Value &te);

  objectXY _overlap;
  Napi::Value get_overlap(const Napi::CallbackInfo &info);
  void set_overlap(const Napi::CallbackInfo &info, const Napi::Value &ovxy);

  double _theta;
  Napi::Value get_theta(const Napi::CallbackInfo &info);
  void set_theta(const Napi::CallbackInfo &info, const Napi::Value &theta);

  double _aspect_ratio;
  Napi::Value get_aspect_ratio(const Napi::CallbackInfo &info);

  /*
  from_json static method
  initialize a Camera class from a json file
  @param json_file_path: string
  @return Camera Object
  */
  static Napi::Value from_json(const Napi::CallbackInfo& info);

  /*
  save method
  save the current Camera class instance to a json file
  @param json_file_path: string
  */
  void save(const Napi::CallbackInfo& info);

};

#endif
