/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
using namespace std;
template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  ListNode* next = head_;
  while(curr) {
    next = curr->next;
    delete curr;
    curr = next;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode->prev = NULL;
  if(head_ == NULL) {
    //cout << "insertFront NULL" << endl;
    newNode->next = NULL;
    head_ = newNode;
    tail_ = newNode;
  }
  else {
    //cout << "insertFront AVAIL" << endl;
    head_->prev = newNode;
    newNode->next = head_;
    head_ = newNode;
  }

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* newNode = new ListNode(ndata);
  newNode->next = NULL;
  if(tail_ == NULL) {
    newNode->prev = NULL;
    head_ = newNode;
    tail_ = newNode;
  }
  else {
    tail_->next = newNode;
    newNode->prev = tail_;
    tail_ = newNode;
  }

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(splitPoint == 0){
    return start;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
      ListNode* prev = curr->prev;
      prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three
  * elements in the list starting for the first three elements. If the
  * end of the list has a set of 1 or 2 elements, no rotation all be done
  * on the last 1 or 2 elements.
  *
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  if(head_ == NULL) {
    return;
  }
  ListNode* one = head_;
  while(one) {
    ListNode* two = one->next;
    if(two == NULL){
      return;
    }
    ListNode* three = two->next;
    if(three == NULL){
      return;
    }

    if(three == tail_){
      one->next = NULL;
      tail_ = one;
    }
    else{
      ListNode* four = three->next;
      one->next = four;
      four->prev = one;
    }

    if(one == head_) {
      two->prev = NULL;
      head_ = two;
    }
    else{
      ListNode* zero = one->prev;
      two->prev = one->prev;
      zero->next = two;
    }

    three->next = one;
    one->prev = three;
    one = one->next;
    ListNode* node = head_;
  }
}
/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  //reverse(head_, tail_);
  if(head_ == NULL){
    return;
  }
  ListNode* curr = head_;
  ListNode* prev = NULL;
  ListNode* next = head_->next;
  while(curr){
    if(curr == head_) {
      tail_ = curr;
      curr->next = NULL;
      curr->prev = next;
    }
    else if(curr->next == NULL) {
      head_ = curr;
      curr->next = prev;
      curr->prev = NULL;
      return;
    }
    else{
      curr->prev = next;
      curr->next = prev;
    }
    curr = next;
    prev = next->prev;
    next = next->next;
  }
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in
  ListNode* curr = startPoint;
  ListNode* end = endPoint;
  ListNode* prev = NULL;
  ListNode* next = NULL;
  ListNode* front = startPoint->prev;
  ListNode* back = endPoint->next;

  while(curr != end){
    if(startPoint == head_){
      prev = NULL;
      next = curr->next;
      head_ = endPoint;
    }
    else{
      next = curr->next;
      prev = curr->prev;
    }
    curr->prev = next;
    curr->next = prev;
    curr = next;
  }
  if(endPoint == tail_){
    next = NULL;
    prev = curr->prev;
    tail_ = startPoint;
  }
  else{
    next = curr->next;
    prev = curr->prev;
  }
  curr->prev = next;
  curr->next = prev;
  curr = next;
  if(back)
    back->prev = startPoint;
  if(front)
    front->next = endPoint;
  startPoint->next = back;
  endPoint->prev = front;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode* curr = head_;
  while(curr) {
    ListNode* end = curr;
    for(int i = 1; i < n; i++){
      if(end->next){
        end = end->next;
      }
    }

    reverse(curr, end);
    if(end == NULL)
      break;
    else if(end->next == NULL)
      break;
    else
      curr = curr->next;
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* one = first;
  ListNode* two = second;
  while(one){
    ListNode* next = one->next;
    if(two == NULL)
      return first;
    if(two->data < first->data) {
      second = second->next;
      two->next = one;
      one->prev = two;
      two->prev = NULL;
      first = two;
      one = first;
      two = second;
    }
    else if(next == NULL){
      one->next = second;
      second->prev = one;
      return first;
    }
    else if((one->data < two->data && two->data < next->data) || (one->data == two->data)){
      second = second->next;
      one->next = two;
      two->prev = one;
      two->next = next;
      next->prev = two;
      two = second;
      one = one->next;
    }
    else{
      one = one->next;
    }

  }
  return first;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1) {
    return start;
  }
  int half = chainLength/2;
  ListNode* divide = split(start, half);
  ListNode* one = mergesort(start,half);
  ListNode* two = mergesort(divide,chainLength-half);


  one = merge(one,two);

  return one;

}
