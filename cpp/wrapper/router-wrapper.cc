#include "router-wrapper.hh"

Napi::FunctionReference RouterWrapper::constructor;
Napi::ObjectReference RouterWrapper::methods_str;

void RouterWrapper::generate_method_strings(Napi::Env env)
{
  Napi::Object methods_str_obj = Napi::Object::New(env);
  methods_str_obj.Set("GET", Napi::Number::New(env, static_cast<double>(Method::GET)));
  methods_str_obj.Set("POST", Napi::Number::New(env, static_cast<double>(Method::POST)));
  methods_str_obj.Set("PUT", Napi::Number::New(env, static_cast<double>(Method::PUT)));
  methods_str_obj.Set("DELETE", Napi::Number::New(env, static_cast<double>(Method::DELETE)));
  methods_str_obj.Set("HEAD", Napi::Number::New(env, static_cast<double>(Method::HEAD)));
  methods_str_obj.Set("PATCH", Napi::Number::New(env, static_cast<double>(Method::PATCH)));
  methods_str = Napi::Persistent(methods_str_obj);
  methods_str.SuppressDestruct();
};

Method RouterWrapper::str_to_method(const Napi::String& s)
{
  Napi::Number n = methods_str.Value().Get(s).As<Napi::Number>();
  return static_cast<Method>(n.Int32Value());
}

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

  generate_method_strings(env);

  return exports;
}

RouterWrapper::RouterWrapper(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<RouterWrapper>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);
  router_ = new Router();
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

  Napi::String method_str = info[0].As<Napi::String>();
  std::string route = info[1].As<Napi::String>().Utf8Value();
  auto handler = info[2].As<Napi::Function>();
  try
  {
    Method method = str_to_method(method_str);
    router_->add_route(method, route, handler);
  }
  catch (const std::exception& ex)
  {
    Napi::Error::New(env, ex.what()).ThrowAsJavaScriptException();
  }
}

Napi::Value RouterWrapper::lookup(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // Napi::HandleScope scope(env);

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

  Napi::String method_str = info[0].As<Napi::String>();
  std::string route = info[1].As<Napi::String>().Utf8Value();
  try
  {
    Method method = str_to_method(method_str);
    Lookup l = router_->lookup(method, route);
  
    Napi::Number error = Napi::Number::New(env, static_cast<int32_t>(l.error));
    Napi::Value handler = l.error == LookupError::NONE ? l.handler->Value() : env.Undefined();
    Napi::Object params = Napi::Object::New(env);
    for (const auto& param: l.params)
    {
      params.Set(param.name, param.value);
    }

    Napi::Object obj = Napi::Object::New(env);
    obj.Set("error", error);
    obj.Set("handler", handler);
    obj.Set("params", params);
    return obj;
  }
  catch (const std::exception& ex)
  {
    Napi::Error::New(env, ex.what()).ThrowAsJavaScriptException();
    return env.Undefined();
  }
}
