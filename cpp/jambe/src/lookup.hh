#pragma once

#include <napi.h>
#include <string>
#include <string_view>
#include <vector>

enum class LookupError
{
  METHOD_NOT_ALLOWED,
  NONE,
  NOT_FOUND,
};

struct Param
{
  Param(const std::string& name, const std::string_view& value)
    : name(name)
    , value(value)
  {
  }

  std::string name;
  std::string value;
};

struct Lookup
{
  LookupError error = LookupError::NONE;
  const Napi::FunctionReference* handler = nullptr;
  std::vector<Param> params;
};
