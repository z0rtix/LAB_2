#include "ArraySequence.h"
#include "ListSequence.h"

#include <iostream>
#include <chrono>
#include <cassert>


using namespace std::chrono;


template <typename F>
long long measure(F f) {
    auto start = high_resolution_clock::now();
    f();
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}


template <typename Seq>
void testMutable(Seq &seq, const char *name) {
    std::cout << "✅ " << name << " базовые операции" << std::endl;;
    assert(seq.getLength() == 0 && seq.isEmpty());

    for (int i = 0; i < 100; i++) seq.append(i);
    assert(seq.getLength() == 100);
    assert(seq.getFirst() == 0);
    assert(seq.getLast() == 99);
    assert(seq.get(50) == 50);

    seq.set(999, 50);
    assert(seq.get(50) == 999);

    seq.removeFirst();
    assert(seq.getFirst() == 1);
    seq.removeLast();
    assert(seq.getLast() == 98);
    seq.removeAt(10);
    assert(seq.get(10) == 12);

    auto *sub = seq.getSubsequence(10, 20);
    assert(sub->getLength() == 11);
    delete sub;

    MutableArraySequence<int> other;
    for (int i = 0; i < 10; i++) other.append(i + 100);
    auto *conc = seq.concat(&other);
    assert(conc->getLength() == seq.getLength() + other.getLength());
    delete conc;

    seq.clear();
    assert(seq.getLength() == 0);
}


void testImmutable(Sequence<int> *seq, const char *name) {
    std::cout << "✅ " << name << " базовые операции" << std::endl;
    assert(seq->getLength() == 0 && seq->isEmpty());

    for (int i = 0; i < 100; i++) {
        auto *tmp = seq->append(i);
        delete seq;
        seq = tmp;
    }

    assert(seq->getLength() == 100);
    assert(seq->getFirst() == 0);
    assert(seq->getLast() == 99);
    assert(seq->get(50) == 50);

    auto *tmp = seq->set(999, 50);
    delete seq; seq = tmp;
    assert(seq->get(50) == 999);

    tmp = seq->removeFirst();
    delete seq; seq = tmp;
    assert(seq->getFirst() == 1);

    tmp = seq->removeLast();
    delete seq; seq = tmp;
    assert(seq->getLast() == 98);

    tmp = seq->removeAt(10);
    delete seq; seq = tmp;
    assert(seq->get(10) == 12);

    auto *sub = seq->getSubsequence(10, 20);
    assert(sub->getLength() == 11);
    delete sub;

    MutableArraySequence<int> other;
    for (int i = 0; i < 10; i++) other.append(i + 100);
    auto *conc = seq->concat(&other);
    assert(conc->getLength() == seq->getLength() + other.getLength());
    delete conc;

    auto *cleared = seq->clear();
    delete seq; seq = cleared;
    assert(seq->getLength() == 0);
    delete seq;
}


void testArrayMapReduceWhere() {
    std::cout << "\n✅ ArraySequence: map, reduce, where" << std::endl;
    MutableArraySequence<int> seq;
    for (int i = 0; i < 10; i++) seq.append(i + 1);

    int sum = seq.reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 55);

    auto *mapped = seq.template map<int>([](int x, int) { return x * 2; });
    assert(mapped->getLength() == 10);
    assert(mapped->get(0) == 2 && mapped->get(9) == 20);

    delete mapped;
    auto *filtered = seq.where([](int x) { return x % 2 == 0; });
    assert(filtered->getLength() == 5);
    assert(filtered->get(0) == 2 && filtered->get(4) == 10);

    delete filtered;
}


void testListMapReduceWhere() {
    std::cout << "✅ ListSequence: map, reduce, where" << std::endl;
    MutableListSequence<int> seq;
    for (int i = 0; i < 10; i++) seq.append(i + 1);

    int sum = seq.reduce([](int a, int b) { return a + b; }, 0);
    assert(sum == 55);

    auto *mapped = seq.template map<int>([](int x, int) { return x * 2; });
    assert(mapped->getLength() == 10);
    assert(mapped->get(0) == 2 && mapped->get(9) == 20);

    delete mapped;
    auto *filtered = seq.where([](int x) { return x % 2 == 0; });
    assert(filtered->getLength() == 5);
    assert(filtered->get(0) == 2 && filtered->get(4) == 10);

    delete filtered;
}


template <typename Seq>
long long stressAppendMutable(Seq &seq) {
    return measure([&] { for (int i = 0; i < 10000; i++) seq.append(i); });
}

long long stressAppendImmutable(Sequence<int> *seq) {
    return measure([&] {
        Sequence<int> *cur = seq;
        for (int i = 0; i < 10000; i++) {
            auto *tmp = cur->append(i);
            delete cur;
            cur = tmp;
        }
        delete cur;
    });
}

void stressTest() {
    std::cout << "\n=== Стресс-тест (10k append) ===\n";
    MutableArraySequence<int> marr;
    long long tArrMut = stressAppendMutable(marr);

    MutableListSequence<int> mlst;
    long long tLstMut = stressAppendMutable(mlst);
    long long tArrImm = stressAppendImmutable(new ImmutableArraySequence<int>());
    long long tLstImm = stressAppendImmutable(new ImmutableListSequence<int>());

    std::cout << "\n========================= PERFORMANCE SUMMARY ===========================\n";
    std::cout << "Type                  Array (ms)   List (ms)       Faster\n";
    std::cout << "-------------------------------------------------------------------------\n";
    double ratioArrList = (double)tLstMut / tArrMut;
    std::cout << "Mutable               " << tArrMut << "             " << tLstMut << "          Array is " << ratioArrList << "x faster\n";
    double ratioIarrIlst = (double)tLstImm / tArrImm;
    std::cout << "Immutable             " << tArrImm << "         " << tLstImm << "         Array is " << ratioIarrIlst << "x faster\n";
    std::cout << "===========================================================================\n";
}


void runAllTests() {
    MutableArraySequence<int> marr;
    testMutable(marr, "Mutable ArraySequence");

    MutableListSequence<int> mlst;
    testMutable(mlst, "Mutable ListSequence");

    testImmutable(new ImmutableArraySequence<int>(), "Immutable ArraySequence");
    testImmutable(new ImmutableListSequence<int>(), "Immutable ListSequence");

    testArrayMapReduceWhere();
    testListMapReduceWhere();

    stressTest();

    std::cout << "\n✅ Все тесты пройдены успешно!\n" << std::endl;
}
