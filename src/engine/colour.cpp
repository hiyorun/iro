#include "colour.hpp"

Colour::Colour(Argb argb) {
  a = AlphaFromInt(argb);
  r = RedFromInt(argb);
  g = GreenFromInt(argb);
  b = BlueFromInt(argb);
}
Colour::~Colour(){};

std::map<std::string, int> Colour::getJSON() {
  return {{"a", a}, {"r", r}, {"g", g}, {"b", b}};
}

std::ostream &operator<<(std::ostream &os, const Colour &colour) {
  double alpha = double(colour.a) / 255;
  os << "rgba(" << colour.r << ", " << colour.g << ", " << colour.b << ", "
     << alpha << ")";
  return os;
};