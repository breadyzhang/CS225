#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal = NULL;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* traverse, Point first){
  traversal = traverse;
  curr = first;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  PNG png = traversal->pngOut();
  traversal->wide = png.width();
  if(traversal->isVisited(curr)){
    Point p = traversal->pop();
    curr = traversal->peek();
    return *this;
  }
  traversal->setVisited(curr);
  unsigned height = png.height();
  unsigned width = png.width();
  Point p = traversal->pop();
  // check pixel to right
  Point point(curr.x + 1, curr.y);
  //std::cout<<"point: "<<point<<std::endl;
  if(point.x < width){
    if(!traversal->isVisited(point)){
      Point start = traversal->getStart();
      HSLAPixel & first = png.getPixel(start.x, start.y);
      HSLAPixel & pixel = png.getPixel(point.x, point.y);
      double delta = calculateDelta(first, pixel);
      double tolerance = traversal->getTolerance();
      if(delta < tolerance){
        traversal->add(point);
        //std::cout<<"added: "<<point<<std::endl;
      }
    }
  }
  // check pixel below
  point.x = curr.x;
  point.y = curr.y+1;
  //std::cout<<"point: "<<point<<std::endl;
  if(point.y < height){
    if(!traversal->isVisited(point)){
      Point start = traversal->getStart();
      HSLAPixel & first = png.getPixel(start.x, start.y);
      HSLAPixel & pixel = png.getPixel(point.x, point.y);
      double delta = calculateDelta(first, pixel);
      double tolerance = traversal->getTolerance();
      if(delta < tolerance){
        traversal->add(point);
        //std::cout<<"added: "<<point<<std::endl;
      }
    }
  }
  // check pixel left
  point.x = curr.x-1;
  point.y = curr.y;
  //std::cout<<"point: "<<point<<std::endl;
  if(point.x < width){
    if(!traversal->isVisited(point)){
      Point start = traversal->getStart();
      HSLAPixel & first = png.getPixel(start.x, start.y);
      HSLAPixel & pixel = png.getPixel(point.x, point.y);
      double delta = calculateDelta(first, pixel);
      double tolerance = traversal->getTolerance();
      if(delta < tolerance){
        traversal->add(point);
        //std::cout<<"added: "<<point<<std::endl;
      }
    }
  }
  //check pixel up
  point.x = curr.x;
  point.y = curr.y-1;
  //std::cout<<"point: "<<point<<std::endl;
  if(point.y < height){
    if(!traversal->isVisited(point)){
      Point start = traversal->getStart();
      HSLAPixel & first = png.getPixel(start.x, start.y);
      HSLAPixel & pixel = png.getPixel(point.x, point.y);
      double delta = calculateDelta(first, pixel);
      double tolerance = traversal->getTolerance();
      if(delta < tolerance){
        traversal->add(point);
        //std::cout<<"added: "<<point<<std::endl;
      }
    }
  }
  curr = traversal->peek();
  while(traversal->isVisited(curr) && !traversal->empty() ){
    traversal->pop();
    curr = traversal->peek();
  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false;
  bool otherEmpty = false;

  if(traversal == NULL)
    thisEmpty = true;
  if(other.traversal == NULL)
    otherEmpty = true;
  if(!thisEmpty)
    thisEmpty = traversal->empty();
  if(!otherEmpty)
    otherEmpty = other.traversal->empty();

  if(thisEmpty && otherEmpty)
    return false;
  else if ((!thisEmpty)&&(!otherEmpty))
    return traversal != other.traversal;
  else
    return true;
}

bool ImageTraversal::isVisited(Point point){
  unsigned x = point.x;
  unsigned y = point.y;
  return visited[x + y*wide];
}

void ImageTraversal::setVisited(Point point){
  unsigned x = point.x;
  unsigned y = point.y;
  visited[x+y*wide] = 1;
  //std::cout<<"setting visited: "<<x<<" "<<y<<" "<<wide<<std::endl;
}
