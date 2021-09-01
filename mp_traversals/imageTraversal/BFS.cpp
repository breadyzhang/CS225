#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {
  /** @todo [Part 1] */
  visited = new int[png.height() * png.width()]();
  // for(unsigned y = 0; y < png.height(); y++){
  //   for(unsigned x = 0; x < png.width(); x++) {
  //     std::cout<<visited[x+y*png.width()];
  //   }
  //   std::cout<<std::endl;
  // }
  img = png;
  first = start;
  diff = tolerance;
  add(start);
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this,first);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
  /** @todo [Part 1] */
  //std::cout<<"adding: "<<point<<std::endl;
  points.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
  /** @todo [Part 1] */
  if(points.size() > 0){
    Point point = points.front();
    points.pop();
    return point;
  }
  return Point(0, 0);
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
  /** @todo [Part 1] */
  if(points.size() > 0){
    return points.front();
  }
  return Point(0, 0);
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
  /** @todo [Part 1] */
  if(points.size() == 0)
    return true;
  return false;
}

PNG BFS::pngOut(){
  return img;
}

Point BFS::getStart(){
  return first;
}

double BFS::getTolerance(){
  return diff;
}
