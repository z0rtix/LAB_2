#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"

#include <iostream>
#include <cassert>


void tests_of_DynamicArray() {
    std::cout << "\n\n=== TESTS OF DYNAMIC ARRAY ===" << std::endl;
    
    DynamicArray<int> arr1(3);
    DynamicArray<int> arr2(5);
    
    assert(arr1.getSize() == 3);
    assert(arr2.getSize() == 5);
    
    for (int i = 0; i < 3; i++) {
        arr1.set(i * 10, i);
        assert(arr1.get(i) == i  *10); 
    }
    for (int i = 0; i < 5; i++) {
        arr2.set(i * 100, i);
        assert(arr2.get(i) == i  *100);
    }
    
    std::cout << "✅ Тесты создания пройдены" << std::endl;
    
    DynamicArray<int> arr3 = arr1;
    assert(arr3.getSize() == arr1.getSize());
    
    for (int i = 0; i < arr1.getSize(); i++) {
        assert(arr3.get(i) == arr1.get(i));
    }
    
    arr3.set(999, 0);
    assert(arr3.get(0) == 999);
    assert(arr1.get(0) == 0);
    
    std::cout << "✅ Тесты копирования пройдены" << std::endl;
    
    int oldSize = arr1.getSize();
    arr1.resize(6);
    assert(arr1.getSize() == 6);
    
    for (int i = 0; i < oldSize; i++) {
        assert(arr1.get(i) == i  *10);
    }
    
    arr1.resize(2);
    assert(arr1.getSize() == 2);
    assert(arr1.get(0) == 0);
    assert(arr1.get(1) == 10);
    
    std::cout << "✅ Тесты resize пройдены" << std::endl;
    
    assert(arr2[2] == 200);
    assert(arr2[4] == 400);
    
    arr2[2] = 999;
    assert(arr2[2] == 999);
    
    std::cout << "✅ Тесты оператора [] пройдены" << std::endl;
    
    bool exceptionThrown = false;
    try {
        arr2.get(100);
    } catch (const IndexOutOfRange&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown == true);
    
    std::cout << "✅ Тесты исключений пройдены" << std::endl;
    
    DynamicArray<DynamicArray<int>> arr7(3);
    arr7.set(arr1, 0);
    arr7.set(arr2, 1);
    arr7.set(arr3, 2);
    
    assert(arr7.getSize() == 3);
    assert(arr7.get(0).getSize() == arr1.getSize());
    assert(arr7.get(1).getSize() == arr2.getSize());

    std::cout << "✅ Тесты массива массивов пройдены" << std::endl;
    
    std::cout << "\n✅ Все тесты DynamicArray пройдены!" << std::endl;
}

void tests_of_LinkedList() {
    std::cout << "\n\n=== TESTS OF LINKED LIST ===" << std::endl;
    
    int data[] = {10, 20, 30, 40, 50};
    LinkedList<int> list1(data, 5);
    
    assert(list1.getLength() == 5);
    assert(list1.getFirst() == 10);
    assert(list1.getLast() == 50);
    assert(list1.get(2) == 30);
    assert(list1.isEmpty() == false);
    
    std::cout << "✅ Тесты создания пройдены" << std::endl;
    
    int len = list1.getLength();
    for (int i = 0; i < len; i++) {
        list1.append((i + 6)  *10);
    }
    list1.prepend(0);
    
    assert(list1.getLength() == 11);
    assert(list1.getFirst() == 0);
    assert(list1.getLast() == 100);
    
    std::cout << "✅ Тесты append/prepend пройдены" << std::endl;
    
    list1.insertAt(-10, 0);
    assert(list1.getFirst() == -10);
    assert(list1.getLength() == 12);
    
    list1.insertAt(35, 5);
    assert(list1.get(5) == 35);
    assert(list1.getLength() == 13);
    
    int lastIndex = list1.getLength() - 1;
    list1.insertAt(110, lastIndex);
    assert(list1.get(lastIndex) == 110);
    assert(list1.getLength() == 14);
    
    std::cout << "✅ Тесты insertAt пройдены" << std::endl;
    
    LinkedList<int> list2;
    for (int i = 1; i < 8; i++) {
        list2.append(i  *1000);
    }
    
    assert(list2.getLength() == 7);
    assert(list2.getFirst() == 1000);
    assert(list2.getLast() == 7000);
    for (int i = 0; i < 7; i++) {
        assert(list2.get(i) == (i+1)*1000);
    }
    
    std::cout << "✅ Тесты второго списка пройдены" << std::endl;
    
    LinkedList<int> *list3 = list1.concat(&list2);
    
    assert(list3->getLength() == list1.getLength() + list2.getLength());
    assert(list3->getFirst() == -10);
    assert(list3->getLast() == 7000);
    assert(list1.getLength() == 14);
    assert(list2.getLength() == 7);
    
    std::cout << "✅ Тесты concat пройдены" << std::endl;
    
    LinkedList<int> *list4 = list3->getSubList(2, 4);
    
    assert(list4->getLength() == 3);
    assert(list4->getFirst() == list3->get(2));
    assert(list4->getLast() == list3->get(4));
    
    std::cout << "✅ Тесты getSubList пройдены" << std::endl;
    
    assert(list1[6] == list1.get(6));
    
    list1[6] = 999;
    assert(list1[6] == 999);
    assert(list1.get(6) == 999);
    
    std::cout << "✅ Тесты оператора [] пройдены" << std::endl;
    
    LinkedList<int> emptyList;
    
    assert(emptyList.getLength() == 0);
    assert(emptyList.isEmpty() == true);
    
    bool exceptionThrown = false;
    try {
        emptyList.getFirst();
    } catch (const IndexOutOfRange&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown == true);
    
    std::cout << "✅ Тесты пустого списка пройдены" << std::endl;
    
    LinkedList<int> list5(list1);
    
    assert(list5.getLength() == list1.getLength());
    for (int i = 0; i < list1.getLength(); i++) {
        assert(list5.get(i) == list1.get(i));
    }
    
    list5.append(777);
    assert(list5.getLength() == list1.getLength() + 1);
    assert(list1.getLength() == 14);
    
    std::cout << "✅ Тесты копирования пройдены" << std::endl;
    
    LinkedList<int> a, b, c;
    a.append(1); a.append(2);
    b.append(10); b.append(20);
    c.append(100); c.append(200);
    
    LinkedList<LinkedList<int>> megaList;
    megaList.append(a); megaList.append(b); megaList.append(c);
    
    assert(megaList.getLength() == 3);
    assert(megaList[0].getLength() == 2);
    assert(megaList[0][1] == 2);
    assert(megaList[1][0] == 10);
    assert(megaList[2].getLast() == 200);
    
    std::cout << "✅ Тесты вложенных списков пройдены" << std::endl;
    
    delete list3;
    delete list4;
    
    std::cout << "\n✅ Все тесты LinkedList пройдены успешно!" << std::endl;
}

