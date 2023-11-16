#include "../Header/readpefile.h"

ReadPeFile::ReadPeFile()
{

}
int ReadPeFile::OpenPeFile(WCHAR fileAddress){

    WCHAR fileAddress2[255] = L"C:\\Users\\karuulme\\Desktop\\TinyCrackMe.exe";
    dosyaHandle = CreateFile(fileAddress2, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (dosyaHandle == INVALID_HANDLE_VALUE) {
        qDebug()<<GetLastError();
            return 1;
    }
    // PE dosyasını haritala
    dosyaMapping = CreateFileMapping(dosyaHandle, NULL, PAGE_READONLY, 0, 0, NULL);
    if (dosyaMapping == NULL) {
        qDebug() << "Dosya haritalama hatası: " << GetLastError();
        CloseHandle(dosyaHandle);
        return 1;
    }
    dosyaGosterici = MapViewOfFile(dosyaMapping, FILE_MAP_READ, 0, 0, 0);
    if (dosyaGosterici == NULL) {
         qDebug() << "Dosya gösterici hatası: " << GetLastError();
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

            DWORD textBaslangicAdresi = bolumHeader[i].PointerToRawData;
            DWORD textBoyutu = bolumHeader[i].SizeOfRawData;

            BYTE* textData = (BYTE*)dosyaGosterici + textBaslangicAdresi;
            TextSection TextSection;
            TextSection.TextDataAddress =   textData;
            TextSection.TextDataSize    =   textBoyutu;
            setTextData(TextSection);
            /*for (BYTE * j = textData; j < (textData+textBoyutu); ++j) {
                printf("%02X ", *j);
                if ((satir + 1) % 16 == 0)
                    std::cout << std::endl;
            }
            std::cout << std::endl;*/
            break;
        }
    }
    return 0;
}

