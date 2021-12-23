#include <iostream>
#include <windows.h>


using namespace std;

void memProtect(DWORD protection) {

    switch (protection)
    {
        case 0:
            cout << "\tОтсутствие доступа" << endl;
            break;
        case PAGE_EXECUTE:
            cout << "\tВключено выполнение доступа к зафиксированной области страниц \n\t(PAGE_EXECUTE)" << endl;
            break;
        case PAGE_EXECUTE_READ:
            cout << "\tВключен доступ только для выполнения или чтения к зафиксированной области страниц. " << endl;
            cout << "\tПопытка записи в зафиксированный регион приводит к нарушению доступа \n\t(PAGE_EXECUTE_READ)" << endl;
            break;
        case PAGE_EXECUTE_READWRITE:
            cout << "\tВключен доступ только для выполнения, чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_EXECUTE_READWRITE)" << endl;
            break;
        case PAGE_EXECUTE_WRITECOPY:
            cout << "\tВключает доступ только для выполнения, чтения или копирования при записи к сопоставленному\nпредставлению объекта сопоставления файлов \n\t(PAGE_EXECUTE_WRITECOPY)" << endl;
            break;
        case PAGE_NOACCESS:
            cout << "\tОтключен весь доступ к зафиксированной области страниц \n\t(PAGE_NOACCESS)" << endl;
            break;
        case PAGE_READONLY:
            cout << "\tВключен доступ только для чтения к зафиксированной области страниц \n\t(PAGE_READONLY)" << endl;
            break;
        case PAGE_READWRITE:
            cout << "\tВключает доступ только для чтения или чтения/записи к зафиксированной области страниц \n\t(PAGE_READWRITE)" << endl;
            break;
        case PAGE_WRITECOPY:
            cout << "\tВключает доступ только для чтения или копирования при записи к сопоставленному представлению объекта сопоставления файлов \n\t(PAGE_WRITECOPY)" << endl;
            break;
    }

    if ((protection & PAGE_GUARD) != 0) cout << "\tСтраницы в регионе защищены \n\t(PAGE_GUARD)" << endl;
    if ((protection & PAGE_NOCACHE) != 0) cout << "\tСтраницы не кэшируются \n\t(PAGE_NOCACHE)" << endl;
    if ((protection & PAGE_WRITECOMBINE) != 0) cout << "\tСтраницы в установлены в режим комбинированной записи \n\t(PAGE_WRITECOMBINE)" << endl;
}


void getSystemInfo() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    char key = '1';

    system("CLS");

    printf("OEM ID: %u\n", systemInfo.dwOemId);

    cout << "Архитектура процессора: ";
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) cout << "x64 (AMD или Intel)" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) cout << "ARM" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) cout << "Intel Itanium Processor Family (IPF)" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) cout << "x86" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) cout << "Неизвестная архитектура" << endl;

    cout << "Размер страницы: " <<  systemInfo.dwPageSize << endl;
    cout << "Указатель на самый низкий адрес памяти, доступный приложениям и библиотекам: " << systemInfo.lpMinimumApplicationAddress << endl;
    cout << "Указатель на самый высокий адрес памяти, доступный приложениям и библиотекам: " << systemInfo.lpMaximumApplicationAddress << endl;
    cout << "Маска, представляющая набор процессоров, настроенных в системе: ";
    for (int i = sizeof(systemInfo.dwActiveProcessorMask); i >= 0; --i) {
        printf("%d", systemInfo.dwActiveProcessorMask & (1 << i) ? 1 : 0);
    }
    cout << endl;
    cout << "Количество логических процессоров в текущей группе: " << systemInfo.dwNumberOfProcessors << endl;
    cout << "Степень детализации начального адреса, по которому может быть выделена виртуальная память: " << systemInfo.dwAllocationGranularity << endl;
    cout << "Уровень процессора: " << systemInfo.wProcessorLevel << endl;
    cout << "Версия процессора, зависящая от архитектуры: " << systemInfo.wProcessorRevision << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}


