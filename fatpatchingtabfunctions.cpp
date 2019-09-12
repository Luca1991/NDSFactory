#include "mainwindow.h"


bool MainWindow::patchFat(const std::string& loadPath, uint32_t shiftSize, const std::string& savePath)
{
    return ndsFactory.patchFat(loadPath, shiftSize, savePath);
}
