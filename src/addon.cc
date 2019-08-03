#include <napi.h>
#include "camera.h"
#include "connection.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  Camera::Init(env, exports);
  Connection::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, InitAll)
