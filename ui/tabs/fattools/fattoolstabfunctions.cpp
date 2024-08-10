#include "./../../mainwindow.h"


bool MainWindow::extractFatData(const std::string& fatDataSectionPath, const std::string& fatSectionPath,
    const std::string& fntSectionPath, uint32_t originalFatDataAddr, const std::string& savePath)
{
    return ndsFactory.extractFatData(fatDataSectionPath, fatSectionPath, fntSectionPath, originalFatDataAddr, savePath);
}

bool MainWindow::patchFat(const std::string& loadPath, uint32_t shiftSize, const std::string& savePath)
{
    return ndsFactory.patchFat(loadPath, shiftSize, savePath);
}
