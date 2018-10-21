#pragma once

#include "lookup.hh"
#include "method.hh"
#include "node.hh"

#include <string>

namespace jambe
{

template <typename T>
class Router
{
public:
  explicit Router();

  void add_route(const std::string& route, Method method, const T& data);
  Lookup<T> lookup(const std::string& route, Method method) const;

private:
  Node<T> root_;
};

#include "router.hxx"

}
