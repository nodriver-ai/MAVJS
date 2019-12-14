#include <napi.h>
#include "mavsdk.h"
#include "system.h"
#include "telemetry.h"
#include "action.h"
#include "info.h"

using namespace mavjs;

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  Mavsdk::Init(env, exports);
  System::Init(env, exports);
  Telemetry::Init(env, exports);
  Action::Init(env, exports);
  Info::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, InitAll)
