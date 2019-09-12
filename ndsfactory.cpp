#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include "ndsfactory.h"
#include "fatstruct.h"


NDSFactory::NDSFactory()
{

}

bool NDSFactory::loadRomHeader(const std::string& romPath, std::vector<char>& romHeader)
{
    std::streampos headerSize = sizeof(NDSHeader);
    std::ifstream romFile (romPath, std::ios::in|std::ios::binary|std::ios::ate);
    if (romFile.is_open())
    {
        romHeader.resize(static_cast<ulong>(headerSize));

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
        long sectionRealSize = sectionFile.tellg();
        sectionFile.close();
        if (sectionRealSize >= size + Arm9FooterSize)
        {
            return true;
        }
    }
    return false;
}

bool NDSFactory::patchFat(const std::string& fatSectionPath, uint32_t shiftSize, const std::string& savePath)
{
    std::vector<char> fatBytes;

    std::ifstream sectionFile (fatSectionPath, std::ios::in|std::ios::binary|std::ios::ate);
    if (!sectionFile.is_open())
        return false;

    long sectionSize = sectionFile.tellg();
    fatBytes.resize(static_cast<ulong>(sectionSize));

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
