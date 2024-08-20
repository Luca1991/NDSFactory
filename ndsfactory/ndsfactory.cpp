#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <format>
#include "ndsfactory.h"
#include "fatstruct.h"
#include "crctable.h"


// Byte offsets for interpreting memory
#define SECOND_BYTE_SHIFT 8
#define THIRD_BYTE_SHIFT 16
#define FOURTH_BYTE_SHIFT 24

// Magic values for FAT extraction
#define CONTROL_BYTE_LENGTH_MASK 0x7F
#define CONTROL_BYTE_DIR_MASK 0x80
#define DUMMY_CONTROL_VALUE 0xFF
#define FNT_HEADER_OFFSET_MASK 0XFFF
#define ROOT_DIRECTORY_ADDRESS 0xF000


NDSFactory::NDSFactory()
{

}

bool NDSFactory::loadRomHeader(const std::string& romPath, std::vector<char>& romHeader)
{
    std::streampos headerSize = sizeof(NDSHeader);
    std::ifstream romFile (romPath, std::ios::in|std::ios::binary|std::ios::ate);
    if (romFile.is_open())
    {
        romHeader.resize(static_cast<unsigned long>(headerSize));

        romFile.seekg (0, std::ios::beg);
        romFile.read (romHeader.data(), headerSize);
        romFile.close();

        return true;
    }
    return false;
}

bool NDSFactory::dumpDataFromFile(const std::string& romPath, const std::string& savePath, uint32_t startAddr, uint32_t size)
{
    std::ifstream romFile (romPath, std::ios::in|std::ios::binary|std::ios::ate);
    std::ofstream savedFile (savePath, std::ios::out|std::ios::binary|std::ios::ate);
    if (romFile.is_open() && savedFile.is_open())
    {
        std::vector<char> dumpBuffer(size);
        romFile.seekg (startAddr, std::ios::beg);
        romFile.read (dumpBuffer.data(), size);
        romFile.close();

        savedFile.write(dumpBuffer.data(), size);
        savedFile.close();
        return true;
    }
    return false;
}

bool NDSFactory::logToFile(const std::string& logPath, const std::string& log)
{
    std::ofstream savedFile(logPath, std::ios::out | std::ios::binary | std::ios::app);
    if (savedFile.is_open())
    {
		savedFile.write(log.c_str(), log.size());
        savedFile.close();
        return true;
    }
    return false;
}


bool NDSFactory::readBytesFromFile(std::vector<char>& byteBuffer, const std::string& romPath, uint32_t startAddr, uint32_t size)
{
    std::ifstream romFile (romPath, std::ios::in|std::ios::binary|std::ios::ate);
    if (romFile.is_open())
    {
        romFile.seekg (startAddr, std::ios::beg);
        romFile.read (byteBuffer.data(), size);
        romFile.close();
        return true;
    }
    return false;
}

bool NDSFactory::writeSectionToFile(const std::string& sectionPath, const std::string& savePath, uint32_t startAddr, uint32_t size)
{
    std::ifstream sectionFile (sectionPath, std::ios::in|std::ios::binary|std::ios::ate);
    std::ofstream savedFile (savePath, std::ios::out|std::ios::binary|std::ios::app);
    if (sectionFile.is_open() && savedFile.is_open())
    {
        std::vector<char> dumpBuffer(size);
        sectionFile.seekg (0, std::ios::beg);
        sectionFile.read (dumpBuffer.data(), size);
        sectionFile.close();

        savedFile.seekp(startAddr, std::ios::beg);
        savedFile.write(dumpBuffer.data(), size);
        savedFile.close();
        return true;
    }
    return false;
}

bool NDSFactory::writeBytesToFile(std::vector<char>& byteBuffer, const std::string& savePath, uint32_t startAddr, uint32_t size)
{
    std::ofstream savedFile (savePath, std::ios::out|std::ios::binary|std::ios::app);
    if (savedFile.is_open())
    {
        savedFile.seekp(startAddr, std::ios::beg);
        savedFile.write(byteBuffer.data(), size);
        savedFile.close();
        return true;
    }
    return false;
}


bool NDSFactory::writePaddingToFile(char paddingChar, const std::string& filePath, uint32_t startAddr, const uint32_t size)
{
    std::vector<char> paddingBytes(size, paddingChar);
    return writeBytesToFile(paddingBytes, filePath, startAddr, size);
}

