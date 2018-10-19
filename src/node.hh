#pragma once

#include "already_registered.hh"
#include "lookup.hh"
#include "method.hh"
#include "route.hh"
#include "wildcard_conflict.hh"

#include <array>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace jambe
{

template <typename T>
class Node
{
public:
  explicit Node(const std::string_view& label);

  void add_route(Route& route, Method method, const T& data);
  bool lookup(Route& route, Method method, Lookup<T>& l) const;

private:
  std::string label_;
  std::unique_ptr<Node<T>> wildcard_node_;
  std::vector<Node<T>> children_;
  std::array<std::optional<T>, JAMBE_METHOD_NB> data_;

  void set_data(Method method, const T& data);
  bool get_data(Method method, T& data) const;
  typename std::vector<Node<T>>::const_iterator cfind_child(const std::string_view& part) const;
  typename std::vector<Node<T>>::iterator find_child(const std::string_view& part);
  std::unique_ptr<Node<T>>& create_wildcard(const std::string_view& part);
  bool lookup_wildcard(Route& route, Method method, Lookup<T>& l) const;
};

}

#include "node.hxx"
