### Лабораторная работа номер 8
----------------------------------


Критериями выполнения базовой части являются:
- Реализация программы, возможность ее запуска, ее взаимодействие с пользователем.
- Выполнение всех пунктов без указанного в скобках слова "Усложненный вариант".

Критериями усложненного варианта является:
- Реализация пункта с припиской "Усложненный вариант".
- Все действия реализованы в виде отдельных функций с описанием их документационных строк.

## Разработать контейнерный класс без использования контейнерных классов стандартной библиотеки C++

### Вариант 1 - Очередь

В рамках задачи требуется написать программу, которая будет содержать реализацию контейнера "очередь" и демонстрировать его работу.

! Разработанный контейнерный класс должен быть шаблонным.
! Разработанный контейнерный класс не должен использовать стандартную библиотеку c++ для хранения своих элементов.

Для очереди определены следующие операции:
- создание пустой очереди
- добавить элемент в конец +
- получить элемент из начала +
- удалить элемент из начала +
- проверка, пустая ли очередь
- получить размер очереди +

(Усложненный вариант) Контейнер должен иметь объект итератор, позволяющий обойти всю очередь через цикл for-each(for(auto el: container))

### Вариант 2 - Стек

В рамках задачи требуется написать программу, которая будет содержать реализацию контейнера "стек" и демонстрировать его работу.

! Разработанный контейнерный класс должен быть шаблонным.
! Разработанный контейнерный класс не должен использовать стандартную библиотеку c++ для хранения своих элементов.

Для стека определены следующие операции:
- создание пустого стека
- проверка, пустой ли стек
- добавить элемент наверх стека
- получить элемент сверху стека
- удалить элемент сверху стека
- получить размер стека

(Усложненный вариант) Контейнер должен иметь объект итератор, позволяющий обойти всю очередь через цикл for-each(for(auto el: container))


### Вариант 3 - Двусвязный список

В рамках задачи требуется написать программу, которая будет содержать реализацию контейнера "двусвязный списка" и демонстрировать его работу.

! Разработанный контейнерный класс должен быть шаблонным.
! Разработанный контейнерный класс не должен использовать стандартную библиотеку c++ для хранения своих элементов.

При этом, список должен быть организован через класс узла списка, хранящий значение конкретно элемента и указатель на следующий и предыдущий элементы.

Для двусвязного списка определены следующие операции:
- создание пустого стека
- проверка, пустой ли список
- получить размер список
- добавить элемент в начало списка
- добавить элемент в конец списка
- получить элемент из начала списка
- получить элемент из конца списка
- удалить элемент из начала списка
- удалить элемент из конца списка

(Усложненный вариант) Контейнер должен иметь объект итератор, позволяющий обойти всю очередь через цикл for-each(for(auto el: container))

### Вариант 4 - Вектор

В рамках задачи требуется написать программу, которая будет содержать реализацию контейнера "вектор" и демонстрировать его работу.

! Разработанный контейнерный класс должен быть шаблонным.
! Разработанный контейнерный класс не должен использовать стандартную библиотеку c++ для хранения своих элементов.

При этом, вектор должен изменять размер внутреннего хранилища не при каждом добавлении или удалении  элемента, а с определенной периодичностью.

Для вектора определены следующие операции:
- создание пустого вектора на n элементов
- проверка, пустой ли вектор
- получить размер вектора
- получение произвольного элемента(через перегрузку operator[])
- изменение размера вектора
- добавление нового элемента в конец вектор
- удаление последнего элемента из вектора

(Усложненный вариант) Контейнер должен иметь объект итератор, позволяющий обойти всю очередь через цикл for-each(for(auto el: container))