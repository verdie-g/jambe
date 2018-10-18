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

// int Router::remove_route(const std::string& route, Method method);
// int Router::lookup(const std::string& route, Method method, jambe_lookup *res) const;
