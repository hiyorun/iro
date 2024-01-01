#include "output.hpp"
#include <nlohmann/json.hpp>

#include <iostream>

using namespace std;
using json = nlohmann::json;

json getJson(Palette &palette) {
  json jsonPalette;
  const std::vector<std::string> colorNames = {
      "primary",   "onPrimary",   "primaryContainer",   "onPrimaryContainer",
      "secondary", "onSecondary", "secondaryContainer", "onSecondaryContainer",
      "tertiary",  "onTertiary",  "tertiaryContainer",  "onTertiaryContainer",
      "error",     "onError",     "errorContainer",     "onErrorContainer",
      "surface",   "onSurface",   "surfaceVariant",     "onSurfaceVariant"};

  for (const auto &colorName : colorNames) {
    jsonPalette[colorName] = palette.getColourByName(colorName).formatJson();
  }
  return jsonPalette;
}

void printJson(Palette &palette, bool prettier) {
  json jsonPalette = getJson(palette);
  int indentation = prettier ? 2 : -1;
  cout << jsonPalette.dump(indentation, ' ', false,
                           nlohmann::json::error_handler_t::replace)
       << endl;
}
