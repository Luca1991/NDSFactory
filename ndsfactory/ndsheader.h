#pragma once

#include <cstdint>

#define IconTitleSize 0xA00
#define Arm9FooterSize 0xC

#pragma pack(push, 1)
struct NDSHeader
{
    char GameTitle[0xC];
    char GameCode[0x4];
    unsigned char MakerCode[0x2];
    unsigned char UnitCode;
    unsigned char DeviceType;
    unsigned char DeviceSize;
    unsigned char Reserved1[0x9];
    unsigned char RomVersion;
    unsigned char Flags;

    uint32_t Arm9RomAddr;
    uint32_t Arm9EntryAddr;
    uint32_t Arm9RamAddr;
    uint32_t Arm9Size;

    uint32_t Arm7RomAddr;
    uint32_t Arm7EntryAddr;
    uint32_t Arm7RamAddr;
    uint32_t Arm7Size;

    uint32_t FilenameTableAddr;
    uint32_t FilenameSize;
    uint32_t FATAddr;
    uint32_t FATSize;

    uint32_t Arm9OverlayAddr;
    uint32_t Arm9OverlaySize;
    uint32_t Arm7OverlayAddr;
    uint32_t Arm7OverlaySize;

    uint32_t NormalCommandsSettings;
    uint32_t Key1CommandsSettings;

    uint32_t IconTitleAddr;

    uint16_t SecureAreaCRC16;
    uint16_t SecureAreaLoadingTimeout;

    uint32_t ARM9AutoLoadListRamAddr;
    uint32_t ARM7AutoLoadListRamAddr;

    uint64_t SecureAreaDisable;

    uint32_t RomSize;
    uint32_t HeaderSize;

    unsigned char Reserved2[0x38];

    unsigned char NintendoLogo[0x9C];
    uint16_t NintendoLogoCRC;
    uint16_t HeaderCRC16;

    uint32_t DebugRomAddr;
    uint32_t DebugSize;
    uint32_t DebugRamAddr;

    unsigned char Reserved3[0x4];
    unsigned char Reserved4[0x90];
};
#pragma pack(pop)
