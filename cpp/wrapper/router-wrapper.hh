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
  static Napi::ObjectReference methods_str;
  static void generate_method_strings(Napi::Env env);
  static Method str_to_method(const Napi::String& s);

  Router *router_;

  void add_route(const Napi::CallbackInfo& info);
  void test(Napi::FunctionReference&& f);
  Napi::Value lookup(const Napi::CallbackInfo& info);
};