int NDSFactory::getCardSizeInBytes(int cardType)
{
    return static_cast<int>(pow(2, 17 + cardType));
}

bool NDSFactory::checkArm9FooterPresence(const std::string& sectionPath, uint32_t size)
{
    std::ifstream sectionFile (sectionPath, std::ios::in|std::ios::binary|std::ios::ate);
    if (sectionFile.is_open())
    {
        std::streamoff sectionRealSize = sectionFile.tellg();
        sectionFile.close();
        if (sectionRealSize >= size + Arm9FooterSize)
        {
            return true;
        }
    }
    return false;
}

bool NDSFactory::extractFatData(const std::string& fatDataSectionPath, const std::string& fatSectionPath,
    const std::string& fntSectionPath, uint32_t originalFatDataAddr, const std::string& savePath, bool logFileIDs)
{
    std::vector<char> fatDataBytes;
    std::vector<char> fatBytes;
    std::vector<char> fntBytes;

    std::ifstream fatDataSectionFile(fatDataSectionPath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!fatDataSectionFile.is_open()) return false;
    std::streamoff fatDataSectionSize = fatDataSectionFile.tellg();
    fatDataBytes.resize(fatDataSectionSize);
    fatDataSectionFile.seekg(0, std::ios::beg);
    fatDataSectionFile.read(fatDataBytes.data(), fatDataSectionSize);
    fatDataSectionFile.close();

    std::ifstream fatSectionFile(fatSectionPath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!fatSectionFile.is_open()) return false;
    std::streamoff fatSectionSize = fatSectionFile.tellg();
    fatBytes.resize(fatSectionSize);
    fatSectionFile.seekg(0, std::ios::beg);
    fatSectionFile.read(fatBytes.data(), fatSectionSize);
    fatSectionFile.close();

    std::ifstream fntSectionFile(fntSectionPath, std::ios::in | std::ios::binary | std::ios::ate);
    if (!fntSectionFile.is_open()) return false;
    std::streamoff fntSectionSize = fntSectionFile.tellg();
    fntBytes.resize(fntSectionSize);
    fntSectionFile.seekg(0, std::ios::beg);
    fntSectionFile.read(fntBytes.data(), fntSectionSize);
    fntSectionFile.close();

    FatRange* pfatrange = reinterpret_cast<FatRange*>(fatBytes.data());

    // This lambda function was written by NyuBlara, all credits to him.
    // I edited it a bit to make it work with the rest of the updated code.
    auto parseFolder = [this, fntBytes, pfatrange, fatDataSectionPath, originalFatDataAddr, savePath, logFileIDs](uint32_t folderId, std::string curPath, auto& parseFolder) {

        uint32_t currentOffset = 8 * (folderId & FNT_HEADER_OFFSET_MASK); // offset for the current directory's info in the FNT header
        // Only the lower 12 bit of the given offset are relevant

        // ---------------------------------------------------------------------
        // About how the FAT and FNT work :
        // The FNT has two sections :
        // a "header" where every entry contains :
        //// - a 4-byte address where the corresponding directory's data starts in the body
        //// - a 2-byte offset that is the index of the first file of the directory in the FAT
        //// (e.g. : if the offset is 42, the first file in the directory is situated at the ROM addresses stored in the 42nd FAT entry)
        //// (and its second will be 43, etc.)
        // a "body" where every entry contains :
        //// - a length+status/control byte : lower 7 bits (control byte & 0x7F) are a length, highest bit (control byte & 0x80) is set if entry is a directory, and not set if it's a file
        //// - a name which length is the length portion of the previous control byte (e.g. : if the control byte was 0x83, the name is three bytes long)
        //// - if the entry is a directory, a 2-byte address (where only the lower 12 bit are relevant for some reason) at which this directory's info is located in the FNT header
        // Thus, the FNT reading operation will consist in bouncing back and forth between body and header every time we must process a subdirectory
        // Thank Heavens for random-access containers !
        // ---------------------------------------------------------------------

        // Get the 4-byte address for the folder data

        uint32_t fntBodyOffset =
            (uint32_t)((unsigned char)fntBytes[currentOffset + 3] << (uint32_t)FOURTH_BYTE_SHIFT |
                (unsigned char)fntBytes[currentOffset + 2] << (uint32_t)THIRD_BYTE_SHIFT |
                (unsigned char)fntBytes[currentOffset + 1] << (uint32_t)SECOND_BYTE_SHIFT |
                (unsigned char)fntBytes[currentOffset]);
        currentOffset += 4;

        // Get the 2-byte offset for the folder's first file in the FAT
        uint16_t fatOffset =
            (uint16_t)((unsigned char)fntBytes[currentOffset + 1] << SECOND_BYTE_SHIFT |
                (unsigned char)fntBytes[currentOffset]);

        // Jump to FNT body a specified address
        currentOffset = fntBodyOffset;

        uint8_t controlByte = DUMMY_CONTROL_VALUE;

        while (true)
        {
            controlByte = fntBytes[currentOffset]; // Entry's control byte
            if (controlByte == 0) break; // A control byte of 0 terminates the directory's contents
            currentOffset++;

            uint8_t nameLength = controlByte & CONTROL_BYTE_LENGTH_MASK; // length of entry name
            bool isDir = controlByte & CONTROL_BYTE_DIR_MASK; // set if entry is a directory

            // Reconstitute name from bytes
            // Btw I wish I could use the actual byte type but I have to comply with the software's choice of using char
            std::vector<char> nameString;
            for (size_t i = 0; i < nameLength; i++) nameString.push_back(fntBytes[currentOffset++]);
            std::string name(&nameString[0], (size_t)nameLength);

            std::string newPath = curPath + '/' + name;

            if (isDir)
            {
                // Get the 2-byte address for this folder's info in the FNT header
                uint16_t subFolderId = ((unsigned char)fntBytes[currentOffset + 1] << SECOND_BYTE_SHIFT |
                    (unsigned char)fntBytes[currentOffset]);
                currentOffset += 2;

                if (!std::filesystem::exists(newPath))
                    if (!std::filesystem::create_directory(newPath)) return false;

                if (logFileIDs)
                {
					std::string log = std::format("{:x}",subFolderId) + ":::" + newPath.substr(savePath.size()+1) + '\n';
                    if (!logToFile(savePath + "/_file_IDs.txt", log)) return false;
                }

                // Jump back to the FNT header and repeat the process for subdirectory !
                if (!parseFolder(subFolderId, newPath, parseFolder)) return false;
            }
            else
            {
                // Remember we have the offset for the directory's first file in the FAT.
                // From then, every file is just the next entry.
                // So we just have to use that offset and increment it every time.

                uint32_t fileStartAddr = (pfatrange + fatOffset)->startAddr - originalFatDataAddr;
                uint32_t fileSize = (pfatrange + fatOffset)->endAddr - (pfatrange + fatOffset)->startAddr;
                if (!dumpDataFromFile(fatDataSectionPath, newPath, fileStartAddr, fileSize)) return false;

                if (logFileIDs)
                {
                    std::string log = std::format("{:x}", fatOffset) + ":::" + newPath.substr(savePath.size()+1) + '\n';
                    if (!logToFile(savePath + "/_file_IDs.txt", log)) return false;
                }
				
                fatOffset++;
            }
        }

        return true;
    };

    return parseFolder(ROOT_DIRECTORY_ADDRESS, savePath, parseFolder);
}

