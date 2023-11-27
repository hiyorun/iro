#include "palette.hpp"
#include <iostream>
#include <ostream>
#include <sstream>

using namespace material_color_utilities;
using namespace std;

// Function to convert string to Argb
Argb stringToArgb(const string &str) {
  stringstream ss(str);
  Argb argb;
  ss >> hex >> argb;
  return argb;
}

void printAll(Palette palette) {
  cout << "getPrimary" << endl;
  cout << palette.getPrimary() << endl << endl;
  cout << "getOnPrimary" << endl;
  cout << palette.getOnPrimary() << endl << endl;
  cout << "getSurface" << endl;
  cout << palette.getSurface() << endl << endl;
  cout << "getOnSurface" << endl;
  cout << palette.getOnSurface() << endl << endl;
  cout << "getSecondary" << endl;
  cout << palette.getSecondary() << endl << endl;
  cout << "getOnSecondary" << endl;
  cout << palette.getOnSecondary() << endl << endl;
  cout << "getPrimaryContainer" << endl;
  cout << palette.getPrimaryContainer() << endl << endl;
  cout << "getOnPrimaryContainer" << endl;
  cout << palette.getOnPrimaryContainer() << endl << endl;
  cout << "getSurfaceBright" << endl;
  cout << palette.getSurfaceBright() << endl << endl;
  cout << "getSurfaceDim" << endl;
  cout << palette.getSurfaceDim() << endl << endl;
  cout << "getSecondaryContainer" << endl;
  cout << palette.getSecondaryContainer() << endl << endl;
  cout << "getOnSecondaryContainer" << endl;
  cout << palette.getOnSecondaryContainer() << endl << endl;
  cout << "getSurfaceVariant" << endl;
  cout << palette.getSurfaceVariant() << endl << endl;
  cout << "getOnSurfaceVariant" << endl;
  cout << palette.getOnSurfaceVariant() << endl << endl;
  cout << "getTertiary" << endl;
  cout << palette.getTertiary() << endl << endl;
  cout << "getOnTertiary" << endl;
  cout << palette.getOnTertiary() << endl << endl;
  cout << "getTertiaryContainer" << endl;
  cout << palette.getTertiaryContainer() << endl << endl;
  cout << "getOnTertiaryContainer" << endl;
  cout << palette.getOnTertiaryContainer() << endl << endl;
  cout << "getError" << endl;
  cout << palette.getError() << endl << endl;
  cout << "getOnError" << endl;
  cout << palette.getOnError() << endl << endl;
  cout << "getErrorContainer" << endl;
  cout << palette.getErrorContainer() << endl << endl;
  cout << "getOnErrorContainer" << endl;
  cout << palette.getOnErrorContainer() << endl << endl;
}

int main(int argc, char *argv[]) {
  // Check if there is at least one command-line argument
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << " <Argb_value>" << endl;
    return 1; // Return an error code
  }

  // Convert the first command-line argument to Argb
  Argb argb = stringToArgb(argv[1]);

  // Create Palette with the Argb value
  Palette palette(argb);

  // Print all the colours
  printAll(palette);
  return 0;
}