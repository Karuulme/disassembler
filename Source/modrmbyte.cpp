#include "../Header/modrmbyte.h"
ModRMAndSibByte::ModRMAndSibByte(TextSection * textSectionn){
    textSection=textSectionn;
}
__int8 ModRMAndSibByte::CalculationDigit(BYTE* byte){
    return (*byte & MODRBITS)>>3;
}
__int8 ModRMAndSibByte::CalculationRMDigit(BYTE* byte){
    return *byte & MODRMBITS;
}
__int8 ModRMAndSibByte::CalculationMODDigit(BYTE* byte){
    return (*byte & MODMODBITS)>>6;
}
__int8  ModRMAndSibByte::CalculationSS(BYTE* byte){
    return (*byte & SIBSCALE)>>6;
}
__int8  ModRMAndSibByte::CalculationIndex(BYTE* byte){
    return (*byte & SIBINDEX)>>3;
}
__int8  ModRMAndSibByte::CalculationBase(BYTE* byte){
    return *byte & SIBBASE;
}
void ModRMAndSibByte::CalculationR(Operands * operands,BYTE RegisterOpcodeFiled){
    __int8 digit=CalculationDigit(&RegisterOpcodeFiled);

    if(strcmp(operands->Operand,R8)==0){
        memcpy_s(operands->RegisterModRM,REGISTERSIZE,r8[digit],2);
    }
    else if(strcmp(operands->Operand,R16)==0){
         memcpy_s(operands->RegisterModRM,REGISTERSIZE,r16[digit], 2);
    }
    else if(strcmp(operands->Operand,R32)==0 || strcmp(operands->Operand,R1632)==0){
         memcpy_s(operands->RegisterModRM,REGISTERSIZE,r32[digit],3);
    }
}
void ModRMAndSibByte::CalculationEffectiveAddress(Operands * operands,BYTE registerOpcodeFiled){
    //https://www.tutorialspoint.com/assembly_programming/assembly_registers.htm BURASI OKUNACAK
    if(strcmp(operands->Operand,RM8)==0 || strcmp(operands->Operand,RM16)==0 || strcmp(operands->Operand,RM32)==0 || strcmp(operands->Operand,RM64)==0 || strcmp(operands->Operand,RM1632)==0){

         __int8 digitRM=CalculationRMDigit(&registerOpcodeFiled);
        CHAR  effectiveAddressName[OPERANDSSIZE];
        memcpy_s(effectiveAddressName,OPERANDSSIZE,effectiveAddress[digitRM],3);
        int disp32={0};
        __int8 force={0};
        if(strcmp(effectiveAddressName,SIB)==0){
            CalculationSib(operands,registerOpcodeFiled);
        }
        else{
            __int8 digit=CalculationDigit(&registerOpcodeFiled);
            __int8 digitMod=CalculationMODDigit(&registerOpcodeFiled);
            switch(digitMod)
            {
            case 0:
                if(digitRM==5){//disp32
                    memcpy_s(&operands->Disp,sizeof(long long int),(textSection->TextDataAddress+textSection->BytesReadSize+1),4);
                    textSection->BytesReadSize+=4;
                }
                else{
                    memcpy_s(operands->RegisterModRM,OPERANDSSIZE,r32[digitMod],sizeof(r32[digitMod]));
                }
                break;
            case 1:
            case 2:
                force=pow(2,digitMod);//2 or 4
                memcpy_s(&operands->RegisterModRM,REGISTERSIZE,effectiveAddress[digitRM],3);
                memcpy_s(&operands->Disp,sizeof(long long int),(textSection->TextDataAddress+textSection->BytesReadSize+1),force);
                textSection->BytesReadSize+=force;
                break;
            case 3:
                memcpy_s(operands->RegisterModRM,OPERANDSSIZE,r32[digitRM],sizeof(r32[digitRM]));
            }
        }
    }
}
void ModRMAndSibByte::CalculationSib(Operands * operands,BYTE registerOpcodeFiled){
    BYTE  sibByte[1];
    memcpy_s(sibByte,1,textSection->TextDataAddress+textSection->BytesReadSize+1,1);
    textSection->BytesReadSize++;
    __int8 sibIndex=CalculationIndex(sibByte);
    __int8 sibSS=CalculationSS(sibByte);
    const char * scaled=base[sibIndex];
    if(strcmp(scaled,EBPMOD)){
        __int8 modBits=CalculationMODDigit(&registerOpcodeFiled);
        switch(modBits){
        case 0x00:
            memcpy_s(&operands->Disp,sizeof(long long int),(textSection->TextDataAddress+textSection->BytesReadSize+1),4);
            textSection->BytesReadSize+=4;
            break;
        case 0x01:
            memcpy_s(&operands->RegisterSibBase,REGISTERSIZE,EBP,3);
            memcpy_s(&operands->Disp,sizeof(long long int),(textSection->TextDataAddress+textSection->BytesReadSize+1),1);
            textSection->BytesReadSize++;
            break;
        case 0x10:
            memcpy_s(&operands->RegisterSibBase,REGISTERSIZE,EBP,3);
            memcpy_s(&operands->Disp,sizeof(long long int),(textSection->TextDataAddress+textSection->BytesReadSize+1),4);
            textSection->BytesReadSize+=4;
            break;
        }
    }
    else{
        memcpy_s(&operands->RegisterSibBase,REGISTERSIZE,scaled,3);
    }
    const char * scaledSelected=scaledIndex[sibIndex];
    if(strcmp(scaledSelected,NONE)!=0){
        __int8 force={0};
        force=pow(2,sibSS);//0 2, 4 or 8
        if(force>1)
            operands->Pow=force;
        memcpy_s(&operands->RegisterSibScalerIndex,REGISTERSIZE,scaledIndex[sibIndex],sizeof(scaledIndex[sibIndex]));
    }
}
/*
void ModRMAndSibByte::Bracket(char operand[OPERANDSSIZE]){
    char  tags[OPERANDSSIZE]={0};
    strcat(tags,"[");
    strcat(tags,operand);
    strcat(tags,"]");
    memcpy_s(operand,OPERANDSSIZE,tags,OPERANDSSIZE);
}*/
