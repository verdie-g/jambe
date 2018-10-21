#pragma once

#include "jambe.hh"

#include <napi.h>

using namespace jambe;

class RouterWrapper : public Napi::ObjectWrap<RouterWrapper>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  RouterWrapper(const Napi::CallbackInfo& info);

private:
  static Napi::FunctionReference constructor;

  Router<Napi::Value> *router_;

  void add_route(const Napi::CallbackInfo& info);
  Napi::Value lookup(const Napi::CallbackInfo& info);
};
