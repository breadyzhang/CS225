
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"
#include <iostream>

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;
using namespace std;


int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  // PNG png;
  // png.readFromFile("picture.png");
  //
  // FloodFilledImage image(png);
  // DFS dfs(png, Point(80,400), 0.1);
  // MyColorPicker bruh(200);
  // image.addFloodFill( dfs, bruh );
  // Animation animation = image.animate(10000);
  // PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  // lastFrame.writeToFile("picture.png");
  //
  // png.readFromFile("picture.png");
  // FloodFilledImage pic(png);
  // DFS dfs(png, Point(), 0.1);
  // MyColorPicker wtf(200);
  // image.addFloodFill(dfs, wtf);
  // lastFrame.writeToFile("myFloodFill.png");


    PNG png;      png.readFromFile("picture.png");

    FloodFilledImage image(png);
    BFS bfs(png, Point(80, 400), 0.05);
    //RainbowColorPicker rainbow(0.05);
    MyColorPicker bruh(30);
    image.addFloodFill( bfs, bruh);

    Animation animation = image.animate(1000);
    //PNG secondFrame = animation.getFrame(1);
    PNG tempLast = animation.getFrame( animation.frameCount() - 1);
    tempLast.writeToFile("halfway.png");

    PNG png2; png2.readFromFile("halfway.png");

    FloodFilledImage image2(png2);
    DFS dfs(png, Point(285, 300), 0.2);
    //SolidColorPicker solid(color);
    MyColorPicker wtf(15);
    image2.addFloodFill( dfs, wtf );

    Animation animation2 = image2.animate(1000);

    PNG lastFrame = animation2.getFrame( animation2.frameCount() - 1 );
    lastFrame.writeToFile("myFloodFill.png");
    animation.write("myFloodFill.gif");
    animation2.write("anotherfloodfill.gif");
  return 0;
}