void tests_of_MutableArraySequence() {
    std::cout << "\n\n=== TESTS OF MUTABLE ARRAY SEQUENCE ===" << std::endl;
    
    MutableArraySequence<int> mutable1;
    assert(mutable1.getLength() == 0);
    assert(mutable1.isEmpty() == true);
    
    std::cout << "✅ Начальные проверки пройдены" << std::endl;
    
    mutable1.append(100);
    assert(mutable1.getLength() == 1);
    assert(mutable1.getFirst() == 100);
    assert(mutable1.getLast() == 100);
    
    mutable1.append(200);
    assert(mutable1.getLength() == 2);
    assert(mutable1.getFirst() == 100);
    assert(mutable1.getLast() == 200);
    
    std::cout << "✅ Тесты append пройдены" << std::endl;
    
    mutable1.prepend(50);
    assert(mutable1.getLength() == 3);
    assert(mutable1.getFirst() == 50);
    assert(mutable1.getLast() == 200);
    
    std::cout << "✅ Тесты prepend пройдены" << std::endl;
    
    mutable1.insertAt(150, 2);
    assert(mutable1.getLength() == 4);
    assert(mutable1.get(2) == 150);
    
    std::cout << "✅ Тесты insertAt пройдены" << std::endl;
    
    assert(mutable1[0] == 50);
    assert(mutable1.getFirst() == 50);
    assert(mutable1.getLast() == 200);
    assert(mutable1.get(2) == 150);
    
    std::cout << "✅ Тесты get методов пройдены" << std::endl;

    MutableArraySequence<int> seque;
    seque.append(10)->append(20)->append(30)->append(40);
    seque.removeFirst();
    assert(seque.getLength() == 3);
    assert(seque.get(0) == 20);
    assert(seque.get(2) == 40);
    
    seque.removeLast();
    assert(seque.getLength() == 2);
    assert(seque.get(0) == 20);
    assert(seque.get(1) == 30);
    
    seque.insertAt(25, 1);
    seque.removeAt(1);
    assert(seque.getLength() == 2);
    assert(seque.get(1) == 30);
    
    seque.removeFirst();
    seque.removeFirst();
    assert(seque.getLength() == 0);
    
    bool caught = false;
    try { seque.removeFirst(); }
    catch (const IndexOutOfRange&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { seque.removeLast(); }
    catch (const IndexOutOfRange&) { caught = true; }
    assert(caught);
    
    caught = false;
    try { seque.removeAt(0); }
    catch (const IndexOutOfRange&) { caught = true; }
    assert(caught);

    std::cout << "✅ Тесты remove пройдены" << std::endl;
    
    mutable1[1] = 999;
    assert(mutable1[1] == 999);
    assert(mutable1.get(1) == 999);
    
    std::cout << "✅ Тесты оператора [] пройдены" << std::endl;
    
    MutableArraySequence<int> mutable2;
    mutable2.append(300)->append(400);
    assert(mutable2.getLength() == 2);
    assert(mutable2.getFirst() == 300);
    assert(mutable2.getLast() == 400);
    
    std::cout << "✅ Тесты цепочки вызовов пройдены" << std::endl;
    
    MutableArraySequence<int> concatSource;
    concatSource.append(1)->append(2);
    ArraySequence<int> *concated = mutable1.concat(&concatSource);
    assert(concated->getLength() == mutable1.getLength() + concatSource.getLength());
    assert(concated->getFirst() == mutable1.getFirst());
    assert(concated->getLast() == concatSource.getLast());
    assert(mutable1.getLength() == 4);
    
    delete concated;
    std::cout << "✅ Тесты concat пройдены" << std::endl;
    
    ArraySequence<int> *sub = mutable1.getSubsequence(1, 2);
    assert(sub->getLength() == 2);
    assert(sub->getFirst() == mutable1.get(1));
    assert(sub->getLast() == mutable1.get(2));
    assert(mutable1.getLength() == 4);
    
    delete sub;
    std::cout << "✅ Тесты getSubsequence пройдены" << std::endl;
    
    MutableArraySequence<int> test;
    test.append(1);
    assert(test.getLength() == 1);
    
    for (int i = 0; i < 5; i++) {
        test.append(i  *10);
    }
    assert(test.getLength() == 6);
    assert(test.getFirst() == 1);
    assert(test.getLast() == 40);
    
    std::cout << "✅ Тесты многократных изменений пройдены" << std::endl;
    
    MutableArraySequence<MutableArraySequence<int>> arrayOfArrays;
    
    MutableArraySequence<int> inner1, inner2, inner3;
    inner1.append(1)->append(2)->append(3);
    inner2.append(10)->append(20);
    inner3.append(100)->append(200)->append(300);
    
    arrayOfArrays.append(inner1)->append(inner2)->append(inner3);
    
    assert(arrayOfArrays.getLength() == 3);
    assert(arrayOfArrays[0].getLength() == 3);
    assert(arrayOfArrays[1].getLength() == 2);
    assert(arrayOfArrays[2].getLength() == 3);
    
    assert(arrayOfArrays[0][0] == 1);
    assert(arrayOfArrays[0][1] == 2);
    assert(arrayOfArrays[0][2] == 3);
    assert(arrayOfArrays[1][0] == 10);
    assert(arrayOfArrays[1][1] == 20);
    assert(arrayOfArrays[2].getLast() == 300);
    
    arrayOfArrays[0].append(999);
    assert(arrayOfArrays[0].getLength() == 4);
    assert(arrayOfArrays[0].getLast() == 999);
    
    std::cout << "✅ Тесты массива массивов пройдены" << std::endl;

    MutableArraySequence<int> seq;
    seq.append(1)->append(2)->append(3)->append(4)->append(5);
    
    auto *mapped = seq.map([](int x) { return x  *2; });
    assert(mapped->getLength() == 5);
    assert(mapped->get(0) == 2);
    assert(mapped->get(4) == 10);
    delete mapped;

    std::cout << "✅ Тесты map пройдены" << std::endl;
    
    ArraySequence<int> *wh = seq.where([](int x) { return x % 4 == 0; });
    assert(wh->getLength() == 1);
    assert(wh->get(0) == 4);
    delete wh;

    std::cout << "✅ Тесты where пройдены" << std::endl;
    
    int sum = seq.reduce([](int acc, int x) { return acc + x; }, 0);
    assert(sum == 15);
    
    int product = seq.reduce([](int acc, int x) { return acc  *x; }, 1);
    assert(product == 120);

    std::cout << "✅ Тесты reduce пройдены" << std::endl;
    
    std::cout << "\n✅ Все тесты MutableArraySequence пройдены успешно!" << std::endl;
}

void tests_of_ImmutableArraySequence() {
    std::cout << "\n\n=== TESTS OF IMMUTABLE ARRAY SEQUENCE ===" << std::endl;
    
    ImmutableArraySequence<int> immutable1;
    assert(immutable1.getLength() == 0);
    assert(immutable1.isEmpty() == true);
    std::cout << "✅ Начальные проверки пройдены" << std::endl;
    
    Sequence<int> *seq2 = immutable1.append(100);
    assert(seq2->getLength() == 1);
    assert(seq2->getFirst() == 100);
    assert(seq2->getLast() == 100);
    assert(immutable1.getLength() == 0);
    
    Sequence<int> *seq3 = seq2->append(200);
    assert(seq3->getLength() == 2);
    assert(seq3->getFirst() == 100);
    assert(seq3->getLast() == 200);
    assert(seq2->getLength() == 1);
    delete seq2;
    delete seq3;
    std::cout << "✅ Тесты append пройдены" << std::endl;
    
    Sequence<int> *seq4 = immutable1.prepend(50);
    assert(seq4->getLength() == 1);
    assert(seq4->getFirst() == 50);
    assert(immutable1.getLength() == 0);
    delete seq4;
    std::cout << "✅ Тесты prepend пройдены" << std::endl;
    
    int data[] = {10, 20, 30, 40, 50};
    ImmutableArraySequence<int> baseSeq(data, 5);
    Sequence<int> *inserted = baseSeq.insertAt(150, 2);
    assert(inserted->getLength() == 6);
    assert(inserted->get(2) == 150);
    assert(inserted->get(3) == 30);
    assert(baseSeq.getLength() == 5);
    delete inserted;
    std::cout << "✅ Тесты insertAt пройдены" << std::endl;

    int data2[] = {1, 2, 3, 4};
    ImmutableArraySequence<int> orig(data2, 4);
    
    Sequence<int> *newSeq = orig.removeFirst();
    assert(newSeq->getLength() == 3);
    assert(newSeq->get(0) == 2);
    assert(newSeq->get(1) == 3);
    assert(newSeq->get(2) == 4);
    delete newSeq;
    
    newSeq = orig.removeLast();
    assert(newSeq->getLength() == 3);
    assert(newSeq->get(0) == 1);
    assert(newSeq->get(1) == 2);
    assert(newSeq->get(2) == 3);
    delete newSeq;
    
    newSeq = orig.removeAt(1);
    assert(newSeq->getLength() == 3);
    assert(newSeq->get(0) == 1);
    assert(newSeq->get(1) == 3);
    assert(newSeq->get(2) == 4);
    delete newSeq;
    
    assert(orig.getLength() == 4);
    assert(orig.get(0) == 1);
    assert(orig.get(1) == 2);
    assert(orig.get(2) == 3);
    assert(orig.get(3) == 4);

    std::cout << "✅ Тесты remove пройдены" << std::endl;
    
    ImmutableArraySequence<int> chain;
    Sequence<int> *c1 = chain.append(300);
    Sequence<int> *c2 = c1->append(400);
    assert(c2->getLength() == 2);
    assert(c2->getFirst() == 300);
    assert(c2->getLast() == 400);
    assert(chain.getLength() == 0);
    delete c1;
    delete c2;
    std::cout << "✅ Тесты цепочки вызовов пройдены" << std::endl;
    
    ImmutableArraySequence<int> concatSource;
    Sequence<int> *cs1 = concatSource.append(1);
    Sequence<int> *cs2 = cs1->append(2);
    Sequence<int> *concated = baseSeq.concat(cs2);
    assert(concated->getLength() == 7);
    assert(concated->getFirst() == 10);
    assert(concated->getLast() == 2);
    assert(baseSeq.getLength() == 5);
    delete cs1;
    delete cs2;
    delete concated;
    std::cout << "✅ Тесты concat пройдены" << std::endl;
    
    Sequence<int> *sub = baseSeq.getSubsequence(1, 3);
    assert(sub->getLength() == 3);
    assert(sub->getFirst() == 20);
    assert(sub->getLast() == 40);
    delete sub;
    std::cout << "✅ Тесты getSubsequence пройдены" << std::endl;
    
    ImmutableArraySequence<int> test;
    Sequence<int> *t1 = test.append(1);
    assert(t1->getLength() == 1);
    Sequence<int> *t2 = t1;
    for (int i = 0; i < 5; ++i) {
        Sequence<int> *old = t2;
        t2 = t2->append(i  *10);
        delete old;
    }
    assert(t2->getLength() == 6);
    assert(t2->getFirst() == 1);
    assert(t2->getLast() == 40);
    delete t2;
    std::cout << "✅ Тесты многократных изменений пройдены" << std::endl;
    
    ImmutableArraySequence<ImmutableArraySequence<int>> arrayOfArrays;
    ImmutableArraySequence<int> inner1, inner2, inner3;
    
    Sequence<int> *i1_1 = inner1.append(1);
    Sequence<int> *i1_2 = i1_1->append(2);
    Sequence<int> *i1_3 = i1_2->append(3);
    Sequence<int> *i2_1 = inner2.append(10);
    Sequence<int> *i2_2 = i2_1->append(20);
    Sequence<int> *i3_1 = inner3.append(100);
    Sequence<int> *i3_2 = i3_1->append(200);
    Sequence<int> *i3_3 = i3_2->append(300);
    
    auto *cast1 = dynamic_cast<ImmutableArraySequence<int>*>(i1_3);
    auto *cast2 = dynamic_cast<ImmutableArraySequence<int>*>(i2_2);
    auto *cast3 = dynamic_cast<ImmutableArraySequence<int>*>(i3_3);
    assert(cast1 && cast2 && cast3);
    
    Sequence<ImmutableArraySequence<int>> *arr1 = arrayOfArrays.append(*cast1);
    Sequence<ImmutableArraySequence<int>> *arr2 = arr1->append(*cast2);
    Sequence<ImmutableArraySequence<int>> *arr3 = arr2->append(*cast3);
    
    assert(arr3->getLength() == 3);
    assert(arr3->get(0).getLength() == 3);
    assert(arr3->get(1).getLength() == 2);
    assert(arr3->get(2).getLength() == 3);
    assert(arrayOfArrays.getLength() == 0);
    
    delete i1_1; delete i1_2; delete i1_3;
    delete i2_1; delete i2_2;
    delete i3_1; delete i3_2; delete i3_3;
    delete arr1; delete arr2; delete arr3;
    std::cout << "✅ Тесты массива массивов пройдены" << std::endl;
    
    std::cout << "\n✅ Все тесты ImmutableArraySequence пройдены успешно!" << std::endl;
}

void tests_of_MutableListSequence() {
    std::cout << "\n\n=== TESTS OF MUTABLE LIST SEQUENCE ===" << std::endl;
    
    MutableListSequence<int> mutable1;
    assert(mutable1.getLength() == 0);
    assert(mutable1.isEmpty() == true);
    
    std::cout << "✅ Начальные проверки пройдены" << std::endl;
    
    mutable1.append(100);
    assert(mutable1.getLength() == 1);
    assert(mutable1.getFirst() == 100);
    assert(mutable1.getLast() == 100);
    
    mutable1.append(200);
    assert(mutable1.getLength() == 2);
    assert(mutable1.getFirst() == 100);
    assert(mutable1.getLast() == 200);
    
    std::cout << "✅ Тесты append пройдены" << std::endl;
    
    mutable1.prepend(50);
    assert(mutable1.getLength() == 3);
    assert(mutable1.getFirst() == 50);
    assert(mutable1.getLast() == 200);
    
    std::cout << "✅ Тесты prepend пройдены" << std::endl;
    
    mutable1.insertAt(150, 2);
    assert(mutable1.getLength() == 4);
    assert(mutable1.get(2) == 150);
    
    std::cout << "✅ Тесты insertAt пройдены" << std::endl;
    
    assert(mutable1[0] == 50);
    assert(mutable1.getFirst() == 50);
    assert(mutable1.getLast() == 200);
    assert(mutable1.get(2) == 150);
    
    std::cout << "✅ Тесты get методов пройдены" << std::endl;

    MutableArraySequence<int> seque;
    seque.append(10)->append(20)->append(30)->append(40);
    
    seque.removeFirst();
    assert(seque.getLength() == 3);
    assert(seque.get(0) == 20);
    assert(seque.get(2) == 40);
    
    seque.removeLast();
    assert(seque.getLength() == 2);
    assert(seque.get(0) == 20);
    assert(seque.get(1) == 30);
    
    seque.insertAt(25, 1);
    seque.removeAt(1);
    assert(seque.getLength() == 2);
    assert(seque.get(1) == 30);
    
    seque.removeFirst();
    seque.removeFirst();
    assert(seque.getLength() == 0);

    std::cout << "✅ Тесты remove пройдены" << std::endl;
    
    mutable1[1] = 999;
    assert(mutable1[1] == 999);
    assert(mutable1.get(1) == 999);
    
    std::cout << "✅ Тесты оператора [] пройдены" << std::endl;
    
    MutableListSequence<int> mutable2;
    mutable2.append(300)->append(400);
    assert(mutable2.getLength() == 2);
    assert(mutable2.getFirst() == 300);
    assert(mutable2.getLast() == 400);
    
    std::cout << "✅ Тесты цепочки вызовов пройдены" << std::endl;
    
    MutableListSequence<int> concatSource;
    concatSource.append(1)->append(2);
    Sequence<int> *concated = mutable1.concat(&concatSource);
    assert(concated->getLength() == mutable1.getLength() + concatSource.getLength());
    assert(concated->getFirst() == mutable1.getFirst());
    assert(concated->getLast() == concatSource.getLast());
    assert(mutable1.getLength() == 4);
    
    delete concated;
    std::cout << "✅ Тесты concat пройдены" << std::endl;
    
    Sequence<int> *sub = mutable1.getSubsequence(1, 2);
    assert(sub->getLength() == 2);
    assert(sub->getFirst() == mutable1.get(1));
    assert(sub->getLast() == mutable1.get(2));
    assert(mutable1.getLength() == 4);
    
    delete sub;
    std::cout << "✅ Тесты getSubsequence пройдены" << std::endl;
    
    MutableListSequence<int> test;
    test.append(1);
    assert(test.getLength() == 1);
    
    for (int i = 0; i < 5; i++) {
        test.append(i  *10);
    }
    assert(test.getLength() == 6);
    assert(test.getFirst() == 1);
    assert(test.getLast() == 40);
    
    std::cout << "✅ Тесты многократных изменений пройдены" << std::endl;
    
    int data[] = {5, 10, 15, 20, 25};
    MutableListSequence<int> fromArray(data, 5);
    assert(fromArray.getLength() == 5);
    assert(fromArray.getFirst() == 5);
    assert(fromArray.getLast() == 25);
    assert(fromArray[2] == 15);
    
    std::cout << "✅ Тесты создания из массива пройдены" << std::endl;
    
    MutableListSequence<int> original;
    original.append(7)->append(8)->append(9);
    MutableListSequence<int> copy = original;
    
    assert(copy.getLength() == original.getLength());
    for (int i = 0; i < original.getLength(); i++) {
        assert(copy.get(i) == original.get(i));
    }
    
    copy.append(777);
    assert(copy.getLength() == 4);
    assert(original.getLength() == 3);
    
    std::cout << "✅ Тесты копирования пройдены" << std::endl;
    
    bool exceptionThrown = false;
    try {
        mutable1.get(100);
    } catch (const IndexOutOfRange&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown == true);
    
    exceptionThrown = false;
    try {
        mutable1.insertAt(999, 100);
    } catch (const IndexOutOfRange&) {
        exceptionThrown = true;
    }
    assert(exceptionThrown == true);
    
    std::cout << "✅ Тесты исключений пройдены" << std::endl;
    
    MutableListSequence<int> toClear;
    toClear.append(1)->append(2)->append(3);
    assert(toClear.getLength() == 3);
    toClear.clear();
    assert(toClear.getLength() == 0);
    assert(toClear.isEmpty() == true);
    
    std::cout << "✅ Тесты очистки пройдены" << std::endl;

    MutableListSequence<MutableListSequence<int>> mutableListOfLists;
    
    MutableListSequence<int> inner1, inner2, inner3;
    inner1.append(1)->append(2)->append(3);
    inner2.append(10)->append(20);
    inner3.append(100)->append(200)->append(300);
    
    mutableListOfLists.append(inner1)->append(inner2)->append(inner3);
    
    assert(mutableListOfLists.getLength() == 3);
    assert(mutableListOfLists[0].getLength() == 3);
    assert(mutableListOfLists[1].getLength() == 2);
    assert(mutableListOfLists[2].getLength() == 3);
    
    assert(mutableListOfLists[0][0] == 1);
    assert(mutableListOfLists[0][1] == 2);
    assert(mutableListOfLists[0][2] == 3);
    assert(mutableListOfLists[1][0] == 10);
    assert(mutableListOfLists[1][1] == 20);
    assert(mutableListOfLists[2].getLast() == 300);
    
    mutableListOfLists[0].append(999);
    assert(mutableListOfLists[0].getLength() == 4);
    assert(mutableListOfLists[0].getLast() == 999);
    
    std::cout << "✅ Тесты списка списков пройдены" << std::endl;

    MutableListSequence<int> seq;
    seq.append(1)->append(2)->append(3)->append(4)->append(5);
    
    auto *mapped = seq.map([](int x) { return x  *2; });
    assert(mapped->getLength() == 5);
    assert(mapped->get(0) == 2);
    assert(mapped->get(4) == 10);
    delete mapped;

    std::cout << "✅ Тесты map пройдены" << std::endl;
    
    ListSequence<int> *wh = seq.where([](int x) { return x % 2 == 0; });
    assert(wh->getLength() == 2);
    assert(wh->get(0) == 2);
    assert(wh->get(1) == 4);
    delete wh;

    std::cout << "✅ Тесты where пройдены" << std::endl;
    
    int sum = seq.reduce([](int acc, int x) { return acc + x; }, 0);
    assert(sum == 15);
    
    int product = seq.reduce([](int acc, int x) { return acc  *x; }, 1);
    assert(product == 120);
    
    std::cout << "✅ Тесты reduce пройдены" << std::endl;
    
    std::cout << "\n✅ Все тесты MutableListSequence пройдены успешно!" << std::endl;
}

void tests_of_ImmutableListSequence() {
    std::cout << "\n\n=== TESTS OF IMMUTABLE LIST SEQUENCE ===" << std::endl;
    
    ImmutableListSequence<int> immutable1;
    assert(immutable1.getLength() == 0);
    assert(immutable1.isEmpty() == true);
    
    std::cout << "✅ Начальные проверки пройдены" << std::endl;
    
    Sequence<int> *seq2 = immutable1.append(100);
    assert(seq2->getLength() == 1);
    assert(seq2->getFirst() == 100);
    assert(seq2->getLast() == 100);
    assert(immutable1.getLength() == 0);
    
    Sequence<int> *seq3 = seq2->append(200);
    assert(seq3->getLength() == 2);
    assert(seq3->getFirst() == 100);
    assert(seq3->getLast() == 200);
    assert(seq2->getLength() == 1);
    
    std::cout << "✅ Тесты append пройдены" << std::endl;
    
    Sequence<int> *seq4 = immutable1.prepend(50);
    assert(seq4->getLength() == 1);
    assert(seq4->getFirst() == 50);
    assert(immutable1.getLength() == 0);
    
    std::cout << "✅ Тесты prepend пройдены" << std::endl;
    
    int data[] = {10, 20, 30, 40, 50};
    ImmutableListSequence<int> baseSeq(data, 5);
    Sequence<int> *inserted = baseSeq.insertAt(150, 2);
    assert(inserted->getLength() == 6);
    assert(inserted->get(2) == 150);
    assert(inserted->get(3) == 30);
    assert(baseSeq.getLength() == 5);
    
    std::cout << "✅ Тесты insertAt пройдены" << std::endl;
    
    assert(inserted->get(0) == 10);
    assert(inserted->getFirst() == 10);
    assert(inserted->getLast() == 50);
    
    std::cout << "✅ Тесты get методов пройдены" << std::endl;

    int data2[] = {1, 2, 3, 4};
    ImmutableListSequence<int> orig(data2, 4);
    
    Sequence<int>* newSeq = orig.removeFirst();
    assert(newSeq->getLength() == 3);
    assert(newSeq->get(0) == 2);
    assert(newSeq->get(1) == 3);
    assert(newSeq->get(2) == 4);
    delete newSeq;
    
    newSeq = orig.removeLast();
    assert(newSeq->getLength() == 3);
    assert(newSeq->get(0) == 1);
    assert(newSeq->get(1) == 2);
    assert(newSeq->get(2) == 3);
    delete newSeq;
    
    newSeq = orig.removeAt(1);
    assert(newSeq->getLength() == 3);
    assert(newSeq->get(0) == 1);
    assert(newSeq->get(1) == 3);
    assert(newSeq->get(2) == 4);
    delete newSeq;
    
    assert(orig.getLength() == 4);
    assert(orig.get(0) == 1);
    assert(orig.get(1) == 2);
    assert(orig.get(2) == 3);
    assert(orig.get(3) == 4);

    std::cout << "✅ Тесты remove пройдены" << std::endl;
    
    ImmutableListSequence<int> chain;
    Sequence<int> *chainTmp = chain.append(300);
    Sequence<int> *chainResult = chainTmp->append(400);
    assert(chainResult->getLength() == 2);
    assert(chainResult->getFirst() == 300);
    assert(chainResult->getLast() == 400);
    assert(chain.getLength() == 0);
    
    std::cout << "✅ Тесты цепочки вызовов пройдены" << std::endl;
    
    ImmutableListSequence<int> concatSource;
    Sequence<int> *concatTmp = concatSource.append(1);
    Sequence<int> *sourceWithData = concatTmp->append(2);
    Sequence<int> *concated = baseSeq.concat(sourceWithData);
    assert(concated->getLength() == 7);
    assert(concated->getFirst() == 10);
    assert(concated->getLast() == 2);
    assert(baseSeq.getLength() == 5);
    
    delete concated;
    std::cout << "✅ Тесты concat пройдены" << std::endl;
    
    Sequence<int> *sub = baseSeq.getSubsequence(1, 3);
    assert(sub->getLength() == 3);
    assert(sub->getFirst() == 20);
    assert(sub->getLast() == 40);
    assert(baseSeq.getLength() == 5);
    
    delete sub;
    std::cout << "✅ Тесты getSubsequence пройдены" << std::endl;
    
    ImmutableListSequence<int> test;
    Sequence<int> *test1 = test.append(1);
    assert(test1->getLength() == 1);
    
    Sequence<int> *test2 = test1;
    for (int i = 0; i < 5; i++) {
        Sequence<int> *oldTest2 = test2;
        test2 = test2->append(i  *10);
        delete oldTest2;
    }
    assert(test2->getLength() == 6);
    assert(test2->getFirst() == 1);
    assert(test2->getLast() == 40);
    
    std::cout << "✅ Тесты многократных изменений пройдены" << std::endl;
    
    ImmutableListSequence<ImmutableListSequence<int>> listOfLists;
    ImmutableListSequence<int> inner1, inner2, inner3;

    Sequence<int> *inner1_t1 = inner1.append(1);
    Sequence<int> *inner1_t2 = inner1_t1->append(2);
    Sequence<int> *inner1Seq = inner1_t2->append(3);
    
    Sequence<int> *inner2_t1 = inner2.append(10);
    Sequence<int> *inner2Seq = inner2_t1->append(20);
    
    Sequence<int> *inner3_t1 = inner3.append(100);
    Sequence<int> *inner3_t2 = inner3_t1->append(200);
    Sequence<int> *inner3Seq = inner3_t2->append(300);

    ImmutableListSequence<int> *castedInner1 = dynamic_cast<ImmutableListSequence<int>*>(inner1Seq);
    ImmutableListSequence<int> *castedInner2 = dynamic_cast<ImmutableListSequence<int>*>(inner2Seq);
    ImmutableListSequence<int> *castedInner3 = dynamic_cast<ImmutableListSequence<int>*>(inner3Seq);

    assert(castedInner1 != nullptr);
    assert(castedInner2 != nullptr);
    assert(castedInner3 != nullptr);

    Sequence<ImmutableListSequence<int>> *list1 = listOfLists.append(*castedInner1);
    Sequence<ImmutableListSequence<int>> *list2 = list1->append(*castedInner2);
    Sequence<ImmutableListSequence<int>> *list3 = list2->append(*castedInner3);

    assert(list3->getLength() == 3);
    assert(list3->get(0).getLength() == 3);
    assert(list3->get(1).getLength() == 2);
    assert(list3->get(2).getLength() == 3);

    assert(listOfLists.getLength() == 0);
        
    std::cout << "✅ Тесты массива массивов пройдены" << std::endl;
    
    delete seq2;
    delete seq3;
    delete seq4;
    delete inserted;
    delete chainTmp;
    delete chainResult;
    delete concatTmp;
    delete sourceWithData;
    delete test2;
    delete inner1_t1;
    delete inner1_t2;
    delete inner1Seq;
    delete inner2_t1;
    delete inner2Seq;
    delete inner3_t1;
    delete inner3_t2;
    delete inner3Seq;
    delete list1;
    delete list2;
    delete list3;
    
    std::cout << "\n✅ Все тесты ImmutableListSequence пройдены успешно!" << std::endl;
}

void tests_of_ListOfLists() {
    std::cout << "\n\n=== TESTS OF LIST OF LISTS ===" << std::endl;
    
    std::cout << "\n1. MutableListSequence<MutableListSequence<int>>:" << std::endl;
    MutableListSequence<MutableListSequence<int>> mutableListOfLists;
    
    MutableListSequence<int> inner1, inner2, inner3;
    inner1.append(1)->append(2)->append(3);
    inner2.append(10)->append(20);
    inner3.append(100)->append(200)->append(300);
    
    mutableListOfLists.append(inner1)->append(inner2)->append(inner3);
    
    assert(mutableListOfLists.getLength() == 3);
    assert(mutableListOfLists[0].getLength() == 3);
    assert(mutableListOfLists[1].getLength() == 2);
    assert(mutableListOfLists[2].getLength() == 3);
    
    assert(mutableListOfLists[0][0] == 1);
    assert(mutableListOfLists[0][1] == 2);
    assert(mutableListOfLists[0][2] == 3);
    assert(mutableListOfLists[1][0] == 10);
    assert(mutableListOfLists[1][1] == 20);
    assert(mutableListOfLists[2].getLast() == 300);
    
    mutableListOfLists[0].append(999);
    assert(mutableListOfLists[0].getLength() == 4);
    assert(mutableListOfLists[0].getLast() == 999);
    
    std::cout << "mutableListOfLists[0]: " << mutableListOfLists[0] << std::endl;
    std::cout << "mutableListOfLists[1]: " << mutableListOfLists[1] << std::endl;
    std::cout << "mutableListOfLists[2]: " << mutableListOfLists[2] << std::endl;
    
    std::cout << "✅ MutableListSequence<MutableListSequence<int>> пройдены" << std::endl;
    
    std::cout << "\n2. ImmutableListSequence<ImmutableListSequence<int>>:" << std::endl;
    ImmutableListSequence<ImmutableListSequence<int>> immutableListOfLists;
    
    ImmutableListSequence<int> immutableInner1, immutableInner2, immutableInner3;
    Sequence<int> *immInner1Seq = immutableInner1.append(1)->append(2)->append(3);
    Sequence<int> *immInner2Seq = immutableInner2.append(10)->append(20);
    Sequence<int> *immInner3Seq = immutableInner3.append(100)->append(200)->append(300);
    
    ImmutableListSequence<int> *casted1 = dynamic_cast<ImmutableListSequence<int>*>(immInner1Seq);
    ImmutableListSequence<int> *casted2 = dynamic_cast<ImmutableListSequence<int>*>(immInner2Seq);
    ImmutableListSequence<int> *casted3 = dynamic_cast<ImmutableListSequence<int>*>(immInner3Seq);
    
    assert(casted1 != nullptr && casted2 != nullptr && casted3 != nullptr);
    
    Sequence<ImmutableListSequence<int>> *list1 = immutableListOfLists.append(*casted1);
    Sequence<ImmutableListSequence<int>> *list2 = list1->append(*casted2);
    Sequence<ImmutableListSequence<int>> *list3 = list2->append(*casted3);
    
    ListSequence<ImmutableListSequence<int>> *castedList = dynamic_cast<ListSequence<ImmutableListSequence<int>>*>(list3);
    assert(castedList != nullptr);
    
    assert(castedList->getLength() == 3);
    assert((*castedList)[0].getLength() == 3);
    assert((*castedList)[1].getLength() == 2);
    assert((*castedList)[2].getLength() == 3);
    
    assert((*castedList)[0][0] == 1);
    assert((*castedList)[0][1] == 2);
    assert((*castedList)[0][2] == 3);
    assert((*castedList)[1][0] == 10);
    assert((*castedList)[1][1] == 20);
    assert((*castedList)[2].getLast() == 300);
    
    assert(immutableListOfLists.getLength() == 0);
    
    std::cout << "(*castedList)[0]: " << (*castedList)[0] << std::endl;
    std::cout << "(*castedList)[1]: " << (*castedList)[1] << std::endl;
    std::cout << "(*castedList)[2]: " << (*castedList)[2] << std::endl;
    
    std::cout << "✅ ImmutableListSequence<ImmutableListSequence<int>> пройдены" << std::endl;
    
    std::cout << "\n3. Смешанные типы:" << std::endl;
    
    MutableListSequence<ImmutableListSequence<int>> mixedList;
    mixedList.append(*casted1)->append(*casted2)->append(*casted3);
    
    assert(mixedList.getLength() == 3);
    assert(mixedList[0].getLength() == 3);
    assert(mixedList[1].getLength() == 2);
    assert(mixedList[2].getLength() == 3);
    
    ImmutableListSequence<MutableListSequence<int>> mixedList2;
    mixedList2.append(inner1)->append(inner2)->append(inner3);
    
    delete immInner1Seq;
    delete immInner2Seq;
    delete immInner3Seq;
    delete list1;
    delete list2;
    delete list3;
    
    std::cout << "✅ Смешанные типы пройдены" << std::endl;
    
    std::cout << "\n4. Глубокое копирование:" << std::endl;
    MutableListSequence<MutableListSequence<int>> originalList;
    originalList.append(inner1)->append(inner2);
    
    MutableListSequence<MutableListSequence<int>> copiedList = originalList;
    
    assert(copiedList.getLength() == originalList.getLength());
    assert(copiedList[0].getLength() == originalList[0].getLength());
    
    copiedList[0].append(777);
    assert(copiedList[0].getLength() == originalList[0].getLength() + 1);
    
    std::cout << "✅ Глубокое копирование пройдено" << std::endl;
    
    std::cout << "\n✅ Все тесты List of Lists пройдены успешно!" << std::endl;
}