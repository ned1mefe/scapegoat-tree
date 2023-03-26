#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod { preorder, inorder, postorder };

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T>& obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T& element);

    bool remove(const T& element);

    void removeAllNodes();

    const T& get(const T& element) const;

    void print(TraversalMethod tp = inorder) const;

    void printPretty() const;

    ScapegoatTree<T>& operator=(const ScapegoatTree<T>& rhs);

    void balance();

    const T& getCeiling(const T& element) const;

    const T& getFloor(const T& element) const;

    const T& getMin() const;

    const T& getMax() const;

    const T& getNext(const T& element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T>* node, TraversalMethod tp) const;
    void printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const;

    /* Recursive Tree Copier */
    Node<T>* copyNodes(Node<T>* node)
    {
        if (node == NULL) return NULL;

        Node<T>* newnode = new Node<T>;

        newnode->element = node->element;

        if (node->left != NULL) newnode->left = copyNodes(node->left);

        if (node->right != NULL) newnode->right = copyNodes(node->right);

        return newnode;
    }

    /* Recursive Tree Deleter */
    void deleteNodes(Node<T>* node)
    {
        if (node == NULL) return;

        if (node->left != NULL) deleteNodes(node->left);
        if (node->right != NULL) deleteNodes(node->right);

        delete node;

    }

    /* Recursive Height Helper */
    int heightHelper(Node<T>* node, int depth) const
    {
        if (node == NULL) return -1;

        if ((node->left == NULL) && (node->right == NULL)) return depth;

        int leftHeight = -1, rightHeight = -1;

        if (node->left != NULL) leftHeight = heightHelper(node->left, depth + 1);
        if (node->right != NULL) rightHeight = heightHelper(node->right, depth + 1);

        if (rightHeight > leftHeight) return rightHeight;
        else return leftHeight;

        // Bu fonksiyona tekrar bak
    }

    /* Recursive Size Helper */
    int sizeHelper(Node<T>* node) const
    {
        if (node == NULL) return 0;

        if ((node->left == NULL) && (node->right == NULL)) return 1;

        return (sizeHelper(node->left) + 1 + sizeHelper(node->right));

        // Buna da tekrar dön bak
    }

    /* Recursive Contains Checker For Nodes */
    bool contains(Node<T>* treeroot, Node<T>* node) const
    {

        if (treeroot == NULL) return false;
        if (node == NULL) return false;

        if (treeroot == node) return true;

        if (node->element < treeroot->element) return contains(treeroot->left, node);
        else return contains(treeroot->right, node);

    }

    /* Overwritten Contains Checker For Elements */
    bool contains(Node<T>* treeroot, T lmnt) const
    {

        if (treeroot == NULL) return false;

        if (treeroot->element == lmnt) return true;

        if (lmnt < treeroot->element) return contains(treeroot->left, lmnt);
        else return contains(treeroot->right, lmnt);

    }

    /* Recursive Parent Finder */
    Node<T>* parentFinder(Node<T>* potParent, Node<T>* child) //potParent should be root
    {

        if (potParent == NULL) return NULL;
        if (child == NULL) return NULL;

        if (potParent == child) return NULL; // anneyle çocuğu aynı yaşta olamaz

        if ((potParent->left == child) || (potParent->right == child)) return potParent;


        if (contains(potParent->left, child)) return parentFinder(potParent->left, child);
        if (contains(potParent->right, child)) return parentFinder(potParent->right, child);

        return NULL;

    }

    /* Scapegoat Finder */
    Node<T>* scapeGoat(Node<T>* potGoatsChild)
    {

        Node<T>* potGoat = parentFinder(root, potGoatsChild);

        if (sizeHelper(potGoatsChild) * 3 > sizeHelper(potGoat) * 2) return potGoat;

        return scapeGoat(potGoat);

    }

    /* Balance Helper */
    void balance(Node<T>* subroot)
    {

        int size = sizeHelper(subroot);
        if (size < 2) return;

        Node<T>* parent = parentFinder(root, subroot);
        Node<T>* newchild;


        T* array = new T[size];

        int a = 0;

        arrayFiller(subroot, array, a);

        newchild = constructor(array, 0, size - 1);

        if (parent == NULL) // When the scapegoat is the root
        {
            root = newchild;
            deleteNodes(subroot);
            delete[] array;
            return;
        }

        if (newchild->element > parent->element) parent->right = newchild;
        if (newchild->element < parent->element) parent->left = newchild;

        deleteNodes(subroot);
        delete[] array;

    }

    /* Balanced Tree Constructor From an Array */
    Node<T>* constructor(T arr[], int minInd, int maxInd) // [0, 1, 2, 3, 4, 5]
    {

        if (minInd > maxInd) return NULL;

        int midInd = (maxInd + minInd) / 2;

        Node<T>* newNode = new Node<T>;

        newNode->element = arr[midInd];

        newNode->left = constructor(arr, minInd, midInd - 1);
        newNode->right = constructor(arr, midInd + 1, maxInd);
        return newNode;
    }

    /* Array Filler From a Subtree */
    void arrayFiller(Node<T>* node, T arr[], int& index)
    {
        if (node == NULL) return;

        arrayFiller(node->left, arr, index);

        arr[index] = node->element;
        index++;

        arrayFiller(node->right, arr, index);

    }

    /* Recursive Insert Helper */
    void simpleInsert(Node<T>* subroot, Node<T>* newNode) //subroot is never NULL here
    {

        if (subroot->element > newNode->element)
        {
            if (subroot->left == NULL)
            {
                subroot->left = newNode;
                return;
            }
            else simpleInsert(subroot->left, newNode);
        }

        if (subroot->element < newNode->element)
        {
            if (subroot->right == NULL)
            {
                subroot->right = newNode;
                return;
            }
            else simpleInsert(subroot->right, newNode);
        }

    }

    /* Finder of biggest integer lesser than the log3/2(upperBound) */
    int logFloor(int upperBound)
    {

        double a = 1;
        int result = -1;

        while (a <= upperBound)
        {
            result++;
            a = a * 3 / 2;
        }

        return result;

    }

    /* Same as get(T &element) func. but returns the Node instead */
    Node<T>* getNode(Node<T>* treeroot, T lmnt) const
    {

        if (treeroot == NULL) return NULL;

        if (treeroot->element == lmnt) return treeroot;

        if (lmnt < treeroot->element) return getNode(treeroot->left, lmnt);
        else return getNode(treeroot->right, lmnt);

    } // Works just like contains()

    /* Recursive Remove Helper */
    void simpleRemove(Node<T>*& subroot, T lmnt)
    {
        if (subroot == NULL) return;

        if (subroot->element > lmnt) simpleRemove(subroot->left, lmnt);
        if (subroot->element < lmnt) simpleRemove(subroot->right, lmnt);

        if (subroot->element == lmnt)
        {
            if ((subroot->left != NULL) && (subroot->right != NULL)) // has 2 children
            {
                subroot->element = getMax(subroot->left);
                simpleRemove(subroot->left, subroot->element);
            }

            else // has 1 or 0 child
            {
                Node<T>* deletedNode = subroot;
                if (subroot->left != NULL) subroot = subroot->left;
                else subroot = subroot->right;
                delete deletedNode;

            } // if has no child, sub->right will be NULL so sub will be NULL
        }

    }

    /* getMax Overwritten Helper */
    const T& getMax(Node<T>* subroot) const
    {
        if (subroot == NULL) throw NoSuchItemException();
        Node<T>* temp = subroot;

        while (temp->right != NULL)
        {
            temp = temp->right;
        }

        return temp->element;
    }

    /* getMin Overwritten Helper */
    const T& getMin(Node<T>* subroot) const
    {
        if (subroot == NULL) throw NoSuchItemException();
        Node<T>* temp = subroot;

        while (temp->left != NULL)
        {
            temp = temp->left;
        }

        return temp->element;
    }

    /* Recursive getCeiling() Helper */
    Node<T>* getCeilingHelper(Node<T>* subroot, T lmnt) const
    {
        if (subroot == NULL) return NULL;

        if (subroot->element == lmnt) return subroot;

        if (subroot->element > lmnt) 
        {
            Node<T>* potCeiling = getCeilingHelper(subroot->left,lmnt);
            
            if (potCeiling == NULL) return subroot;
            
            return potCeiling; 
        }

        if (subroot->element < lmnt) 
        {
            Node<T>* potCeiling = getCeilingHelper(subroot->right,lmnt);
            
            return potCeiling;
        }

        return NULL; // which never happens
    }

    /* Recursive getFloor() Helper */
    Node<T>* getFloorHelper(Node<T>* subroot, T lmnt) const
    {
        if (subroot == NULL) return NULL;
     
        if (subroot->element == lmnt) return subroot;

        if (subroot->element < lmnt) 
        {
            Node<T>* potFloor = getFloorHelper(subroot->right,lmnt);
            
            if (potFloor == NULL) return subroot;
            
            return potFloor; 
        }

        if (subroot->element > lmnt) 
        {
            Node<T>* potFloor = getFloorHelper(subroot->left,lmnt);
            
            return potFloor;
        }

        return NULL; // which never happens
    }

    /* Recursive getNext() Helper */
    Node<T>* getNextHelper(Node<T>* subroot, T lmnt) const
    {
        if (subroot == NULL) return NULL;

        if (subroot->element == lmnt) return getNextHelper(subroot->right, lmnt);

        if (subroot->element > lmnt) 
        {
            Node<T>* potNext = getNextHelper(subroot->left,lmnt);
            
            if (potNext == NULL) return subroot;
            
            return potNext; 
        }

        if (subroot->element < lmnt) 
        {
            Node<T>* potNext = getNextHelper(subroot->right,lmnt);
            
            return potNext;
        }

        return NULL; // which never happens
    }

