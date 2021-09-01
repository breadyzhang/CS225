/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* pivot = t->right;
    t->right = pivot->left;
    pivot->left = t;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;
    pivot->height = std::max(heightOrNeg1(t), heightOrNeg1(pivot->right)) + 1;
    t = pivot;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* pivot = t->left;
    t->left = pivot->right;
    pivot->right = t;
    t->height = std::max(heightOrNeg1(t->right), heightOrNeg1(t->left)) + 1;
    pivot->height = std::max(heightOrNeg1(t), heightOrNeg1(pivot->left)) + 1;
    t = pivot;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(heightOrNeg1(subtree) == -1)
      return;
    //std::cout<<"rebalance looking at: " <<subtree->key<<std::endl;
    int left,right;
    if(subtree->left == NULL)
      left = -1;
    else
      left = subtree->left->height;
    if(subtree->right == NULL)
      right = -1;
    else
      right = subtree->right->height;

    if(abs(right - left) <= 1){
      return;
    }
    // right heavy
    if(right - left >= 1){
      Node* pivot = subtree->right;
      // right stick

      int pright,pleft;
      if(pivot->left == NULL)
        pleft = -1;
      else
        pleft = pivot->left->height;
      if(pivot->right == NULL)
        pright = -1;
      else
        pright = pivot->right->height;

      if(pright > pleft){
        rotateLeft(subtree);
        //std::cout<<"left"<<std::endl;
        return;
      }
      else{
        rotateRightLeft(subtree);
        //std::cout<<"rightleft"<<std::endl;
        return;
      }
    }
    else{
      Node* pivot = subtree->left;
      int pright, pleft;

      if(pivot->left == NULL)
        pleft = -1;
      else
        pleft = pivot->left->height;
      if(pivot->right == NULL)
        pright = -1;
      else
        pright = pivot->right->height;

      if(pleft > pright){
        rotateRight(subtree);
        //std::cout<<"right"<<std::endl;
        return;
      }
      else{
        rotateLeftRight(subtree);
        //std::cout<<"leftright"<<std::endl;
        return;
      }
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      subtree = new Node(key, value);
      return;
    }
    if(key < subtree->key){
      insert(subtree->left, key, value);
    }
    else{
      insert(subtree->right, key, value);
    }
    subtree->height = std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
    //std::cout<<"insert: "<<key<<std::endl;
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    //std::cout<<"removing: " <<key<<std::endl;
    //std::cout<<"looking at: " << subtree->key<<std::endl;
    //std::cout<<" left,right: " <<heightOrNeg1(subtree->left)<<" "<<heightOrNeg1(subtree->right)<<std::endl;
    if (key < subtree->key) {
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            //std::cout<<"nochild"<<std::endl;
            subtree = NULL;
            clear(subtree);
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //std::cout<<"twochild"<<std::endl;
            Node* replace = subtree->left;
            Node* prev;
            while(replace->right){
              prev = replace;
              replace = replace->right;
            }
            swap(subtree, replace);
            delete replace;
            prev->right = NULL;
            //delete replace;
            //std::cout<<subtree->left->key<<std::endl;
            twochildRemove(subtree->left);
        } else {
            /* one-child remove */
            // your code here
            // std::cout<<"onechild"<<std::endl;
            if(heightOrNeg1(subtree->left) != -1){
              //swap(subtree, subtree->left);
              Node* temp = subtree->left;
              delete subtree;
              subtree = temp;
              // subtree->left = temp->left;
              // subtree->right = temp->right;
              //delete temp;
            }
            else {
              //swap(subtree, subtree->right);
              Node* temp = subtree->right;
              delete subtree;
              subtree = temp;
              // subtree->left = temp->left;
              // subtree->right = temp->right;
              //delete temp;
            }
            delete subtree;
            subtree = NULL;
        }
        // your code here
    }
    if(subtree != NULL){
      subtree->height = std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left)) + 1;
      //std::cout<<subtree->key<<" height: "<<subtree->height<<std::endl;
      //std::cout<<" left,right: " <<heightOrNeg1(subtree->left)<<" "<<heightOrNeg1(subtree->right)<<std::endl;
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::twochildRemove(Node* subroot){
  if(heightOrNeg1(subroot) == -1){
    //std::cout<<"it's null here"<<std::endl;
    return;
  }
  twochildRemove(subroot->right);
  subroot->height = std::max(heightOrNeg1(subroot->left), heightOrNeg1(subroot->right)) + 1;
  //std::cout<<"key: "<<subroot->key<<" height: "<<subroot->height<<std::endl;
}
