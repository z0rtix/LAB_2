#include "menu.h"
#include "ArraySequence.h"
#include "ListSequence.h"

#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <algorithm>

// -------------------------------------------------------------
// Вспомогательные функции для ввода/очистки
// -------------------------------------------------------------
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

std::string readString(const std::string& prompt) {
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}

// -------------------------------------------------------------
// Функции для работы с int (map, where, reduce)
// -------------------------------------------------------------
int square(int x) { return x * x; }
int cube(int x) { return x * x * x; }
int add10(int x) { return x + 10; }

bool isEven(int x) { return x % 2 == 0; }
bool isOdd(int x) { return x % 2 != 0; }
bool greaterThan5(int x) { return x > 5; }

int sum(int acc, int x) { return acc + x; }
int product(int acc, int x) { return acc * x; }

// -------------------------------------------------------------
// Функции для работы с string (map, where, reduce)
// -------------------------------------------------------------
std::string toUpper(const std::string& s) {
    std::string res = s;
    for (char& c : res) c = std::toupper(c);
    return res;
}
std::string addExclamation(const std::string& s) { return s + "!"; }
std::string reverse(const std::string& s) {
    std::string res = s;
    std::reverse(res.begin(), res.end());
    return res;
}

bool lengthGreater3(const std::string& s) { return s.length() > 3; }
bool startsWithA(const std::string& s) {
    if (s.empty()) return false;
    char c = std::tolower(s[0]);
    return c == 'a';
}
bool containsE(const std::string& s) {
    for (char c : s) if (std::tolower(c) == 'e') return true;
    return false;
}

// Reduce для строк: конкатенация через пробел
std::string concatStrings(const std::string& acc, const std::string& s) {
    if (acc.empty()) return s;
    return acc + " " + s;
}
// Альтернативный reduce: сумма длин
int totalLength(int acc, const std::string& s) { return acc + s.length(); }

// -------------------------------------------------------------
// Перечисление типов последовательностей
// -------------------------------------------------------------
enum SeqType { MUTABLE_ARRAY, IMMUTABLE_ARRAY, MUTABLE_LIST, IMMUTABLE_LIST, EXIT_PROGRAM };

SeqType chooseSequenceType() {
    std::cout << "\n=== ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ ===\n";
    std::cout << "1 - MutableArraySequence\n";
    std::cout << "2 - ImmutableArraySequence\n";
    std::cout << "3 - MutableListSequence\n";
    std::cout << "4 - ImmutableListSequence\n";
    std::cout << "0 - Выход из программы\n";
    int choice = readInt("> ");
    switch (choice) {
        case 1: return MUTABLE_ARRAY;
        case 2: return IMMUTABLE_ARRAY;
        case 3: return MUTABLE_LIST;
        case 4: return IMMUTABLE_LIST;
        default: return EXIT_PROGRAM;
    }
}

// Создание пустой последовательности (для int)
Sequence<int>* createEmptySequenceInt(SeqType type) {
    switch (type) {
        case MUTABLE_ARRAY:   return new MutableArraySequence<int>();
        case IMMUTABLE_ARRAY: return new ImmutableArraySequence<int>();
        case MUTABLE_LIST:    return new MutableListSequence<int>();
        case IMMUTABLE_LIST:  return new ImmutableListSequence<int>();
        default: return nullptr;
    }
}
// Создание из массива int
Sequence<int>* createFromArrayInt(SeqType type, int* items, int count) {
    switch (type) {
        case MUTABLE_ARRAY:   return new MutableArraySequence<int>(items, count);
        case IMMUTABLE_ARRAY: return new ImmutableArraySequence<int>(items, count);
        case MUTABLE_LIST:    return new MutableListSequence<int>(items, count);
        case IMMUTABLE_LIST:  return new ImmutableListSequence<int>(items, count);
        default: return nullptr;
    }
}

// Аналогично для string
Sequence<std::string>* createEmptySequenceString(SeqType type) {
    switch (type) {
        case MUTABLE_ARRAY:   return new MutableArraySequence<std::string>();
        case IMMUTABLE_ARRAY: return new ImmutableArraySequence<std::string>();
        case MUTABLE_LIST:    return new MutableListSequence<std::string>();
        case IMMUTABLE_LIST:  return new ImmutableListSequence<std::string>();
        default: return nullptr;
    }
}
Sequence<std::string>* createFromArrayString(SeqType type, std::string* items, int count) {
    switch (type) {
        case MUTABLE_ARRAY:   return new MutableArraySequence<std::string>(items, count);
        case IMMUTABLE_ARRAY: return new ImmutableArraySequence<std::string>(items, count);
        case MUTABLE_LIST:    return new MutableListSequence<std::string>(items, count);
        case IMMUTABLE_LIST:  return new ImmutableListSequence<std::string>(items, count);
        default: return nullptr;
    }
}

