#ifndef AVL_NODE_H
#define AVL_NODE_H

/**
 * This is a generic template for an AVL node, the nodes of AVL Tree
 * the nodes of a tree can have unique data stored in them *
 */

template <class T>
class AvlNode
{
    T *data;
    int key;
    AvlNode<T> *left, *right, *parent;
    int height;

    void updateHeight();
    AvlNode<T>* r_rotation();
    AvlNode<T>* l_rotation();
    AvlNode<T>* lr_rotation();
    AvlNode<T>* rl_rotation();
    AvlNode<T>* balanceTree();
    int getBalanceFactor();
    AvlNode<T> *removeAUX();
    void adjustParent(AvlNode<T>* takePlace);

public:
    AvlNode(int key, T *data_in = nullptr, AvlNode* parent = nullptr);
    ~AvlNode();
    void clearAll();
    AvlNode<T>* insert(int keyAdd, T* dataAdd = nullptr);
    AvlNode<T>* remove(int keyRemove);
    AvlNode<T>* search(int keyFind);
    AvlNode<T>* getMinNode();
    AvlNode<T>* getMaxNode();
    T* getData();
    int getKey();
    AvlNode<T>* getLeftSon();
    AvlNode<T>* getRightSon();
    AvlNode<T>* getParent();
    int mapInOrder(int* keys, int size);
    int mapSucc(int* keys, int size);

};


/**
 * creates node
 * @tparam T
 * @param key
 * @param data_in
 * @param parent
 */
template<class T>
AvlNode<T>::AvlNode(int key, T *data_in, AvlNode* parent):
data(data_in), key(key), left(nullptr), right(nullptr), parent(parent), height(1) {}

/**
 * delete node and it release its data
 * does not delete its parent or sons!
 * @tparam T
 */
template<class T>
AvlNode<T>::~AvlNode(){
    if(data != nullptr){
        delete data;
        data = nullptr;
    }
}

/**
 * delete the node and all its sons, grandsons and so on
 * use when we want to delete not just the current node (this) but all the data that connects to it
 * @param T
 */
template<class T>
void AvlNode<T>::clearAll() {
    if (left != nullptr) {
        left->clearAll();
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        right->clearAll();
        delete right;
        right = nullptr;
    }
}

/**
 * @tparam T
 * @return the custom data of the node
 */
template<class T>
T* AvlNode<T>::getData(){
    return data;
}

/**
 * @tparam T
 * @return node's key
 */
template<class T>
int AvlNode<T>::getKey() {
    return key;
}

/**
 * @tparam T
 * @return ptr to left son
 */
template<class T>
AvlNode<T>* AvlNode<T>::getLeftSon() {
    return left;
}

/**
 * @tparam T
 * @return ptr to right son
 */
template<class T>
AvlNode<T>* AvlNode<T>::getRightSon() {
    return right;
}

/**
 * @tparam T
 * @return ptr to node's parent
 */
template<class T>
AvlNode<T>* AvlNode<T>::getParent() {
    return parent;
}

/**
 * @tparam T
 * @param keyFind
 * @return a node given its key (if not found return nullptr)
 */
template<class T>
AvlNode<T>* AvlNode<T>::search(int keyFind){
    if(keyFind == key) {
        return this;
    }
    else if(keyFind < key){
        if (left != nullptr) {
            return left->search(keyFind);
        }
        else {
            return nullptr;
        }
    }
    else {
        if (right != nullptr) {
            return right->search(keyFind);
        }
        else {
            return nullptr;
        }
    }
}


/**
 *
 * @tparam T
 * @param keyAdd
 * @param dataAdd
 * @return add a new node in this connected nodes data structure, with param keyAdd and dataAdd
 * the insert is by AVL-ordering-by-key
 * if during insert founds that keyAdd already in struct, does not do anything
 */
template <class T>
AvlNode<T>* AvlNode<T>::insert(int keyAdd, T* dataAdd) {

    if (keyAdd > key) {
        if (right == nullptr) {
            right = new AvlNode(keyAdd, dataAdd, this);
        }
        else {
            right->insert(keyAdd, dataAdd);
        }
    }
    else if (keyAdd < key){
        if (left == nullptr) {
            left = new AvlNode(keyAdd, dataAdd, this);
        }
        else {
            left->insert(keyAdd, dataAdd);
        }
    }
    else {
        return nullptr; // indicate already in tree. no actions or changing in tree
    }
    return balanceTree();
}

/**
 * updeate node's height
 * @tparam T
 */
template<class T>
void AvlNode<T>::updateHeight() {
    int tmpRight = 0, tmpLeft = 0;
    if (left != nullptr) {
        tmpLeft = left->height;
    }
    if (right != nullptr) {
        tmpRight = right->height;
    }

    if (tmpLeft > tmpRight) {
        height = tmpLeft + 1;
    }
    else {
        height = tmpRight + 1;
    }
}

/**
 * single right rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::r_rotation() {
    AvlNode<T>* tmpRight = right;
    right = right->left;
    if (right != nullptr) {
        right->parent = this;
    }
    tmpRight->left = this;
    tmpRight->parent = this->parent;
    if (this->parent != nullptr) {
        if (this->parent->left != nullptr && this->parent->left->key == this->key) {
            this->parent->left = tmpRight;
        }
        else {
            this->parent->right = tmpRight;
        }
    }
    this->parent = tmpRight;
    this->updateHeight();
    tmpRight->updateHeight();
    return tmpRight;
}

/**
 * single left rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::l_rotation() {
    AvlNode<T>* tmpLeft = left;
    left = left->right;
    if (left != nullptr) {
        left->parent = this;
    }
    tmpLeft->right = this;
    tmpLeft->parent = this->parent;
    if (this->parent != nullptr) {
        if (this->parent->left != nullptr && this->parent->left->key == this->key) {
            this->parent->left = tmpLeft;
        }
        else {
            this->parent->right = tmpLeft;
        }
    }
    this->parent=tmpLeft;
    this->updateHeight();
    tmpLeft->updateHeight();
    return tmpLeft;
}

/**
 * one right rotation and than left rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::lr_rotation() {
    left->r_rotation();
    return this->l_rotation();
}

/**
 * one left rotation and than right rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::rl_rotation() {
    right->l_rotation();
    return this->r_rotation();
}

/**
 *
 * @tparam T
 * @return AVL balance factor (left son height - right son height)
 */
