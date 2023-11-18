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
__int8  ModRMAndSibByte::CalculationScale(BYTE* byte){
    return (*byte & SIBSCALE)>>6;
}
__int8  ModRMAndSibByte::CalculationIndex(BYTE* byte){
    return (*byte & SIBINDEX)>>3;
}
__int8  ModRMAndSibByte::CalculationBase(BYTE* byte){
    return *byte & SIBBASE;
}
void ModRMAndSibByte::reverseString(char str[]) {
    int start = 0;
    int end = strlen(str) - 1;

    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
void ModRMAndSibByte::CalculationR(char * op,BYTE RegisterOpcodeFiled){
    __int8 digit=CalculationDigit(&RegisterOpcodeFiled);

    if(strcmp(op,R8)==0){
        memcpy_s(op,OPERANDSSIZE,r8[digit],sizeof(r8[digit]));
    }
    else if(strcmp(op,R16)==0){
         memcpy_s(op,OPERANDSSIZE,r16[digit],sizeof(r16[digit]));
    }
    else if(strcmp(op,R32)==0 || strcmp(op,R1632)==0){
         memcpy_s(op,OPERANDSSIZE,r32[digit],sizeof(r32[digit]));
    }
}
void ModRMAndSibByte::CalculationEffectiveAddress(char * op,BYTE registerOpcodeFiled){
    if(strcmp(op,RM8)==0 || strcmp(op,RM16)==0 || strcmp(op,RM32)==0 || strcmp(op,RM64)==0 || strcmp(op,RM1632)==0){

        __int8 digit=CalculationDigit(&registerOpcodeFiled);
        __int8 digitRM=CalculationRMDigit(&registerOpcodeFiled);
        __int8 digitMod=CalculationMODDigit(&registerOpcodeFiled);
        CHAR  operand[OPERANDSSIZE]={0};
        memcpy_s(operand,OPERANDSSIZE,effectiveAddress[digitRM],sizeof(effectiveAddress[digitRM]));
        /************************************************************
         * ÖNCEMİ! /  UYARI!
         * Disp4 değerleri int'e yazılır ve oradan hexe çevrilerek yazılır
        *************************************************************/
        if(strcmp(operand,SIB)==0){
            memcpy_s(operand,OPERANDSSIZE,CalculationSib(op,registerOpcodeFiled),OPERANDSSIZE);
        }
        else{
            if(digitMod<1){
                if(digitRM==5){//disp32
                    memcpy_s(operand,OPERANDSSIZE,textSection->TextDataAddress+textSection->BytesReadSize+1,4);
                    textSection->BytesReadSize+=4;
                    reverseString(operand);
                }
            }
            else if(digitMod==1){
                memcpy_s(operand,OPERANDSSIZE,effectiveAddress[digitRM],sizeof(effectiveAddress[digitRM]));
                strcpy(operand,"+");
                //memcpy_s(operand,OPERANDSSIZE,,1);
                strncat(operand,(const char*)(textSection->TextDataAddress+textSection->BytesReadSize+1),1);
                textSection->BytesReadSize++;
            }
            else if(digitMod==2){
                memcpy_s(operand,OPERANDSSIZE,effectiveAddress[digitRM],sizeof(effectiveAddress[digitRM]));
                int disp32={0};
                memcpy_s(&disp32,4,(textSection->TextDataAddress+textSection->BytesReadSize+1),4);
                QString hexvalue = QString("%1").arg(disp32, 8, 16, QLatin1Char( '0' ));//HEX'E ÇEVİRME İŞLEMİ
                if(disp32>0){
                    strcat(operand,"+");
                }
                sprintf(operand+5, "%X",disp32);
                strcat(operand,hexvalue.toUpper().toUtf8().constData());
                textSection->BytesReadSize+=4;
            }
            else{
                memcpy_s(operand,OPERANDSSIZE,r32[digitRM],sizeof(r32[digitRM]));
            }
        }
        Bracket(operand);
        memcpy_s(op,OPERANDSSIZE,operand,OPERANDSSIZE);
    }
}
char * ModRMAndSibByte::CalculationSib(char * op,BYTE registerOpcodeFiled){
    CHAR  operand[OPERANDSSIZE]={0};
    BYTE  sibByte[1];
    memcpy_s(sibByte,1,textSection->TextDataAddress+textSection->BytesReadSize+1,1);
    textSection->BytesReadSize++;
    __int8 sibBaseIndex=CalculationBase(sibByte);
    __int8 sibIndex=CalculationIndex(sibByte);
    const char * scaled=scaledIndex[sibIndex];
    if(sibBaseIndex==0b00000101){//5
        __int8 modBits=CalculationMODDigit(&registerOpcodeFiled);
        switch(modBits){
        case 0x00:
            int disp32={0};
            if(strcmp(scaled,NONE)!=0){
                strcat(operand,scaled);
                __int8 sibSS=CalculationScale(sibByte);
                if(sibSS>0){ //ÜSLÜYÜ HESAPLAR VE SICALED INDEX'IN YANINA KOYAR
                    __int8 result = std::pow(2, sibSS);
                    strcat(operand,"*");
                    strcat(operand,(char*)(__int8)pow(2,sibSS));
                }
            }
            memcpy_s(&disp32,4,(textSection->TextDataAddress+textSection->BytesReadSize+1),4);
            textSection->BytesReadSize+=4;
            QString hexvalue = QString("%1").arg(disp32, 8, 16, QLatin1Char( '0' ));//HEX'E ÇEVİRME İŞLEMİ
            if(disp32>0){
                strcat(operand,"+");
            }
            strcat(operand,hexvalue.toUpper().toUtf8().constData());
            break;
        case 0x01:
            operand
            textSection->TextDataAddress+textSection->BytesReadSize+1
            break;
        case 0x10:
            break;
        }
    }
    else{

    }
    //qDebug()<<;


    return operand;
}
void ModRMAndSibByte::Bracket(char operand[OPERANDSSIZE]){
    char  tags[OPERANDSSIZE]={0};
    strcat(tags,"[");
    strcat(tags,operand);
    strcat(tags,"]");
    memcpy_s(operand,OPERANDSSIZE,tags,OPERANDSSIZE);
}
