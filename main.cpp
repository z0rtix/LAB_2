#include "tests.h"
#include "menu.h"

#include <iostream>


int main() {
    tests_of_DynamicArray();
    tests_of_LinkedList();
    tests_of_MutableArraySequence();
    tests_of_ImmutableArraySequence();
    tests_of_MutableListSequence();
    tests_of_ImmutableListSequence();

    startMenu();

    return 0;
}