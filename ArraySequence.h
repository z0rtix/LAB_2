#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"

#include <iostream>


template <class T>
class ArraySequence : public Sequence<T> {
    protected:
        DynamicArray<T> *array;
        virtual ArraySequence<T> *instance() = 0;

    public:
        ArraySequence();
        ArraySequence(int size);
        ArraySequence(T *items, int count);
        ArraySequence(const DynamicArray<T>& otherArray);
        ArraySequence(const ArraySequence<T>& other); 
        ArraySequence(const LinkedList<T>& list);
        
        virtual ~ArraySequence();

        friend std::ostream& operator<<(std::ostream& os, const ArraySequence<T>& seq) {
            os << *seq.array;
            return os;
        }

        T& operator[](int index) {
            return (*array)[index];
        }

        const T& operator[](int index) const {
            return (*array)[index];
        }

        ArraySequence<T>& operator=(const ArraySequence<T>& other) {
            if (this != &other) {
                *array = *other.array;
            }
            return *this;
        }
        
        T getFirst() const override;
        T getLast() const override;
        T get(int index) const override;

        int getLength() const override;
        bool isEmpty() const override;
        void print() const override;
        
        ArraySequence<T> *append(T item) override;
        ArraySequence<T> *prepend(T item) override;
        ArraySequence<T> *insertAt(T item, int index) override;
        ArraySequence<T> *clear() override;

        ArraySequence<T> *concat(Sequence<T> *list) const override;
        ArraySequence<T> *getSubsequence(int     startIndex, int endIndex) const override;
        IEnumerator<T> *getEnumerator() const;

        virtual ArraySequence<T> *copy() const = 0;

        template <typename Func> ArraySequence<T> *map(Func mapper);
        template <typename Func, typename U> U reduce(Func reducer, U initial);
        template <typename Func> ArraySequence<T> *where(Func predicate);
};

template <class T>
ArraySequence<T>::ArraySequence() {
    array = new DynamicArray<T>();
}

template <class T>
ArraySequence<T>::ArraySequence(int size) {
    array = new DynamicArray<T>(size);
}

template <class T>
ArraySequence<T>::ArraySequence(T *items, int count) {
    array = new DynamicArray<T>(items, count);
}

template <class T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& otherArray) {
    array = new DynamicArray<T>(otherArray);
}

template <class T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) {
    array = new DynamicArray<T>(*other.array);
}

template <class T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list) {
    array = new DynamicArray<T>(list.getLength());
    for (int i = 0; i < list.getLength(); i++) {
        array->set(i, list.get(i));
    }
}

template <class T>
ArraySequence<T>::~ArraySequence() {
    delete array;
}

template <class T>
T ArraySequence<T>::getFirst() const {
    return array->get(0);
}

template <class T>
T ArraySequence<T>::getLast() const {
    return array->get(array->getSize() - 1);
}

template <class T>
T ArraySequence<T>::get(int index) const {
    return array->get(index);
}

template <class T>
int ArraySequence<T>::getLength() const {
    return array->getSize();
}

template <class T>
bool ArraySequence<T>::isEmpty() const {
    return array->isEmpty();
}

template <class T>
void ArraySequence<T>::print() const {
    array->print();
}

template <class T>
ArraySequence<T> *ArraySequence<T>::append(T item) {
    ArraySequence<T> *obj = instance();
    int newSize = obj->array->getSize() + 1;
    obj->array->resize(newSize);
    obj->array->set(newSize - 1, item);
    return obj;
}

template <class T>
ArraySequence<T> *ArraySequence<T>::prepend(T item) {
    ArraySequence<T> *obj = instance();
    int oldSize = obj->array->getSize();
    int newSize = oldSize + 1;
    obj->array->resize(newSize);
    
    for (int i = oldSize - 1; i >= 0; i--) {
        obj->array->set(i + 1, obj->array->get(i));
    }
    obj->array->set(0, item);
    return obj;
}

