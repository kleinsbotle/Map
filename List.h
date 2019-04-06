//
// Created by efg on 27.02.2019.
//

#ifndef LAB1_2_LIST_H
#define LAB1_2_LIST_H

#pragma once

#include <iostream>
#include <stdexcept>


template <typename Data>
class List;

template <typename Data>
std::ostream& operator << (std::ostream &out, List<Data> &list){
    if (list.is_empty()){
        out << "\nThe list is empty\n";
    }
    else{
        typename List<Data>::Node* node;
        node = list.get_head();
        out << '\n';
        for (int i = 0; i < list.get_size(); i++){
            out << node->data << ' ';
            node = node->next;
        }
    }
    return out;
}


template <typename Data>
std::ostream& operator << (std::ostream &out, List<Data> *list){
    if (list->is_empty()){
        out << "\nThe list is empty\n";
    }
    else{
        typename List<Data>::Node* node;
        node = list->get_head();
        out << '\n';
        for (int i = 0; i < list->get_size(); i++){
            out << node->data << ' ';
            node = node->next;
        }
    }
    return out;
}


template <typename Data>
class List{

private:

    class Node{
    public:
        Data data;
        Node* prev;
        Node* next;
        Node (){
            next = nullptr;
            prev = nullptr;
        }
        Node (Data elem){
            data = elem;
            next = nullptr;
            prev = nullptr;
        }
        ~Node() { next = nullptr; prev = nullptr;};
    };


    Node *head, *tail;
    size_t size;



    void __empty_list();  //makes list empty


public:
    List ();
    ~List();
    void push_back(Data data);  //pushes element in the end of the list
    void push_front(Data data);  //pushes element in the beginning of the list
    void pop_back();  //deletes last element
    void pop_front(); //deletes first element
    void insert(size_t index, Data data);  //add element before element with that index
    Data at(size_t);
    void remove(size_t);
    size_t get_size();
    List<Data>::Node* get_head();
    void clear();
    bool is_empty();
    void set(size_t index, Data data);  //add element instead of element with that index
    int find(Data data);   //return index of the element or -1 if the element's not found
    friend std::ostream& operator <<  <Data>(std::ostream &out, List &list);
    friend std::ostream& operator <<  <Data>(std::ostream &out, List *list);

};

template <typename Data>
List<Data>::List(){
    head  = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename Data>
List<Data>::~List(){
    clear();
}



template <typename Data>
void List<Data>::push_front(Data data){
    Node *first, *new_node;
    new_node = new Node(data);
    size++;
    if (head){
        first = head;
        first->prev = new_node;
        head = new_node;
        new_node->next = first;
    }
    else{
        head = tail = new_node;
    }
}

template <typename Data>
void List<Data>::push_back(Data data){
    Node *last, *new_node;
    new_node = new Node(data);
    size++;
    if (tail){
        last = tail;
        last->next = new_node;
        tail = new_node;
        tail->prev = last;
    }
    else{
        tail = new_node;
        head = tail;
    }
}


template <typename Data>
void List<Data>::pop_front(){

    if (is_empty())
        throw std::length_error("The list is empty");

    if (size == 1){  //after deleting the list will be empty
        delete head;
        __empty_list();
        return;
    }
    else{
        Node* node = head;
        head = node->next;
        head->prev = nullptr;
        delete node;
        size--;
    }


}

template <typename Data>
void List<Data>::pop_back(){

    if (is_empty())
        throw std::length_error("The list is empty");

    if (size == 1){  //after deleting the list will be empty
        delete tail;
        __empty_list();
        return;
    }
    else{
        Node* node = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete node;
        size--;
    }


}



template <typename Data>
void List<Data>::insert(size_t index, Data data){
    Node *node, *new_node, *prev_node;
    if (is_empty())
        throw std::length_error("The list is empty");
    if (index > size)
        throw std::out_of_range("Incorrect index");

    if (index == 0){
        push_front(data);
    }
    else{
        new_node = new Node(data);
        size++;
        node = head;
        for (int i = 0;  i < index; i++){
            node = node->next;
        }
        prev_node = node->prev;
        prev_node->next = new_node;
        new_node->prev = prev_node;
        new_node->next = node;
        node->prev = new_node;
    }
}


template <typename Data>
Data List<Data>::at(size_t index){
    if (is_empty())
        throw std::length_error("The list is empty");
    if (index > size)
        throw std::out_of_range("Incorrect index");

    Node* node = head;
    for (int i = 0; i < index; i++){
        node = node->next;
    }
    return node->data;
}

template <typename Data>
void List<Data>::remove(size_t index){
    if (is_empty())
        throw std::length_error("The list is empty");
    if (index > size)
        throw std::out_of_range("Incorrect index");

    if (index == 0){
        pop_front();
    }
    else if (index == size - 1){
        pop_back();
    }
    else{
        Node *node, *prev, *next;
        node = head;
        size--;
        for (int i = 0; i < index; i++)
            node = node->next;
        prev = node->prev;
        next = node->next;
        prev->next = next;
        next->prev = prev;
        delete node;
    }
}

template <typename Data>
size_t List<Data>::get_size(){
    return size;
}


template <typename Data>
void List<Data>::__empty_list(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename Data>
void List<Data>::clear(){
    if (size == 0){
        return;
    }
    else if (size == 1){
        delete head;
        __empty_list();
    }
    else{
        while (head){
            pop_front();
        }
        delete head;
        delete tail;
        __empty_list();
    }
}

template <typename Data>
bool List<Data>::is_empty(){
    if (!size) return true;
    else return false;
}


template <typename Data>
void List<Data>::set(size_t index, Data data){
    if (is_empty())
        throw std::length_error("The list is empty");
    if (index > size)
        throw std::out_of_range("Incorrect index");

    Node *node, *new_node, *next, *prev;
    new_node = new Node(data);
    if (index == 0){
        node = head;
        next = node->next;
        head = new_node;
        new_node->next = next;
        next->prev = new_node;
    }
    else if (index == size - 1){
        node = tail;
        prev = node->prev;
        tail = new_node;
        new_node->prev = prev;
        prev->next = new_node;
    }
    else{
        node = head;
        for (int i = 0; i < index; i++){
            node = node->next;
        }
        prev = node->prev;
        next = node->next;
        new_node->prev = prev;
        new_node->next = next;
        prev->next = new_node;
        next->prev = new_node;
    }
    delete node;
}

template <typename Data>
typename List<Data>::Node* List<Data>::get_head(){
    return head;
}

template <typename Data>
int List<Data>::find(Data data){
    Node* node = head;
    int index = 0;
    while (node){
        if (node->data == data)
            return index;
        node = node->next;
        index++;
    }
    return -1;
}

#endif //LAB1_2_LIST_H

