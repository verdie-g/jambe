#include "router.hh"

using namespace jambe;

Router::Router()
  : root_("")
{
}

void Router::add_route(Method method, const std::string& route, const Napi::Function& handler)
{
  Route r(route);
  root_.add_route(method, r, handler);
}

Lookup Router::lookup(Method method, const std::string& route) const
{
  Lookup l;
  Route r(route);
  root_.lookup(method, r, l);
  return l;
}
