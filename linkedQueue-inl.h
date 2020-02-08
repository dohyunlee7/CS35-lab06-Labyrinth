/*
  Copyright (c) 2019
  Swarthmore College Computer Science Department, Swarthmore PA
  J. Brody, A. Danner, M. Gagne, L. Meeden, Z. Palmer, A. Soni, M. Wehar
  Distributed as course material for Fall 2019
  CPSC 035: Data Structures and Algorithms
*/

#include "linkedQueue.h"

using namespace std;

template <typename T> LinkedQueue<T>::LinkedQueue() {
}

template <typename T> void LinkedQueue<T>::enqueue(T element) {
    this->actualList.insertLast(element);
}

template <typename T> T LinkedQueue<T>::dequeue() {
    return this->actualList.removeFirst();
}

template <typename T> void LinkedQueue<T>::insert(T element) {
    enqueue(element);
}

template <typename T> T LinkedQueue<T>::remove() {
    return dequeue();
}

template <typename T> int LinkedQueue<T>::getSize() {
    return this->actualList.getSize();
}

template <typename T> bool LinkedQueue<T>::isEmpty() {
    return this->actualList.isEmpty();
}

template <typename T> T LinkedQueue<T>::peek() {
    return this->actualList.getFirst();
}
