#ifndef PEFILE_H
#define PEFILE_H
#include <QObject>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <QDebug>
#include <Header/define.h>


class ReadPeFile:public QObject
{
    Q_OBJECT
private:
    LPVOID dosyaGosterici;
    HANDLE dosyaMapping;
    HANDLE dosyaHandle;
public:
    ReadPeFile();
    ~ReadPeFile(){
        UnmapViewOfFile(dosyaGosterici);
        CloseHandle(dosyaMapping);
        CloseHandle(dosyaHandle);
    }
    int OpenPeFile(WCHAR fileAddress);

signals:
    void setTextData(TextSection textSection);

};

#endif // PEFILE_H

