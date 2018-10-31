#pragma once

#include "lookup.hh"
#include "method.hh"
#include "route.hh"

#include <array>
#include <memory>
#include <napi.h>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace jambe
{

class Node
{
public:
  explicit Node(const std::string_view& label);

  void add_route(Method method, Route& route, const Napi::Function& handler);
  bool lookup(Method method, Route& route, Lookup& l) const;

private:
  std::string label_;
  std::unique_ptr<Node> wildcard_node_;
  std::vector<Node> children_;
  std::array<std::optional<Napi::FunctionReference>, JAMBE_METHOD_NB> handlers_;

  bool get_handler(Method method, const Napi::FunctionReference*& handler) const;
  bool handler(Method method, Napi::FunctionReference* handler) const;
  bool lookup_wildcard(Method method, Route& route, Lookup& l) const;
  typename std::vector<Node>::const_iterator cfind_child(const std::string_view& part) const;

  void set_handler(Method method, const Napi::Function& handler);
  typename std::vector<Node>::iterator find_child(const std::string_view& part);
  std::unique_ptr<Node>& create_wildcard(const std::string_view& part);
};

}
