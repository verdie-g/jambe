#pragma once

#include <stdexcept>
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

template <typename T>
struct Lookup
{
  Lookup()
    : error(LookupError::NONE)
  {
  }

  LookupError error;
  T data;
  std::vector<Param> params;

  const std::string& get_param(const std::string& name) const
  {
    for (const auto& param: params)
    {
      if (param.name == name)
      {
        return param.value;
      }
    }

    throw std::runtime_error("Parameter not found");
  }
};