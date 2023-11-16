#ifndef MODRMBYTE_H
#define MODRMBYTE_H
#include <Header/Define.h>

struct ModRMAndSibByte
{
public:
    void    CalculationEffectiveAddress();
    void    CalculationScalerIndex();
private:
    const char * effectiveAddress   [8] =   {EAX,ECX,EDX,EBX,SIB,ESI,EDI};
    const char * scaledIndex        [8] =   {EAX,ECX,EDX,EBX,NONE,EBP,ESI,EDI};
    const char * base               [8] =   {EAX,ECX,EDX,ESP,EBPMOD,ESI,EDI};
    const char * r8                 [8] =   {AL,CL,DL,BL,AH,CH,DH,BH};
    const char * r16                [8] =   {AX,CX,DX,BX,BP,SI,DI};
    const char * r32                [8] =   {EAX,ECX,EDX,ESP,EBP,ESI,EDI};
    const char * mm                 [8] =   {MM0,MM1,MM2,MM3,MM4,MM5,MM6,MM7};
    const char * xmm                [8] =   {XMM0,XMM1,XMM2,XMM3,XMM4,XMM5,XMM6,XMM7};
    const char * sreg               [8] =   {ES,CS,SS,DS,FS,GS,RES,RES};
};

#endif // MODRMBYTE_H
