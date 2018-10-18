#include <stdexcept>

namespace jambe
{

class AlreadyRegisteredException : public std::exception
{
public:
  virtual const char* what() const noexcept
  {
    return "Already registered data for this route";
  }
};

}