bool NDSFactory::patchFat(const std::string& fatSectionPath, uint32_t shiftSize, const std::string& savePath)
{
    std::vector<char> fatBytes;

    std::ifstream sectionFile (fatSectionPath, std::ios::in|std::ios::binary|std::ios::ate);
    if (!sectionFile.is_open())
        return false;

    std::streamoff sectionSize = sectionFile.tellg();
    fatBytes.resize(sectionSize);

    sectionFile.seekg (0, std::ios::beg);

    sectionFile.read (fatBytes.data(), sectionSize);
    sectionFile.close();

    FatRange* pfatrange = reinterpret_cast<FatRange*>(fatBytes.data());

    for(size_t i = 0; i < fatBytes.size(); i += sizeof(FatRange), pfatrange++) {
        pfatrange->startAddr += shiftSize;
        pfatrange->endAddr += shiftSize;
    }

    return writeBytesToFile(fatBytes, savePath, 0, static_cast<uint32_t>(sectionSize));
}

uint16_t NDSFactory::calcHeaderCrc16(const std::vector<char>& romHeader)
{
    uint8_t loc;
    uint16_t crc = 0xFFFF;
    size_t size = 0x15E;
    size_t index = 0;

   while (size--)
   {
       loc = static_cast<unsigned char>(romHeader[index] ^ crc);
       index++;
       crc >>= 8;
       crc ^= lCRCTable[loc];
   }
   return crc;

}
