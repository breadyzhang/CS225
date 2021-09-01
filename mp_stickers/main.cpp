#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage->png
  //
  Image waffle, pog, orange, lego;
  waffle.readFromFile("waffle.png");
  pog.readFromFile("pog.png");
  pog.scale(90,90);
  orange.readFromFile("orange.png");
  orange.scale(100,100);
  lego.readFromFile("lego.png");
  lego.scale(120,120);
  StickerSheet* sheet = new StickerSheet(waffle, 6);
  sheet->addSticker(lego, 0, 0);
  sheet->addSticker(orange, 20, 20);
  sheet->addSticker(pog, 40, 20);
  sheet->addSticker(pog, 100, 100);
  Image rendering = sheet->render();
  rendering.writeToFile("myImage.png");

  return 0;
}
