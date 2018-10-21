#include <stdexcept>

namespace jambe
{

class WildcardConflictException : public std::exception
{
public:
  virtual const char* what() const noexcept
  {
    return "Wildcards have different names";
  }
};

}
