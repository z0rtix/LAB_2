#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "IndexOutOfRange.h"
#include "IEnumerator.h"

#include <iostream> 


template <class T>
class LinkedList {
    private:
        struct Node {
            T data;
            Node *next;
        };
        Node *first;
        Node *last;
        int size;
        
    public:
        LinkedList();
        LinkedList (T *items, int count);
        LinkedList (const LinkedList <T> & list);
        ~LinkedList();

        friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& list) {
            Node *current = list.first;
            os << "{";
            while (current != nullptr) {
                os << current->data;
                current = current->next;
                if (current != nullptr) {
                    os << ", ";
                }
            }
            os << "}";
            return os;
        }

        const T& operator[](int index) const {
            if (index < 0 || index >= size) {
                throw IndexOutOfRange();
            }
            Node *current = first;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

        T& operator[](int index) {
            if (index < 0 || index >= size) {
                throw IndexOutOfRange();
            }
            Node *current = first;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }

        LinkedList<T>& operator=(const LinkedList<T>& other) {
            if (this != &other) {
                clear();
                
                Node *current = other.first;
                while (current != nullptr) {
                    append(current->data);
                    current = current->next;
                }
            }
            return *this;
        }

        T getFirst() const;
        T getLast() const;
        T get(int index) const;

        int getLength() const;
        bool isEmpty() const;
        void print() const;

        void append(T item); 
        void prepend(T item); 
        void insertAt(T item, int index);
        void set(int index, T item);

        void removeFirst();
        void removeLast();
        void removeAt(int index);
        void clear();

        LinkedList<T> *concat(LinkedList<T> *list);
        LinkedList<T> *getSubList(int startIndex, int endIndex);
        IEnumerator<T> *getEnumerator() const;
};


template <class T>
LinkedList<T>::LinkedList() : first(nullptr), last(nullptr), size(0) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) : first(nullptr), last(nullptr), size(0) {
    if (list.first == nullptr) {
        return;
    }
    Node *current = list.first;
    Node *prevNode = nullptr;
    while (current != nullptr) {
        Node *newNode = new Node{current->data, nullptr};
        if (first == nullptr) {
            first = newNode;
        } 
        else {
            prevNode->next = newNode;
        }
        prevNode = newNode;
        last = newNode;
        current = current->next;
        size++;
    }
}

template <class T>
LinkedList<T>::LinkedList(T *items, int count) : first(nullptr), last(nullptr), size(0) {
    if (items == nullptr || count == 0) {
        return;
    }
    for (int i = 0; i < count; i++) {
        Node *newNode = new Node{items[i], nullptr};
        
        if (first == nullptr) {
            first = newNode;
            last = newNode;
        } 
        else {
            last->next = newNode;
            last = newNode;
        }
        size++;
    }
}

template <class T>
LinkedList<T>::~LinkedList() {
    Node *current = first;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

template <class T>
T LinkedList<T>::getFirst() const {
    if (first == nullptr) {
        throw IndexOutOfRange();
    }
    return first->data;
}

template <class T>
T LinkedList<T>::getLast() const {
    if (last == nullptr) {
        throw IndexOutOfRange();
    }
    return last->data;
}

template <class T>
T LinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw IndexOutOfRange();
    }

    Node *current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template <class T>
int LinkedList<T>::getLength() const {
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const {
    return size == 0;
}

template <class T>
void LinkedList<T>::print() const {
    Node *current = first;
    std::cout << "{";
    while (current != nullptr) {
        std::cout << current->data;
        current = current->next;
        if (current != nullptr) {
            std::cout << ", ";
        }
    }
    std::cout << "}" << std::endl;
}

template <class T>
void LinkedList<T>::append(T item) {
    Node *newNode = new Node{item, nullptr};
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        last = newNode;
    }
    size++;
}

template <class T>
void LinkedList<T>::prepend(T item) {
    Node *newNode = new Node{item, first};
    first = newNode;
    if (last == nullptr) {
        last = newNode;
    }
    size++;
}

template <class T>
void LinkedList<T>::insertAt(T item, int index) {
    if (index < 0 || index > size) {
        throw IndexOutOfRange();
    }
    else if (index == 0) {
        prepend(item);
    }
    else if (index == size) {
        append(item);
    }
    else {
        Node *newNode = new Node{item, nullptr};
        Node *current = first;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

template <class T>
void LinkedList<T>::set(int index, T item) {
    if (index < 0 || index >= size) {
        throw IndexOutOfRange();
    }
    
    Node *current = first;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    
    current->data = item;
}

template <class T>
void LinkedList<T>::removeFirst() {
    if (size == 0) throw IndexOutOfRange();
    Node *old = first;
    first = first->next;
    delete old;
    size--;
    if (size == 0) last = nullptr;
}

template <class T>
void LinkedList<T>::removeLast() {
    if (size == 0) throw IndexOutOfRange();
    if (size == 1) {
        delete first;
        first = last = nullptr;
    } else {
        Node *current = first;
        while (current->next != last) {
            current = current->next;
        }
        delete last;
        current->next = nullptr;
        last = current;
    }
    size--;
}

template <class T>
void LinkedList<T>::removeAt(int index) {
    if (index < 0 || index >= size) throw IndexOutOfRange();
    if (index == 0) return removeFirst();
    if (index == size - 1) return removeLast();
    Node *prev = first;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }
    Node *toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
    size--;
}

template <class T>
void LinkedList<T>::clear() {
    if (first == nullptr) return;
    
    Node *current = first;
    while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    first = nullptr;
    last = nullptr;
    size = 0;
}

template <class T>
LinkedList<T> *LinkedList<T>::concat(LinkedList<T> *list) {
    LinkedList<T> *newList = new LinkedList<T>(*this);
    Node *current = list->first;
    while (current != nullptr) {
        newList->append(current->data);
        current = current->next;
    }
    return newList;
}

template <class T>
LinkedList<T> *LinkedList<T>::getSubList(int start, int end) {
    if (start < 0 || start >= size || end < 0 || end >= size || start > end) {
        throw IndexOutOfRange();
    }
    LinkedList<T> *newList = new LinkedList<T>();
    for (int i = start; i <= end; i++) {
        newList->append(get(i));
    }
    return newList;
}

template <class T>
IEnumerator<T> *LinkedList<T>::getEnumerator() const {
    class LinkedListEnumerator : public IEnumerator<T> {
        private:
            Node *next;
            Node *current_obj;
            bool started;
        
        public:
            LinkedListEnumerator(Node *first) : next(first), current_obj(nullptr), started(false) {}

            ~LinkedListEnumerator() = default;
            
            bool moveNext() override {
                if (!started) {
                    current_obj = next;
                    started = true;
                } 
                else {
                    current_obj = current_obj->next;
                }
                return current_obj != nullptr;
            }
            
            T current() override {
                if (!current_obj || !started) {
                    throw IndexOutOfRange();
                }
                return current_obj->data;
            }
    };
        
    return new LinkedListEnumerator(first);
}

#endif