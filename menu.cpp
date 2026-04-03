#include "menu.h"
#include "ArraySequence.h"
#include "ListSequence.h"

#include <iostream>
#include <limits>
#include <string>


void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const std::string& prompt) {
    int val;
    std::cout << prompt;
    while (!(std::cin >> val)) {
        std::cout << "Ошибка, введите число: ";
        clearInput();
    }
    clearInput();
    return val;
}

std::string readString(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::getline(std::cin, val);
    return val;
}


int square(int x) { return x * x; }
int cube(int x) { return x * x * x; }
int add10(int x) { return x + 10; }

bool isEven(int x) { return x % 2 == 0; }
bool isOdd(int x) { return x % 2 != 0; }
bool greater5(int x) { return x > 5; }

int sum(int a, int b) { return a + b; }
int mult(int a, int b) { return a * b; }


std::string toUpper(const std::string& s) {
    std::string res = s;
    for (char& c : res) c = toupper(c);
    return res;
}
std::string addBang(const std::string& s) { return s + "!"; }
std::string rev(const std::string& s) {
    std::string res = s;
    int i = 0, j = res.size()-1;
    while (i < j) { char t = res[i]; res[i] = res[j]; res[j] = t; i++; j--; }
    return res;
}


bool longer3(const std::string& s) { return s.size() > 3; }
bool startsA(const std::string& s) { return !s.empty() && (s[0]=='a'||s[0]=='A'); }
bool hasE(const std::string& s) {
    for (char c : s) if (c=='e'||c=='E') return true;
    return false;
}


std::string concatSpace(const std::string& a, const std::string& b) {
    if (a.empty()) return b;
    return a + " " + b;
}

int sumLen(int acc, const std::string& s) { return acc + s.size(); }
int chooseDataType() {
    std::cout << "\n=== ВЫБОР ТИПА ДАННЫХ ===\n";
    std::cout << "1 - int\n2 - string\n0 - Выход\n";
    return readInt("> ");
}
int chooseType() {
    std::cout << "\n=== ВЫБОР ТИПА ПОСЛЕДОВАТЕЛЬНОСТИ ===\n";
    std::cout << "1 - MutableArray\n";
    std::cout << "2 - ImmutableArray\n";
    std::cout << "3 - MutableList\n";
    std::cout << "4 - ImmutableList\n";
    std::cout << "0 - Назад\n";
    return readInt("> ");
}

Sequence<int> *createEmptyInt(int type) {
    switch (type) {
        case 1: return new MutableArraySequence<int>();
        case 2: return new ImmutableArraySequence<int>();
        case 3: return new MutableListSequence<int>();
        case 4: return new ImmutableListSequence<int>();
        default: return nullptr;
    }
}

Sequence<int> *createFromArrayInt(int type, int *arr, int size) {
    switch (type) {
        case 1: return new MutableArraySequence<int>(arr, size);
        case 2: return new ImmutableArraySequence<int>(arr, size);
        case 3: return new MutableListSequence<int>(arr, size);
        case 4: return new ImmutableListSequence<int>(arr, size);
        default: return nullptr;
    }
}

Sequence<std::string> *createEmptyString(int type) {
    switch (type) {
        case 1: return new MutableArraySequence<std::string>();
        case 2: return new ImmutableArraySequence<std::string>();
        case 3: return new MutableListSequence<std::string>();
        case 4: return new ImmutableListSequence<std::string>();
        default: return nullptr;
    }
}

Sequence<std::string> *createFromArrayString(int type, std::string *arr, int size) {
    switch (type) {
        case 1: return new MutableArraySequence<std::string>(arr, size);
        case 2: return new ImmutableArraySequence<std::string>(arr, size);
        case 3: return new MutableListSequence<std::string>(arr, size);
        case 4: return new ImmutableListSequence<std::string>(arr, size);
        default: return nullptr;
    }
}

