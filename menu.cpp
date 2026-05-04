#include "menu.h"
#include "ArraySequence.h"
#include "ListSequence.h"

#include <iostream>
#include <limits>
#include <string>
#include <functional>


using namespace std;


void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readInt(const string &prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val)) {
        cout << "Ошибка. Введите целое число: ";
        clearInput();
    }
    clearInput();
    return val;
}

string readString(const string &prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

template <typename T>
void printSeq(Sequence<T> *seq) {
    IEnumerator<T> *en = seq->getEnumerator();
    cout << "[";
    bool first = true;
    while (en->moveNext()) {
        if (!first) cout << ", ";
        cout << en->current();
        first = false;
    }
    cout << "]\n";
    delete en;
}


void menuMutableArrayInt() {
    MutableArraySequence<int> *seq = new MutableArraySequence<int>();
    cout << "Создать с тестовыми данными [1,2,3,4,5]? (y/n): ";

    char ans; cin >> ans; clearInput();
    if (ans == 'y' || ans == 'Y') {
        seq->append(1)->append(2)->append(3)->append(4)->append(5);
    }

    int run = 1;
    while (run) {
        cout << "\n=== Текущая последовательность (MutableArray<int>) ===\n";
        printSeq(seq);
        cout << "Размер: " << seq->getLength() << "\n";
        cout << "1 - append\n2 - prepend\n3 - insertAt\n4 - removeFirst\n5 - removeLast\n6 - removeAt\n"
             << "7 - set\n8 - get\n9 - clear\n10 - map\n11 - reduce\n12 - where\n0 - сменить\n> ";
        int cmd = readInt("");

        try {
            if (cmd == 0) { delete seq; break; }
            if (cmd == 1) {
                int val = readInt("Введите int: ");
                seq->append(val);
                cout << "✅\n";
            } else if (cmd == 2) {
                int val = readInt("Введите int: ");
                seq->prepend(val);
                cout << "✅\n";
            } else if (cmd == 3) {
                int idx = readInt("Индекс: ");
                int val = readInt("Введите int: ");
                seq->insertAt(val, idx);
                cout << "✅\n";
            } else if (cmd == 4) {
                seq->removeFirst();
                cout << "✅\n";
            } else if (cmd == 5) {
                seq->removeLast();
                cout << "✅\n";
            } else if (cmd == 6) {
                int idx = readInt("Индекс: ");
                seq->removeAt(idx);
                cout << "✅\n";
            } else if (cmd == 7) {
                int idx = readInt("Индекс: ");
                int val = readInt("Новое значение: ");
                seq->set(idx, val);
                cout << "✅\n";
            } else if (cmd == 8) {
                int idx = readInt("Индекс: ");
                cout << "Элемент[" << idx << "] = " << seq->get(idx) << "\n";
            } else if (cmd == 9) {
                seq->clear();
                cout << "✅ Очищено\n";
            } else if (cmd == 10) {
                cout << "1 - квадрат\n2 - куб\n3 - +10\n";
                int opt = readInt("> ");
                Sequence<int> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->template map<int>([](int x, int) { return x * x; });
                else if (opt == 2) newSeq = seq->template map<int>([](int x, int) { return x * x * x; });
                else newSeq = seq->template map<int>([](int x, int) { return x + 10; });
                if (newSeq) {
                    cout << "Результат map: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableArraySequence<int>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            } else if (cmd == 11) {
                cout << "1 - сумма\n2 - произведение\n";
                int opt = readInt("> ");
                int init = (opt == 1) ? 0 : 1;
                int res = seq->reduce(opt == 1 ? [](int a, int b) { return a + b; } : [](int a, int b) { return a * b; }, init);
                cout << "Результат: " << res << "\n";
            } else if (cmd == 12) {
                cout << "1 - четные\n2 - нечетные\n3 - >5\n";
                int opt = readInt("> ");
                Sequence<int> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->where([](int x) { return x % 2 == 0; });
                else if (opt == 2) newSeq = seq->where([](int x) { return x % 2 != 0; });
                else newSeq = seq->where([](int x) { return x > 5; });
                if (newSeq) {
                    cout << "Результат where: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableArraySequence<int>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            }
        } catch (const IndexOutOfRange&) {
            cout << "Ошибка: индекс вне диапазона!\n";
        } catch (const exception &e) {
            cout << "Ошибка: " << e.what() << "\n";
        }
    }
}


void menuMutableListInt() {
    MutableListSequence<int> *seq = new MutableListSequence<int>();
    cout << "Создать с тестовыми данными [1,2,3,4,5]? (y/n): ";
    char ans; cin >> ans; clearInput();

    if (ans == 'y' || ans == 'Y') {
        seq->append(1)->append(2)->append(3)->append(4)->append(5);
    }
    
    int run = 1;
    while (run) {
        cout << "\n=== Текущая последовательность (MutableList<int>) ===\n";
        printSeq(seq);
        cout << "Размер: " << seq->getLength() << "\n";
        cout << "1 - append\n2 - prepend\n3 - insertAt\n4 - removeFirst\n5 - removeLast\n6 - removeAt\n"
             << "7 - set\n8 - get\n9 - clear\n10 - map\n11 - reduce\n12 - where\n0 - сменить\n> ";
        int cmd = readInt("");
        try {
            if (cmd == 0) { delete seq; break; }
            if (cmd == 1) {
                int val = readInt("Введите int: ");
                seq->append(val);
                cout << "✅\n";
            } else if (cmd == 2) {
                int val = readInt("Введите int: ");
                seq->prepend(val);
                cout << "✅\n";
            } else if (cmd == 3) {
                int idx = readInt("Индекс: ");
                int val = readInt("Введите int: ");
                seq->insertAt(val, idx);
                cout << "✅\n";
            } else if (cmd == 4) {
                seq->removeFirst();
                cout << "✅\n";
            } else if (cmd == 5) {
                seq->removeLast();
                cout << "✅\n";
            } else if (cmd == 6) {
                int idx = readInt("Индекс: ");
                seq->removeAt(idx);
                cout << "✅\n";
            } else if (cmd == 7) {
                int idx = readInt("Индекс: ");
                int val = readInt("Новое значение: ");
                seq->set(idx, val);
                cout << "✅\n";
            } else if (cmd == 8) {
                int idx = readInt("Индекс: ");
                cout << "Элемент[" << idx << "] = " << seq->get(idx) << "\n";
            } else if (cmd == 9) {
                seq->clear();
                cout << "✅ Очищено\n";
            } else if (cmd == 10) {
                cout << "1 - квадрат\n2 - куб\n3 - +10\n";
                int opt = readInt("> ");
                Sequence<int> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->template map<int>([](int x, int) { return x * x; });
                else if (opt == 2) newSeq = seq->template map<int>([](int x, int) { return x * x * x; });
                else newSeq = seq->template map<int>([](int x, int) { return x + 10; });
                if (newSeq) {
                    cout << "Результат map: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableListSequence<int>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            } else if (cmd == 11) {
                cout << "1 - сумма\n2 - произведение\n";
                int opt = readInt("> ");
                int init = (opt == 1) ? 0 : 1;
                int res = seq->reduce(opt == 1 ? [](int a, int b) { return a + b; } : [](int a, int b) { return a * b; }, init);
                cout << "Результат: " << res << "\n";
            } else if (cmd == 12) {
                cout << "1 - четные\n2 - нечетные\n3 - >5\n";
                int opt = readInt("> ");
                Sequence<int> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->where([](int x) { return x % 2 == 0; });
                else if (opt == 2) newSeq = seq->where([](int x) { return x % 2 != 0; });
                else newSeq = seq->where([](int x) { return x > 5; });
                if (newSeq) {
                    cout << "Результат where: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableListSequence<int>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            }
        } catch (const IndexOutOfRange&) {
            cout << "Ошибка: индекс вне диапазона!\n";
        } catch (const exception &e) {
            cout << "Ошибка: " << e.what() << "\n";
        }
    }
}


void menuMutableArrayString() {
    MutableArraySequence<string> *seq = new MutableArraySequence<string>();
    cout << "Создать с тестовыми данными [apple, banana, cherry]? (y/n): ";
    char ans; cin >> ans; clearInput();
    if (ans == 'y' || ans == 'Y') {
        seq->append("apple")->append("banana")->append("cherry");
    }
    int run = 1;
    while (run) {
        cout << "\n=== Текущая последовательность (MutableArray<string>) ===\n";
        printSeq(seq);
        cout << "Размер: " << seq->getLength() << "\n";
        cout << "1 - append\n2 - prepend\n3 - insertAt\n4 - removeFirst\n5 - removeLast\n6 - removeAt\n"
             << "7 - set\n8 - get\n9 - clear\n10 - map\n11 - reduce\n12 - where\n0 - сменить\n> ";
        int cmd = readInt("");
        try {
            if (cmd == 0) { delete seq; break; }
            if (cmd == 1) {
                string val = readString("Введите строку: ");
                seq->append(val);
                cout << "✅\n";
            } else if (cmd == 2) {
                string val = readString("Введите строку: ");
                seq->prepend(val);
                cout << "✅\n";
            } else if (cmd == 3) {
                int idx = readInt("Индекс: ");
                string val = readString("Введите строку: ");
                seq->insertAt(val, idx);
                cout << "✅\n";
            } else if (cmd == 4) {
                seq->removeFirst();
                cout << "✅\n";
            } else if (cmd == 5) {
                seq->removeLast();
                cout << "✅\n";
            } else if (cmd == 6) {
                int idx = readInt("Индекс: ");
                seq->removeAt(idx);
                cout << "✅\n";
            } else if (cmd == 7) {
                int idx = readInt("Индекс: ");
                string val = readString("Новое значение: ");
                seq->set(val, idx);
                cout << "✅\n";
            } else if (cmd == 8) {
                int idx = readInt("Индекс: ");
                cout << "Элемент[" << idx << "] = " << seq->get(idx) << "\n";
            } else if (cmd == 9) {
                seq->clear();
                cout << "✅ Очищено\n";
            } else if (cmd == 10) {
                cout << "1 - UPPER\n2 - добавить '!'\n3 - реверс\n";
                int opt = readInt("> ");
                Sequence<string> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->template map<string>([](string s, int) { for (char &c : s) c = toupper(c); return s; });
                else if (opt == 2) newSeq = seq->template map<string>([](string s, int) { return s + "!"; });
                else newSeq = seq->template map<string>([](string s, int) { return string(s.rbegin(), s.rend()); });
                if (newSeq) {
                    cout << "Результат map: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableArraySequence<string>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            } else if (cmd == 11) {
                cout << "1 - конкатенация через пробел\n2 - сумма длин\n";
                int opt = readInt("> ");
                if (opt == 1) {
                    string res = seq->reduce([](string a, string b) { return a.empty() ? b : a + " " + b; }, string());
                    cout << "Результат: " << res << "\n";
                } else {
                    int len = seq->reduce([](int acc, string s) { return acc + s.length(); }, 0);
                    cout << "Сумма длин: " << len << "\n";
                }
            } else if (cmd == 12) {
                cout << "1 - длина > 3\n2 - начинается с A/a\n3 - содержит 'e'\n";
                int opt = readInt("> ");
                Sequence<string> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->where([](string s) { return s.length() > 3; });
                else if (opt == 2) newSeq = seq->where([](string s) { return !s.empty() && (s[0] == 'a' || s[0] == 'A'); });
                else newSeq = seq->where([](string s) { return s.find('e') != string::npos || s.find('E') != string::npos; });
                if (newSeq) {
                    cout << "Результат where: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableArraySequence<string>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            }
        } catch (const IndexOutOfRange&) {
            cout << "Ошибка: индекс вне диапазона!\n";
        } catch (const exception &e) {
            cout << "Ошибка: " << e.what() << "\n";
        }
    }
}


void menuMutableListString() {
    MutableListSequence<string> *seq = new MutableListSequence<string>();
    cout << "Создать с тестовыми данными [apple, banana, cherry]? (y/n): ";
    char ans; cin >> ans; clearInput();
    if (ans == 'y' || ans == 'Y') {
        seq->append("apple")->append("banana")->append("cherry");
    }
    int run = 1;
    while (run) {
        cout << "\n=== Текущая последовательность (MutableList<string>) ===\n";
        printSeq(seq);
        cout << "Размер: " << seq->getLength() << "\n";
        cout << "1 - append\n2 - prepend\n3 - insertAt\n4 - removeFirst\n5 - removeLast\n6 - removeAt\n"
             << "7 - set\n8 - get\n9 - clear\n10 - map\n11 - reduce\n12 - where\n0 - сменить\n> ";
        int cmd = readInt("");
        try {
            if (cmd == 0) { delete seq; break; }
            if (cmd == 1) {
                string val = readString("Введите строку: ");
                seq->append(val);
                cout << "✅\n";
            } else if (cmd == 2) {
                string val = readString("Введите строку: ");
                seq->prepend(val);
                cout << "✅\n";
            } else if (cmd == 3) {
                int idx = readInt("Индекс: ");
                string val = readString("Введите строку: ");
                seq->insertAt(val, idx);
                cout << "✅\n";
            } else if (cmd == 4) {
                seq->removeFirst();
                cout << "✅\n";
            } else if (cmd == 5) {
                seq->removeLast();
                cout << "✅\n";
            } else if (cmd == 6) {
                int idx = readInt("Индекс: ");
                seq->removeAt(idx);
                cout << "✅\n";
            } else if (cmd == 7) {
                int idx = readInt("Индекс: ");
                string val = readString("Новое значение: ");
                seq->set(val, idx);
                cout << "✅\n";
            } else if (cmd == 8) {
                int idx = readInt("Индекс: ");
                cout << "Элемент[" << idx << "] = " << seq->get(idx) << "\n";
            } else if (cmd == 9) {
                seq->clear();
                cout << "✅ Очищено\n";
            } else if (cmd == 10) {
                cout << "1 - UPPER\n2 - добавить '!'\n3 - реверс\n";
                int opt = readInt("> ");
                Sequence<string> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->template map<string>([](string s, int) { for (char &c : s) c = toupper(c); return s; });
                else if (opt == 2) newSeq = seq->template map<string>([](string s, int) { return s + "!"; });
                else newSeq = seq->template map<string>([](string s, int) { return string(s.rbegin(), s.rend()); });
                if (newSeq) {
                    cout << "Результат map: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableListSequence<string>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            } else if (cmd == 11) {
                cout << "1 - конкатенация через пробел\n2 - сумма длин\n";
                int opt = readInt("> ");
                if (opt == 1) {
                    string res = seq->reduce([](string a, string b) { return a.empty() ? b : a + " " + b; }, string());
                    cout << "Результат: " << res << "\n";
                } else {
                    int len = seq->reduce([](int acc, string s) { return acc + s.length(); }, 0);
                    cout << "Сумма длин: " << len << "\n";
                }
            } else if (cmd == 12) {
                cout << "1 - длина > 3\n2 - начинается с A/a\n3 - содержит 'e'\n";
                int opt = readInt("> ");
                Sequence<string> *newSeq = nullptr;
                if (opt == 1) newSeq = seq->where([](string s) { return s.length() > 3; });
                else if (opt == 2) newSeq = seq->where([](string s) { return !s.empty() && (s[0] == 'a' || s[0] == 'A'); });
                else newSeq = seq->where([](string s) { return s.find('e') != string::npos || s.find('E') != string::npos; });
                if (newSeq) {
                    cout << "Результат where: ";
                    printSeq(newSeq);
                    cout << "Заменить текущую? (y/n): ";
                    char a; cin >> a; clearInput();
                    if (a == 'y' || a == 'Y') {
                        delete seq;
                        seq = static_cast<MutableListSequence<string>*>(newSeq);
                        cout << "✅ Заменено\n";
                    } else {
                        delete newSeq;
                        cout << "✅ Оставлено\n";
                    }
                }
            }
        } catch (const IndexOutOfRange&) {
            cout << "Ошибка: индекс вне диапазона!\n";
        } catch (const exception &e) {
            cout << "Ошибка: " << e.what() << "\n";
        }
    }
}



void runMenu() {
    while (true) {
        cout << "\n=== ВЫБОР ТИПА ===\n";
        cout << "1 - int\n2 - string\n0 - выход\n";
        int dt = readInt("> ");
        if (dt == 0) break;
        if (dt != 1 && dt != 2) continue;

        cout << "\n=== ВЫБОР КОНТЕЙНЕРА ===\n";
        cout << "1 - MutableArray\n2 - MutableList\n";
        int ct = readInt("> ");
        if (ct != 1 && ct != 2) continue;

        if (dt == 1) {
            if (ct == 1) menuMutableArrayInt();
            else menuMutableListInt();
        } else {
            if (ct == 1) menuMutableArrayString();
            else menuMutableListString();
        }
    }
    cout << "Программа завершена.\n";
}