// -------------------------------------------------------------
// Работа с последовательностью для типа int
// -------------------------------------------------------------
void printSequenceInt(Sequence<int>* seq) { seq->print(); }

void demonstrateEnumeratorInt(Sequence<int>* seq) {
    IEnumerator<int>* en = seq->getEnumerator();
    std::cout << "Перебор через энумератор: ";
    while (en->moveNext()) std::cout << en->current() << " ";
    std::cout << std::endl;
    delete en;
}

void workWithSequenceInt(Sequence<int>*& seq) {
    int running = 1;
    while (running) {
        std::cout << "\n=== ТЕКУЩАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ (int) ===\n";
        printSequenceInt(seq);
        std::cout << "Размер: " << seq->getLength() << std::endl;

        std::cout << "\n=== МЕНЮ ОПЕРАЦИЙ ===\n";
        std::cout << "1  - Append\n2  - Prepend\n3  - InsertAt\n4  - Get\n";
        std::cout << "5  - GetFirst / GetLast\n6  - Clear\n";
        std::cout << "7  - GetSubsequence\n8  - Map\n9  - Reduce\n10 - Where\n";
        std::cout << "11 - Энумератор\n0  - Выйти к выбору типа последовательности\n> ";

        int choice = readInt("");
        try {
            switch (choice) {
                case 1: {
                    int val = readInt("Введите целое число: ");
                    Sequence<int>* newSeq = seq->append(val);
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Append выполнен\n";
                    break;
                }
                case 2: {
                    int val = readInt("Введите целое число: ");
                    Sequence<int>* newSeq = seq->prepend(val);
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Prepend выполнен\n";
                    break;
                }
                case 3: {
                    int val = readInt("Введите целое число: ");
                    int idx = readInt("Введите индекс: ");
                    Sequence<int>* newSeq = seq->insertAt(val, idx);
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ InsertAt выполнен\n";
                    break;
                }
                case 4: {
                    int idx = readInt("Введите индекс: ");
                    std::cout << "Элемент [" << idx << "] = " << seq->get(idx) << std::endl;
                    break;
                }
                case 5:
                    std::cout << "First: " << seq->getFirst() << ", Last: " << seq->getLast() << std::endl;
                    break;
                case 6: {
                    Sequence<int>* newSeq = seq->clear();
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Очищено\n";
                    break;
                }
                case 7: {
                    int start = readInt("Введите startIndex: ");
                    int end = readInt("Введите endIndex: ");
                    Sequence<int>* sub = seq->getSubsequence(start, end);
                    std::cout << "Подпоследовательность: "; printSequenceInt(sub);
                    char ans;
                    std::cout << "Заменить текущую? (y/n): "; std::cin >> ans; clearInput();
                    if (ans == 'y' || ans == 'Y') { delete seq; seq = sub; std::cout << "✅ Заменено\n"; }
                    else { delete sub; std::cout << "✅ Не заменено\n"; }
                    break;
                }
                case 8: {
                    std::cout << "1 - квадрат\n2 - куб\n3 - прибавить 10\n";
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
                        std::cout << "Результат map: "; printSequenceInt(newSeq);
                        char ans;
                        std::cout << "Заменить текущую? (y/n): "; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') { delete seq; seq = newSeq; std::cout << "✅ Заменено\n"; }
                        else { delete newSeq; std::cout << "✅ Не заменено\n"; }
                    }
                    break;
                }
                case 9: {
                    std::cout << "1 - сумма\n2 - произведение\n";
                    int rchoice = readInt("> ");
                    int init = (rchoice == 1) ? 0 : 1;
                    int result = 0;
                    if (auto* arr = dynamic_cast<ArraySequence<int>*>(seq))
                        result = arr->reduce(rchoice == 1 ? sum : product, init);
                    else if (auto* lst = dynamic_cast<ListSequence<int>*>(seq))
                        result = lst->reduce(rchoice == 1 ? sum : product, init);
                    std::cout << "Результат reduce: " << result << std::endl;
                    break;
                }
                case 10: {
                    std::cout << "1 - четные\n2 - нечетные\n3 - больше 5\n";
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
                        std::cout << "Результат where: "; printSequenceInt(newSeq);
                        char ans;
                        std::cout << "Заменить текущую? (y/n): "; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') { delete seq; seq = newSeq; std::cout << "✅ Заменено\n"; }
                        else { delete newSeq; std::cout << "✅ Не заменено\n"; }
                    }
                    break;
                }
                case 11:
                    demonstrateEnumeratorInt(seq);
                    break;
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

// -------------------------------------------------------------
// Работа с последовательностью для типа string
// -------------------------------------------------------------
void printSequenceString(Sequence<std::string>* seq) { seq->print(); }

void demonstrateEnumeratorString(Sequence<std::string>* seq) {
    IEnumerator<std::string>* en = seq->getEnumerator();
    std::cout << "Перебор через энумератор: ";
    while (en->moveNext()) std::cout << en->current() << " ";
    std::cout << std::endl;
    delete en;
}

void workWithSequenceString(Sequence<std::string>*& seq) {
    int running = 1;
    while (running) {
        std::cout << "\n=== ТЕКУЩАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ (string) ===\n";
        printSequenceString(seq);
        std::cout << "Размер: " << seq->getLength() << std::endl;

        std::cout << "\n=== МЕНЮ ОПЕРАЦИЙ ===\n";
        std::cout << "1  - Append\n2  - Prepend\n3  - InsertAt\n4  - Get\n";
        std::cout << "5  - GetFirst / GetLast\n6  - Clear\n";
        std::cout << "7  - GetSubsequence\n8  - Map\n9  - Reduce\n10 - Where\n";
        std::cout << "11 - Энумератор\n0  - Выйти к выбору типа последовательности\n> ";

        int choice = readInt("");
        try {
            switch (choice) {
                case 1: {
                    std::string val = readString("Введите строку: ");
                    Sequence<std::string>* newSeq = seq->append(val);
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Append выполнен\n";
                    break;
                }
                case 2: {
                    std::string val = readString("Введите строку: ");
                    Sequence<std::string>* newSeq = seq->prepend(val);
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Prepend выполнен\n";
                    break;
                }
                case 3: {
                    std::string val = readString("Введите строку: ");
                    int idx = readInt("Введите индекс: ");
                    Sequence<std::string>* newSeq = seq->insertAt(val, idx);
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ InsertAt выполнен\n";
                    break;
                }
                case 4: {
                    int idx = readInt("Введите индекс: ");
                    std::cout << "Элемент [" << idx << "] = " << seq->get(idx) << std::endl;
                    break;
                }
                case 5:
                    std::cout << "First: " << seq->getFirst() << ", Last: " << seq->getLast() << std::endl;
                    break;
                case 6: {
                    Sequence<std::string>* newSeq = seq->clear();
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Очищено\n";
                    break;
                }
                case 7: {
                    int start = readInt("Введите startIndex: ");
                    int end = readInt("Введите endIndex: ");
                    Sequence<std::string>* sub = seq->getSubsequence(start, end);
                    std::cout << "Подпоследовательность: "; printSequenceString(sub);
                    char ans;
                    std::cout << "Заменить текущую? (y/n): "; std::cin >> ans; clearInput();
                    if (ans == 'y' || ans == 'Y') { delete seq; seq = sub; std::cout << "✅ Заменено\n"; }
                    else { delete sub; std::cout << "✅ Не заменено\n"; }
                    break;
                }
                case 8: {
                    std::cout << "1 - в верхний регистр\n2 - добавить '!'\n3 - перевернуть\n";
                    int mchoice = readInt("> ");
                    Sequence<std::string>* newSeq = nullptr;
                    if (auto* arr = dynamic_cast<ArraySequence<std::string>*>(seq)) {
                        if (mchoice == 1) newSeq = arr->map(toUpper);
                        else if (mchoice == 2) newSeq = arr->map(addExclamation);
                        else newSeq = arr->map(reverse);
                    } else if (auto* lst = dynamic_cast<ListSequence<std::string>*>(seq)) {
                        if (mchoice == 1) newSeq = lst->map(toUpper);
                        else if (mchoice == 2) newSeq = lst->map(addExclamation);
                        else newSeq = lst->map(reverse);
                    }
                    if (newSeq) {
                        std::cout << "Результат map: "; printSequenceString(newSeq);
                        char ans;
                        std::cout << "Заменить текущую? (y/n): "; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') { delete seq; seq = newSeq; std::cout << "✅ Заменено\n"; }
                        else { delete newSeq; std::cout << "✅ Не заменено\n"; }
                    }
                    break;
                }
                case 9: {
                    std::cout << "1 - конкатенация через пробел\n2 - суммарная длина строк\n";
                    int rchoice = readInt("> ");
                    if (rchoice == 1) {
                        std::string result;
                        if (auto* arr = dynamic_cast<ArraySequence<std::string>*>(seq))
                            result = arr->reduce(concatStrings, std::string(""));
                        else if (auto* lst = dynamic_cast<ListSequence<std::string>*>(seq))
                            result = lst->reduce(concatStrings, std::string(""));
                        std::cout << "Результат reduce: " << result << std::endl;
                    } else {
                        int total = 0;
                        if (auto* arr = dynamic_cast<ArraySequence<std::string>*>(seq))
                            total = arr->reduce(totalLength, 0);
                        else if (auto* lst = dynamic_cast<ListSequence<std::string>*>(seq))
                            total = lst->reduce(totalLength, 0);
                        std::cout << "Суммарная длина строк: " << total << std::endl;
                    }
                    break;
                }
                case 10: {
                    std::cout << "1 - длина > 3\n2 - начинается с A/a\n3 - содержит 'e'\n";
                    int wchoice = readInt("> ");
                    Sequence<std::string>* newSeq = nullptr;
                    if (auto* arr = dynamic_cast<ArraySequence<std::string>*>(seq)) {
                        if (wchoice == 1) newSeq = arr->where(lengthGreater3);
                        else if (wchoice == 2) newSeq = arr->where(startsWithA);
                        else newSeq = arr->where(containsE);
                    } else if (auto* lst = dynamic_cast<ListSequence<std::string>*>(seq)) {
                        if (wchoice == 1) newSeq = lst->where(lengthGreater3);
                        else if (wchoice == 2) newSeq = lst->where(startsWithA);
                        else newSeq = lst->where(containsE);
                    }
                    if (newSeq) {
                        std::cout << "Результат where: "; printSequenceString(newSeq);
                        char ans;
                        std::cout << "Заменить текущую? (y/n): "; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') { delete seq; seq = newSeq; std::cout << "✅ Заменено\n"; }
                        else { delete newSeq; std::cout << "✅ Не заменено\n"; }
                    }
                    break;
                }
                case 11:
                    demonstrateEnumeratorString(seq);
                    break;
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

// -------------------------------------------------------------
// Главная функция консольного меню
// -------------------------------------------------------------
void console_menu_mode() {
    std::cout << "=== Лабораторная работа №2 ===\n";
    while (true) {
        std::cout << "\n=== ВЫБОР ТИПА ДАННЫХ ===\n";
        std::cout << "1 - int\n2 - string\n0 - Выход\n> ";
        int dataType = readInt("");
        if (dataType == 0) break;

        SeqType seqType = chooseSequenceType();
        if (seqType == EXIT_PROGRAM) break;

        if (dataType == 1) {
            // Работа с int
            std::cout << "Создать последовательность с тестовыми данными [1,2,3,4,5]? (y/n): ";
            char ans; std::cin >> ans; clearInput();
            Sequence<int>* seq = nullptr;
            if (ans == 'y' || ans == 'Y') {
                int testData[] = {1, 2, 3, 4, 5};
                seq = createFromArrayInt(seqType, testData, 5);
            } else {
                seq = createEmptySequenceInt(seqType);
            }
            workWithSequenceInt(seq);
            delete seq;
        } else if (dataType == 2) {
            // Работа со string
            std::cout << "Создать последовательность с тестовыми данными [\"apple\", \"banana\", \"cherry\"]? (y/n): ";
            char ans; std::cin >> ans; clearInput();
            Sequence<std::string>* seq = nullptr;
            if (ans == 'y' || ans == 'Y') {
                std::string testData[] = {"apple", "banana", "cherry"};
                seq = createFromArrayString(seqType, testData, 3);
            } else {
                seq = createEmptySequenceString(seqType);
            }
            workWithSequenceString(seq);
            delete seq;
        }
    }
    std::cout << "Программа завершена.\n";
}