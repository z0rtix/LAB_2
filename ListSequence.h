#ifndef LISTSEQUENCE_H
#define LISTSEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"

template <class T>
class ListSequence: public Sequence<T> {
    private:
        LinkedList<T> *list;
        virtual ListSequence<T>* instance() = 0;

    public:
        ListSequence();
        ListSequence(T *items, int count);
        ListSequence(LinkedList<T>* linkedList);
        ListSequence(const ListSequence <T> & list);
        ListSequence(const DynamicArray<T>& dynamicArray);
        
        virtual ~ListSequence();

        friend std::ostream& operator<<(std::ostream& os, const ListSequence<T>& seq) {
            os << *seq.list;
            return os;
        }

        T& operator[](int index) {
            return (*list)[index];
        }

        const T& operator[](int index) const {
            return (*list)[index];
        }

        ListSequence<T>& operator=(const ListSequence<T>& other) {
            if (this != &other) {
                *list = *other.list;
            }
            return *this;
        }
        
        T getFirst() const override;
        T getLast() const override;
        T get(int index) const override;

        int getLength() const override;
        bool isEmpty() const override;
        void print() const override;
        
        ListSequence<T>* append(T item) override;
        ListSequence<T>* prepend(T item) override;
        ListSequence<T>* insertAt(T item, int index) override;
        ListSequence<T>* clear() override;

        ListSequence<T>* concat(Sequence<T>* sequence) const override;
        ListSequence<T>* getSubsequence(int startIndex, int endIndex) const override;
        IEnumerator<T>* getEnumerator() const;

        virtual ListSequence<T>* copy() const = 0;

        template <typename Func> ListSequence<T>* map(Func mapper);
        template <typename Func, typename U> U reduce(Func reducer, U initial);
        template <typename Func> ListSequence<T>* where(Func predicate);
};

template <class T>
ListSequence<T>::ListSequence() {
    list = new LinkedList<T>();
}

template <class T>
ListSequence<T>::ListSequence(T *items, int count) {
    list = new LinkedList<T>(items, count);
}

template <class T>
ListSequence<T>::ListSequence(LinkedList<T>* linkedList) {
    list = *linkedList;
}

template <class T>
ListSequence<T>::ListSequence(const ListSequence <T> & list) {
    this->list = new LinkedList<T>(*list.list);
}

template <class T>
ListSequence<T>::ListSequence(const DynamicArray<T>& dynamicArray) {
    list = new LinkedList<T>();
    for (int i = 0; i < dynamicArray.getSize(); i++) {
        list->append(dynamicArray.get(i));
    }
}

template <class T>
ListSequence<T>::~ListSequence() {
    delete list;
}

template <class T>
T ListSequence<T>::getFirst() const {
    return list->getFirst();
}

template <class T>
T ListSequence<T>::getLast() const {
    return list->getLast();
}

template <class T>
T ListSequence<T>::get(int index) const {
    return list->get(index);
}

template <class T>
int ListSequence<T>::getLength() const {
    return list->getLength();
}

template <class T>
bool ListSequence<T>::isEmpty() const {
    return list->isEmpty();
}

template <class T>
void ListSequence<T>::print() const {
    list->print();
}

template <class T>
ListSequence<T>* ListSequence<T>::append(T item) {
    ListSequence<T>* obj = instance();
    obj->list->append(item);
    return obj;
}

template <class T>
ListSequence<T>* ListSequence<T>::prepend(T item) {
    ListSequence<T>* obj = instance();
    obj->list->prepend(item);
    return obj;
}

template <class T>
ListSequence<T>* ListSequence<T>::insertAt(T item, int index) {
    ListSequence<T>* obj = instance();
    obj->list->insertAt(item, index);
    return obj;
}

template <class T>
ListSequence<T>* ListSequence<T>::clear() {
    ListSequence<T>* obj = instance();
    obj->list->clear();
    return obj;
}

template <class T>
ListSequence<T>* ListSequence<T>::concat(Sequence<T>* list) const {
    ListSequence<T>* result = this->copy();
    
    for (int i = 0; i < list->getLength(); i++) {
        result->list->append(list->get(i));
    }
    
    return result;
}

template <class T>
ListSequence<T>* ListSequence<T>::getSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex >= getLength() || startIndex > endIndex) {
        throw IndexOutOfRange();
    }
    
    ListSequence<T>* result = this->copy()->clear();
    
    for (int i = startIndex; i <= endIndex; i++) {
        result->list->append(this->get(i));
    }
    
    return result;
}

template <class T>
IEnumerator<T>* ListSequence<T>::getEnumerator() const {
    return list->getEnumerator();
}

template <class T>
template <typename Func>
ListSequence<T>* ListSequence<T>::map(Func mapper) {
    ListSequence<T>* obj = instance();
    for (int i = 0; i < list->getLength(); i++) {
        obj->list->set(i, mapper(list->get(i)));
    }
    return obj;
}

template <class T>
template <typename Func, typename U>
U ListSequence<T>::reduce(Func reducer, U initial) {
    U result = initial;
    for (int i = 0; i < getLength(); i++) {
        result = reducer(result, get(i));
    }
    return result;
}

template <class T>
template <typename Func>
ListSequence<T>* ListSequence<T>::where(Func predicate) {
    ListSequence<T>* result = instance()->copy()->clear();
    for (int i = 0; i < getLength(); i++) {
        if (predicate(get(i))) {
            result->list->append(get(i));
        }
    }
    return result;
};


template <class T>
class MutableListSequence : public ListSequence<T> {
    private:
        ListSequence<T>* instance() override {
            return this;
        }

    public:
        MutableListSequence() : ListSequence<T>() {}
        MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
        MutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}

        ListSequence<T>* copy() const override {
            return new MutableListSequence<T>(*this);
        }
};

template <class T>
class ImmutableListSequence : public ListSequence<T> {
    private:
        ListSequence<T>* instance() override {
            return new ImmutableListSequence<T>(*this);
        }

    public:
        ImmutableListSequence() : ListSequence<T>() {}
        ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
        ImmutableListSequence(const ListSequence<T>& other) : ListSequence<T>(other) {}

        ListSequence<T>* copy() const override {
            return new ImmutableListSequence<T>(*this);
        }
};

#endif