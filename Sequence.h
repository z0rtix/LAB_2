#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "IEnumerator.h"


template <class T>
class Sequence {
    public:
        virtual ~Sequence() = default;
        
        virtual T getFirst() const = 0;
        virtual T getLast() const = 0;
        virtual T get(int index) const = 0;
        
        virtual int getLength() const = 0;
        virtual bool isEmpty() const = 0;
        virtual void print() const = 0;
        
        virtual Sequence<T> *append(T item) = 0;
        virtual Sequence<T> *prepend(T item) = 0;
        virtual Sequence<T> *insertAt(T item, int index) = 0;

        virtual Sequence<T> *removeFirst() = 0;
        virtual Sequence<T> *removeLast() = 0;
        virtual Sequence<T> *removeAt(int index) = 0;
        virtual Sequence<T> *clear() = 0;

        virtual Sequence<T> *concat(Sequence<T> *list) const = 0;
        virtual Sequence<T> *getSubsequence(int startIndex, int endIndex) const = 0;
        virtual IEnumerator<T> *getEnumerator() const = 0;

        virtual Sequence<T> *copy() const = 0;
};

#endif