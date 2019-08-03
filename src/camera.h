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
  @param aov: double -> Angle of View in `radians`
  @param ixy: objectXY -> image resolution in `pixels`
  @param ts: double -> camera sampling period in `seconds`
  @param te: double -> camera exposure time in `seconds`
  @param ovxy: objectXY -> overlap in `meters`
  @param theta: double -> maximum allowed amount of blur in `pixels`
  @param aspectRatio: double -> imageResolution.x / imageResolution.y
  */
class Camera : public Napi::ObjectWrap<Camera> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Camera(const Napi::CallbackInfo &info);

 private:
  static Napi::FunctionReference constructor;

  std::string _name;
  Napi::Value GetName(const Napi::CallbackInfo &info);

  double _resolution;
  Napi::Value GetResolution(const Napi::CallbackInfo &info);
  void SetResolution(const Napi::CallbackInfo &info, const Napi::Value &resolution);

  double _angleOfView;
  Napi::Value GetAngleOfView(const Napi::CallbackInfo &info);
  void SetAngleOfView(const Napi::CallbackInfo &info, const Napi::Value &aov);

  objectXY _imageResolution;
  Napi::Value GetImageResolution(const Napi::CallbackInfo &info);
  void SetImageResolution(const Napi::CallbackInfo &info, const Napi::Value &ixy);

  double _ts;
  Napi::Value GetTS(const Napi::CallbackInfo &info);
  void SetTS(const Napi::CallbackInfo &info, const Napi::Value &ts);

  double _te;
  Napi::Value GetTE(const Napi::CallbackInfo &info);
  void SetTE(const Napi::CallbackInfo &info, const Napi::Value &te);

  objectXY _overlap;
  Napi::Value GetOverlap(const Napi::CallbackInfo &info);
  void SetOverlap(const Napi::CallbackInfo &info, const Napi::Value &ovxy);

  double _theta;
  Napi::Value GetTheta(const Napi::CallbackInfo &info);
  void SetTheta(const Napi::CallbackInfo &info, const Napi::Value &theta);

  double _aspectRatio;
  Napi::Value GetAspectRatio(const Napi::CallbackInfo &info);

  /*
  FromJson static method
  initialize a Camera class from a json file
  @param json_file_path: string
  @return Camera Object
  */
  static Napi::Value FromJson(const Napi::CallbackInfo& info);

  /*
  save method
  save the current Camera class instance to a json file
  @param json_file_path: string
  */
  void Save(const Napi::CallbackInfo& info);

};

#endif