private: // DO NOT CHANGE THIS PART.
    Node<T>* root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {

    root = NULL;
    upperBound = 0;

}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T>& obj) {

    root = copyNodes(obj.root);
    upperBound = obj.upperBound;

}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {

    deleteNodes(root);
    upperBound = 0;

}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {

    return (root == NULL);

}

template<class T>
int ScapegoatTree<T>::getHeight() const {

    return heightHelper(root, 0);

}

template<class T>
int ScapegoatTree<T>::getSize() const {

    return sizeHelper(root);

}

template<class T>
bool ScapegoatTree<T>::insert(const T& element) {

    if (contains(root, element)) return false; // checks if it contains

    // this part inserts the new node
    Node<T>* newNode = new Node<T>;
    newNode->element = element;

    if (root == NULL) // for an empty tree
    {
        root = newNode;
        upperBound++;
        return true;
    }

    simpleInsert(root, newNode);
    upperBound++;
    // insertion ends here

    if (logFloor(upperBound) < getHeight())
    {
        // When the Scapegoat is root, balance func. handles it

        Node<T>* theGoat = scapeGoat(newNode);

        balance(theGoat);

    }

    return true;

}

template<class T>
bool ScapegoatTree<T>::remove(const T& element) {

    if (!contains(root, element)) return false;

    simpleRemove(root, element);

    if (getSize() < (upperBound / 2.0))
    {
        balance();
        upperBound = getSize();
    }
    return true;

}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {

    upperBound = 0;
    deleteNodes(root);
    root = NULL;

}

