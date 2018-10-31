#include "router.hh"

using namespace jambe;

std::array<const char*, JAMBE_METHOD_NB> Router::methods =
{
  "GET",
  "POST",
  "PUT",
  "DELETE",
  "HEAD",
  "PATCH",
};

Method Router::str_to_method(const std::string& str)
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

Router::Router()
  : root_("")
{
}

void Router::add_route(Method method, const std::string& route, const Napi::Function& handler)
{
  Route r(route);
  root_.add_route(method, r, handler);
}

void Router::add_route(const std::string& method_str, const std::string& route, const Napi::Function& handler)
{
  Route r(route);
  Method method = str_to_method(method_str);
  root_.add_route(method, r, handler);
}

Lookup Router::lookup(Method method, const std::string& route) const
{
  Lookup l;
  Route r(route);
  root_.lookup(method, r, l);
  return l;
}

Lookup Router::lookup(const std::string& method_str, const std::string& route) const
{
  Lookup l;
  Route r(route);
  Method method = str_to_method(method_str);
  root_.lookup(method, r, l);
  return l;
}
