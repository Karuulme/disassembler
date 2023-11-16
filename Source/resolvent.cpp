
#include "../Header/Resolvent.h"

Resolvent::Resolvent()
{
    DetermineInstructions();
}

void Resolvent::getTextData(TextSection textSection){
    textSection=textSection;
}
char * Resolvent::ReadMoreByte(const __int8 byteSize){
    char  bytes[4];
    __int8 i=0;
    for(BYTE* data=textSection.TextDataAddress;i<byteSize;data++,i++){
        bytes[i]=*data;
    }
    textSection.BytesReadSize+=byteSize;
}
BYTE  Resolvent::ReadOneByte(){
    //BYTE byte=(BYTE)*(textSection.TextDataAddress+textSection.BytesReadSize);
    return (BYTE)*(bytes+textSection.BytesReadSize);
}
void  Resolvent::DetermineInstructions(){
    BYTE byte;
    __int8 columnByte;
    //while(textSection.BytesReadSize<2){//textSection.TextDataSize!=textSection.TextDataSize){
        InstructionPrefixes instructionPrefixes={0};
        byte=ReadOneByte();
        //PREFİX
        columnByte=Prefix(&instructionPrefixes,byte);
        if(columnByte!=-1)
            byte=ReadOneByte();
        //PREFİX 0x0F
        columnByte=Prefix0F(&instructionPrefixes,byte);
        if(columnByte!=-1)
            byte=ReadOneByte();
        instructionPrefixes.PrimaryOpcode=byte;
        bool boolenFind= FindInstruction(&instructionPrefixes);
        if(boolenFind){
            WriteOperands(&instructionPrefixes);
        }
    //}
}
__int8 Resolvent::Prefix(InstructionPrefixes * instructionPrefixes,BYTE prefix){
    switch(prefix){
    case 0x26:
        instructionPrefixes->Prefix=0x26;
        break;
    case 0x2E:
        instructionPrefixes->Prefix= 0x2E;
        break;
    case 0x36:
        instructionPrefixes->Prefix= 0x36;
        break;
    case 0x3E:
        instructionPrefixes->Prefix= 0x3E;
        break;
    case 0x64:
        instructionPrefixes->Prefix= 0x64;
        break;
    case 0x65:
        instructionPrefixes->Prefix= 0x65;
        break;
    case 0x66:
        instructionPrefixes->Prefix= 0x66;
        break;
    case 0x67:
        instructionPrefixes->Prefix= 0x67;
        break;
    case 0x9B:
        instructionPrefixes->Prefix= 0x9B;
        break;
    case 0xF0:
        instructionPrefixes->Prefix= 0xF0;
        break;
    case 0xF2:
        instructionPrefixes->Prefix= 0xF2;
        break;
    case 0xF3:
        instructionPrefixes->Prefix= 0xF3;
        break;
    default:
        instructionPrefixes->Prefix= 0;
        return -1;
        break;
    }
    textSection.BytesReadSize++;
    return 1;
}
__int8 Resolvent::Prefix0F(InstructionPrefixes * instructionPrefixes,BYTE prefix0f){
    switch(prefix0f){
    case 0x0F:
        instructionPrefixes->Prefix0F= 0x0F;
        break;
    default:
        instructionPrefixes->Prefix0F= 0;
        return -1;
    }
    textSection.BytesReadSize++;
    return 1;
}
bool Resolvent::FindInstruction(InstructionPrefixes * instructionPrefixes){
    QList<QJsonObject> matchingInstructions;
    QList<QJsonObject> matchingInstructions2;
    QJsonObject matchingInstruction;
    BYTE byte;
    matchingInstructions=bringInstructions.getInstructions(instructionPrefixes);
    if(matchingInstructions.size()>1){
        bool seconderyColumn=false;
        bool registerOpcodeFiled=false;
        for (const auto& matchingInstructionIn : matchingInstructions) {
            if(matchingInstructionIn["SecondaryOpcode"].toString()!=nullptr){
                seconderyColumn=true;
            }
            if(matchingInstructionIn["RegisterOpcodeFiled"].toString()!=nullptr){
                registerOpcodeFiled=true;
            }
        }
        textSection.BytesReadSize++;
        byte=ReadOneByte();
        if(seconderyColumn){
            instructionPrefixes->SecondaryOpcode=byte;
        }
        if(registerOpcodeFiled){
            instructionPrefixes->RegisterOpcodeFiled=byte;
            instructionPrefixes->RegisterOpcodeModRM=byte;
        }
        bool ok;
        for (const auto& matchingInstructionIn : matchingInstructions) {
            if( matchingInstructionIn["Prefix0F"].toString().toUInt(&ok,16)== instructionPrefixes->Prefix0F &&
                matchingInstructionIn["PrimaryOpcode"].toString().toUInt(&ok,16)== instructionPrefixes->PrimaryOpcode &&
                matchingInstructionIn["SecondaryOpcode"].toString().toUInt(&ok,16)==instructionPrefixes->SecondaryOpcode &&
                matchingInstructionIn["RegisterOpcodeFiled"].toString().toInt()==CalculationDigit(&instructionPrefixes->RegisterOpcodeFiled)){
                matchingInstructions2.append(matchingInstructionIn);
                break;
            }
        }
/************************************************************************************************************************************************
 * DİKKAT! / UYARI!
 * Aynı PrimaryOpcode, SecondaryOpcode ve Digit değerine sahip olan birden fazla tlaimatlar DB-DF Arasındadır.
 * Bu talimatlarda modrm değeri C0'a eşit ve büyük ise sadece ST operantına sahip talimatı alınır. Diğer durumda m64int,m94/108 veya m64real gibi talimatlar ele alınır.
 * 0. indexdeki talimat m64int,m94/108 veya m64real içerir, 1. indexdeki talimat sadece STX,STX,STX.... değerlerini içerir.
 ************************************************************************************************************************************************/
        if(matchingInstructions2.size()>1){
            matchingInstruction=matchingInstructions2.at(instructionPrefixes->RegisterOpcodeFiled>=0xC0 ? 1:0);
        }
        else{
            matchingInstruction=matchingInstructions2.at(0);
        }
    }
    else{
        matchingInstruction=matchingInstructions.at(0);
    }
    QString mNemonic=matchingInstruction["InstructionMnemonic"].toString();
    QString operand1=matchingInstruction["Operand1"].toString();
    QString operand2=matchingInstruction["Operand2"].toString();
    QString operand3=matchingInstruction["Operand3"].toString();
    QString operand4=matchingInstruction["Operand4"].toString();
    if(mNemonic==nullptr){
        return false;
    }

    memcpy_s(instructionPrefixes->InstructionMnemonic,OPERANDSSIZE,&mNemonic,sizeof(mNemonic));
    memcpy_s(instructionPrefixes->Operand1,OPERANDSSIZE,&operand1,sizeof(operand1));
    memcpy_s(instructionPrefixes->Operand2,OPERANDSSIZE,&operand2,sizeof(operand2));
    memcpy_s(instructionPrefixes->Operand3,OPERANDSSIZE,&operand3,sizeof(operand3));
    memcpy_s(instructionPrefixes->Operand4,OPERANDSSIZE,&operand4,sizeof(operand4));
    matchingInstructions.clear();
    matchingInstructions2.clear();
    return true;
}
__int8 Resolvent::CalculationDigit(BYTE* byte){
    return (*byte & MODRBITS)>>3;
}
__int8 Resolvent::CalculationRMDigit(BYTE* byte){
    return *byte & MODRMBITS;
}
__int8 Resolvent::CalculationMODDigit(BYTE* byte){
    return (*byte & MODMODBITS)>>6;
}
void Resolvent::WriteOperands(InstructionPrefixes * PinstructionPrefixes){
    __int8 index = CalculationDigit(&PinstructionPrefixes->RegisterOpcodeFiled);
#if OS==64
    index+ = CalculationRexPrefixR(instructionPrefixes->PrefixRex);
#endif
    for (char* op = PinstructionPrefixes->Operand1; op < PinstructionPrefixes->Operand1+sizeof(PinstructionPrefixes->Operand1)*4; op += sizeof(PinstructionPrefixes->Operand1)) {
#if OS==32
        WriteOperandType1(op,index);
#elif OS==64
        ModRMx64R(op,index);
#endif
    }
}
void Resolvent::ReadAndPlaceValues(InstructionPrefixes *  pinstructionPrefixes){
    for (char* op = pinstructionPrefixes->Operand1; op < pinstructionPrefixes->Operand1+sizeof(pinstructionPrefixes->Operand1)*4; op += sizeof(pinstructionPrefixes->Operand1)) {
        /*
         * BURADAKİ OKUMALARDA, TERSTEN YAZDIRMA VE İŞARETLİ SAYILARA DİKKAT EDİLECEK!
        */
        if(strcmp(op,IMM8)==0){
            //op= 1 Byte okuma
            //ReadByte(1);
        }
        if(strcmp(op,IMM16)==0){
            //op= 2 Byte okuma
            //ReadByte(2);
        }
        if(strcmp(op,IMM1632)==0){
            //op= 4 Byte okuma
            //ReadByte(4);
        }
        if(strcmp(op,IMM163264)==0){
            //op= 8 Byte okuma
            //ReadByte(8);
        }
    }
}
#if OS==32
void Resolvent::WriteOperandType1(char * op,__int8 index){
    if(strcmp(op,R8)==0){
        //memcpy_s(op,OPERANDSSIZE,tableModRMx32.r8[index],sizeof(tableModRMx32.r8[index]));
    }
    else if(strcmp(op,R16)==0){
       // memcpy_s(op,OPERANDSSIZE,tableModRMx32.r16[index],sizeof(tableModRMx32.r8[index]));
    }
    else if(strcmp(op,R32)==0 || strcmp(op,R1632)==0){
       // memcpy_s(op,OPERANDSSIZE,tableModRMx32.r32[index],sizeof(tableModRMx32.r8[index]));
    }
    else if(strcmp(op,RM8)==0){

    }
    else if(strcmp(op,RM16)==0){

    }
    else if(strcmp(op,RM32)==0){

    }
    else if(strcmp(op,RM64)==0){

    }
    // OPERANDLARI GİZLENECEK KOMUTLAR
    else if(strcmp(op,M8)==0){
        memset(op,0,OPERANDSSIZE);
    }
    else if(strcmp(op,M16)==0){
        memset(op,0,OPERANDSSIZE);
    }
    else if(strcmp(op,M32)==0){
        memset(op,0,OPERANDSSIZE);
    }
    else if(strcmp(op,M64)==0){
        memset(op,0,OPERANDSSIZE);
    }
    else if(strcmp(op,M1632)==0){
        memset(op,0,OPERANDSSIZE);
    }
    else if(strcmp(op,M16321632)==0){
        // BURASI AYRIYETTEN İNCELENECEK // BOUND' un alanı
    }
}
void Resolvent::WriteOperandType2(char * op,BYTE * registerOpcodeModRM,BYTE * registerOpcodeSIB){
    if(strcmp(op,ST)==0){
        memcpy_s(op,20,"ST(0)",5);
    }
    else if(strcmp(op,M32REAL)==0 || strcmp(op,M64REAL)==0 || strcmp(op,M80REAL)==0)
    {
        //R/M okuması gerçekleştirecek
    }
    else if(strcmp(op,STI)==0){
        if(((int)(unsigned char)*registerOpcodeModRM)>=0xC0){
            __int16 stDigit=CalculationRMDigit(registerOpcodeModRM);
            char stOperand[6]="ST( )";//3. index boş,Digit oraya  yazılacak
            stDigit += 0x30;
            memcpy_s(stOperand+3,1,&stDigit, 1);
            memcpy_s(op,OPERANDSSIZE,&stOperand,sizeof(stOperand));
        }
        else{
            //effective address ALANINA BAKILACAK
            CHAR  operand[OPERANDSSIZE];
            CalculationRMDigit(registerOpcodeModRM);
           // const char * effectiveAddress = tableModRMEffectiveAddressModx32.EffectiveAddress[CalculationRMDigit(registerOpcodeModRM)];
            //memcpy_s(operand,OPERANDSSIZE,effectiveAddress,sizeof(effectiveAddress));
            __int8 modDigit = CalculationMODDigit(registerOpcodeModRM);
            if(true){//effectiveAddress==SIB){

            }
            else{
                switch (modDigit) {
                case 1:
                    // DISP 8 DEĞER OKUMASI
                    strcat_s(operand,sizeof(operand),"+25");
                    break;
                case 2:
                    // DISP 32 DEĞER OKUMASI
                    strcat_s(operand,sizeof(operand),"-25");
                    break;
                }
            }
            BRACKET(operand);
            memcpy_s(op,OPERANDSSIZE,operand,OPERANDSSIZE);
        }
    }
    else if(strcmp(op,ST1)==0){
        memcpy_s(op,OPERANDSSIZE,"ST(1)",6);
    }
    else if(strcmp(op,ST2)==0){
        memcpy_s(op,OPERANDSSIZE,"ST(2)",6);
    }
    else if(strcmp(op,ST)==0){
        memcpy_s(op,OPERANDSSIZE,"ST(0)",6);
    }

}
#elif OS==64
void Resolvent::ModRMx64R(char * op,__int8 index){
    if(strcmp(op,R8)==0){
        memcpy_s(op,20,tableModRMx32.r8[index],sizeof(tableModRMx32.r8[index]));
    }
    else if(strcmp(op,R16)==0){
        memcpy_s(op,20,tableModRMx32.r16[index],sizeof(tableModRMx32.r8[index]));
    }
    else if(strcmp(op,R32)==0 || strcmp(op,R1632)==0){
        memcpy_s(op,20,tableModRMx32.r32[index],sizeof(tableModRMx32.r8[index]));
    }
}
__int16 Resolvent::CalculationRexPrefixB(BYTE* byte){
    return (strtoul(byte, 0, 16)) & REXB;
}
__int16 Resolvent::CalculationRexPrefixX(BYTE* byte){
    return (strtoul(byte, 0, 16)) & REXX>>1;
}
__int16 Resolvent::CalculationRexPrefixR(BYTE* byte){
    return (strtoul(byte, 0, 16)) & REXR>>2;
}
__int16 Resolvent::CalculationRexPrefixW(BYTE* byte){
    return (strtoul(byte, 0, 16)) &  REXW>>3;
}
#endif













