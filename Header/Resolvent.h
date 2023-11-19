#ifndef MODRMX32ANDX64_H
#define MODRMX32ANDX64_H
#include <QObject>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <windows.h>
#include <Header/bringinstructions.h>
#include <QString>

#include <QDebug>

class Resolvent:public QObject
{
    Q_OBJECT
public:
    Resolvent();
    //BYTE bytes[10] = { 0x11,0x90,0xD4,0x99,0x96,0x22};
    BYTE bytes[10] = { 0x11,0xB5,0xFE,0x9A,0x00,0x00};
    TextSection textSection;
    BringInstructions bringInstructions;
    ModRMAndSibByte modRMAndSibByte;
    //BYTE bytes[10] = { 0x63,0x74,0x78,0x20 };
    void    WriteOperands(InstructionPrefixes * instructionPrefixes);
    void    ReadAndPlaceValues(InstructionPrefixes * PinstructionPrefixes);
    void    WriteST(InstructionPrefixes * instructionPrefixes);
    char *  ReadMoreByte(const __int8 byteSize);
    BYTE    ReadOneByte();
    void    CalculationScaledIndex();
    void    DetermineInstructions();
    __int8  Prefix(InstructionPrefixes * instructionPrefixes,BYTE prefix);
    __int8  Prefix0F(InstructionPrefixes * instructionPrefixes,BYTE prefix0f);
    bool    FindInstruction(InstructionPrefixes * instructionPrefixes);
    #if OS==32
        void    WriteOperandType1(Operands *operands,__int8 RegisterOpcodeFiled);
        void    WriteOperandType2(char * op,BYTE * registerOpcodeModRM,BYTE * registerOpcodeSIB);
    #elif OS==64
        void    ModRMx64R(char * op,__int8 index);
        __int16  CalculationRexPrefixB(BYTE* byte);
        __int16  CalculationRexPrefixX(BYTE* byte);
        __int16  CalculationRexPrefixR(BYTE* byte);
        __int16  CalculationRexPrefixW(BYTE* byte);
    #endif
public slots:
        void getTextData(TextSection textSection);
};

#endif // MODRMX32ANDX64_H
