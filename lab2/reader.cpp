#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("CLS");
    int key = 1;

    char mapName[MAX_PATH];
    HANDLE fileMapHandle = NULL;
    LPVOID fileMapView = NULL;
    string fileInput;

    cout << "Введите имя отображения:" << endl;
    cin >> mapName;


    fileMapHandle = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, (LPCTSTR)mapName);

    if (fileMapHandle != NULL)
    {
        fileMapView = MapViewOfFile(fileMapHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        cout << "Получено сообщение:" << endl;
        cout << (char*)fileMapView << endl << endl;
        cout << "Работа обеих программ завершена.";

        cout << "\n0) Закрыть" << endl;
        do {
            cin >> key;
        } while (key != '0');
        system("CLS");

        key = 1;

    }

    UnmapViewOfFile(fileMapView);
    CloseHandle(fileMapHandle);

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");

    return 0;
}

