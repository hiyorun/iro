#include "colour.hpp"
#include "cpp/cam/hct.h"
#include "cpp/scheme/dynamic_scheme.h"
#include "cpp/scheme/scheme_tonal_spot.h"

using namespace material_color_utilities;

class Palette {
private:
  Hct initialColour = Hct(0x00000000);
  DynamicScheme lightScheme = SchemeTonalSpot(initialColour, false, 0.0);
  DynamicScheme darkScheme = SchemeTonalSpot(initialColour, true, 0.0);

public:
  Palette(Hct hct);
  Palette(Argb argb);
  Palette(Hct hct, double contrastLevel);
  ~Palette();
  void setSchemes(Hct hct, double contrastLevel = 0.0);
  Colour getPrimary();
  Colour getOnPrimary();
  Colour getSurface();
  Colour getOnSurface();
  Colour getSecondary();
  Colour getOnSecondary();
  Colour getPrimaryContainer();
  Colour getOnPrimaryContainer();
  Colour getSurfaceBright();
  Colour getSurfaceDim();
  Colour getSecondaryContainer();
  Colour getOnSecondaryContainer();
  Colour getSurfaceVariant();
  Colour getOnSurfaceVariant();
  Colour getTertiary();
  Colour getOnTertiary();
  Colour getTertiaryContainer();
  Colour getOnTertiaryContainer();
  Colour getError();
  Colour getOnError();
  Colour getErrorContainer();
  Colour getOnErrorContainer();
};