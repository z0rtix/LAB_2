#include "menu.h"
#include "ArraySequence.h"
#include "ListSequence.h"

#include <iostream>
#include <limits>


void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt) {
    int value;
    std::cout << prompt;
    while (!(std::cin >> value)) {
        std::cout << "Ошибка ввода. Введите целое число: ";
        clearInput();
    }
    clearInput();
    return value;
}

int square(int x) { return x * x; }
int cube(int x) { return x * x * x; }
int add10(int x) { return x + 10; }

bool isEven(int x) { return x % 2 == 0; }
bool isOdd(int x) { return x % 2 != 0; }
bool greaterThan5(int x) { return x > 5; }

int sum(int acc, int x) { return acc + x; }
int product(int acc, int x) { return acc * x; }

enum SeqType { MUTABLE_ARRAY, IMMUTABLE_ARRAY, MUTABLE_LIST, IMMUTABLE_LIST };

SeqType chooseSequenceType() {
    std::cout << "\n=== ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ ===\n";
    std::cout << "1 - MutableArraySequence\n";
    std::cout << "2 - ImmutableArraySequence\n";
    std::cout << "3 - MutableListSequence\n";
    std::cout << "4 - ImmutableListSequence\n";
    std::cout << "0 - Выход\n";
    int choice = readInt("> ");
    switch (choice) {
        case 1: return MUTABLE_ARRAY;
        case 2: return IMMUTABLE_ARRAY;
        case 3: return MUTABLE_LIST;
        case 4: return IMMUTABLE_LIST;
        default: return MUTABLE_ARRAY;
    }
}

Sequence<int>* createEmptySequence(SeqType type) {
    switch (type) {
        case MUTABLE_ARRAY:   return new MutableArraySequence<int>();
        case IMMUTABLE_ARRAY: return new ImmutableArraySequence<int>();
        case MUTABLE_LIST:    return new MutableListSequence<int>();
        case IMMUTABLE_LIST:  return new ImmutableListSequence<int>();
    }
    return nullptr;
}

Sequence<int>* createFromArray(SeqType type, int* items, int count) {
    switch (type) {
        case MUTABLE_ARRAY:   return new MutableArraySequence<int>(items, count);
        case IMMUTABLE_ARRAY: return new ImmutableArraySequence<int>(items, count);
        case MUTABLE_LIST:    return new MutableListSequence<int>(items, count);
        case IMMUTABLE_LIST:  return new ImmutableListSequence<int>(items, count);
    }
    return nullptr;
}

void printSequence(Sequence<int>* seq) {
    seq->print();
}

void demonstrateEnumerator(Sequence<int>* seq) {
    IEnumerator<int>* en = seq->getEnumerator();
    std::cout << "Перебор через энумератор: ";
    while (en->moveNext()) {
        std::cout << en->current() << " ";
    }
    std::cout << std::endl;
    delete en;
}

