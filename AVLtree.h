#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
class AVLnode
{
public:

    T data; // will be the data stored in each node
    AVLnode *left; // pointer to the left child
    AvLnode *right; // pointer to the right child
    int height; // will be used to calculate balance factor
    
    AVLnode(T d)
    {
        data = d; // argument is assigned to data

        left = nullptr; // left child is set to nullptr
        right = nullptr; // right child is set to nullptr

        height = 1; // height is set to one
    }
}; // end class AVLnode

template<typename T>
class AVLtree
{
public:
    AVLnode<T> *root; // pointer to the root node
    
    AVLtree(); // constructor for AVLtree

    AVLnode<T>* insert(AVLnode<T> *node, T data); // method to insert a new node into the tree and balance the tree

    int getHeight(AVLnode<T> *node); // method to get the height of a node

    int getMax(const int a, const int b); // method to get the greater of the left or right node, used in calculating the balance factor

    int getBalance(AVLnode<T> *node); // method to get the balance factor of a node

    // rotational methods
    AVLnode<T>* rightRotate(AVLnode<T> *y); // right rotate method

    AVLnode<T>* leftRotate(AVLnode<T> *x); // left rotate method

    AVLnode<T>* leftRightRotate(AVLnode<T> *node); // method for left right rotation

    AVLnode<T> *rightLeftRotate(AVLnode<T> *node); // method for right left rotation

    

}; // end class AVLtree

template <typename T>
AVLtree<T>::AVLtree()
{
    root = nullptr; // starts with root having no children hence the nullptr use
}

template <typename T>
AVLnode<T>* AVLtree<T>::insert(AVLnode<T> *node, T data)
{
    // base case to break the recursion
    if(node == nullptr)
        return new AVLNode<T>(data); // create a new node with data ARG as the data stored in the node

    // insert to the left of node IE the data to be inserted is less than the node
    if(data < node->data)
        node->left = insert(node->left, data);
    else if(data > node->data) // the data to be inserted is greater than node so it goes onto the right
        node->right = insert(node->right, data); 
    else
        return node; // duplicate data which is not allowed

    // update the height of the current node
    node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node); // get the balance factor of the node

    // left left case
    if(balance > 1 && data < node->left->data)
        return rightRotate(node);
    
    // right right case
    if(balance < -1 && data > node->right->data)
        return leftRotate(node);

    // left right case
    if(balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // right left case
    if(balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
    
}

template <typename T>
int AVLtree<T>::getMax(const int a, const int b)
{
    return (a > b) ? a: b;
}

