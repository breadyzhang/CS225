/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

class Image : public cs225::PNG {
public:
  void lighten();
  void lighten(double);
  void darken();
  void darken(double);
  void saturate();
  void saturate(double);
  void desaturate();
  void desaturate(double);
  void grayscale();
  void rotateColor(double);
  void illinify();
  void scale(double);
  void scale(unsigned, unsigned);
};
