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

    char fileName[MAX_PATH];
    char fileMap[MAX_PATH];
    HANDLE file = NULL;
    HANDLE fileMapHandle = NULL;
    LPVOID fileMapView = NULL;
    string fileInput;

    cout << "Введите имя файла:" << endl;
    cin >> fileName;

    file = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file != INVALID_HANDLE_VALUE) {

        cout << "Введите имя отображения:" << endl;
        cin >> fileMap;

        fileMapHandle = CreateFileMapping(file, NULL, PAGE_READWRITE, 0, 128, (LPCTSTR)fileMap);
        fileMapView = MapViewOfFile(fileMapHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);

        if (fileMapView != NULL) cout << "Файл успешно спроецирован." << endl << endl;

        cin.ignore(32767, '\n');
        cout << "Введите сообщение:" << endl;
        getline(cin, fileInput);

        CopyMemory((LPVOID)fileMapView, fileInput.c_str(), fileInput.length() * sizeof(char));

        cout << endl << "Данные записаны. НЕ ЗАКРЫВАЙТЕ данную программу!";

        cout << "\n0) Закрыть" << endl;
        do {
            cin >> key;
        } while (key != '0');
        system("CLS");

        key = 1;
    }
    else {
        cout << "Ошибка создания файла. Код ошибки: " << GetLastError() << endl;
    }

    if (fileMapView != NULL && file != NULL) {

        UnmapViewOfFile(fileMapView);
        CloseHandle(file);

    }

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");

    return 0;
}