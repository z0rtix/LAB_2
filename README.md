# Лабораторная работа №2
## Динамический массив, связанный список и последовательность на языке C++

### Описание
Реализация системы линейных структур данных на языке C++ с использованием ООП и шаблонов. Проект включает три основных АТД: DynamicArray (динамический массив), LinkedList (связный список) и Sequence (абстрактная последовательность). Реализованы изменяемые (mutable) и неизменяемые (immutable) версии последовательностей.

### Сборка
make

### Запуск
./lab2

### Структура проекта
lab2/
├── DynamicArray.h      # Динамический массив
├── LinkedList.h        # Связный список
├── Sequence.h          # Абстрактный класс Sequence
├── ArraySequence.h     # Sequence на основе DynamicArray
├── ListSequence.h      # Sequence на основе LinkedList
├── IEnumerator.h       # Интерфейс итератора
├── IndexOutOfRange.h   # Класс исключения
├── tests.cpp           # Модульные тесты
├── main.cpp            # Точка входа
├── Makefile
└── README.md

### Основные операции
DynamicArray: конструкторы, getSize, get, set, resize, operator[]

LinkedList: конструкторы, getFirst, getLast, get, getLength, append, prepend, concat, getSubList, operator[]

Sequence: getFirst, getLast, get, getLength, append, prepend, insertAt, concat, getSubsequence

ArraySequence/ListSequence: реализуют Sequence в mutable и immutable вариантах

Дополнительно: map, reduce, where, итераторы, перегрузка операторов

### Тестирование
Модульные тесты покрывают все основные операции, граничные случаи и исключения. Тесты реализованы для каждого класса отдельно.
