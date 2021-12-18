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
    PVOID address = NULL;
    SIZE_T size;
    string message;
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
        if (memInfo.AllocationProtect && (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READWRITE | PAGE_WRITECOPY))
        {
            destination = (CHAR*)address;
            CopyMemory(address, message.c_str(), size);
            cout << endl << "Ячейка памяти 0x" << address << " заполнена успешно. Введённая информация:" << endl;
            for (size_t i = 0; i < message.length(); i++) {
                cout << ((CHAR*)address)[i];
            }
            cout << endl;
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


void virtualProtect() {
    //code
}


void virtualFree() {
    //code
}

void writeAddresses() {
    MEMORY_BASIC_INFORMATION buff;
    LPCVOID add = (LPCVOID)0x00010000;
    int offset = 4096 * 10;

    while (VirtualQuery(add, &buff, 256))
    {
        if ((buff.AllocationProtect && (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READWRITE | PAGE_WRITECOPY)) && (buff.State == MEM_COMMIT)) {
            cout << add << " protect = " << buff.AllocationProtect << endl;
        }
        add = (LPCVOID)((long long)add + offset);
    }
}