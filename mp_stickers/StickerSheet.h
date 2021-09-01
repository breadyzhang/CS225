/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet {
public:
  StickerSheet(const Image &, unsigned);
  ~StickerSheet();
  StickerSheet(const StickerSheet &);
  const StickerSheet operator=(const StickerSheet &);
  void changeMaxStickers(unsigned);
  int addSticker(Image &, unsigned, unsigned);
  bool translate(unsigned, unsigned, unsigned);
  void removeSticker(unsigned);
  Image* getSticker(unsigned);
  Image render() const;
private:
  const Image* base_;
  Image** image_;
  unsigned max_;
  unsigned* x_;
  unsigned* y_;
  void _copy(const StickerSheet &);
  void _destroy();
};
