#include "node.hh"

#include <stdexcept>

using namespace jambe;

Node::Node(const std::string_view& label)
  : label_(label)
  , wildcard_node_(nullptr)
{
}

void Node::add_route(Method method, Route& route, const Napi::Function& handler)
{
  if (route.is_end())
  {
    set_handler(method, handler);
    return;
  }

  std::string_view part = route.next_part();

  if (part.front() == ':')
  {
    create_wildcard(part)->add_route(method, route, handler);
    return;
  }

  auto child = find_child(part);
  if (child == children_.end() || child->label_ != part)
  {
    child = children_.emplace(child, part);
  }

  child->add_route(method, route, handler);
}

bool Node::lookup(Method method, Route& route, Lookup& l) const
{
  if (route.is_end())
  {
    if (!get_handler(method, l.handler))
    {
      l.error = LookupError::METHOD_NOT_ALLOWED;
      return false;
    }
    return true;
  }

  Route route_save = route;
  std::string_view part = route.next_part();
  auto child = cfind_child(part);

  if (child == children_.cend()
      || child->label_ != part
      || !child->lookup(method, route, l))
  {
    return lookup_wildcard(method, route_save, l);
  }

  return true;
}

void Node::set_handler(Method method, const Napi::Function& handler)
{
  int i = static_cast<int>(method);
  if (handlers_[i].has_value())
  {
    throw std::runtime_error("Already registered route");
  }

  handlers_[i] = Napi::Reference<Napi::Function>::New(handler);
}

bool Node::get_handler(Method method, const Napi::FunctionReference*& handler) const
{
  int i = static_cast<int>(method);
  if (!handlers_[i].has_value())
  {
    return false;
  }

  handler = &handlers_[i].value();
  return true;
}

typename std::vector<Node>::const_iterator Node::cfind_child(const std::string_view& part) const
{
  auto child = children_.cbegin();
  for (; child != children_.cend() && child->label_ < part; child++)
  {
  }
  return child;
}

typename std::vector<Node>::iterator Node::find_child(const std::string_view& part)
{
  auto child = children_.begin();
  for (; child != children_.end() && child->label_ < part; child++)
  {
  }
  return child;
}

std::unique_ptr<Node>& Node::create_wildcard(const std::string_view& part)
{
  std::string_view name = part.substr(1);
  if (wildcard_node_ != nullptr && wildcard_node_->label_ != name)
  {
    throw std::runtime_error("Wildcard conflict");
  }

  if (wildcard_node_ == nullptr)
  {
    wildcard_node_ = std::make_unique<Node>(name);
  }

  return wildcard_node_;
}

bool Node::lookup_wildcard(Method method, Route& route, Lookup& l) const
{
  std::string_view part = route.next_part();
  LookupError save_err = l.error;

  if (wildcard_node_ != nullptr && wildcard_node_->lookup(method, route, l))
  {
    l.params.emplace_back(wildcard_node_->label_, part);
    l.error = LookupError::NONE;
    return true;
  }

  if (save_err == LookupError::NONE)
  {
    l.error = LookupError::NOT_FOUND;
  }
  return false;
}