void virtMemoryStatus() {
    MEMORYSTATUS status;
    GlobalMemoryStatus(&status);
    char key = '1';

    system("CLS");

    cout << "Размер структуры MEMORYSTATUS: " << status.dwLength << " байт" << endl;
    cout << "Процент используемой физической памяти: " << status.dwMemoryLoad << "%" << endl;
    cout << "Объем фактической физической памяти: " << status.dwTotalPhys << " байт" << endl;
    cout << "Объем физической памяти, доступной в данный момент: " << status.dwAvailPhys << " байт" << endl;
    cout << "Текущий размер ограничения фиксированной памяти: " << status.dwTotalPageFile << " байт" << endl;
    cout << "Максимальный объем памяти, который может зафиксировать текущий процесс: " << status.dwAvailPageFile << " байт" << endl;
    cout << "Размер пользовательской части виртуального адресного пространства вызывающего процесса: " << status.dwTotalVirtual << " байт" << endl;
    cout << "Объем невыделенной и незафиксированной памяти: " << status.dwAvailVirtual << " байт" << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}


void virtualQuery() {
    long long buff;
    LPCVOID lpAddress;
    MEMORY_BASIC_INFORMATION lpBuffer;
    SIZE_T result;
    char key = '1';

    system("CLS");
    cout << "Введите адрес: 0x";
    cin >> hex >> buff;
    lpAddress = (LPCVOID)buff;
    cout << endl;

    result = VirtualQuery(lpAddress,&lpBuffer,256);
    if (result != 0) {
        int flag = 0;
        cout << "Фактическое количество байт в информационном буфере: " << result << endl;

        cout << "Указатель на базовый адрес региона страниц: " << lpBuffer.BaseAddress << endl;
        cout << "Указатель на базовый адрес диапазона страниц, выделенных пользователем: " << lpBuffer.AllocationBase << endl;
        cout << "Опция защиты памяти при первоначальном выделении области: \n";
        memProtect(lpBuffer.AllocationProtect);
        cout << "Размер региона, начинающейся с базового адреса, в котором все страницы имеют одинаковые атрибуты: " << lpBuffer.RegionSize << " байт" << endl;

        cout << "Состояние страниц в регионе: ";
        if (lpBuffer.State == MEM_COMMIT) cout << "\n\tзафиксированная страница" << endl;
        if (lpBuffer.State == MEM_FREE) cout  << "\n\tсвободные страницы, недоступные для вызывающего процесса и доступные для выделения" << endl;
        if (lpBuffer.State == MEM_RESERVE) {
            cout << "\n\tзарезервированные страницы, на которых зарезервирован диапазон виртуального адресного пространства\n\tпроцесса без выделения какого-либо физического хранилища" << endl;
        }

        //cout << "Защита доступа к страницам в области: " << lpBuffer.Protect << endl;

        cout << "Защита доступа к страницам в регионе: ";
        if (lpBuffer.Type == MEM_IMAGE) {
            cout << "\n\tстраницы памяти в пределах региона отображаются в виде раздела изображения" << endl;
            flag = 1;
        }
        if (lpBuffer.Type == MEM_MAPPED) {
            cout << "\n\tстраницы памяти в пределах региона сопоставляются с представлением раздела" << endl;
            flag = 1;
        }
        if (lpBuffer.Type == MEM_PRIVATE) {
            cout << "\n\tстраницы памяти в пределах региона являются частными" << endl;
            flag = 1;
        }
        if (flag == 0) {
            cout << lpBuffer.Type << endl;
        }

    } else cout << "Что-то пошло не так! Код ошибки: " << GetLastError() << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}


