#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "ndsheader.h"
#include "fatstruct.h"
#include "nfresult.h"


class NDSFactory
{
public:
    NFResult loadRomHeader(const std::string& romPath, std::vector<char>& header);
    NFResult dumpDataFromFile(const std::string& romPath, const std::string& savePath, uint32_t startAddr, uint32_t size);
    NFResult readBytesFromFile(std::vector<char>& byteBuffer, const std::string& romPath, uint32_t startAddr, uint32_t size);
    NFResult writeSectionToFile(const std::string& sectionPath, const std::string& savePath, uint32_t startAddr, uint32_t size);
    NFResult writeBytesToFile(std::vector<char>& byteBuffer, const std::string& savePath, uint32_t startAddr, uint32_t size);
    NFResult writePaddingToFile(char paddingChar, const std::string& savePath, uint32_t startAddr, uint32_t size);
    int getCardSizeInBytes(int cardType);
    bool checkArm9FooterPresence(const std::string& sectionPath, uint32_t size);
    NFResult extractFatData(const std::string& fatDataSectionPath, const std::string& fatSectionPath,
        const std::string& fntSectionPath, uint32_t originalFatDataAddr, const std::string& savePath, bool logFileIDs);
    NFResult patchFat(const std::string& sectionPath, uint32_t shiftSize, const std::string& savePath);
    NFResult buildFatData(const std::string& fatDataDirPath, const std::string& originalFatPath, uint32_t fatDataAddr, const std::string& savePath);
    uint16_t calcHeaderCrc16(const std::vector<char>& romHeader);

private:
    bool logToFile(const std::string& logPath, const std::string& log);

};

