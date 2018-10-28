#include "lookup-wrapper.hh"

Napi::FunctionReference LookupWrapper::constructor;

Napi::Object LookupWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "Lookup", {
  });

  constructor = Napi::Persistent(ctor);
  constructor.SuppressDestruct();

  exports.Set("Lookup", ctor);
  return exports;
}

LookupWrapper::LookupWrapper(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<LookupWrapper>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  lookup_ = new Lookup<Napi::Value>();
}
