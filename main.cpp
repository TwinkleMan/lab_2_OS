#include <iostream>
#include <windows.h>
#include "menu.h"
#include "prog1.h"

menuItem mainMenu[] {
        {1,"��������� ���������� � �������������� �������",getSystemInfo},
        {2,"����������� ������� ����������� ������",virtMemoryStatus},
        {3,"����������� ��������� ����������� ������� ������",virtualQuery},
        {4,"�������������� �������",virtualAlloc},
        {5,"�������������� ������� � �������� ��� ���������� ������",virtualAllocMem},
        {6,"������ ������ � ������ ������",writeData},
        {7,"��������� ������ ������� ��� ��������� ������� ������",virtualProtect},
        {8,"������� ���������� ������ � ������������ ������� ��������� ������������",virtualFree},
        {9,"������",writeAddresses},
        {0,"�����"}
};
static const unsigned int mainMenuSize = sizeof(mainMenu) / sizeof(mainMenu[0]);

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("CLS");
    MenuEngine(&mainMenu[0], mainMenuSize);

    return 0;
}
