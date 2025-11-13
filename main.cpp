#include <iostream>
#include "Hex.h"

int main() {
    std::cout << "Демонстрация конструкторов: " << std::endl;

    Hex firstHex{1,2,3,4};
    std::cout << "Первое число: ";
    firstHex.print(std::cout) << std::endl;

    Hex secondHex("A3");
    std::cout << "Второе число: ";
    secondHex.print(std::cout) << std::endl;

    Hex thirdHex(5, 0xB);
    std::cout << "Третье число: ";
    thirdHex.print(std::cout) << std::endl;

    Hex copyHex(firstHex);
    std::cout << "Копия первого числа: ";
    copyHex.print(std::cout) << std::endl;

    Hex movedHex(std::move(copyHex));
    std::cout << "Перемещённое число: ";
    movedHex.print(std::cout) << std::endl;

    std::cout << "Демонстрация арифметических операций: " << std::endl;

    Hex sum = firstHex.add(secondHex);
    std::cout << "Результат сложения: ";
    firstHex.print(std::cout) << '+';
    secondHex.print(std::cout) << '=';
    sum.print(std::cout) << std::endl;

try {
        Hex diff = sum.remove(secondHex);
        std::cout << "Разность ";
        sum.print(std::cout) << " - ";
        secondHex.print(std::cout) << " = ";
        diff.print(std::cout) << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при вычитании: " << e.what() << std::endl;
    }

    std::cout << "\n--- Операции сравнения ---" << std::endl;
    std::cout << "firstHex < secondHex : " << (firstHex.lessThen(secondHex) ? "true" : "false") << std::endl;
    std::cout << "firstHex > secondHex : " << (firstHex.biggerThen(secondHex) ? "true" : "false") << std::endl;
    std::cout << "firstHex == secondHex : " << (firstHex.equal(secondHex) ? "true" : "false") << std::endl;

    std::cout << "\n--- Проверка обработки исключений ---" << std::endl;
    try {
        Hex invalidHex("1G");
    }
    catch (const std::exception& e) {
        std::cerr << "Перехвачено исключение: " << e.what() << std::endl;
    }

    try {
        Hex smaller("3");
        Hex bigger("F5");
        Hex bad = smaller.remove(bigger);
    }
    catch (const std::exception& e) {
        std::cerr << "Перехвачено исключение: " << e.what() << std::endl;
    }

    std::cout << "\n--- Завершение программы, вызов деструкторов ---" << std::endl;
    std::cout << "=== Лабораторная работа завершена ===" << std::endl;

    return 0;
}
