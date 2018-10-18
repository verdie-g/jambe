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
bool Node<T>::lookup(Route& route, Method method, Lookup<T>& l) const
{
  if (route.is_end())
  {
    if (!get_data(method, l.data))
    {
      l.error = LookupError::METHOD_NOT_ALLOWED;
      return false;
    }
    return true;
  }

  std::string_view part = route.next_part();
  auto child = cfind_child(part);

  if (child == children_.cend()
      || child->label_ != part
      || !child->lookup(route, method, l))
  {
    return lookup_wildcard(route, method, l, part);
  }

  return true;
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
bool Node<T>::get_data(Method method, T& data) const
{
  int i = static_cast<int>(method);
  if (!data_[i].has_value())
  {
    return false;
  }

  data = data_[i].value();
  return true;
}

template <typename T>
typename std::vector<Node<T>>::const_iterator Node<T>::cfind_child(const std::string_view& part) const
{
  auto child = children_.cbegin();
  for (; child != children_.cend() && child->label_ < part; child++)
  {
  }
  return child;
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
  std::string_view name = part.substr(1);
  if (wildcard_node_ != nullptr && wildcard_node_->label_ != name)
  {
    throw WildcardConflictException();
  }

  if (wildcard_node_ == nullptr)
  {
    wildcard_node_ = std::make_unique<Node<T>>(name);
  }

  return wildcard_node_;
}

template <typename T>
bool Node<T>::lookup_wildcard(Route& route, Method method, Lookup<T>& l, const std::string_view& part) const
{
  if (wildcard_node_ != nullptr && wildcard_node_->lookup(route, method, l))
  {
    l.params.emplace_back(wildcard_node_->label_, part);
    return true;
  }

  l.error = LookupError::NOT_FOUND;
  return false;
}

}