template<class T>
const T& ScapegoatTree<T>::get(const T& element) const {

    if (!contains(root, element)) throw NoSuchItemException();

    else return (getNode(root,element)->element);

}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        {
            if (isEmpty()) {
                // the tree is empty.
                std::cout << "BST_preorder{}" << std::endl;
                return;
            }
            std::cout << "BST_preorder{" << std::endl;
            print(root, tp);
            std::cout << std::endl << "}" << std::endl;

        }

    }
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == postorder) {

        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T>* node, TraversalMethod tp) const {

    if (tp == preorder) {

        if (node == NULL) return;

        std::cout << "\t" << node->element;

        if (node->left) std::cout << "," << std::endl;
        print(node->left, preorder);

        if (node->right) std::cout << "," << std::endl;
        print(node->right, preorder);


    }
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == postorder) {

        if (node == NULL) return;

        print(node->left, postorder);
        if (node->left) std::cout << "," << std::endl;

        print(node->right, postorder);
        if (node->right) std::cout << "," << std::endl;

        std::cout << "\t" << node->element;

    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T>* node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T>& ScapegoatTree<T>::operator=(const ScapegoatTree<T>& rhs) {

    if (this == &rhs) return *this;

    deleteNodes(root);

    root = copyNodes(rhs.root);
    upperBound = rhs.upperBound;
    return *this;

}

template<class T>
void ScapegoatTree<T>::balance() {

    balance(root);

}

template<class T>
const T& ScapegoatTree<T>::getCeiling(const T& element) const {
    
    Node<T>* ceilingNode = getCeilingHelper(root,element);
    
    if (ceilingNode == NULL) throw NoSuchItemException();

    else return ceilingNode->element;

}

template<class T>
const T& ScapegoatTree<T>::getFloor(const T& element) const {
    
    Node<T>* floorNode = getFloorHelper(root,element);

    if (floorNode == NULL) throw NoSuchItemException();

    else return floorNode->element;

}

template<class T>
const T& ScapegoatTree<T>::getMin() const {

    return getMin(root);

}

template<class T>
const T& ScapegoatTree<T>::getMax() const {

    return getMax(root);

}

template<class T>
const T& ScapegoatTree<T>::getNext(const T& element) const {
        
    Node<T>* nextNode = getNextHelper(root,element);
    
    if (nextNode == NULL) throw NoSuchItemException();

    else return nextNode->element;
}