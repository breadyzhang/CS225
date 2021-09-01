#include "StickerSheet.h"
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max) {
  image_ = new Image*[max];
  base_ = &picture;
  x_ = new unsigned[max];
  y_ = new unsigned[max];
  max_ = max;
  for(unsigned i = 0; i < max; i++) {
    image_[i] = NULL;
  }
}

StickerSheet::~StickerSheet(){
  _destroy();
}

StickerSheet::StickerSheet(const StickerSheet &other) {
    image_ = NULL;
    _copy(other);
}

StickerSheet const StickerSheet::operator=(const StickerSheet &other) {
  if(this != &other) {
    _copy(other);
  }
  return *this;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y) {
  unsigned index = 0;
  while(image_[index] != NULL && index < max_) {
    //cout << "somthing in here" <<endl;
    index++;
  }
  if(index >= max_){
    //cout<<"index overload"<<endl;
    return -1;
  }
  //out << "index: " << index << endl;
  image_[index] = &sticker;
  x_[index] = x;
  y_[index] = y;
  //cout << x_[index] << ", " << y_[index] << endl;
  return index;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
  if(index > max_ || image_[index] == NULL) {
    return false;
  }
  x_[index] = x;
  y_[index] = y;
  return true;
}

void StickerSheet::removeSticker(unsigned index) {
  image_[index] = NULL;
  x_[index] = 0;
  y_[index] = 0;
}

Image* StickerSheet::getSticker(unsigned index) {
  if(index > max_ || image_[index] == NULL) {
    return NULL;
  }
  return image_[index];
}

Image StickerSheet::render() const {
  Image render = *base_;
  unsigned width, height;
  for(unsigned i = 0; i < max_; i++) {
    //cout << "index: " << i << endl;
    if(image_[i] == NULL){
      //cout << "null" << endl;
    }
    else{
      //cout << "printing: " << i <<endl;
      //cout << "x[i]_: " << x_[i] << " y_[i]: " << y_[i] << endl;
      for(unsigned j = 0; j < image_[i]->width(); j++) {
        if(x_[i] + j >= base_->width()){
          //cout << "break j" << endl;
          j = image_[i]->width() + 20;
        }
        else {
          for(unsigned k = 0; k < image_[i]->height(); k++) {
            if(y_[i] + k >= base_->height()){
              //cout << "break k" << endl;
              k = image_[i]->height() + 20;
            }
            else{
              cs225::HSLAPixel & pixel = image_[i]->getPixel(j,k);
              cs225::HSLAPixel & rendered = render.getPixel(x_[i] + j, y_[i] + k);
              if(pixel.a == 0){}
              else {
                rendered = pixel;
              }
            }
          }
        }
      }
    }
  }
  return render;
}

void StickerSheet::changeMaxStickers(unsigned max) {
  unsigned* x = new unsigned[max];
  unsigned* y = new unsigned[max];
  Image** image = new Image*[max];
  if(max > max_) {
    for(unsigned i = 0; i < max; i++) {
      //cout<<"changeMaxStickers: " <<i<<endl;
      if(i >= max_){
        //<<"making it null" << endl;
        image[i] = NULL;
      }
      else {
        x[i] = x_[i];
        y[i] = y_[i];
        image[i] = image_[i];
      }
    }
  }
  else {
    for(unsigned i = 0; i < max; i++) {
        x[i] = x_[i];
        y[i] = y_[i];
        image[i] = image_[i];
    }
  }
  max_ = max;
  delete[] x_;
  delete[] y_;
  delete[] image_;
  x_ = x;
  y_ = y;
  image_ = image;
}

void StickerSheet::_copy(const StickerSheet &other) {
  _destroy();
  max_ = other.max_;
  image_ = new Image*[max_];
  x_ = new unsigned[max_];
  y_ = new unsigned[max_];
  base_ = other.base_;
  for(unsigned i = 0; i < max_; i++) {
    image_[i] = other.image_[i];
    x_[i] = other.x_[i];
    y_[i] = other.y_[i];
  }
}

void StickerSheet::_destroy() {
  delete[] image_;
  delete[] x_;
  delete[] y_;
  //delete base_;
}
