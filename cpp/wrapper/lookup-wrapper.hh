#pragma once

#include "jambe.hh"

#include <napi.h>

using namespace jambe;

class LookupWrapper : public Napi::ObjectWrap<LookupWrapper>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  LookupWrapper(const Napi::CallbackInfo& info);

private:
  static Napi::FunctionReference constructor;

  Lookup<Napi::Value> *lookup_;
};