template <class T>
int AvlNode<T>::getBalanceFactor() {
    updateHeight();
    int tmpRight = 0, tmpLeft = 0; // if son in nullptr its height is 0
    if (right != nullptr) {
        tmpRight = right->height;
    }
    if (left != nullptr) {
        tmpLeft = left->height;
    }
    return tmpLeft - tmpRight;
}

/**
 * balances nodes (as AVL tree)
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::balanceTree(){
    int bf = getBalanceFactor(); // bf = Balance Factor

    if(bf > 1){
        int sub_bf = left->getBalanceFactor();
        if(sub_bf >= 0 ) {
            return l_rotation();
        }
        else {
            return lr_rotation();
        }
    }
    else if(bf < -1){
        int sub_bf = right->getBalanceFactor();
        if(sub_bf > 0){
            return rl_rotation();
        }
        else{
            return r_rotation();
        }
    }
    return this;
}

/**
 * find if keyRemove is one of nodes key and remove it from struct
 * @tparam T
 * @param keyRemove
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::remove(int keyRemove){
    if(keyRemove < key) { //if key is lower than root, search left subtree
        if (left != nullptr) {
            left->remove(keyRemove);
        }
        else {
            return this;
        }
    }
    else if(keyRemove > key) { //if key is bigger than root, search right subtree
        if (right != nullptr) {
            right->remove(keyRemove);
        }
        else {
            return this;
        }
    }
    else{ //key found, current node holds key
        return this->removeAUX(); // calls a function that actually delete current node
    }
    return balanceTree();
}

/**
 * delete this (Current) from node-struct
 * @tparam T
 * @param keyRemove
 * @return update root of sub-node-struct
 */
template<class T>
AvlNode<T> * AvlNode<T>::removeAUX() {
    if(left != nullptr) { //Find successor of node
        AvlNode<T> *successor = left->getMaxNode();
        if (left->right != nullptr) {
            successor->parent->right = successor->left;
            if (successor->left != nullptr) {
                successor->left->parent = successor->parent;
            }
            successor->left = this->left;
            this->left->parent = successor;
        }
        this->adjustParent(successor);
        successor->right = this->right;
        if (this->right != nullptr) {
            this->right->parent = successor;
        }
        delete this;
        return successor->balanceTree();
    }
    else if (right != nullptr) {
        AvlNode<T> *successor = this->right;
        this->adjustParent(successor);
        delete this;
        return successor->balanceTree();
    }
    else { // no sons to delete node
        this->adjustParent(nullptr);
        delete this;
        return nullptr;
    }
}

/**
 * adjust parents between nodes that been delete and its successor
 * @tparam T
 * @param takePlace - successor
 */
template<class T>
void AvlNode<T>::adjustParent(AvlNode<T> *takePlace) {
    if (takePlace != nullptr) {
        takePlace->parent = this->parent;
    }
    if (this->parent != nullptr) {
        if (this->parent->left != nullptr && this->parent->left->key == this->key) {
            this->parent->left = takePlace;
        }
        else {
            this->parent->right = takePlace;
        }
    }
}

/**
 *
 * @tparam T
 * @return min by key node in struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::getMinNode() {
    if (left != nullptr) {
        return left->getMinNode();
    }
    return this;
}

/**
 *
 * @tparam T
 * @return max by key node in struct
 */
template<class T>
AvlNode<T>* AvlNode<T>::getMaxNode() {
    if (right != nullptr) {
        return right->getMaxNode();
    }
    return this;
}

/**
 * scan the node-struct by "in-order" method
 * (from current down. does not go up to parent)
 * @tparam T
 * @param keys - arr. assign the  #size lowest keys in the tree into this arr
 * @param size - num of data to copy into keys[]
 * @return the number of keys that were assign to keys[]
 */
template<class T>
int AvlNode<T>::mapInOrder(int* keys, int size) {
    if (size <= 0 || keys == nullptr) {
        return 0;
    }

    int index = 0;
    if (left != nullptr) {
        index += left->mapInOrder(keys, size);
        if (index >= size) {
            return index;
        }
    }

    keys[index++] = key;

    if (index < size && right != nullptr) {
        index += right->mapInOrder(keys+index, size-index);
    }
    return index;
}

/**
 * scan the node-struct by "successor in-order" method
 * (from current up. does not go to current sons)
 * @tparam T
 * @param keys - arr. assign the  #size lowest keys in the tree into this arr
 * @param size - num of data to copy into keys[]
 * @return the number of keys that were assign to keys[]
 */
template<class T>
int AvlNode<T>::mapSucc(int* keys, int size) {
    if (size <= 0 || keys == nullptr) {
        return 0;
    }
    int index = 0;
    AvlNode<T> *current = this;
    while (current  && index < size) {
        keys[index++] = current->key;
        if (current->right) {
            index += current->right->mapInOrder(keys+index, size-index);
        }
        current = current->parent;
    }
    return index;
}

#endif //AVL_NODE_H