template <class T>
ArraySequence<T> *ArraySequence<T>::insertAt(T item, int index) {
    ArraySequence<T> *obj = instance();
    int currentSize = obj->array->getSize();
    if (index < 0 || index > currentSize) {
        throw IndexOutOfRange();
    }

    obj->array->resize(currentSize + 1);    

    for (int i = currentSize - 1; i >= index; i--) {
        obj->array->set(i + 1, obj->array->get(i));
    }

    obj->array->set(index, item);

    return obj;
}

template <class T>
ArraySequence<T> *ArraySequence<T>::clear() {
    ArraySequence<T> *obj = instance();
    obj->array->resize(0);
    return obj;
}

template <class T>
ArraySequence<T>* ArraySequence<T>::concat(Sequence<T>* list) const {
    ArraySequence<T>* result = this->copy();
    result->array->resize(0);
    
    for (int i = 0; i < getLength(); i++) {
        int newSize = result->array->getSize() + 1;
        result->array->resize(newSize);
        result->array->set(newSize - 1, get(i));
    }
    for (int i = 0; i < list->getLength(); i++) {
        int newSize = result->array->getSize() + 1;
        result->array->resize(newSize);
        result->array->set(newSize - 1, list->get(i));
    }
    return result;
}

template <class T>
ArraySequence<T> *ArraySequence<T>::getSubsequence(int startIndex, int endIndex) const { 
    if (startIndex < 0 || endIndex >= getLength() || startIndex > endIndex) {
        throw IndexOutOfRange();
    }
    
    ArraySequence<T> *result = this->copy();
    result->array->resize(0);
    
    for (int i = startIndex; i <= endIndex; i++) {
        int newSize = result->array->getSize() + 1;
        result->array->resize(newSize);
        result->array->set(newSize - 1, this->get(i));
    }
    
    return result;
}

template <class T>
IEnumerator<T> *ArraySequence<T>::getEnumerator() const {
    return array->getEnumerator();
}

template <class T>
template <typename Func>
ArraySequence<T> *ArraySequence<T>::map(Func mapper) {
    ArraySequence<T> *obj = this->copy();
    for (int i = 0; i < array->getSize(); i++) {
        obj->array->set(i, mapper(array->get(i)));
    }
    return obj;
}

template <class T>
template <typename Func, typename U>
U ArraySequence<T>::reduce(Func reducer, U initial) {
    U result = initial;
    for (int i = 0; i < getLength(); i++) {
        result = reducer(result, get(i));
    }
    return result;
}

template <class T>
template <typename Func>
ArraySequence<T>* ArraySequence<T>::where(Func predicate) {
    ArraySequence<T>* result = this->copy();
    result->array->resize(0);
    
    for (int i = 0; i < getLength(); i++) {
        if (predicate(get(i))) {
            int newSize = result->array->getSize() + 1;
            result->array->resize(newSize);
            result->array->set(newSize - 1, get(i));
        }
    }
    return result;
}


template <class T>
class MutableArraySequence : public ArraySequence<T> {
    private:
        ArraySequence<T> *instance() override {
            return this;
        }

    public:
        MutableArraySequence() : ArraySequence<T>() {}
        MutableArraySequence(int size) : ArraySequence<T>(size) {}
        MutableArraySequence(T *items, int count) : ArraySequence<T>(items, count) {}
        MutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

        ArraySequence<T> *copy() const override {
            return new MutableArraySequence<T>(*this);
        }
};

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
    private:
        ArraySequence<T> *instance() override {
            return new ImmutableArraySequence<T>(*this);
        }

    public:
        ImmutableArraySequence() : ArraySequence<T>() {}
        ImmutableArraySequence(int size) : ArraySequence<T>(size) {}
        ImmutableArraySequence(T *items, int count) : ArraySequence<T>(items, count) {}
        ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

        ArraySequence<T> *copy() const override {
            return new ImmutableArraySequence<T>(*this);
        }
};

#endif