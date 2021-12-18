#include <iostream>
#include <windows.h>


using namespace std;

void memProtect(DWORD protection) {

    switch (protection)
    {
        case 0:
            cout << "\t���������� �������" << endl;
            break;
        case PAGE_EXECUTE:
            cout << "\t�������� ���������� ������� � ��������������� ������� ������� \n\t(PAGE_EXECUTE)" << endl;
            break;
        case PAGE_EXECUTE_READ:
            cout << "\t������� ������ ������ ��� ���������� ��� ������ � ��������������� ������� �������. " << endl;
            cout << "\t������� ������ � ��������������� ������ �������� � ��������� ������� \n\t(PAGE_EXECUTE_READ)" << endl;
            break;
        case PAGE_EXECUTE_READWRITE:
            cout << "\t������� ������ ������ ��� ����������, ������ ��� ������/������ � ��������������� ������� ������� \n\t(PAGE_EXECUTE_READWRITE)" << endl;
            break;
        case PAGE_EXECUTE_WRITECOPY:
            cout << "\t�������� ������ ������ ��� ����������, ������ ��� ����������� ��� ������ � ���������������\n������������� ������� ������������� ������ \n\t(PAGE_EXECUTE_WRITECOPY)" << endl;
            break;
        case PAGE_NOACCESS:
            cout << "\t�������� ���� ������ � ��������������� ������� ������� \n\t(PAGE_NOACCESS)" << endl;
            break;
        case PAGE_READONLY:
            cout << "\t������� ������ ������ ��� ������ � ��������������� ������� ������� \n\t(PAGE_READONLY)" << endl;
            break;
        case PAGE_READWRITE:
            cout << "\t�������� ������ ������ ��� ������ ��� ������/������ � ��������������� ������� ������� \n\t(PAGE_READWRITE)" << endl;
            break;
        case PAGE_WRITECOPY:
            cout << "\t�������� ������ ������ ��� ������ ��� ����������� ��� ������ � ��������������� ������������� ������� ������������� ������ \n\t(PAGE_WRITECOPY)" << endl;
            break;
    }

    if ((protection & PAGE_GUARD) != 0) cout << "\t�������� � ������� �������� \n\t(PAGE_GUARD)" << endl;
    if ((protection & PAGE_NOCACHE) != 0) cout << "\t�������� �� ���������� \n\t(PAGE_NOCACHE)" << endl;
    if ((protection & PAGE_WRITECOMBINE) != 0) cout << "\t�������� � ����������� � ����� ��������������� ������ \n\t(PAGE_WRITECOMBINE)" << endl;
}


