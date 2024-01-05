#include "palette.hpp"
#include "cpp/dynamiccolor/material_dynamic_colors.h"
#include <iostream>

Palette::Palette(Hct hct) : currentMode(PaletteMode::LIGHT) {
  initialColour = hct;
  setSchemes(hct);
}
Palette::Palette(Argb argb) : currentMode(PaletteMode::LIGHT) {
  initialColour = Hct(argb);
  setSchemes(initialColour);
}
Palette::Palette(Hct hct, double contrastLevel) {
  initialColour = hct;
  setSchemes(hct, contrastLevel);
}
Palette::~Palette() {
  initialColour = Hct(0x00000000);
  setSchemes(initialColour);
}

void Palette::setMode(PaletteMode mode) { currentMode = mode; }

PaletteMode Palette::getMode() { return currentMode; }

void Palette::setSchemes(Hct hct, double contrastLevel) {
  lightScheme = SchemeTonalSpot(initialColour, false, contrastLevel);
  darkScheme = SchemeTonalSpot(initialColour, true, contrastLevel);
}
Colour Palette::getPrimary() {
  return Colour(
      MaterialDynamicColors::Primary().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnPrimary() {
  return Colour(
      MaterialDynamicColors::OnPrimary().GetArgb(getScheme(currentMode)));
}
Colour Palette::getSurface() {
  return Colour(
      MaterialDynamicColors::Surface().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnSurface() {
  return Colour(
      MaterialDynamicColors::OnSurface().GetArgb(getScheme(currentMode)));
}
Colour Palette::getSecondary() {
  return Colour(
      MaterialDynamicColors::Secondary().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnSecondary() {
  return Colour(
      MaterialDynamicColors::OnSecondary().GetArgb(getScheme(currentMode)));
}
Colour Palette::getPrimaryContainer() {
  return Colour(MaterialDynamicColors::PrimaryContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getOnPrimaryContainer() {
  return Colour(MaterialDynamicColors::OnPrimaryContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getSurfaceBright() {
  return Colour(
      MaterialDynamicColors::SurfaceBright().GetArgb(getScheme(currentMode)));
}
Colour Palette::getSurfaceDim() {
  return Colour(
      MaterialDynamicColors::SurfaceDim().GetArgb(getScheme(currentMode)));
}
Colour Palette::getSecondaryContainer() {
  return Colour(MaterialDynamicColors::SecondaryContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getOnSecondaryContainer() {
  return Colour(MaterialDynamicColors::OnSecondaryContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getSurfaceVariant() {
  return Colour(
      MaterialDynamicColors::SurfaceVariant().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnSurfaceVariant() {
  return Colour(MaterialDynamicColors::OnSurfaceVariant().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getTertiary() {
  return Colour(
      MaterialDynamicColors::Tertiary().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnTertiary() {
  return Colour(
      MaterialDynamicColors::OnTertiary().GetArgb(getScheme(currentMode)));
}
Colour Palette::getTertiaryContainer() {
  return Colour(MaterialDynamicColors::TertiaryContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getOnTertiaryContainer() {
  return Colour(MaterialDynamicColors::OnTertiaryContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getError() {
  return Colour(MaterialDynamicColors::Error().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnError() {
  return Colour(
      MaterialDynamicColors::OnError().GetArgb(getScheme(currentMode)));
}
Colour Palette::getErrorContainer() {
  return Colour(
      MaterialDynamicColors::ErrorContainer().GetArgb(getScheme(currentMode)));
}
Colour Palette::getOnErrorContainer() {
  return Colour(MaterialDynamicColors::OnErrorContainer().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getShadow() {
  return Colour(MaterialDynamicColors::Shadow().GetArgb(
      getScheme(currentMode)));
}
Colour Palette::getOutline() {
  return Colour(MaterialDynamicColors::Outline().GetArgb(
      getScheme(currentMode)));
}

Colour Palette::getColourByName(const std::string &colourName) {
  auto it = colourMap.find(colourName);
  if (it != colourMap.end()) {
    return (it->second)();
  } else {
    std::cerr << "Unknown colour name: " << colourName << std::endl;
  }

  return Colour(0xFF000000);
}

DynamicScheme Palette::getScheme(PaletteMode mode) {
  if (mode == PaletteMode::LIGHT) {
    return lightScheme;
  }
  return darkScheme;
};