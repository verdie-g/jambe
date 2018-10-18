#include "route.hh"

#include <stdexcept>

using namespace jambe;

void Route::throw_if_malformed(const std::string& route)
{
  if (route.empty())
  {
    throw std::invalid_argument("route cannot be empty");
  } 

  if (route.front() != '/')
  {
    throw std::invalid_argument("route should start with a '/'");
  }

  for (size_t i = 1; i < route.length(); ++i)
  {
    if (route[i] == ':' && (route[i - 1] != '/' || i == route.length() - 1))
    {
      throw std::invalid_argument("unexpected ':' character");
    }
  }
}

Route::Route(const std::string& route)
  : route_(route.data())
  , i_(0)
{
  if (route_.at(i_) == '/')
  {
    ++i_;
  }
}

std::string_view Route::next_part()
{
  std::size_t start = i_;
  while (i_ < route_.length() && route_.at(i_) != '/')
  {
    i_++;
  }
  std::size_t count = i_ - start;
  i_ += static_cast<int>(!is_end());
  return route_.substr(start, count);
}

bool Route::is_end() const
{
  return i_ == route_.length();
}
