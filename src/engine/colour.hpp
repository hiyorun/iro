#include "cpp/utils/utils.h"
#include <map>
#include <ostream>

using namespace material_color_utilities;

class Colour {
public:
  int a, r, g, b;
  Colour(Argb argb);
  ~Colour();

  std::string toHex(int r, int g, int b);
  std::string toHex(int a, int r, int g, int b);
  std::string toRgba(int a, int r, int g, int b);
  std::string toRgb(int r, int g, int b);
  std::map<std::string, std::string> formatJson();

  friend std::ostream &operator<<(std::ostream &os, const Colour &colour);
};