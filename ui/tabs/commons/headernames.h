#pragma once

#include <array>
#include <string>
#include <vector>

extern std::vector<std::string> ndsHeaderNamesArr;

namespace NDSHeaderNames {
    enum  {
        GameTitle,
        GameCode,
        MakerCode,
        UnitCode,
        DeviceCode,
        CardSize,
        CardInfo,
        Flags,
        ARM9RomAddress,
        ARM9EntryAddress,
        ARM9RamAddress,
        ARM9Size,
        ARM7RomAddress,
        ARM7EntryAddress,
        ARM7RamAddress,
        ARM7Size,
        FilenameTableAddress,
        FilenameTableSize,
        FATAddress,
        FATSize,
        ARM9OverlayAddress,
        ARM9OverlaySize,
        ARM7OverlayAddress,
        ARM7OverlaySize,
        Port40001A4hNC,
        Port40001a4hKC,
        IconTitleAddress,
        SecureAreaCRC16,
        SecureAreaTimeout,
        ARM9ALRamAddress,
        ARM7ALRamAddress,
        SecureAreaDisable,
        UsedRomSize,
        HeaderSize,
        NintendoLogo,
        NintendoLogoCRC,
        HeaderCRC,
        DebugRomAddress,
        DebugSize,
        DebugRamAddress,
        FATFilesAddress
    };
}
