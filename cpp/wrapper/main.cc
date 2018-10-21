#include <napi.h>
#include "router-wrapper.hh"
#include "lookup-wrapper.hh"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  LookupWrapper::Init(env, exports);
  return RouterWrapper::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitAll)
