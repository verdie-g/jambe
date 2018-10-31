#pragma once

#include "lookup.hh"
#include "method.hh"
#include "node.hh"
#include "route.hh"

#include <cstring>
#include <napi.h>
#include <string>

namespace jambe
{

class Router
{
public:
  explicit Router();

  void add_route(Method method, const std::string& route, const Napi::Function& handler);
  void add_route(const std::string& method_str, const std::string& route, const Napi::Function& handler);
  Lookup lookup(Method method, const std::string& route) const;
  Lookup lookup(const std::string& method_str, const std::string& route) const;

private:
  static std::array<const char*, JAMBE_METHOD_NB> methods;
  static Method str_to_method(const std::string& str);

  Node root_;
};

}
