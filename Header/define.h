
#ifndef DEFINE_H
#define DEFINE_H
#include <stdio.h>

#include <minwindef.h>
#endif // DEFINE_H

/* ****For x64 REX Prefix: 0100WRXB  ****
* W     -0->  0 = CS.D tarafından belirlenen operand boyutu
* W     -0->  1 = 64 Bit İşlenen Boyutu
* R     -1-> ModR/M reg alanının genişletilmesi
* X     -1-> SİB endeks alanının genişletilmesi
* B     -1-> ModR/M r/m alanının, SİB temel alanının veya Opcode reg alanının genişletilmesi
*/
#define REXB        0X1
#define REXX        0X2
#define REXR        0X4
#define REXW        0X8
/*
 * ModR/M Byte
*/
#define MODMODBITS  0B11000000
#define MODRBITS    0B00111000
#define MODRMBITS   0B00000111

/*
 * x86x64  register and operands
*/
#define AH          "AH"
#define AL          "AL"
#define AX          "AX"
#define BH          "BH"
#define BL          "BL"
#define BP          "BP"
#define BPL         "BPL"
#define BX          "BX"
#define CH          "CH"
#define CL          "CL"
#define CR0         "CR0"
#define CR2         "CR2"
#define CR3         "CR3"
#define CR4         "CR4"
#define CR8         "CR8"
#define CRN         "CRN"
#define CS          "CS"
#define CX          "CX"
#define DH          "DH"
#define DI          "DI"
#define DIL         "DIL"
#define DL          "DL"
#define DR0         "DR0"
#define DR1         "DR1"
#define DR2         "DR2"
#define DR3         "DR3"
#define DR41        "DR4"
#define DR51        "DR5"
#define DR6         "DR6"
#define DR7         "DR7"
#define DRN         "DRN"
#define DS          "DS"
#define DX          "DX"
#define EAX         "EAX"
#define EBP         "EBP"
#define EBX         "EBX"
#define ECX         "ECX"
#define EDI         "EDI"
#define EDX         "EDX"
#define EFLAGS      "EFLAGS"
#define ES          "ES"
#define ESI         "ESI"
#define ESP         "ESP"
#define FLAGS       "FLAGS"
#define FS          "FS"
#define GDTR        "GDTR"
#define GS          "GS"
#define IA32BIOSSIG "IA32BIOSSIG"
#define IA32KERNEL  "IA32KERNEL"
#define IDTR        "IDTR"
#define IMM16       "IMM16"
#define IMM1632     "IMM1632"
#define IMM163264   "IMM163264"
#define IMM8        "IMM8"
#define invd        "invd"
#define LDTR        "LDTR"
#define M           "M"
#define M128        "M128"
#define M1428       "M1428"
#define M16         "M16"
#define M16163264   "M16163264"
#define M1632       "M1632"
#define M163264     "M163264"
#define M16INT      "M16INT"
#define M32         "M32"
#define M3264       "M3264"
#define M32INT      "M32INT"
#define M32REAL     "M32REAL"
#define M512        "M512"
#define M64         "M64"
#define M64INT      "M64INT"
#define M64REAL     "M64REAL"
#define M8          "M8"
#define M80DEC      "M80DEC"
#define M80REAL     "M80REAL"
#define M94108      "M94108"
#define MM          "MM"
#define MM0         "MM0"
#define MM1         "MM1"
#define MM2         "MM2"
#define MM3         "MM3"
#define MM4         "MM4"
#define MM5         "MM5"
#define MM6         "MM6"
#define MM7         "MM7"
#define MMM64       "MMM64"
#define MOFFS163264 "MOFFS163264"
#define MOFFS8      "MOFFS8"
#define MSR         "MSR"
#define MSW         "MSW"
#define R           "R"
#define R10         "R10"
#define R10B        "R10B"
#define R10D        "R10D"
#define R10W        "R10W"
#define R11         "R11"
#define R11B        "R11B"
#define R11D        "R11D"
#define R11W        "R11W"
#define R12         "R12"
#define R12B        "R12B"
#define R12D        "R12D"
#define R12W        "R12W"
#define R13         "R13"
#define R13B        "R13B"
#define R13D        "R13D"
#define R13W        "R13W"
#define R14         "R14"
#define R14B        "R14B"
#define R14D        "R14D"
#define R14W        "R14W"
#define R15         "R15"
#define R15B        "R15B"
#define R15D        "R15D"
#define R15W        "R15W"
#define R16         "R16"
#define R32         "R32"
#define R1632       "R1632"
#define R163264     "R163264"
#define R3264       "R3264"
#define R64         "R64"
#define R6416       "R6416"
#define R8          "R8"
#define R8B         "R8B"
#define R8D         "R8D"
#define R8W         "R8W"
#define R9          "R9"
#define R9B         "R9B"
#define R9D         "R9D"
#define R9W         "R9W"
#define RAX         "RAX"
#define RBP         "RBP"
#define RBX         "RBX"
#define RCX         "RCX"
#define RDI         "RDI"
#define RDX         "RDX"
#define REL1632     "REL1632"
#define REL8        "REL8"
#define RFLAGS      "RFLAGS"
#define RM16        "RM16"
#define RM1632      "RM1632"
#define RM163264    "RM163264"
#define RM32        "RM32"
#define RM3264      "RM3264"
#define RM64        "RM64"
#define RM6416      "RM6416"
#define RM8         "RM8"
#define RSI         "RSI"
#define RSP         "RSP"
#define SI          "SI"
#define SIL         "SIL"
#define SP          "SP"
#define SPL         "SPL"
#define SREG        "SREG"
#define SS          "SS"
#define ST          "ST"
#define ST1         "ST1"
#define ST2         "ST2"
#define STI         "STI"
#define STIM32REAL  "STIM32REAL"
#define TR          "TR"
#define XCR         "XCR"
#define XMM         "XMM"
#define XMM0        "XMM0"
#define XMM1        "XMM1"
#define XMM10       "XMM10"
#define XMM11       "XMM11"
#define XMM12       "XMM12"
#define XMM13       "XMM13"
#define XMM14       "XMM14"
#define XMM15       "XMM15"
#define XMM2        "XMM2"
#define XMM3        "XMM3"
#define XMM4        "XMM4"
#define XMM5        "XMM5"
#define XMM6        "XMM6"
#define XMM7        "XMM7"
#define XMM8        "XMM8"
#define XMM9        "XMM9"
#define XMMM128     "XMMM128"
#define XMMM32      "XMMM32"
#define XMMM64      "XMMM64"
#define RES         "RES"
#define M16321632   "M16321632"
#define DISP8       "DISP8"
#define DISP32      "DISP32"
#define SIB         "SIB"
#define NONE        "NONE"
#define EBPMOD      "EBPMOD"
#define BRACKET(v)  (snprintf(v, 10,"[%s]", v+1))
#define OS          32
#define OPERANDSSIZE 20

struct InstructionPrefixes{
    unsigned __int8 Prefix;
    unsigned __int8 Prefix0F;
    unsigned __int8 PrimaryOpcode;
    unsigned __int8 SecondaryOpcode;
    unsigned __int8 RegisterOpcodeFiled;
    unsigned __int8 RegisterOpcodeModRM;
    unsigned __int8 RegisterOpcodeSIB;
    char InstructionMnemonic[OPERANDSSIZE];
    char Operand1[OPERANDSSIZE];
    char Operand2[OPERANDSSIZE];
    char Operand3[OPERANDSSIZE];
    char Operand4[OPERANDSSIZE];
};
/*
struct Instructions{
    unsigned __int8 Prefix;
    unsigned __int8 Prefix0F;
    unsigned __int8 PrimaryOpcode;
    unsigned __int8 SecondaryOpcode;
    unsigned __int8 RegisterOpcodeFiled;
    const char * InstructionMnemonic;
    const char * Operand1;
    const char * Operand2;
    const char * Operand3;
    const char * Operand4;
};*/

struct TextSection{
    BYTE *  TextDataAddress;
    DWORD   TextDataSize;
    DWORD   BytesReadSize=0;
};
