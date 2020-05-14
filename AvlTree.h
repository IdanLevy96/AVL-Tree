#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "AvlNode.h"

/**
 * This is a generic template for an AVL Tree - the nodes of a tree can have unique data stored in them.
 * For example, a node may hold another AVL Tree inside it
 * in this implementation, the tree is in charge of it's data and it's memory management.
*/
template <class T>
class AvlTree
{
    AvlNode<T>* root;
    AvlNode<T>* min_node; // lowest by key data in tree

public:
    AvlTree();
    ~AvlTree();
    void insert(int key, T* data = nullptr);
    void remove(int key);
    bool isEmpty();
    AvlNode<T>* search(int key);
    AvlNode<T>* getMinNode();
    int mapSucc(int* keys, int size);

};

/**
 * Initialize an empty AVL tree
 */
template <class T>
AvlTree<T>::AvlTree(): root(nullptr), min_node(nullptr) {};


/**
 * delete tree and release all its data
 */
template <class T>
AvlTree<T>::~AvlTree() {
    if (root != nullptr) {
        root->clearAll();
        delete root;
        root=nullptr;
    }
}

/**
 * insert a single data represent by key to the tree
 * if key already shows in tree - nothing will be done
 * @param key the key of the data (node)
 * @param data
 */
template <class T>
void AvlTree<T>::insert(int key, T* data){
    if (root == nullptr) { // in case the tree is empty
        root = new AvlNode<T>(key,data);
        min_node = root;
    }
    else {
        root = root->insert(key, data);

        if (!min_node || key < min_node->getKey()) { // in case we insert new min by key data
            this->min_node = root->getMinNode();
        }
    }
}

/**
 * Remove the data (node) with the key value from the tree
 * @param key
 */
template<class T>
void AvlTree<T>::remove(int key){
    bool flag = min_node != nullptr && min_node->getKey() == key;
    if (root != nullptr) {
        root = root->remove(key);
        if (flag) {
            if (root != nullptr) {
                min_node = root->getMinNode();
            }
            else {
                min_node = nullptr;
            }
        }
    }
}

/**
 * @param key
 * @return Returns a node given its key
 * return nullptr if not found
 */
template<class T>
AvlNode<T>* AvlTree<T>::search(int key){
    if (root == nullptr) {
        return nullptr;
    }

    return root->search(key);
}

/**
 * @return true if tree has no data, false otherwise
 */
template<class T>
bool AvlTree<T>::isEmpty() {
    return (root == nullptr);
}

/**
 * @return min by key node in the tree
 */
template<class T>
AvlNode<T>* AvlTree<T>::getMinNode() {
    return min_node;
}

/**
 * scan the tree by "successor in-order" method
 * @tparam T
 * @param keys - arr. assign the  #size lowest keys in the tree into this arr
 * @param size - num of data to copy into keys[]
 * @return the number of keys that were assign to keys[]
 */
template<class T>
int AvlTree<T>::mapSucc(int* keys, int size) {
    if (size <= 0 || keys == nullptr || min_node == nullptr) {
        return 0;
    }

    return min_node->mapSucc(keys, size);
}

#endif //AVL_TREE_H
