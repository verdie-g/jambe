#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

namespace jambe
{

class Route
{
public:
  // static void throw_if_malformed(const std::string& route);

  Route(const std::string& route);

  std::string_view next_part();
  bool is_end() const;

private:
  std::string_view route_;
  size_t i_;
};

class MalformedRouteException : public std::exception
{
public:
  virtual const char* what() const noexcept
  {
    return "Malformed route";
  }
};

class RouteEndException : public std::exception
{
public:
  virtual const char* what() const noexcept
  {
    return "End of route reached";
  }
};

}
