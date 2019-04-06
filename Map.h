//
// Created by efg on 01.03.2019.
//

#ifndef RB_TREE_MAP_H
#define RB_TREE_MAP_H

#include <iostream>
#include <stdexcept>
#include <string>

#include "List.h"



#define maxrow 7           //constants're being used to print the tree
#define matrix_size 80
#define offset 40



template <typename T>
class RB_Tree{

private:

    class Node{
    public:
        bool color; //red = true; black = false
        T data;
        size_t key;   //key cannot be negative
        Node *left, *right;
        Node* dad;


        Node(T elem, size_t key){
            data = elem;
            color = true;  //new node is colored red by default
            this->key = key;
            left = nullptr;
            right = nullptr;
            dad = nullptr;
        }

    };
    


    Node* root;
    size_t size;

    int** SCREEN;                                //matrix to print the tree
    void __clrcsr();                             //fill the matrix with 0
    void __out_nodes(Node* v, int r, int c);     //add keys to the matrix
    RB_Tree<T>::Node* __add_node(T data, size_t key);
    void __r_rotation(Node* node);
    void __l_rotation(Node* node);
    void __balance(Node* node);
    void __delete_balance(Node* node);
    void delete_tree(Node* node);
    void inorder_walk_key(Node* node, List<size_t> *keys);       //add all the keys in the list of keys in descending order
    void inorder_walk_value(Node* node, List<T> *values);     //add al the values in the list of values (in key descending order)
    RB_Tree<T>::Node* __next_node(Node* node);
    RB_Tree<T>::Node* __find(size_t key);



public:

    RB_Tree();
    ~RB_Tree();
    void Insert(T data, size_t key);
    void OutTree();
    size_t GetSize();
    RB_Tree<T>::Node* GetRoot();
    List<size_t>* GetKeys();
    List<T>* GetValues();
    T Find(size_t key);
    void Remove(size_t key);
    void ClearMap();

};


template <typename T>
RB_Tree<T>::RB_Tree(){
    root = nullptr;
    size = 0;
    SCREEN = new int*[maxrow];
    for (int i = 0; i < maxrow; i++){
        SCREEN[i] = new int[matrix_size];
    }
}

template <typename T>
RB_Tree<T>::~RB_Tree(){
    ClearMap();
}

template <typename T>
void RB_Tree<T>::delete_tree(Node* node){
    if (node){
        delete_tree(node->right);
        delete_tree(node->left);
    }
    delete node;
}


template <typename T>
typename RB_Tree<T>::Node* RB_Tree<T>::GetRoot(){
    return root;
}

template <typename T>
void RB_Tree<T>::__clrcsr(){
    for (int i = 0; i < maxrow; ++i){
        for (int j = 0; j < matrix_size; j++){
            SCREEN[i][j] = 0;
        }
    }
}


template <typename T>
size_t RB_Tree<T>::GetSize(){
    return size;
}

template <typename T>
void RB_Tree<T>::__out_nodes(Node* v, int str, int m_size){
    if (str && m_size && (m_size < matrix_size)){
        if (v->color)
            SCREEN[str - 1][m_size - 1] = -(v->key);
        else
            SCREEN[str - 1][m_size - 1] = v->key;
    }
    if (str < maxrow){
        if (v->left)
            __out_nodes(v->left, str + 1, m_size - (offset >> str));
        if (v->right)
            __out_nodes(v->right, str + 1, m_size + (offset >> str));
    }
}

template <typename T>
void RB_Tree<T>::OutTree(){
    __clrcsr();
    if (!size){
        std::cout << "\nThe list is empty\n";
        return;
    }
    __out_nodes(root, 1, offset);

    for (int i = 0; i < maxrow; ++i){
        SCREEN[i][matrix_size - 1] = 0;
        std::cout << '\n';
        for (int j = 0; j < matrix_size; j++){
            if (SCREEN[i][j] == 0)
                std::cout << "--";
            else if (SCREEN[i][j] < 0)
                std::cout << -(SCREEN[i][j]) << "R";
            else
                std::cout << SCREEN[i][j];
        }
    }
    std::cout << '\n';
}



template <typename T>
typename RB_Tree<T>::Node* RB_Tree<T>::__add_node(T data, size_t key){
    Node *new_node, *node, *y;
    new_node = new Node(data, key);
    y = nullptr;
    node = root;
    while (node){
        y = node;
        if (new_node->key < node->key)
            node = node->left;
        else if (new_node->key == node->key)
            throw std::invalid_argument("This key is already being used");
        else
            node = node->right;
    }
    new_node->dad = y;
    if (!y)
        root = new_node;
    else if (new_node->key < y->key)
        y->left = new_node;
    else
        y->right = new_node;

    size++;
    return new_node;
}




template <typename T>
void RB_Tree<T>::Insert(T data, size_t key){

    Node *new_node;
    new_node = __add_node(data, key);
    __balance(new_node);

}


template <typename T>
void RB_Tree<T>::__r_rotation(Node* y){
    Node* x;
    x = y->left;
    y->left = x->right;

    if (x->right)
        x->right->dad = y;

    x->dad = y->dad;
    if (!y->dad)
        root = x;
    else if (y->key < y->dad->key)
        y->dad->left = x;
    else
        y->dad->right = x;
    x->right = y;
    y->dad = x;
}

template <typename T>
void RB_Tree<T>::__l_rotation(Node* x){
    Node* y;

    y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->dad = x;
    y->dad = x->dad;
    if (!x->dad)
        root = y;
    else if (x->key < x->dad->key)
        x->dad->left = y;
    else
        x->dad->right = y;
    y->left = x;
    x->dad = y;
}

