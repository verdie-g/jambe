#pragma once

#include <string>
#include <string_view>

namespace jambe
{

class Route
{
public:
  static void throw_if_malformed(const std::string& route);

  Route(const std::string& route);

  std::string_view next_part();
  bool is_end() const;

private:
  std::string_view route_;
  size_t i_;
};

}