void getSystemInfo() {
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    char key = '1';

    system("CLS");

    printf("OEM ID: %u\n", systemInfo.dwOemId);

    cout << "����������� ����������: ";
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) cout << "x64 (AMD ��� Intel)" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM) cout << "ARM" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64) cout << "Intel Itanium Processor Family (IPF)" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) cout << "x86" << endl;
    if (systemInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_UNKNOWN) cout << "����������� �����������" << endl;

    cout << "������ ��������: " <<  systemInfo.dwPageSize << endl;
    cout << "��������� �� ����� ������ ����� ������, ��������� ����������� � �����������: " << systemInfo.lpMinimumApplicationAddress << endl;
    cout << "��������� �� ����� ������� ����� ������, ��������� ����������� � �����������: " << systemInfo.lpMaximumApplicationAddress << endl;
    cout << "�����, �������������� ����� �����������, ����������� � �������: ";
    for (int i = sizeof(systemInfo.dwActiveProcessorMask); i >= 0; --i) {
        printf("%d", systemInfo.dwActiveProcessorMask & (1 << i) ? 1 : 0);
    }
    cout << endl;
    cout << "���������� ���������� ����������� � ������� ������: " << systemInfo.dwNumberOfProcessors << endl;
    cout << "������� ����������� ���������� ������, �� �������� ����� ���� �������� ����������� ������: " << systemInfo.dwAllocationGranularity << endl;
    cout << "������� ����������: " << systemInfo.wProcessorLevel << endl;
    cout << "������ ����������, ��������� �� �����������: " << systemInfo.wProcessorRevision << endl;

    cout << "\n0) �����" << endl;
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

    cout << "������ ��������� MEMORYSTATUS: " << status.dwLength << " ����" << endl;
    cout << "������� ������������ ���������� ������: " << status.dwMemoryLoad << "%" << endl;
    cout << "����� ����������� ���������� ������: " << status.dwTotalPhys << " ����" << endl;
    cout << "����� ���������� ������, ��������� � ������ ������: " << status.dwAvailPhys << " ����" << endl;
    cout << "������� ������ ����������� ������������� ������: " << status.dwTotalPageFile << " ����" << endl;
    cout << "������������ ����� ������, ������� ����� ������������� ������� �������: " << status.dwAvailPageFile << " ����" << endl;
    cout << "������ ���������������� ����� ������������ ��������� ������������ ����������� ��������: " << status.dwTotalVirtual << " ����" << endl;
    cout << "����� ������������ � ����������������� ������: " << status.dwAvailVirtual << " ����" << endl;

    cout << "\n0) �����" << endl;
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
    cout << "������� �����: 0x";
    cin >> hex >> buff;
    lpAddress = (LPCVOID)buff;
    cout << endl;

    result = VirtualQuery(lpAddress,&lpBuffer,256);
    if (result != 0) {
        int flag = 0;
        cout << "����������� ���������� ���� � �������������� ������: " << result << endl;

        cout << "��������� �� ������� ����� ������� �������: " << lpBuffer.BaseAddress << endl;
        cout << "��������� �� ������� ����� ��������� �������, ���������� �������������: " << lpBuffer.AllocationBase << endl;
        cout << "����� ������ ������ ��� �������������� ��������� �������: \n";
        memProtect(lpBuffer.AllocationProtect);
        cout << "������ �������, ������������ � �������� ������, � ������� ��� �������� ����� ���������� ��������: " << lpBuffer.RegionSize << " ����" << endl;

        cout << "��������� ������� � �������: ";
        if (lpBuffer.State == MEM_COMMIT) cout << "\n\t��������������� ��������" << endl;
        if (lpBuffer.State == MEM_FREE) cout  << "\n\t��������� ��������, ����������� ��� ����������� �������� � ��������� ��� ���������" << endl;
        if (lpBuffer.State == MEM_RESERVE) {
            cout << "\n\t����������������� ��������, �� ������� �������������� �������� ������������ ��������� ������������\n\t�������� ��� ��������� ������-���� ����������� ���������" << endl;
        }

        //cout << "������ ������� � ��������� � �������: " << lpBuffer.Protect << endl;

        cout << "������ ������� � ��������� � �������: ";
        if (lpBuffer.Type == MEM_IMAGE) {
            cout << "\n\t�������� ������ � �������� ������� ������������ � ���� ������� �����������" << endl;
            flag = 1;
        }
        if (lpBuffer.Type == MEM_MAPPED) {
            cout << "\n\t�������� ������ � �������� ������� �������������� � �������������� �������" << endl;
            flag = 1;
        }
        if (lpBuffer.Type == MEM_PRIVATE) {
            cout << "\n\t�������� ������ � �������� ������� �������� ��������" << endl;
            flag = 1;
        }
        if (flag == 0) {
            cout << lpBuffer.Type << endl;
        }

    } else cout << "���-�� ����� �� ���! ��� ������: " << GetLastError() << endl;

    cout << "\n0) �����" << endl;
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
        cout << "�������������� �������������� �������! ������� ����� �������: " << basicAddrAuto << endl << endl;
        cout << "�������������� � ������ ����� ������ ������ �������." << endl;
        cout << "������� �����: 0x";
        cin >> input;

        basicAddrManual = VirtualAlloc(input, systemInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);

        if (basicAddrManual != NULL) cout << "�������������� � ������ ������ �������! ������� ����� �������: " << basicAddrManual << endl << endl;
        else cout << "������ ��������������, ��� ������: " << GetLastError() << endl;
    } else cout << "������ ��������������, ��� ������: " << GetLastError() << endl;

    cout << "\n0) �����" << endl;
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
        cout << "�������������� �������������� � �������� ������ ������ �������!\n������� ����� �������: " << basicAddrAuto << endl << endl;
        cout << "�������������� � �������� ������ � ������ ����� ������ ������ �������." << endl;
        cout << "������� �����: 0x";
        cin >> input;

        basicAddrManual = VirtualAlloc(input, systemInfo.dwPageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

        if (basicAddrManual != NULL) cout << "�������������� � �������� ������ � ������ ������ ������ �������!\n������� ����� �������: " << basicAddrManual << endl << endl;
        else cout << "������ �������������� � �������� ������, ��� ������: " << GetLastError() << endl;
    } else cout << "������ �������������� � �������� ������, ��� ������: " << GetLastError() << endl;

    cout << "\n0) �����" << endl;
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
    cout << "������� ������, ������� �� ������ ��������" << endl;
    cin >> message;
    size = message.length() * sizeof(char);
    const char *p = message.c_str();
    cout << endl;

    cout << "������� ��������� ����� ����� ������: 0x";
    cin  >> address;
    cout << endl;

    if (address != NULL)
    {
        VirtualQuery(address, &memInfo, 256);
        if (memInfo.AllocationProtect && (PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY | PAGE_READWRITE | PAGE_WRITECOPY))
        {
            destination = (CHAR*)address;
            CopyMemory(address, message.c_str(), size);
            cout << endl << "������ ������ 0x" << address << " ��������� �������. �������� ����������:" << endl;
            for (size_t i = 0; i < message.length(); i++) {
                cout << ((CHAR*)address)[i];
            }
            cout << endl;
        }
        else {
            cout << "������� ������� �� ������������� �����������! ��� ������: " << GetLastError() << endl;
        }
    }
    else cout << "����� ����, ��� ������: " << GetLastError() << endl;

    cout << "\n0) �����" << endl;
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