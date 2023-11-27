#include "cpp/utils/utils.h"
#include <ostream>
using namespace material_color_utilities;

class Colour {
public:
  int a, r, g, b;
  Colour(Argb argb);
  ~Colour();

  friend std::ostream& operator<<(std::ostream& os, const Colour& colour);
};