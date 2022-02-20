# Основи об'єктно-орієнтованого програмування

## Лабораторна робота № 1a. Моделювання з використанням UML

### Ultimate Tic Tac Toe Player

Програма написана на основі [AI course at the Hebrew University](https://eranamar.herokuapp.com/uttt.html)

Для виконання лабораторної роботи було реалізовано [алгоритм Minimax](https://en.wikipedia.org/wiki/Minimax) з [Alpha-Beta pruning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)

Евристика - CellsWeight

Середа розробки - [Visual Studio Code](https://code.visualstudio.com/) та [CMake](https://cmake.org/)

Керування залежностями - [vcpkg](https://vcpkg.io/en/index.html)

Unit tests - [GoogleTest](https://google.github.io/googletest/)

Документація - [Doxygen](https://www.doxygen.nl/index.html)

### Опис

На початковому етапі маємо реалізацію алгоритму та програму яка грає сама з собою у текстовому режимі.

Мінімальне використовування юніт тестів.

### Зміни

* Перепроектування з використовуванням ООП
* Збільшення покриття тестами
* Додати графоній
* Чоловік або чоловікиня як опонент
* Мережевий режим гри
