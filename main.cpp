#include <iostream>
#include <windows.h>
#include "menu.h"
#include "prog1.h"

menuItem mainMenu[] {
        {1,"Получение информации о вычислительной системе",getSystemInfo},
        {2,"Определение статуса виртуальной памяти",virtMemoryStatus},
        {3,"Определение состояния конкретного участка памяти",virtualQuery},
        {4,"Резервирование региона",virtualAlloc},
        {5,"Резервирование региона и передача ему физической памяти",virtualAllocMem},
        {6,"Запись данных в ячейки памяти",writeData},
        {7,"Установка защиты доступа для заданного региона памяти",virtualProtect},
        {8,"Возврат физической памяти и освобождение региона адресного пространства",virtualFree},
        {9,"адреса",writeAddresses},
        {0,"Выход"}
};
static const unsigned int mainMenuSize = sizeof(mainMenu) / sizeof(mainMenu[0]);

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("CLS");
    MenuEngine(&mainMenu[0], mainMenuSize);

    return 0;
}
