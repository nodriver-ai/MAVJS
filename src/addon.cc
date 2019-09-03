#include <napi.h>
#include "camera.h"
#include "ndbox.h"
#include "drone.h"
#include "missionPlan.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  Camera::Init(env, exports);
  Ndbox::Init(env, exports);
  Drone::Init(env, exports);
  MissionPlan::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, InitAll)
