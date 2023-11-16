#include <windows.h>
#include <iostream>

#pragma comment(lib, "imagehlp.lib")
using namespace std;
int main() {
    BYTE bytes[10] = { 0x10,0x11,0x22,0x330,0x44,0x55,0x66,0x77,0x88,0x99 };
    cout << (int)(*(bytes+2));
    /*
    WCHAR fileAddress[255] = L"C:\\Users\\karuulme\\Desktop\\TinyCrackMe.exe";
    HANDLE dosyaHandle = CreateFile(fileAddress, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (dosyaHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "Dosya açma hatası: " << GetLastError() << std::endl;
        return 1;
    }

    // PE dosyasını haritala
    HANDLE dosyaMapping = CreateFileMapping(dosyaHandle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (dosyaMapping == NULL) {
        std::cerr << "Dosya haritalama hatası: " << GetLastError() << std::endl;
        CloseHandle(dosyaHandle);
        return 1;
    }

    LPVOID dosyaGosterici = MapViewOfFile(dosyaMapping, FILE_MAP_READ, 0, 0, 0);
    if (dosyaGosterici == NULL) {
        std::cerr << "Dosya gösterici hatası: " << GetLastError() << std::endl;
        CloseHandle(dosyaMapping);
        CloseHandle(dosyaHandle);
        return 1;
    }

    // PE dosyasının bölümlerini al
    IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)dosyaGosterici;
    IMAGE_NT_HEADERS* ntHeader = (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

    IMAGE_SECTION_HEADER* bolumHeader = IMAGE_FIRST_SECTION(ntHeader);

    // Her bir bölümü yazdır
    for (int i = 0; i < ntHeader->FileHeader.NumberOfSections; ++i) {
        if (strncmp((const char*)bolumHeader[i].Name, ".text", 5) == 0) {
            std::cout << ".text Bölümü İçeriği:" << std::endl;

            // .text bölümünün başlangıç adresini ve boyutunu al
            DWORD textBaslangicAdresi = bolumHeader[i].PointerToRawData;
            DWORD textBoyutu = bolumHeader[i].SizeOfRawData;

            // .text bölümünün içeriğini heksadesimal formatta yazdır
            BYTE* textData = (BYTE*)dosyaGosterici + textBaslangicAdresi;
            int satir=0;
            char data[4];
            int ii = 0;
            for (BYTE * j = textData; ii <4; ++j,ii++) {
                printf("%i ", *j);
                data[ii] = *j;
                if ((satir + 1) % 16 == 0)
                    std::cout << std::endl;
            }
            cout<< endl;
            cout << (int)data[0] << endl;
            cout << (int)data[1] << endl;
            cout << (int)data[2] << endl;
            cout << (int)data[3] << endl;
            std::cout << std::endl;
            break;
        }
    }

    // Belleği serbest bırak
    UnmapViewOfFile(dosyaGosterici);
    CloseHandle(dosyaMapping);
    CloseHandle(dosyaHandle);
    */
    return 0;
}
