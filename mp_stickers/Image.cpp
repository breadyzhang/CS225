#include "Image.h"
using namespace std;
void Image::darken(){

  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.l >= .1)
        pixel.l = pixel.l - .1;
      else
        pixel.l = 0;
    }
  }
}

void Image::darken(double amount) {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.l >= amount)
        pixel.l = pixel.l - amount;
      else
        pixel.l = 0;
    }
  }
}

void Image::desaturate() {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.s >= .1)
        pixel.s = pixel.s - .1;
      else
        pixel.s = 0;
    }
  }
}

void Image::desaturate(double amount) {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.s >= amount)
        pixel.s = pixel.s - amount;
      else
        pixel.s = 0;
    }
  }
}

void Image::grayscale() {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      pixel.s = 0;
    }
  }
}

void Image::illinify() {
  int blue = 216;
  int orange = 11;
  for(unsigned i = 0; i < width(); i++){
    for(unsigned j = 0; j < height(); j++){
      cs225::HSLAPixel & pixel = getPixel(i,j);
      double hue = pixel.h;
      if(hue < 318 && hue > 108){
        pixel.h = blue;
      }
      else
        pixel.h = orange;
    }
  }
}

void Image::lighten() {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.l + .1 > 1)
        pixel.l = 1;
      else
        pixel.l = pixel.l + .1;
    }
  }
}

void Image::lighten(double amount) {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.l + amount > 1)
        pixel.l = 1;
      else
        pixel.l = pixel.l + amount;
    }
  }
}

void Image::rotateColor(double degrees) {
  for(unsigned int i = 0; i < width(); i++) {
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      pixel.h = pixel.h + degrees;
      if(pixel.h > 360) {
        pixel.h = pixel.h - 360;
      }
      else if(pixel.h < 0) {
        pixel.h = pixel.h + 360;
      }
    }
  }
}

void Image::saturate() {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.s + .1 > 1)
        pixel.s = 1;
      else
        pixel.s = pixel.s + .1;
    }
  }
}

void Image::saturate(double amount) {
  for(unsigned int i = 0; i < width(); i++){
    for(unsigned int j = 0; j < height(); j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      if(pixel.s + amount > 1)
        pixel.s = 1;
      else
        pixel.s = pixel.s + amount;
    }
  }
}

void Image::scale(double factor) {
  unsigned oldwidth = width();
  unsigned oldheight = height();
  unsigned width = factor * oldwidth;
  unsigned height = factor * oldheight;
  cs225::PNG scaled = cs225::PNG(width, height);
  //cout << "width: " << width << " height: " << height << endl;
  for(unsigned i = 0; i < width; i++) {
    for(unsigned j = 0; j < height; j++) {
      unsigned x = i / factor;
      unsigned y = j / factor;
      //cout << x << " , " << y << endl;
      cs225::HSLAPixel & pixel = getPixel(x,y);
      cs225::HSLAPixel & scaledPixel = scaled.getPixel(i,j);
      scaledPixel = pixel;
    }
  }
  resize(width, height);
  //cout << width() << " , " << height() << endl;
  for(unsigned i = 0; i < width; i++) {
    for(unsigned j = 0; j < height; j++) {
      cs225::HSLAPixel & pixel = getPixel(i,j);
      cs225::HSLAPixel & scaledPixel = scaled.getPixel(i,j);
      pixel = scaledPixel;
    }
  }
}

void Image::scale(unsigned w, unsigned h) {
  double wfactor = (double)w / width();
  double hfactor = (double)h / height();
  //cout << wfactor << " " << hfactor << endl;
  if(wfactor > hfactor) {
    //cout << "scaling using width" << endl;
    scale(hfactor);
    //cout << width() << ", " << height() << endl;
  }
  else{
    //cout << "scaling using height" << endl;
    scale(wfactor);
  }
}
