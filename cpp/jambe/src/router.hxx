#pragma once

#include "route.hh"
#include "router.hh"

#include <cstring>

template <typename T>
std::array<const char*, JAMBE_METHOD_NB> Router<T>::methods =
{
  "GET",
  "POST",
  "PUT",
  "DELETE",
  "HEAD",
  "PATCH",
};

template <typename T>
Method Router<T>::str_to_method(const std::string& str)
{
  for (std::size_t i = 0; i < methods.size(); ++i)
  {
    if (std::strcmp(str.data(), methods[i]) == 0)
    {
      return static_cast<Method>(i);
    }
  }

  throw std::runtime_error("Unexpected method");
}

template <typename T>
Router<T>::Router()
  : root_("")
{
}

template <typename T>
void Router<T>::add_route(const std::string& route, Method method, const T& data)
{
  Route r(route);
  root_.add_route(r, method, data);
}

template <typename T>
void Router<T>::add_route(const std::string& route, const std::string& method_str, const T& data)
{
  Route r(route);
  Method method = str_to_method(method_str);
  root_.add_route(r, method, data);
}

template <typename T>
Lookup<T> Router<T>::lookup(const std::string& route, Method method) const
{
  Lookup<T> l;
  Route r(route);
  root_.lookup(r, method, l);
  return l;
}

template <typename T>
Lookup<T> Router<T>::lookup(const std::string& route, const std::string& method_str) const
{
  Lookup<T> l;
  Route r(route);
  Method method = str_to_method(method_str);
  root_.lookup(r, method, l);
  return l;
}

// int Router::remove_route(const std::string& route, Method method);
// optimize footprint