void virtualAlloc() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    LPVOID basicAddrAuto, basicAddrManual, input;
    char key = '1';

    system("CLS");
    basicAddrAuto = VirtualAlloc(NULL,systemInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if (basicAddrAuto != NULL) {
        cout << "Автоматическое резервирование успешно! Базовый адрес региона: " << basicAddrAuto << endl << endl;
        cout << "Резервирование в режиме ввода адреса начала региона." << endl;
        cout << "Введите адрес: 0x";
        cin >> input;

        basicAddrManual = VirtualAlloc(input, systemInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        if (basicAddrManual != NULL) cout << "Резервирование в ручном режиме успешно! Базовый адрес региона: " << basicAddrManual << endl << endl;
        else cout << "Ошибка резервирования, код ошибки: " << GetLastError() << endl;
    } else cout << "Ошибка резервирования, код ошибки: " << GetLastError() << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}


void virtualAllocMem() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    LPVOID basicAddrAuto, basicAddrManual, input;
    char key = '1';

    system("CLS");
    basicAddrAuto = VirtualAlloc(NULL,systemInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (basicAddrAuto != NULL) {
        cout << "Автоматическое резервирование и передача памяти прошли успешно!\nБазовый адрес региона: " << basicAddrAuto << endl << endl;
        cout << "Резервирование и передача памяти в режиме ввода адреса начала региона." << endl;
        cout << "Введите адрес: 0x";
        cin >> input;

        basicAddrManual = VirtualAlloc(input, systemInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        if (basicAddrManual != NULL) cout << "Резервирование и передача памяти в ручном режиме прошли успешно!\nБазовый адрес региона: " << basicAddrManual << endl << endl;
        else cout << "Ошибка резервирования и передача памяти, код ошибки: " << GetLastError() << endl;
    } else cout << "Ошибка резервирования и передача памяти, код ошибки: " << GetLastError() << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}


void writeData() {
    LPVOID address = NULL;
    SIZE_T size;
    string message = "";
    MEMORY_BASIC_INFORMATION memInfo;
    CHAR* destination = NULL;
    char key = '1';

    system("CLS");
    cout << "Введите данные, которые вы хотите записать" << endl;
    cin >> message;
    size = message.length() * sizeof(char);
    const char *p = message.c_str();
    cout << endl;

    cout << "Введите начальный адрес места записи: 0x";
    cin  >> address;
    cout << endl;

    if (address != NULL)
    {
        VirtualQuery(address, &memInfo, 256);
        if (memInfo.State && (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READWRITE | PAGE_WRITECOPY))
        {
            destination = (CHAR*)address;
            CopyMemory(destination, message.c_str(), size);
            cout << endl << "Ячейка памяти " << address << " заполнена успешно. Введённая информация:" << endl;
            cout << destination;
            cout << endl;

            //VirtualFree(destination,0,MEM_RELEASE);
        }
        else {
            cout << "Уровень доступа не соответствует требованиям! Код ошибки: " << GetLastError() << endl;
        }
    }
    else cout << "Адрес пуст, код ошибки: " << GetLastError() << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}

void protectMenu() {

    cout << "Выберите уровень защиты:" << endl;
    cout << "1) PAGE_EXECUTE" << endl;
    cout << "2) PAGE_EXECUTE_READ" << endl;
    cout << "3) PAGE_EXECUTE_READWRITE" << endl;
    cout << "4) PAGE_EXECUTE_WRITECOPY" << endl;
    cout << "5) PAGE_NOACCESS" << endl;
    cout << "6) PAGE_READONLY" << endl;
    cout << "7) PAGE_READWRITE" << endl;
    cout << "8) PAGE_WRITECOPY" << endl;

}

DWORD protectChoose(int x) {

    DWORD level;

    switch (x) {
        case 1:
            level = PAGE_EXECUTE;
            break;
        case 2:
            level = PAGE_EXECUTE_READ;
            break;
        case 3:
            level = PAGE_EXECUTE_READWRITE;
            break;
        case 4:
            level = PAGE_EXECUTE_WRITECOPY;
            break;
        case 5:
            level = PAGE_NOACCESS;
            break;
        case 6:
            level = PAGE_READONLY;
            break;
        case 7:
            level = PAGE_READWRITE;
            break;
        case 8:
            level = PAGE_WRITECOPY;
            break;
    }

    return level;
}

void virtualProtect() {
    char key = '1';

    system("CLS");
    LPVOID address = NULL;

    int inputLevel;

    DWORD oldLevel = 0;
    DWORD newLevel = 0;

    cout << "Введите адрес: 0x";
    cin >> address;

    if (address != NULL) {
        protectMenu();
        cin >> inputLevel;

        system("cls");

        newLevel = protectChoose(inputLevel);
        cout << "Новый уровень защиты: ";
        memProtect(newLevel);
        cout << endl;
        if (VirtualProtect(address, sizeof(DWORD), newLevel, &oldLevel))
        {
            cout << "Старый уровень защиты:" << endl;
            memProtect(oldLevel);
        }
        else cout << "Ошибка: " << GetLastError() << endl;

    }
    else cout << "Нулевой адрес (NULL)" << endl;

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");

}


void virtualFree() {
    system("CLS");
    char key = '1';

    LPVOID address = NULL;

    cout << "Введите адрес для возврата физической памяти и освобождения региона: 0x";
    cin >> address;

    if (VirtualFree((CHAR*)address,0,MEM_RELEASE)) {
        cout << "Регион успешно освобожден\n" << endl;
    } else {
        cout << "Что-то пошло не так, код ошибки: " << GetLastError() << endl;
    }

    cout << "\n0) Выход" << endl;
    do {
        cin >> key;
    } while (key != '0');
    system("CLS");
}
