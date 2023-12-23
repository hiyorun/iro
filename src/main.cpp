#include "engine/palette.hpp"
#include "nlohmann/json.hpp"

#include <iostream>
#include <iterator>
#include <ostream>

using namespace material_color_utilities;
using namespace std;
using json = nlohmann::json;

Argb stringToArgb(const string &str) {
  stringstream ss(str);
  Argb argb;
  ss >> hex >> argb;
  return argb;
}

void help() {
  cout << "Usage: iroha [OPTIONS]\n"
       << "Options:\n"
       << "  -c, --colour <value>\tDeclare a color using ARGB format (e.g., "
          "ff902922)\n"
       << "  -d, --dark-mode\tEnable dark mode\n"
       << "  -h, --help\t\tDisplay this help message\n"
       << "  -j, --json\t\tPrint JSON representation of the palette\n"
       << "\n"
       << "Color Options:\n"
       << "  --colour <value>\tDeclare a color using ARGB format (e.g., "
          "ff902922)\n"
       << "\n"
       << "Examples:\n"
       << "  iroha -j --colour ff902922\n"
       << "  iroha -d -j -c ff902922\n";
}

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

int main(int argc, char *argv[]) {
  if (argc < 2) {
    help();
    return 1;
  }

  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::function<void(Palette &)>> stdOps;
  std::vector<std::function<void(Palette &)>> outOps;

  for (auto flag = args.begin(); flag != args.end(); flag++) {
    if (flag->compare("-h") == 0 || flag->compare("--help") == 0) {
      help();
      return 0;
    } else if (flag->compare("-d") == 0 || flag->compare("--dark-mode") == 0) {

      stdOps.push_back(
          [](Palette &palette) { palette.setMode(PaletteMode::DARK); });
    } else if (flag->compare("-j") == 0 || flag->compare("--json") == 0) {

      outOps.push_back([](Palette &palette) { printJson(palette); });
    } else if (flag->compare("-c") == 0 || flag->compare("--colour") == 0) {
      if (std::next(flag) == args.end()) {
        help();
        return 1;
      }
      Argb argb = stringToArgb(std::next(flag)->c_str());

      stdOps.push_back([argb](Palette &palette) { palette = Palette(argb); });

      flag++;
    } else {
      std::cerr << "Unknown option '" << flag->c_str() << "'!\n";
      help();
      return 1;
    }
  }

  Palette palette(Hct(0x00000000));
  for (const auto &operation : stdOps) {
    operation(palette);
  }

  for (const auto &operation : outOps) {
    operation(palette);
  }

  return 0;
}
