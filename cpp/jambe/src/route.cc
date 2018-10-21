#include "route.hh"

#include <stdexcept>

using namespace jambe;

Route::Route(const std::string& route)
  : route_(route.data())
  , i_(0)
{
  if (route.empty())
  {
    throw MalformedRouteException();
  }

  if (route.front() != '/')
  {
    throw MalformedRouteException();
  }

  ++i_;
}

std::string_view Route::next_part()
{
  if (is_end())
  {
    throw RouteEndException();
  }

  std::size_t start = i_;
  for (; i_ < route_.length() && route_[i_] != '/'; ++i_)
  {
    if (route_[i_] == ':' && (i_ == 0 || route_[i_ - 1] != '/' || i_ == route_.length() - 1 || route_[i_ + 1] == '/'))
    {
      throw MalformedRouteException();
    }
  }

  std::size_t count = i_ - start;
  if (count == 0)
  {
    throw MalformedRouteException();
  }

  i_ += static_cast<int>(!is_end());
  return route_.substr(start, count);
}

bool Route::is_end() const
{
  return i_ == route_.length();
}
