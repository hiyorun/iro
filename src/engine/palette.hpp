#include "colour.hpp"
#include "cpp/cam/hct.h"
#include "cpp/scheme/dynamic_scheme.h"
#include "cpp/scheme/scheme_tonal_spot.h"
#include <functional>
#include <string>
#include <unordered_map>

using namespace material_color_utilities;

enum class PaletteMode { LIGHT, DARK };

class Palette {
private:
  Hct initialColour = Hct(0x00000000);
  DynamicScheme lightScheme = SchemeTonalSpot(initialColour, false, 0.0);
  DynamicScheme darkScheme = SchemeTonalSpot(initialColour, true, 0.0);
  PaletteMode currentMode;

  DynamicScheme getScheme(PaletteMode mode);

  std::unordered_map<std::string, std::function<Colour()>> colourMap = {
      {"primary", [this]() { return getPrimary(); }},
      {"onPrimary", [this]() { return getOnPrimary(); }},
      {"surface", [this]() { return getSurface(); }},
      {"onSurface", [this]() { return getOnSurface(); }},
      {"secondary", [this]() { return getSecondary(); }},
      {"onSecondary", [this]() { return getOnSecondary(); }},
      {"primaryContainer", [this]() { return getPrimaryContainer(); }},
      {"onPrimaryContainer", [this]() { return getOnPrimaryContainer(); }},
      {"surfaceBright", [this]() { return getSurfaceBright(); }},
      {"surfaceDim", [this]() { return getSurfaceDim(); }},
      {"secondaryContainer", [this]() { return getSecondaryContainer(); }},
      {"onSecondaryContainer", [this]() { return getOnSecondaryContainer(); }},
      {"surfaceVariant", [this]() { return getSurfaceVariant(); }},
      {"onSurfaceVariant", [this]() { return getOnSurfaceVariant(); }},
      {"tertiary", [this]() { return getTertiary(); }},
      {"onTertiary", [this]() { return getOnTertiary(); }},
      {"tertiaryContainer", [this]() { return getTertiaryContainer(); }},
      {"onTertiaryContainer", [this]() { return getOnTertiaryContainer(); }},
      {"error", [this]() { return getError(); }},
      {"onError", [this]() { return getOnError(); }},
      {"errorContainer", [this]() { return getErrorContainer(); }},
      {"onErrorContainer", [this]() { return getOnErrorContainer(); }},
      {"shadow", [this]() { return getShadow(); }},
      {"outline", [this]() { return getOutline(); }},
  };

public:
  Palette(Hct hct);
  Palette(Argb argb);
  Palette(Hct hct, double contrastLevel);
  ~Palette();
  void setMode(PaletteMode mode);
  PaletteMode getMode();
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
  Colour getShadow();
  Colour getOutline();
  Colour getColourByName(const std::string &colourName);
};