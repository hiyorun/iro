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
  cout << "Usage: your_program [OPTIONS] <Argb_value> \n"
       << "Options:\n"
       << "  -h, --help\t\tDisplay this help message\n"
       << "  -j, --json\t\tPrint JSON representation of the palette\n";
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
  cout << jsonPalette.dump(2) << endl;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    help();
    return 1;
  }

  std::vector<std::string> args{argv + 1, argv + argc};
  for (auto flag = args.begin(); flag != args.end(); flag++) {
    if (flag->compare("-h") == 0 || flag->compare("--help") == 0) {
      help();
      return 0;
    } else if (flag->compare("-j") == 0 || flag->compare("--json") == 0) {
      if (std::next(flag) == args.end()) {
        help();

        return 1;
      }
      Argb argb = stringToArgb(std::next(flag)->c_str());
      Palette palette = Palette(argb);
      printJson(palette);

      flag++;

      continue;
    } else {
      std::cerr << "Unknown option '" << flag->c_str() << "'!\n";
      help();

      return 1;
    }
  }
}
