/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedStack.h"

using namespace std;

template <typename T> LinkedStack<T>::LinkedStack() {
}

template <typename T> void LinkedStack<T>::push(T element) {
    this->actualList.insertLast(element);
}

template <typename T> T LinkedStack<T>::pop() {
    return this->actualList.removeLast();
}

template <typename T> void LinkedStack<T>::insert(T element) {
    push(element);
}

template <typename T> T LinkedStack<T>::remove() {
    return pop();
}

template <typename T> int LinkedStack<T>::getSize() {
    return this->actualList.getSize();
}

template <typename T> bool LinkedStack<T>::isEmpty() {
    return this->actualList.isEmpty();
}

template <typename T> T LinkedStack<T>::peek() {
    return this->actualList.getLast();
}
