#include "cpp/utils/utils.h"
#include <map>
#include <ostream>
using namespace material_color_utilities;

class Colour {
public:
  int a, r, g, b;
  Colour(Argb argb);
  ~Colour();

  std::map<std::string, int> getJSON();

  friend std::ostream &operator<<(std::ostream &os, const Colour &colour);
};