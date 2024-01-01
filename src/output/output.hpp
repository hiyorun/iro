#include "../engine/palette.hpp"

#include <inja.hpp>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// JSON
json getJson(Palette &palette);
void printJson(Palette &palette, bool prettier = false);

class InjaTpl {
private:
  inja::Environment env;
  inja::Template tmpl;
  string inputPath, outputPath;

public:
  InjaTpl();
  InjaTpl(string inputPath, string outputPath);
  ~InjaTpl();
  void setInputPath(string path);
  void setOutputPath(string path);
  void printInja(Palette &palette);
};