void showInt(Sequence<int> *seq) { seq->print(); }
void showString(Sequence<std::string> *seq) { seq->print(); }
void showEnumeratorInt(Sequence<int> *seq) {
    IEnumerator<int> *en = seq->getEnumerator();
    std::cout << "Перебор: ";
    while (en->moveNext()) std::cout << en->current() << " ";
    std::cout << std::endl;
    delete en;
}
void showEnumeratorString(Sequence<std::string> *seq) {
    IEnumerator<std::string> *en = seq->getEnumerator();
    std::cout << "Перебор: ";
    while (en->moveNext()) std::cout << en->current() << " ";
    std::cout << std::endl;
    delete en;
}
void workInt(Sequence<int>*& seq, bool isMutable) {
    int run = 1;
    while (run) {
        std::cout << "\n=== ТЕКУЩАЯ (int) ===\n";
        showInt(seq);
        std::cout << "Размер: " << seq->getLength() << "\n";

        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1  - Добавить в конец (append)\n";
        std::cout << "2  - Добавить в начало (prepend)\n";
        std::cout << "3  - Вставить по индексу (insertAt)\n";
        std::cout << "4  - Получить элемент (get)\n";
        std::cout << "5  - Первый и последний (getFirst/getLast)\n";
        std::cout << "6  - Очистить (clear)\n";
        std::cout << "7  - Взять подпоследовательность (getSubsequence)\n";
        std::cout << "8  - Применить функцию (map)\n";
        std::cout << "9  - Свернуть (reduce)\n";
        std::cout << "10 - Отфильтровать (where)\n";
        std::cout << "11 - Энумератор\n";
        std::cout << "0  - Выйти\n";
        int cmd = readInt("> ");

        try {
            if (cmd == 0) { run = 0; continue; }

            if (cmd == 1 || cmd == 2 || cmd == 3 || cmd == 6) {
                Sequence<int> *newSeq = nullptr;
                if (cmd == 1) {
                    int val = readInt("Число: ");
                    newSeq = seq->append(val);
                } else if (cmd == 2) {
                    int val = readInt("Число: ");
                    newSeq = seq->prepend(val);
                } else if (cmd == 3) {
                    int val = readInt("Число: ");
                    int idx = readInt("Индекс: ");
                    newSeq = seq->insertAt(val, idx);
                } else if (cmd == 6) {
                    newSeq = seq->clear();
                }

                if (isMutable) {
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Готово\n";
                } else {
                    std::cout << "Текущая: "; showInt(seq);
                    std::cout << "Новая:  "; showInt(newSeq);
                    std::cout << "Заменить текущую на новую? (y/n): ";
                    char ans; std::cin >> ans; clearInput();
                    if (ans == 'y' || ans == 'Y') {
                        delete seq; seq = newSeq;
                        std::cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        std::cout << "✅ Оставлена текущая\n";
                    }
                }
            }
            else if (cmd == 4) {
                int idx = readInt("Индекс: ");
                std::cout << "Элемент: " << seq->get(idx) << std::endl;
            }
            else if (cmd == 5) {
                std::cout << "Первый: " << seq->getFirst() << ", Последний: " << seq->getLast() << std::endl;
            }
            else if (cmd == 7) {
                int start = readInt("Начальный индекс: ");
                int end = readInt("Конечный индекс: ");
                Sequence<int> *sub = seq->getSubsequence(start, end);
                std::cout << "Подпоследовательность: "; showInt(sub);
                if (isMutable) {
                    delete sub;
                } else {
                    std::cout << "Заменить текущую на подпоследовательность? (y/n): ";
                    char ans; std::cin >> ans; clearInput();
                    if (ans == 'y' || ans == 'Y') {
                        delete seq; seq = sub;
                        std::cout << "✅ Заменено\n";
                    } else {
                        delete sub;
                    }
                }
            }
            else if (cmd == 8) {
                std::cout << "1 - квадрат\n2 - куб\n3 - +10\n";
                int opt = readInt("> ");
                Sequence<int> *newSeq = nullptr;
                if (auto *a = dynamic_cast<ArraySequence<int>*>(seq)) {
                    if (opt == 1) newSeq = a->map(square);
                    else if (opt == 2) newSeq = a->map(cube);
                    else newSeq = a->map(add10);
                } else if (auto *l = dynamic_cast<ListSequence<int>*>(seq)) {
                    if (opt == 1) newSeq = l->map(square);
                    else if (opt == 2) newSeq = l->map(cube);
                    else newSeq = l->map(add10);
                }
                if (newSeq) {
                    std::cout << "Результат map: "; showInt(newSeq);
                    if (isMutable) {
                        delete newSeq;
                    } else {
                        std::cout << "Заменить текущую? (y/n): ";
                        char ans; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq; seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                }
            }
            else if (cmd == 9) {
                std::cout << "1 - сумма\n2 - произведение\n";
                int opt = readInt("> ");
                int init = (opt == 1) ? 0 : 1;
                int res = 0;
                if (auto *a = dynamic_cast<ArraySequence<int>*>(seq))
                    res = a->reduce((opt == 1) ? sum : mult, init);
                else if (auto *l = dynamic_cast<ListSequence<int>*>(seq))
                    res = l->reduce((opt == 1) ? sum : mult, init);
                std::cout << "Результат: " << res << std::endl;
            }
            else if (cmd == 10) {
                std::cout << "1 - четные\n2 - нечетные\n3 - больше 5\n";
                int opt = readInt("> ");
                Sequence<int> *newSeq = nullptr;
                if (auto *a = dynamic_cast<ArraySequence<int>*>(seq)) {
                    if (opt == 1) newSeq = a->where(isEven);
                    else if (opt == 2) newSeq = a->where(isOdd);
                    else newSeq = a->where(greater5);
                } else if (auto *l = dynamic_cast<ListSequence<int>*>(seq)) {
                    if (opt == 1) newSeq = l->where(isEven);
                    else if (opt == 2) newSeq = l->where(isOdd);
                    else newSeq = l->where(greater5);
                }
                if (newSeq) {
                    std::cout << "Результат where: "; showInt(newSeq);
                    if (isMutable) {
                        delete newSeq;
                    } else {
                        std::cout << "Заменить текущую? (y/n): ";
                        char ans; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq; seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                }
            }
            else if (cmd == 11) {
                showEnumeratorInt(seq);
            }
            else {
                std::cout << "Неверная команда\n";
            }
        } catch (const IndexOutOfRange&) {
            std::cout << "Ошибка: индекс вне границ!\n";
        }
    }
}

void workString(Sequence<std::string>*& seq, bool isMutable) {
    int run = 1;
    while (run) {
        std::cout << "\n=== ТЕКУЩАЯ (string) ===\n";
        showString(seq);
        std::cout << "Размер: " << seq->getLength() << "\n";

        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1  - Добавить в конец (append)\n";
        std::cout << "2  - Добавить в начало (prepend)\n";
        std::cout << "3  - Вставить по индексу (insertAt)\n";
        std::cout << "4  - Получить элемент (get)\n";
        std::cout << "5  - Первый и последний (getFirst/getLast)\n";
        std::cout << "6  - Очистить (clear)\n";
        std::cout << "7  - Взять подпоследовательность (getSubsequence)\n";
        std::cout << "8  - Применить функцию (map)\n";
        std::cout << "9  - Свернуть (reduce)\n";
        std::cout << "10 - Отфильтровать (where)\n";
        std::cout << "11 - Энумератор\n";
        std::cout << "0  - Выйти\n";
        int cmd = readInt("> ");

        try {
            if (cmd == 0) { run = 0; continue; }

            if (cmd == 1 || cmd == 2 || cmd == 3 || cmd == 6) {
                Sequence<std::string> *newSeq = nullptr;
                if (cmd == 1) {
                    std::string val = readString("Строка: ");
                    newSeq = seq->append(val);
                } else if (cmd == 2) {
                    std::string val = readString("Строка: ");
                    newSeq = seq->prepend(val);
                } else if (cmd == 3) {
                    std::string val = readString("Строка: ");
                    int idx = readInt("Индекс: ");
                    newSeq = seq->insertAt(val, idx);
                } else if (cmd == 6) {
                    newSeq = seq->clear();
                }

                if (isMutable) {
                    if (newSeq != seq) { delete seq; seq = newSeq; }
                    std::cout << "✅ Готово\n";
                } else {
                    std::cout << "Текущая: "; showString(seq);
                    std::cout << "Новая:  "; showString(newSeq);
                    std::cout << "Заменить текущую на новую? (y/n): ";
                    char ans; std::cin >> ans; clearInput();
                    if (ans == 'y' || ans == 'Y') {
                        delete seq; seq = newSeq;
                        std::cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        std::cout << "✅ Оставлена текущая\n";
                    }
                }
            }
            else if (cmd == 4) {
                int idx = readInt("Индекс: ");
                std::cout << "Элемент: " << seq->get(idx) << std::endl;
            }
            else if (cmd == 5) {
                std::cout << "Первый: " << seq->getFirst() << ", Последний: " << seq->getLast() << std::endl;
            }
            else if (cmd == 7) {
                int start = readInt("Начальный индекс: ");
                int end = readInt("Конечный индекс: ");
                Sequence<std::string> *sub = seq->getSubsequence(start, end);
                std::cout << "Подпоследовательность: "; showString(sub);
                if (isMutable) {
                    delete sub;
                } else {
                    std::cout << "Заменить текущую на подпоследовательность? (y/n): ";
                    char ans; std::cin >> ans; clearInput();
                    if (ans == 'y' || ans == 'Y') {
                        delete seq; seq = sub;
                        std::cout << "✅ Заменено\n";
                    } else {
                        delete sub;
                    }
                }
            }
            else if (cmd == 8) {
                std::cout << "1 - в верхний регистр\n2 - добавить '!'\n3 - перевернуть\n";
                int opt = readInt("> ");
                Sequence<std::string> *newSeq = nullptr;
                if (auto *a = dynamic_cast<ArraySequence<std::string>*>(seq)) {
                    if (opt == 1) newSeq = a->map(toUpper);
                    else if (opt == 2) newSeq = a->map(addBang);
                    else newSeq = a->map(rev);
                } else if (auto *l = dynamic_cast<ListSequence<std::string>*>(seq)) {
                    if (opt == 1) newSeq = l->map(toUpper);
                    else if (opt == 2) newSeq = l->map(addBang);
                    else newSeq = l->map(rev);
                }
                if (newSeq) {
                    std::cout << "Результат map: "; showString(newSeq);
                    if (isMutable) {
                        delete newSeq;
                    } else {
                        std::cout << "Заменить текущую? (y/n): ";
                        char ans; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq; seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                }
            }
            else if (cmd == 9) {
                std::cout << "1 - конкатенация через пробел\n2 - сумма длин\n";
                int opt = readInt("> ");
                if (opt == 1) {
                    std::string res;
                    if (auto *a = dynamic_cast<ArraySequence<std::string>*>(seq))
                        res = a->reduce(concatSpace, std::string(""));
                    else if (auto *l = dynamic_cast<ListSequence<std::string>*>(seq))
                        res = l->reduce(concatSpace, std::string(""));
                    std::cout << "Результат: " << res << std::endl;
                } else {
                    int total = 0;
                    if (auto *a = dynamic_cast<ArraySequence<std::string>*>(seq))
                        total = a->reduce(sumLen, 0);
                    else if (auto *l = dynamic_cast<ListSequence<std::string>*>(seq))
                        total = l->reduce(sumLen, 0);
                    std::cout << "Сумма длин: " << total << std::endl;
                }
            }
            else if (cmd == 10) {
                std::cout << "1 - длина > 3\n2 - начинается с A/a\n3 - содержит e/E\n";
                int opt = readInt("> ");
                Sequence<std::string> *newSeq = nullptr;
                if (auto *a = dynamic_cast<ArraySequence<std::string>*>(seq)) {
                    if (opt == 1) newSeq = a->where(longer3);
                    else if (opt == 2) newSeq = a->where(startsA);
                    else newSeq = a->where(hasE);
                } else if (auto *l = dynamic_cast<ListSequence<std::string>*>(seq)) {
                    if (opt == 1) newSeq = l->where(longer3);
                    else if (opt == 2) newSeq = l->where(startsA);
                    else newSeq = l->where(hasE);
                }
                if (newSeq) {
                    std::cout << "Результат where: "; showString(newSeq);
                    if (isMutable) {
                        delete newSeq;
                    } else {
                        std::cout << "Заменить текущую? (y/n): ";
                        char ans; std::cin >> ans; clearInput();
                        if (ans == 'y' || ans == 'Y') {
                            delete seq; seq = newSeq;
                            std::cout << "✅ Заменено\n";
                        } else {
                            delete newSeq;
                        }
                    }
                }
            }
            else if (cmd == 11) {
                showEnumeratorString(seq);
            }
            else {
                std::cout << "Неверная команда\n";
            }
        } catch (const IndexOutOfRange&) {
            std::cout << "Ошибка: индекс вне границ!\n";
        }
    }
}

void startMenu() {
    std::cout << "=== КОНСОЛЬНОЕ МЕНЮ ===\n";
    while (true) {
        int dataType = chooseDataType();
        if (dataType == 0) break;
        if (dataType != 1 && dataType != 2) continue;

        int type = chooseType();
        if (type == 0) continue;
        if (type < 1 || type > 4) continue;

        bool mutableFlag = (type == 1 || type == 3);

        if (dataType == 1) {
            std::cout << "Создать с тестовыми данными [1,2,3,4,5]? (y/n): ";
            char ans; std::cin >> ans; clearInput();
            Sequence<int> *seq = nullptr;
            if (ans == 'y' || ans == 'Y') {
                int test[] = {1,2,3,4,5};
                seq = createFromArrayInt(type, test, 5);
            } else {
                seq = createEmptyInt(type);
            }
            workInt(seq, mutableFlag);
            delete seq;
        } else {
            std::cout << "Создать с тестовыми данными [\"apple\",\"banana\",\"cherry\"]? (y/n): ";
            char ans; std::cin >> ans; clearInput();
            Sequence<std::string> *seq = nullptr;
            if (ans == 'y' || ans == 'Y') {
                std::string test[] = {"apple","banana","cherry"};
                seq = createFromArrayString(type, test, 3);
            } else {
                seq = createEmptyString(type);
            }
            workString(seq, mutableFlag);
            delete seq;
        }
    }
    std::cout << "Программа завершена!\n";
}