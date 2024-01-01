#include "colour.hpp"
#include <sstream>
#include <string>

Colour::Colour(Argb argb) {
  a = AlphaFromInt(argb);
  r = RedFromInt(argb);
  g = GreenFromInt(argb);
  b = BlueFromInt(argb);
}
Colour::~Colour(){};

// For generating hex colours without alpha (#RRGGBB)
std::string Colour::toHex(int r, int g, int b) {
  std::stringstream ss;
  ss << std::hex << (r << 16 | g << 8 | b);
  return ss.str();
}

// For generating hex colours with alpha (#RRGGBBAA)
std::string Colour::toHex(int a, int r, int g, int b) {
  std::stringstream ss;
  ss << std::hex << (r << 24 | g << 16 | b << 8 | a);
  return ss.str();
}

std::string Colour::toRgba(int a, int r, int g, int b) {
  std::stringstream ss;
  ss << "rgba(" << r << ", " << g << ", " << b << ", " << a / 255 << ")";
  return ss.str();
}

std::string Colour::toRgb(int r, int g, int b) {
  std::stringstream ss;
  ss << "rgb(" << r << ", " << g << ", " << b << ", " << a / 255 << ")";
  return ss.str();
}

std::map<std::string, std::string> Colour::formatJson() {
  return {
      {"a", std::to_string(a)},        {"r", std::to_string(r)},
      {"g", std::to_string(g)},        {"b", std::to_string(b)},
      {"hexAlpha", toHex(a, r, g, b)}, {"hex", toHex(r, g, b)},
      {"rgba", toRgba(a, r, g, b)},    {"rgb", toRgb(r, g, b)},
  };
}

std::ostream &operator<<(std::ostream &os, const Colour &colour) {
  double alpha = double(colour.a) / 255;
  os << "rgba(" << colour.r << ", " << colour.g << ", " << colour.b << ", "
     << alpha << ")";
  return os;
};