#include "router-wrapper.hh"

#include <napi.h>

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return RouterWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
