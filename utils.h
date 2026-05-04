#ifndef UTILS_H
#define UTILS_H

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"


template <typename T>
void printSequence(const DynamicArray<T>& arr);

template <typename T>
void printSequence(const LinkedList<T>& lst);

template <typename T>
void printSequence(Sequence<T>* seq);


#endif