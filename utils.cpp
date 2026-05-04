#include "utils.h"

#include <iostream>


template <typename T>
void printSequence(const DynamicArray<T> &arr) {
    IEnumerator<T> *en = arr.getEnumerator();
    std::cout << "[";
    bool first = true;
    while (en->moveNext()) {
        if (!first) std::cout << ", ";
        std::cout << en->current();
        first = false;
    }
    std::cout << "]" << std::endl;
    delete en;
}

template <typename T>
void printSequence(const LinkedList<T> &lst) {
    IEnumerator<T> *en = lst.getEnumerator();
    std::cout << "{";
    bool first = true;
    while (en->moveNext()) {
        if (!first) std::cout << ", ";
        std::cout << en->current();
        first = false;
    }
    std::cout << "}" << std::endl;
    delete en;
}

template <typename T>
void printSequence(Sequence<T> *seq) {
    IEnumerator<T> *en = seq->getEnumerator();
    std::cout << "[";
    bool first = true;
    while (en->moveNext()) {
        if (!first) std::cout << ", ";
        std::cout << en->current();
        first = false;
    }
    std::cout << "]" << std::endl;
    delete en;
}


template void printSequence<int>(const DynamicArray<int>&);
template void printSequence<int>(const LinkedList<int>&);
template void printSequence<int>(Sequence<int>*);

template void printSequence<std::string>(const DynamicArray<std::string>&);
template void printSequence<std::string>(const LinkedList<std::string>&);
template void printSequence<std::string>(Sequence<std::string>*);