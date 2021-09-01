#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  // creating PNGS objects in and out
  cs225::PNG in;
  in.readFromFile(inputFile);
  // setting dimensions of out to be same as in
  cs225::PNG out(in.width(), in.height());

  for(unsigned x = 0; x < in.width(); x++) {
    for(unsigned y = 0; y < in.height(); y++) {
      unsigned rotatex = in.width() - x - 1;
      unsigned rotatey = in.height() - y - 1;

      cs225::HSLAPixel & pixelout = out.getPixel(x,y);
      pixelout = in.getPixel(rotatex, rotatey);
    }
  }

  out.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3

  // generating 4 random colors that will create a gradient in the picture
  srand(time(0));
  double hue1 = rand() % 90;
  srand(time(0) + 1);
  double hue2 = rand() % 90 + 90;
  srand(time(0) + 2);
  double hue3 = rand() % 90 + 180;
  srand(time(0) + 3);
  double hue4 = rand() % 90 + 270;
  std::cout << hue1 << " " << hue2 << " " << hue3 << " " << hue4 << std::endl;

  for(unsigned x = 0; x < width; x++) {
    for(unsigned y = 0; y < height; y++) {
      double wid = width;
      double hei = height;
      double percentwide = (wid - x) / wid;
      double percenthigh = (hei - y) / hei;
      cs225::HSLAPixel & pixel = png.getPixel(x,y);
      double color = (percentwide * hue1 + (1 - percentwide) * hue2) * percenthigh + (percentwide * hue3 + (1 - percentwide) * hue4) * (1-percenthigh);
      pixel.h = color;
      pixel.l = .5;
      pixel.s = 1;

    }
  }

  return png;
}