template <typename T>
void RB_Tree<T>::__balance(Node* node){
    Node *dad, *uncle;


   while ((node != root) && (node->dad->color)){
       dad = node->dad;
       if (dad->key < dad->dad->key){
           uncle = dad->dad->right;
           if ((uncle) && (uncle->color)){
               dad->color = false;
               uncle->color = false;
               dad->dad->color = true;
               node = dad->dad;
           }
           else{
               if (node->key > node->dad->key){
                   node = node->dad;
                   __l_rotation(node);
               }
               node->dad->color = false;
               dad = node->dad;
               dad->dad->color = true;
               __r_rotation(node->dad->dad);
           }
       }
       else{
           uncle = dad->dad->left;
           if ((uncle) && (uncle->color)){
               dad->color = false;
               uncle->color = false;
               dad->dad->color = true;
               node = dad->dad;
           }
           else{
               if (node->key < node->dad->key){
                   node = node->dad;
                   __r_rotation(node);
               }
               node->dad->color = false;
               dad = node->dad;
               dad->dad->color = true;
               __l_rotation(node->dad->dad);
           }
       }
   }
   root->color = false;
}

template <typename T>
List<size_t>* RB_Tree<T>::GetKeys(){
    List<size_t> *keys = new List<size_t>;
    inorder_walk_key(root, keys);
    return keys;
}

template <typename T>
List<T>* RB_Tree<T>::GetValues(){
    List<T> *values = new List<T>;
    inorder_walk_value(root, values);
    return values;
}

template <typename T>
typename RB_Tree<T>::Node* RB_Tree<T>::__find(size_t key){

    if (!size)
        return nullptr;

    Node* node = root;
    while ((node) && (key != node->key)){
       if (key < node->key)
           node = node->left;
       else
           node = node->right;
    }
    return node;
}

template <typename T>
T RB_Tree<T>::Find(size_t key){
    Node *node = __find(key);
    if (node)
        return node->data;
    else
    {
        std::cout << "\nThe element with that key has not been found\n";
        return 0;
    }
}



template <typename T>
typename RB_Tree<T>::Node* RB_Tree<T>::__next_node(Node* node){  //Function returns the next element (search by key)
    if (node->right){
       node = node->right;
       while (node->left)
           node = node->left;
       return node;
    }
    Node* dad = node->dad;
    while ((dad) && (node->key > dad->key)){
        node = dad;
        dad = node->dad;
    }
    return dad;
}

template <typename T>
void RB_Tree<T>::__delete_balance(Node* node){
    Node *node2;
    if (!node) return;
    while ((node != root) && (!node->color)){
        if (node->key < node->dad->key){

            node2 = node->dad->right;
            if ((node2) && (node2->color)){
                node2->color = false;
                node->dad->color = true;
                __l_rotation(node->dad);
                node2 = node->dad->right;
            }
            if (((!node2->left->color) && (!node2->right->color)) || ((!node2->left) && (!node2->right))){
                node2->color = true;
                node = node->dad;
            }
            else {
                if ((!node2->right->color) || (!node2->right)) {
                    node2->left->color = false;
                    node2->color = true;
                    __r_rotation(node2);
                    node2 = node->dad->right;
                }
                node2->color = node->dad->color;
                node->dad->color = false;
                node2->right->color = false;
                __l_rotation(node->dad);
                node = root;
            }
        }
        else {

            node2 = node->dad->left;
            if (node2->color){
                node2->color = false;
                node->dad->color = true;
                __r_rotation(node->dad);
                node2 = node->dad->left;
            }
            if (((!node2->left->color) && (!node2->right->color)) || ((!node2->left) && (!node2->right))){
                node2->color = true;
                node = node->dad;
            }
            else {
                if ((!node2->left->color) || (!node2->left)) {
                    node2->right->color = false;
                    node2->color = true;
                    __l_rotation(node2);
                    node2 = node->dad->left;
                }
                node2->color = node->dad->color;
                node->dad->color = false;
                node2->left->color = false;
                __r_rotation(node->dad);
                node = root;
            }
        }
    }
    if (node) node->color = false;
}

template <typename T>
void RB_Tree<T>::Remove(size_t key){
    Node *node = __find(key);
    if (!node)
        throw std::invalid_argument("\nThere is no element with that key\n");


    Node *child, *d_node;
    if ((!node->left) || (!node->right))
        d_node = node;
    else                            //if the deleted element has two children
        d_node = __next_node(node);     //we need to find the next element (search by key)

    if (d_node->left)
        child = d_node->left;
    else
        child = d_node->right;

    if (child)
        child->dad = d_node->dad;



    if (!d_node->dad)
        root = child;
    else if (d_node->key < d_node->dad->key)  //if the deleted element is the left child
        d_node->dad->left = child;
    else
        d_node->dad->right = child;
    if (node != d_node){
        node->key = d_node->key;
        node->data = d_node->data;
    }
    size--;
    if (!d_node->color)
        __delete_balance(child);



    delete d_node;
}

template <typename T>
void RB_Tree<T>::inorder_walk_key(Node* node, List<size_t> *keys){
    if (node){
        inorder_walk_key(node->left, keys);
        keys->push_back(node->key);
        inorder_walk_key(node->right, keys);
    }
}

template <typename T>
void RB_Tree<T>::inorder_walk_value(Node* node, List<T> *values){
    if (node){
        inorder_walk_value(node->left, values);
        values->push_back(node->data);
        inorder_walk_value(node->right, values);
    }
}

template <typename T>
void RB_Tree<T>::ClearMap(){
    delete_tree(root);
    root = nullptr;
    size = 0;
    for (int i = 0; i < maxrow; i++)
        delete SCREEN[i];
    delete SCREEN;
}





#endif //RB_TREE_MAP_H