void workWithSequence(Sequence<int>*& seq, SeqType /*type*/) {
    int running = 1;
    while (running) {
        std::cout << "\n=== ТЕКУЩАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ===\n";
        printSequence(seq);
        std::cout << "Размер: " << seq->getLength() << std::endl;
        
        std::cout << "\n=== МЕНЮ ОПЕРАЦИЙ ===\n";
        std::cout << "1  - Append\n";
        std::cout << "2  - Prepend\n";
        std::cout << "3  - InsertAt\n";
        std::cout << "4  - Get\n";
        std::cout << "5  - GetFirst / GetLast\n";
        std::cout << "6  - Clear\n";
        std::cout << "7  - Concat\n";
        std::cout << "8  - GetSubsequence\n";
        std::cout << "9  - Map\n";
        std::cout << "10 - Reduce\n";
        std::cout << "11 - Where\n";
        std::cout << "12 - Энумератор\n";
        std::cout << "0  - Выход\n";
        std::cout << "> ";
        
        int choice = readInt("");
        
        try {
            switch (choice) {
                case 1: {
                    int val = readInt("Введите целое число: ");
                    Sequence<int>* newSeq = seq->append(val);
                    if (newSeq != seq) {
                        delete seq;
                        seq = newSeq;
                    }
                    std::cout << "✅ Append выполнен\n";
                    break;
                }
                case 2: {
                    int val = readInt("Введите целое число: ");
                    Sequence<int>* newSeq = seq->prepend(val);
                    if (newSeq != seq) {
                        delete seq;
                        seq = newSeq;
                    }
                    std::cout << "✅ Prepend выполнен\n";
                    break;
                }
                case 3: {
                    int val = readInt("Введите целое число: ");
                    int idx = readInt("Введите индекс: ");
                    Sequence<int>* newSeq = seq->insertAt(val, idx);
                    if (newSeq != seq) {
                        delete seq;
                        seq = newSeq;
                    }
                    std::cout << "✅ InsertAt выполнен\n";
                    break;
                }
                case 4: {
                    int idx = readInt("Введите индекс: ");
                    std::cout << "Элемент [" << idx << "] = " << seq->get(idx) << std::endl;
                    break;
                }
                case 5: {
                    std::cout << "First: " << seq->getFirst() << ", Last: " << seq->getLast() << std::endl;
                    break;
                }
                case 6: {
                    Sequence<int>* newSeq = seq->clear();
                    if (newSeq != seq) {
                        delete seq;
                        seq = newSeq;
                    }
                    std::cout << "✅ Очищено\n";
                    break;
                }
                case 7: {
                    std::cout << "Создайте последовательность для сцепления:\n";
                    SeqType otherType = chooseSequenceType();
                    if (otherType >= 0 && otherType <= 3) {
                        Sequence<int>* other = createEmptySequence(otherType);
                        other = other->append(100)->append(200)->append(300);
                        std::cout << "Другая последовательность: ";
                        printSequence(other);
                        Sequence<int>* newSeq = seq->concat(other);
                        std::cout << "Результат concat: ";
                        printSequence(newSeq);
                        delete other;
                        char ans;
                        std::cout << "Заменить текущую? (y/n): ";
                        std::cin >> ans;
                        clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq;
                            seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                    break;
                }
                case 8: {
                    int start = readInt("Введите startIndex: ");
                    int end = readInt("Введите endIndex: ");
                    Sequence<int>* sub = seq->getSubsequence(start, end);
                    std::cout << "Подпоследовательность: ";
                    printSequence(sub);
                    char ans;
                    std::cout << "Заменить текущую? (y/n): ";
                    std::cin >> ans;
                    clearInput();
                    if (ans == 'y' || ans == 'Y') {
                        delete seq;
                        seq = sub;
                        std::cout << "✅ Заменено\n";
                    } else {
                        delete sub;
                    }
                    break;
                }
                case 9: {
                    std::cout << "Выберите функцию map:\n1 - квадрат\n2 - куб\n3 - прибавить 10\n";
                    int mchoice = readInt("> ");
                    Sequence<int>* newSeq = nullptr;
                    if (auto* arr = dynamic_cast<ArraySequence<int>*>(seq)) {
                        if (mchoice == 1) newSeq = arr->map(square);
                        else if (mchoice == 2) newSeq = arr->map(cube);
                        else newSeq = arr->map(add10);
                    } else if (auto* lst = dynamic_cast<ListSequence<int>*>(seq)) {
                        if (mchoice == 1) newSeq = lst->map(square);
                        else if (mchoice == 2) newSeq = lst->map(cube);
                        else newSeq = lst->map(add10);
                    }
                    if (newSeq) {
                        std::cout << "Результат map: ";
                        printSequence(newSeq);
                        char ans;
                        std::cout << "Заменить текущую? (y/n): ";
                        std::cin >> ans;
                        clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq;
                            seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                    break;
                }
                case 10: {
                    std::cout << "Выберите reduce:\n1 - сумма\n2 - произведение\n";
                    int rchoice = readInt("> ");
                    int init = (rchoice == 1) ? 0 : 1;
                    int result = 0;
                    if (auto* arr = dynamic_cast<ArraySequence<int>*>(seq)) {
                        result = arr->reduce(rchoice == 1 ? sum : product, init);
                    } else if (auto* lst = dynamic_cast<ListSequence<int>*>(seq)) {
                        result = lst->reduce(rchoice == 1 ? sum : product, init);
                    }
                    std::cout << "Результат reduce: " << result << std::endl;
                    break;
                }
                case 11: {
                    std::cout << "Выберите where:\n1 - четные\n2 - нечетные\n3 - больше 5\n";
                    int wchoice = readInt("> ");
                    Sequence<int>* newSeq = nullptr;
                    if (auto* arr = dynamic_cast<ArraySequence<int>*>(seq)) {
                        if (wchoice == 1) newSeq = arr->where(isEven);
                        else if (wchoice == 2) newSeq = arr->where(isOdd);
                        else newSeq = arr->where(greaterThan5);
                    } else if (auto* lst = dynamic_cast<ListSequence<int>*>(seq)) {
                        if (wchoice == 1) newSeq = lst->where(isEven);
                        else if (wchoice == 2) newSeq = lst->where(isOdd);
                        else newSeq = lst->where(greaterThan5);
                    }
                    if (newSeq) {
                        std::cout << "Результат where: ";
                        printSequence(newSeq);
                        char ans;
                        std::cout << "Заменить текущую? (y/n): ";
                        std::cin >> ans;
                        clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq;
                            seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                    break;
                }
                case 12: {
                    demonstrateEnumerator(seq);
                    break;
                }
                case 0:
                    running = 0;
                    break;
                default:
                    std::cout << "Неверный выбор\n";
            }
        } catch (const IndexOutOfRange&) {
            std::cout << "❌ Ошибка: индекс вне диапазона!\n";
        } catch (const std::exception& e) {
            std::cout << "❌ Ошибка: " << e.what() << std::endl;
        }
    }
}

void console_menu_mode() {
    std::cout << "=== Лабораторная работа №2 ===\n";
    int programRunning = 1;
    while (programRunning) {
        SeqType type = chooseSequenceType();
        if (type == MUTABLE_ARRAY || type == IMMUTABLE_ARRAY || type == MUTABLE_LIST || type == IMMUTABLE_LIST) {
            std::cout << "Создать последовательность с тестовыми данными? (y/n): ";
            char ans;
            std::cin >> ans;
            clearInput();
            Sequence<int>* seq = nullptr;
            if (ans == 'y' || ans == 'Y') {
                int testData[] = {1, 2, 3, 4, 5};
                seq = createFromArray(type, testData, 5);
            } else {
                seq = createEmptySequence(type);
            }
            workWithSequence(seq, type);
            delete seq;
        } else {
            programRunning = 0;
        }
    }
    std::cout << "Программа завершена.\n";
}