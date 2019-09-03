#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <napi.h>

struct objectXY {
  double x;
  double y;
};

class Camera : public Napi::ObjectWrap<Camera> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  Camera(const Napi::CallbackInfo &info);

 private:
  static Napi::FunctionReference constructor;
  static Napi::Object read_from_json(Napi::Env env, Napi::Value path);

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

  double _altitude;
  Napi::Value get_altitude(const Napi::CallbackInfo &info);
  void set_altitude(const Napi::CallbackInfo &info, const Napi::Value &altitude);

  double _aspect_ratio;
  Napi::Value get_aspect_ratio(const Napi::CallbackInfo &info);

  static Napi::Value from_json(const Napi::CallbackInfo& info);
  void save(const Napi::CallbackInfo& info);

  static Napi::Value get_default_cameras(const Napi::CallbackInfo& info);

};

#endif
