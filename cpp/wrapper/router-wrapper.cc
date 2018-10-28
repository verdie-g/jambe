#include "router-wrapper.hh"

Napi::FunctionReference RouterWrapper::constructor;

Napi::Object RouterWrapper::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "Router", {
      InstanceMethod("lookup", &RouterWrapper::lookup),
      InstanceMethod("addRoute", &RouterWrapper::add_route),
  });

  constructor = Napi::Persistent(ctor);
  constructor.SuppressDestruct();

  exports.Set("Router", ctor);
  return exports;
}

RouterWrapper::RouterWrapper(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<RouterWrapper>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  router_ = new Router<Napi::Value>();
}

void RouterWrapper::add_route(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 3)
  {
    Napi::Error::New(env, "3 arguments expected").ThrowAsJavaScriptException();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "String expected for argument 0").ThrowAsJavaScriptException();
  }

  if (!info[1].IsString())
  {
    Napi::TypeError::New(env, "String expected for argument 1").ThrowAsJavaScriptException();
  }

  if (!info[2].IsFunction())
  {
    Napi::TypeError::New(env, "Function expected for argument 2").ThrowAsJavaScriptException();
  }

  std::string route = info[0].As<Napi::String>().Utf8Value();
  std::string method = info[1].As<Napi::String>().Utf8Value();
  try
  {
    router_->add_route(route, method, info[2]);
  }
  catch (const std::exception& ex)
  {
    Napi::Error::New(env, ex.what()).ThrowAsJavaScriptException();
  }
}

Napi::Value RouterWrapper::lookup(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 2)
  {
    Napi::Error::New(env, "2 arguments expected").ThrowAsJavaScriptException();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "String expected for argument 0").ThrowAsJavaScriptException();
  }

  if (!info[1].IsString())
  {
    Napi::TypeError::New(env, "String expected for argument 1").ThrowAsJavaScriptException();
  }

  std::string route = info[0].As<Napi::String>().Utf8Value();
  std::string method = info[1].As<Napi::String>().Utf8Value();
  try
  {
    Lookup l = router_->lookup(route, method);
    // FIXME: return L
    return Napi::Number::New(env, 5.0);
  }
  catch (const std::exception& ex)
  {
    Napi::Error::New(env, ex.what()).ThrowAsJavaScriptException();
  }
}
