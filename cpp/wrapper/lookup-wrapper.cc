#include "lookup-wrapper.hh"

Napi::FunctionReference LookupWrapper::constructor;

Napi::Object LookupWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "Lookup", {
      InstanceMethod("getParam", &LookupWrapper::get_param),
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

Napi::Value LookupWrapper::get_param(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1 || !info[0].IsString())
  {
    Napi::TypeError::New(env, "String expected for argument 0").ThrowAsJavaScriptException();
  }

  std::string name = info[0].As<Napi::String>().Utf8Value();
  try
  {
    const std::string& value = lookup_->get_param(name);
    return Napi::String::New(env, value);
  }
  catch (const std::exception& ex)
  {
    Napi::Error::New(env, ex.what()).ThrowAsJavaScriptException();
  }
}
