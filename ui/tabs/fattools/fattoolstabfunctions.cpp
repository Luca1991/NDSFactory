#include <filesystem> 
#include "./../../mainwindow.h"


NFResult MainWindow::extractFatData(const std::string& fatDataSectionPath, const std::string& fatSectionPath,
    const std::string& fntSectionPath, uint32_t originalFatDataAddr, const std::string& savePath, bool logFileIDs)
{
    return ndsFactory.extractFatData(fatDataSectionPath, fatSectionPath, fntSectionPath, originalFatDataAddr, savePath, logFileIDs);
}

NFResult MainWindow::patchFat(const std::string& loadPath, uint32_t shiftSize, const std::string& savePath)
{
    return ndsFactory.patchFat(loadPath, shiftSize, savePath);
}

NFResult MainWindow::buildFatData(const std::string& fatDataDirPath, const std::string& originalFatPath, uint32_t fatDataAddr, const std::string& savePath)
{
	return ndsFactory.buildFatData(fatDataDirPath, originalFatPath, fatDataAddr, savePath);
}
