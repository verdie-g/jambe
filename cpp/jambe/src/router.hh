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
  Lookup lookup(Method method, const std::string& route) const;

private:
  static std::array<const char*, JAMBE_METHOD_NB> methods;

  Node root_;
};

}
