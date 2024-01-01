#include "output/output.hpp"

#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

using namespace material_color_utilities;
using namespace std;

Argb stringToArgb(const string &str) {
  stringstream ss(str);
  Argb argb;
  ss >> hex >> argb;
  return argb;
}

void help() {
  cout << "Usage: iroha [OPTIONS]\n"
       << "Options:\n"
       << "  -c, --colour <value>\t\tDeclare a color using ARGB format (e.g., "
          "ff902922)\n"
       << "  -d, --dark-mode\t\tEnable dark mode\n"
       << "  -h, --help\t\t\tDisplay this help message\n"
       << "  -i, --inja <template-path>\tPrint Inja template for the palette\n"
       << "  -j, --json\t\t\tPrint JSON representation of the palette\n"
       << "\n"
       << "Examples:\n"
       << "  iroha -j --colour ff902922\n"
       << "  iroha -d -j -c ff902922\n"
       << "  iroha -i template.css -c ff902922\n";
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
    if (*flag == "-h" || *flag == "--help") {
      help();
      return 0;
    } else if (*flag == "-d" || *flag == "--dark-mode") {
      stdOps.push_back(
          [](Palette &palette) { palette.setMode(PaletteMode::DARK); });
    } else if (*flag == "-i" || *flag == "--inja") {
      if (std::next(flag) == args.end()) {
        help();
        return 1;
      }
      outOps.push_back([flag](Palette &palette) {
        InjaTpl inja = InjaTpl(std::next(flag)->c_str(), "./output.css");
        inja.printInja(palette);
      });
      flag++;
    } else if (*flag == "-j" || *flag == "--json") {
      outOps.push_back([](Palette &palette) { printJson(palette); });
    } else if (*flag == "-f" || *flag == "--formatted-json") {
      outOps.push_back([](Palette &palette) { printJson(palette, true); });
    } else if (*flag == "-c" || *flag == "--colour") {
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
