namespace jambe
{

template <typename T>
Node<T>::Node(const std::string_view& label)
  : label_(label)
  , wildcard_node_(nullptr)
{
}

template <typename T>
void Node<T>::add_route(Route& route, Method method, const T& data)
{
  if (route.is_end())
  {
    set_data(method, data);
    return;
  }

  std::string_view part = route.next_part();

  if (part.front() == ':')
  {
    create_wildcard(part)->add_route(route, method, data);
    return;
  }

  auto child = find_child(part);
  
  if (child == children_.end() || child->label_ != part)
  {
    child = children_.emplace(child, part);
  }

  child->add_route(route, method, data);
}

template <typename T>
void Node<T>::set_data(Method method, const T& data)
{
  int i = static_cast<int>(method);
  if (data_[i].has_value())
  {
    throw AlreadyRegisteredException(); 
  }

  data_[i] = data;
}

template <typename T>
typename std::vector<Node<T>>::iterator Node<T>::find_child(const std::string_view& part)
{
  auto child = children_.begin();
  for (; child != children_.end() && child->label_ < part; child++)
  {
  }
  return child;
}

template <typename T>
std::unique_ptr<Node<T>>& Node<T>::create_wildcard(const std::string_view& part)
{
  if (wildcard_node_ != nullptr && wildcard_node_->label_ != part)
  {
    throw WildcardConflictException();
  }

  if (wildcard_node_ == nullptr)
  {
    wildcard_node_ = std::make_unique<Node<T>>(part);
  }

  return wildcard_node_;
}

}
