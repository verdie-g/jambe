#pragma once

#include "already_registered.hh"
#include "method.hh"
#include "route.hh"

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

private:
  std::string label_;
  std::unique_ptr<Node<T>> wildcard_node_;
  std::vector<Node<T>> children_;
  std::array<std::optional<T>, JAMBE_METHOD_NB> data_;

  void set_data(Method method, const T& data);
  void set_data_or_continue(Route& route, Method method, const T& data);
};

}

#include "node.hxx"
