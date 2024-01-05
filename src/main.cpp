#define MAGICKCORE_HDRI_ENABLE 1
#include "cpp/quantize/celebi.h"
#include "cpp/quantize/wsmeans.h"
#include "cpp/score/score.h"
#include "cpp/utils/utils.h"
#include "output/output.hpp"
#include <Magick++.h>
#include <cstdint>
#include <vector>

#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>

using namespace Magick;
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
       << "\n"
       << "Colour passing methods:\n"
       << "  -c, --colour <value>\t\tDeclare a colour using ARGB format (e.g., "
          "ff902922)\n"
       << "  -m, --image <path>\t\tPath to image\n"
       << "\n"
       << "Outputs:\n"
       << "  -i, --inja <template-path>\tPath to Inja template for the "
          "palette. This will require -o\n"
       << "  -o, --output <path>\t\tOutput path\n"
       << "  -j, --json\t\t\tPrint JSON representation of the palette\n"
       << "\n"
       << "Options:\n"
       << "  -d, --dark-mode\t\tEnable dark mode\n"
       << "  -h, --help\t\t\tDisplay this help message\n"
       << "\n"
       << "Examples:\n"
       << "  iroha -j --colour ff902922\n"
       << "  iroha -d -j -c ff902922\n"
       << "  iroha -i template.css -o output.css -c ff902922\n"
       << "  iroha -m poisonous-red-fluff.png -i template.css -o output.css\n";
}

vector<Argb> magicc(filesystem::path path) {
  vector<Argb> colours;
  Image image(path);
  image.resize(Magick::Geometry(256, 256));
  for (int i = 0; i < image.columns(); i++) {
    for (int j = 0; j < image.rows(); j++) {
      ColorRGB pixel = image.pixelColor(i, j);
      stringstream ss;
      ss << hex
         << (int(pixel.alpha() * 255) << 24 | int(pixel.red() * 255) << 16 |
             int(pixel.green() * 255) << 8 | int(pixel.blue() * 255));
      colours.push_back(stringToArgb(ss.str()));
    }
  }
  return colours;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    help();
    return 1;
  }

  InitializeMagick(*argv);

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
    } else if (*flag == "-m" || *flag == "--image") {
      if (next(flag) == args.end()) {
        help();
        return 1;
      }
      vector<Argb> argbVec = magicc(next(flag)->c_str());
      QuantizerResult quantizerRes = QuantizeCelebi(argbVec, uint32_t(128));

      std::map<Argb, uint32_t> convertedMap;

      for (const auto &pair : quantizerRes.color_to_count) {
        // Assuming that the values are within the valid range of uint32_t
        convertedMap[pair.first] = static_cast<uint32_t>(pair.second);
      }

      vector<Argb> colours = RankedSuggestions(convertedMap);

      argb = colours[0];
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
