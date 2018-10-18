#pragma once

#include "route.hh"
#include "router.hh"

template <typename T>
Router<T>::Router()
  : root_("")
{
}

template <typename T>
void Router<T>::add_route(const std::string& route, Method method, const T& data)
{
  Route::throw_if_malformed(route);
  Route r(route);
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

// int Router::remove_route(const std::string& route, Method method);
// optimize footprint
