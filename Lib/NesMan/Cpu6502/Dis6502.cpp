//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ----   NES Debugger Project   ----                  **
**                                                                      **
**          Copyright (C), 2026-2026, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING or LICENSE files)                     **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Dis6502 class.
**
**      @file       NesMan/Dis6502.cpp
**/

#include    "NesDbg/pch/PreCompile.h"

#include    "Dis6502.h"

#include    "NesDbg/NesMan/BaseCpuCore.h"
#include    "NesDbg/NesMan/MemoryManager.h"
#include    "NesDbg/NesMan/NesManager.h"

#include    "InstTable.h"

#include    <cstring>
#include    <ostream>
#include    <sstream>


NESDBG_NAMESPACE_BEGIN
namespace  NesMan  {

namespace  {

CONSTEXPR_VAR   const   MnemonicMap
dis6502Mnemonics[] = {
    //  NOP 系  //
    { 0x000000FF, 0x00000082, "nop" },
    { 0x000000FF, 0x000000C2, "nop" },
    { 0x000000FF, 0x000000E2, "nop" },

    //  HLT 系  //
    { 0x0000008F, 0x00000002, "hlt" },
    { 0x0000009F, 0x00000092, "hlt" },

    //  xxx1 0000   //
    { 0x000000FF, 0x00000010, "BPL" },
    { 0x000000FF, 0x00000030, "BMI" },
    { 0x000000FF, 0x00000050, "BVC" },
    { 0x000000FF, 0x00000070, "BVS" },
    { 0x000000FF, 0x00000090, "BCC" },
    { 0x000000FF, 0x000000B0, "BCS" },
    { 0x000000FF, 0x000000D0, "BNE" },
    { 0x000000FF, 0x000000F0, "BEQ" },

    //  xxx1 1000   //
    { 0x000000FF, 0x00000018, "CLC" },
    { 0x000000FF, 0x00000038, "SEC" },
    { 0x000000FF, 0x00000058, "CLI" },
    { 0x000000FF, 0x00000078, "SEI" },
    { 0x000000FF, 0x00000098, "TYA" },
    { 0x000000FF, 0x000000B8, "CLV" },
    { 0x000000FF, 0x000000D8, "CLD" },
    { 0x000000FF, 0x000000F8, "SED" },

    //  xxxx xx01   //
    { 0x000000E3, 0x00000001, "ORA" },
    { 0x000000E3, 0x00000021, "AND" },
    { 0x000000E3, 0x00000041, "EOR" },
    { 0x000000E3, 0x00000061, "ADC" },
    { 0x000000FF, 0x00000089, "nop" },
    { 0x000000E3, 0x00000081, "STA" },
    { 0x000000E3, 0x000000A1, "LDA" },
    { 0x000000E3, 0x000000C1, "CMP" },
    { 0x000000E3, 0x000000E1, "SBC" },

    //  xxxx xx10   //
    { 0x0000009F, 0x0000001A, "nop" },
    { 0x000000DF, 0x000000DA, "nop" },
    { 0x000000FF, 0x0000000A, "ASL" },
    { 0x000000E3, 0x00000002, "ASL" },
    { 0x000000FF, 0x0000002A, "ROL" },
    { 0x000000E3, 0x00000022, "ROL" },
    { 0x000000FF, 0x0000004A, "LSR" },
    { 0x000000E3, 0x00000042, "LSR" },
    { 0x000000FF, 0x0000006A, "ROR" },
    { 0x000000E3, 0x00000062, "ROR" },

    { 0x000000FF, 0x0000008A, "TXA" },
    { 0x000000FF, 0x0000009A, "TXS" },
    { 0x000000FF, 0x0000009E, "shx" },
    { 0x000000E3, 0x00000082, "STX" },

    { 0x000000FF, 0x000000AA, "TAX" },
    { 0x000000FF, 0x000000BA, "TSX" },
    { 0x000000E3, 0x000000A2, "LDX" },

    { 0x000000FF, 0x000000CA, "DEX" },
    { 0x000000E7, 0x000000C6, "DEC" },
    { 0x000000FF, 0x000000EA, "NOP" },
    { 0x000000E7, 0x000000E6, "INC" },

    //  xxxx xx11   //
    { 0x000000FF, 0x0000000B, "anc" },
    { 0x000000E3, 0x00000003, "slo" },
    { 0x000000FF, 0x0000002B, "anc" },
    { 0x000000E3, 0x00000023, "rla" },
    { 0x000000FF, 0x0000004B, "alr" },
    { 0x000000E3, 0x00000043, "sre" },
    { 0x000000FF, 0x0000006B, "arr" },
    { 0x000000E3, 0x00000063, "rra" },

    { 0x000000FF, 0x0000008B, "ane" },
    { 0x000000FF, 0x00000093, "sha" },
    { 0x000000FF, 0x0000009B, "shs" },
    { 0x000000FF, 0x0000009F, "sha" },
    { 0x000000E3, 0x00000083, "sax" },

    { 0x000000FF, 0x000000BB, "las" },
    { 0x000000E3, 0x000000A3, "lax" },
    { 0x000000FF, 0x000000CB, "sbx" },
    { 0x000000E3, 0x000000C3, "dcp" },
    { 0x000000FF, 0x000000EB, "sbc" },
    { 0x000000E3, 0x000000E3, "isb" },

    //  xxx0 0000   //
    { 0x000000FF, 0x00000000, "BRK" },
    { 0x000000FF, 0x00000020, "JSR" },
    { 0x000000FF, 0x00000040, "RTI" },
    { 0x000000FF, 0x00000060, "RTS" },
    { 0x000000FF, 0x00000080, "nop" },
    { 0x000000FF, 0x000000A0, "LDY" },
    { 0x000000FF, 0x000000C0, "CPY" },
    { 0x000000FF, 0x000000E0, "CPX" },

    //  xxx0 1000   //
    { 0x000000FF, 0x00000008, "PHP" },
    { 0x000000FF, 0x00000028, "PLP" },
    { 0x000000FF, 0x00000048, "PHA" },
    { 0x000000FF, 0x00000068, "PLA" },
    { 0x000000FF, 0x00000088, "DEY" },
    { 0x000000FF, 0x000000A8, "TAY" },
    { 0x000000FF, 0x000000C8, "INY" },
    { 0x000000FF, 0x000000E8, "INX" },

    //  xxxx 0100   //
    { 0x000000F7, 0x00000024, "BIT" },
    { 0x000000DF, 0x0000004C, "JMP" },
    { 0x000000FF, 0x0000009C, "shy" },
    { 0x000000E7, 0x00000084, "STY" },
    { 0x000000E7, 0x000000A4, "LDY" },
    { 0x000000F7, 0x000000C4, "CPY" },
    { 0x000000F7, 0x000000E4, "CPX" },
    { 0x00000007, 0x00000004, "nop" },

    //  Unknown.    //
    { 0x00000000, 0x00000000,  "[ ??? ]" },
};

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    Dis6502  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

Dis6502::Dis6502()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

Dis6502::~Dis6502()
{
}

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//----------------------------------------------------------------
//    ニーモニックを表示する。
//

std::ostream  &
Dis6502::writeMnemonic(
        std::ostream       &outStr,
        GuestMemoryAddress  gmAddr,
        GuestMemoryAddress &gmNext)  const
{
    char    buf[256] = { 0 };
    size_t  len = 0;
    size_t  rem = sizeof(buf) - 1;
    char *  dst = buf;

    //  現時点でのレジスタのコピーを取得する。  //
    RegBank         cpuRegs;
    this->m_pManNes->getCurrentCpu().getRegisters(cpuRegs);

    const uint32_t  opeCode = this->m_pManMem->readMemory<uint32_t>(gmAddr);
    const MnemonicMap *  oc = dis6502Mnemonics;
    for ( ; (opeCode & oc->mask) != oc->cval; ++ oc );

    const  OpeCode  ocInst  = (opeCode & 0x000000FF);
    const  BtByte   opSize  = g_opeCodeSize[ocInst];
    const  AddressingMode::ModeValues
        adr = AddressingMode::g_opeCodeAddrs[ocInst];

    gmNext  = gmAddr + opSize;

    len = snprintf(dst, rem, "  %04X:  %02X", gmAddr, ocInst);
    if ( gmAddr == cpuRegs.PC ) {
        dst[0] = '>';
    }
    dst += len;
    rem -= len;

    uint32_t    ocTemp  = (opeCode >> 8);
    switch ( opSize ) {
    case  3:
        len = snprintf(dst, rem, " %02X", (ocTemp & 0xFF));
        dst += len;
        rem -= len;
        ocTemp  >>= 8;
        //  no break;
    case  2:
        len = snprintf(dst, rem, " %02X", (ocTemp & 0xFF));
        dst += len;
        rem -= len;
        ocTemp  >>= 8;
        //  no break;
    default:
        break;
    }
    len = dst - buf;
    while ( len < 20 ) {
        * (dst ++)  = ' ';
        ++ len;
    }

    const  char  *  src = oc->mnemonic;
    len = snprintf(dst, rem, "%s  ", src);
    outStr  <<  buf;

    //  オペランドの表示。  //
    memset(buf, 0, sizeof(buf));
    dst = buf;
    rem = sizeof(buf) - 1;

    switch ( adr ) {
    case  AddressingMode::AM_IMP:
        break;
    case  AddressingMode::AM_ACC:
        len = snprintf(dst, rem, "A");
        break;
    case  AddressingMode::AM_IMM:
        len = writeImmediage(opeCode, dst, rem);
        break;
    case  AddressingMode::AM_ZER:
        len = writeZeroPage(opeCode, dst, rem, ' ', 0);
        break;
    case  AddressingMode::AM_ZPX:
        len = writeZeroPage(opeCode, dst, rem, 'X', cpuRegs.X);
        break;
    case  AddressingMode::AM_ZPY:
        len = writeZeroPage(opeCode, dst, rem, 'Y', cpuRegs.Y);
        break;
    case  AddressingMode::AM_ABS:
        if ( (ocInst == 0x20) || (ocInst == 0x4C) ) {
            len = writeJumpAbsolute(opeCode, dst, rem);
            break;
        }
        len = writeAbsolute(opeCode, dst, rem, ' ', 0);
        break;
    case  AddressingMode::AM_ABX:
        len = writeAbsolute(opeCode, dst, rem, 'X', cpuRegs.X);
        break;
    case  AddressingMode::AM_ABY:
        len = writeAbsolute(opeCode, dst, rem, 'Y', cpuRegs.Y);
        break;
    case  AddressingMode::AM_IDX:
        len = writePreIndexIndirect (opeCode, dst, rem, 'X', cpuRegs.X);
        break;
    case  AddressingMode::AM_IDY:
        len = writePostIndexIndirect(opeCode, dst, rem, 'Y', cpuRegs.Y);
        break;
    case  AddressingMode::AM_REL:
        len = writeRelative(opeCode, dst, rem, gmNext);
        break;
    case  AddressingMode::AM_IND:
        len = writeJumpIndirect(opeCode, dst, rem);
        break;
    default:
        break;
    }
    outStr  <<  buf;

    return ( outStr );
}

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    絶対番地オペランドを表示する。
//

inline  size_t
Dis6502::writeAbsolute(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen,
        const  char     regName,
        const  RegType  idxReg)  const
{
    const   GuestMemoryAddress  gmShow  = (opeCode >> 8) & 0x0000FFFF;
    const   GuestMemoryAddress  gmAddr  = (gmShow + idxReg) & 0x0000FFFF;
    const   BtByte  cv  = this->m_pManMem->peekMemory<BtByte>(gmAddr);

    return  snprintf(dst, remLen, "$%04X%c%c @ $%04X = #$%02X",
                    gmShow, (regName != ' ' ? ',' : ' '), regName,
                    gmAddr, cv
    );
}

//----------------------------------------------------------------
//    即値
//

inline  size_t
Dis6502::writeImmediage(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen)  const
{
    return  snprintf(dst, remLen, "#$%02X", (opeCode >> 8) & 0x00FF);
}

//----------------------------------------------------------------
//    絶対番地ジャンプ。
//

inline  size_t
Dis6502::writeJumpAbsolute(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen)  const
{
    const   GuestMemoryAddress  gmShow  = (opeCode >> 8) & 0x0000FFFF;
    return  snprintf(dst, remLen, "$%04X", gmShow);
}

//----------------------------------------------------------------
//    インダイレクトジャンプ。
//

inline  size_t
Dis6502::writeJumpIndirect(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen)  const
{
    const   GuestMemoryAddress  gmShow  = (opeCode >> 8) & 0xFFFF;
    return  snprintf(dst, remLen, "($%04X)", gmShow);
}

//----------------------------------------------------------------
//    インダイレクトオペランドを表示する。
//

inline  size_t
Dis6502::writePostIndexIndirect(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen,
        const  char     regName,
        const  RegType  idxReg)  const
{
    const   GuestMemoryAddress  gmShow  = (opeCode >> 8) & 0x000000FF;
    return  snprintf(dst, remLen, "($%02X),%c", gmShow, regName);
}

//----------------------------------------------------------------
//    インダイレクトオペランドを表示する。
//

inline  size_t
Dis6502::writePreIndexIndirect(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen,
        const  char     regName,
        const  RegType  idxReg)  const
{
    const   GuestMemoryAddress  gmShow  = (opeCode >> 8) & 0x000000FF;
    return  snprintf(dst, remLen, "($%02X,%c)", gmShow, regName);
}

//----------------------------------------------------------------
//    相対アドレスオペランドを表示する。
//

inline  size_t
Dis6502::writeRelative(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen,
        GuestMemoryAddress  regPC)  const
{
    const   GuestMemoryAddress  gmOffs  = (opeCode >> 8) & 0x00FF;
    const   GuestMemoryAddress  gmAddr  =
        (regPC & 0xFF00) | ((regPC + gmOffs) & 0x00FF);
    return  snprintf(dst, remLen, "$%04X  ; $%02X", gmAddr, gmOffs);
}

//----------------------------------------------------------------
//    ゼロページオペランドを表示する。
//

inline  size_t
Dis6502::writeZeroPage(
        const  OpeCode  opeCode,
        char  *  const  dst,
        const  size_t   remLen,
        const  char     regName,
        const  RegType  idxReg)  const
{
    const   GuestMemoryAddress  gmShow  = (opeCode >> 8) & 0x000000FF;
    const   GuestMemoryAddress  gmAddr  = (gmShow + idxReg) & 0x000000FF;
    const   BtByte  cv  = this->m_pManMem->peekMemory<BtByte>(gmAddr);

    return  snprintf(dst, remLen, "<$%02X%c%c @ $%02X = #$%02X",
                    gmShow, (regName != ' ' ? ',' : ' '), regName,
                    gmAddr, cv
    );
}

//========================================================================
//
//    For Tests.
//

const   std::string
dumpMnemonicMap(
        const  OpeCode  opeCode)
{
    const MnemonicMap *  oc = dis6502Mnemonics;
    for ( ; (opeCode & oc->mask) != oc->cval; ++ oc );
    return ( std::string(oc->mnemonic) );
}

}   //  End of namespace  NesMan
NESDBG_NAMESPACE_END
