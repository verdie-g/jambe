#pragma once

#include "method.hh"
#include "node.hh"

#include <string>
#include <vector>

#define JAMBE_ERROR_NOT_FOUND          404
#define JAMBE_ERROR_METHOD_NOT_ALLOWED 405
#define JAMBE_ERROR_INTERNAL           500

namespace jambe
{

struct Param
{
  std::string name;
  std::string value;
};

template <typename T>
class Lookup
{
  std::vector<Param> params;
  T data;
  int error;
};

template <typename T>
class Router
{
public:
  explicit Router();

  void add_route(const std::string& route, Method method, const T& data);
  // void remove_route(const std::string& route, Method method);
  // Lookup<T> lookup(const std::string& route, Method method) const;

private:
  Node<T> root_;
};

#include "router.hxx"

}
