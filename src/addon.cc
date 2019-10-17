#include <napi.h>
#include "mavsdk.h"
#include "drone.h"
#include "camera.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  MavSDK::Init(env, exports);
  Drone::Init(env, exports);
  Camera::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, InitAll)
