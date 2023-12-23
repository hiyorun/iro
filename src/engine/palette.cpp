#include "palette.hpp"
#include "cpp/dynamiccolor/material_dynamic_colors.h"
#include <iostream>

Palette::Palette(Hct hct) {
  initialColour = hct;
  setSchemes(hct);
}
Palette::Palette(Argb argb) {
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
void Palette::setSchemes(Hct hct, double contrastLevel) {
  lightScheme = SchemeTonalSpot(initialColour, false, contrastLevel);
  darkScheme = SchemeTonalSpot(initialColour, true, contrastLevel);
}
Colour Palette::getPrimary() {
  return Colour(MaterialDynamicColors::Primary().GetArgb(lightScheme));
}
Colour Palette::getOnPrimary() {
  return Colour(MaterialDynamicColors::OnPrimary().GetArgb(lightScheme));
}
Colour Palette::getSurface() {
  return Colour(MaterialDynamicColors::Surface().GetArgb(lightScheme));
}
Colour Palette::getOnSurface() {
  return Colour(MaterialDynamicColors::OnSurface().GetArgb(lightScheme));
}
Colour Palette::getSecondary() {
  return Colour(MaterialDynamicColors::Secondary().GetArgb(lightScheme));
}
Colour Palette::getOnSecondary() {
  return Colour(MaterialDynamicColors::OnSecondary().GetArgb(lightScheme));
}
Colour Palette::getPrimaryContainer() {
  return Colour(MaterialDynamicColors::PrimaryContainer().GetArgb(lightScheme));
}
Colour Palette::getOnPrimaryContainer() {
  return Colour(
      MaterialDynamicColors::OnPrimaryContainer().GetArgb(lightScheme));
}
Colour Palette::getSurfaceBright() {
  return Colour(MaterialDynamicColors::SurfaceBright().GetArgb(lightScheme));
}
Colour Palette::getSurfaceDim() {
  return Colour(MaterialDynamicColors::SurfaceDim().GetArgb(lightScheme));
}
Colour Palette::getSecondaryContainer() {
  return Colour(
      MaterialDynamicColors::SecondaryContainer().GetArgb(lightScheme));
}
Colour Palette::getOnSecondaryContainer() {
  return Colour(
      MaterialDynamicColors::OnSecondaryContainer().GetArgb(lightScheme));
}
Colour Palette::getSurfaceVariant() {
  return Colour(MaterialDynamicColors::SurfaceVariant().GetArgb(lightScheme));
}
Colour Palette::getOnSurfaceVariant() {
  return Colour(MaterialDynamicColors::OnSurfaceVariant().GetArgb(lightScheme));
}
Colour Palette::getTertiary() {
  return Colour(MaterialDynamicColors::Tertiary().GetArgb(lightScheme));
}
Colour Palette::getOnTertiary() {
  return Colour(MaterialDynamicColors::OnTertiary().GetArgb(lightScheme));
}
Colour Palette::getTertiaryContainer() {
  return Colour(
      MaterialDynamicColors::TertiaryContainer().GetArgb(lightScheme));
}
Colour Palette::getOnTertiaryContainer() {
  return Colour(
      MaterialDynamicColors::OnTertiaryContainer().GetArgb(lightScheme));
}
Colour Palette::getError() {
  return Colour(MaterialDynamicColors::Error().GetArgb(lightScheme));
}
Colour Palette::getOnError() {
  return Colour(MaterialDynamicColors::OnError().GetArgb(lightScheme));
}
Colour Palette::getErrorContainer() {
  return Colour(MaterialDynamicColors::ErrorContainer().GetArgb(lightScheme));
}
Colour Palette::getOnErrorContainer() {
  return Colour(MaterialDynamicColors::OnErrorContainer().GetArgb(lightScheme));
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
