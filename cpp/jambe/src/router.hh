#pragma once

#include "lookup.hh"
#include "method.hh"
#include "node.hh"

#include <string>
#include <cstring>

namespace jambe
{

template <typename T>
class Router
{
public:
  explicit Router();

  void add_route(const std::string& route, Method method, const T& data);
  void add_route(const std::string& route, const std::string& method_str, const T& data);
  Lookup<T> lookup(const std::string& route, Method method) const;
  Lookup<T> lookup(const std::string& route, const std::string& method_str) const;

private:
  static std::array<const char*, JAMBE_METHOD_NB> methods;
  static Method str_to_method(const std::string& str);

  Node<T> root_;
};

#include "router.hxx"

}
