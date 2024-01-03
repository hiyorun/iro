#include "output/output.hpp"

#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

using namespace material_color_utilities;
using namespace std;

struct {
  string input, output = "";
} path;

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
       << "  -i, --inja <template-path>\tPrint Inja template for the palette\n"
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

  Argb argb;

  vector<string> args{argv + 1, argv + argc};
  vector<function<void(Palette &)>> stdOps;
  vector<function<void(Palette &)>> outOps;

  for (auto flag = args.begin(); flag != args.end(); flag++) {
    if (*flag == "-h" || *flag == "--help") {
      help();
      return 0;
    } else if (*flag == "-d" || *flag == "--dark-mode") {
      stdOps.push_back(
          [](Palette &palette) { palette.setMode(PaletteMode::DARK); });
    } else if (*flag == "-i" || *flag == "--inja") {
      if (next(flag) == args.end()) {
        help();
        return 1;
      }
      path.input = next(flag)->c_str();
      if (path.output != "") {
        outOps.push_back([](Palette &palette) {
          InjaTpl inja = InjaTpl(path.input, path.output);
          inja.printInja(palette);
        });
      }
      flag++;
    } else if (*flag == "-j" || *flag == "--json") {
      outOps.push_back([](Palette &palette) { printJson(palette); });
    } else if (*flag == "-f" || *flag == "--formatted-json") {
      outOps.push_back([](Palette &palette) { printJson(palette, true); });
    } else if (*flag == "-o" || *flag == "--output") {
      if (next(flag) == args.end()) {
        help();
        return 1;
      }
      path.output = next(flag)->c_str();
      flag++;
      if (path.input != "") {
        outOps.push_back([](Palette &palette) {
          InjaTpl inja = InjaTpl(path.input, path.output);
          inja.printInja(palette);
        });
      }
    } else if (*flag == "-c" || *flag == "--colour") {
      if (next(flag) == args.end()) {
        help();
        return 1;
      }
      argb = stringToArgb(next(flag)->c_str());
      flag++;
    } else {
      cerr << "Unknown option '" << flag->c_str() << "'!\n";
      help();
      return 1;
    }
  }

  Palette palette((Hct(argb)));
  for (const auto &operation : stdOps) {
    operation(palette);
  }

  for (const auto &operation : outOps) {
    operation(palette);
  }

  return 0;
}
