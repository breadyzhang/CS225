/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] < second[curDim]){
      return true;
    }
    else if(second[curDim] < first[curDim]){
      return false;
    }
    else{
      return first < second;
    }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double current = 0;
     double pot = 0;
     for(int i = 0; i < Dim; i++) {
       pot += (potential[i] - target[i]) * (potential[i] - target[i]);
       current = (currentBest[i] - target[i]) * (currentBest[i] - target[i]);
     }
     pot = sqrt(pot);
     current = sqrt(current);
     if(pot < current)
      return true;
     return false;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
     if(newPoints.empty()){
       root = NULL;
       size = 0;
     }
     unsigned offset = 0;
     if(newPoints.size() % 2 == 1){
       offset = newPoints.size() / 2;
     }
     else{
       offset = newPoints.size()/2 - 1;
     }
     auto it = newPoints.begin() + offset;

     root = new KDTreeNode(*it);
     vector<Point<Dim>> leftPoints;
     leftPoints.assign(newPoints.begin(), it);
     vector<Point<Dim>> rightPoints;
     rightPoints.assign(it+1, newPoints.end());
     //root->left = new KDTreeNode(leftPoints);
     // root->right = new KDTreeNode(rightPoints);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
 _destroy();
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return Point<Dim>();
}

template <int Dim>
void KDTree<Dim>::_copy(const vector<Point<Dim>>& newPoints){
  _destroy();

}

template<int Dim>
void KDTree<Dim>::_destroy() {

}
