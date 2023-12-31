#include "output.hpp"
#include <nlohmann/json.hpp>

#include <iostream>

using namespace std;
using json = nlohmann::json;

void printJson(Palette &palette) {
  json jsonPalette;
  const std::vector<std::string> colorNames = {
      "primary",   "onPrimary",   "primaryContainer",   "onPrimaryContainer",
      "secondary", "onSecondary", "secondaryContainer", "onSecondaryContainer",
      "tertiary",  "onTertiary",  "tertiaryContainer",  "onTertiaryContainer",
      "error",     "onError",     "errorContainer",     "onErrorContainer",
      "surface",   "onSurface",   "surfaceVariant",     "onSurfaceVariant"};

  for (const auto &colorName : colorNames) {
    jsonPalette[colorName] = palette.getColourByName(colorName).getJSON();
  }
  cout << jsonPalette.dump(-1, ' ', false,
                           nlohmann::json::error_handler_t::replace)
       << endl;
}