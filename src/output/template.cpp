#include "output.hpp"
#include <inja.hpp>

#include <iostream>
#include <string>

using namespace std;

InjaTpl::InjaTpl(){};
InjaTpl::InjaTpl(std::string inputPath, std::string outputPath)
    : inputPath(std::move(inputPath)), outputPath(std::move(outputPath)) {
  cout << "input: " << this->inputPath << endl;
}
InjaTpl::~InjaTpl() { cout << "Injatpl destroyed" << endl; };
void InjaTpl::setInputPath(string path) {
  inputPath = std::move(path);
  cout << "input" << inputPath << endl;
};
void InjaTpl::setOutputPath(string path) { outputPath = path; };
void InjaTpl::printInja(Palette &palette) {
  tmpl = env.parse_template(inputPath);
  env.write(tmpl, getJson(palette), outputPath);
}