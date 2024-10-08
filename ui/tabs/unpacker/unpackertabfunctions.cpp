#include <QDir>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include "../../mainwindow.h"
#include "../../ui_mainwindow.h"
#include "../commons/headernames.h"
#include "../../models/ndsheadermodel.h"
#include "../../../ndsfactory/fatstruct.h"

// Size constants
#define ICON_TITLE_SIZE 0xA00

void MainWindow::populateHeader(NDSHeader* ndsHeader)
{
    auto* headerDataModel = new NDSHeaderModel(ndsHeader);
    ui->unpackerHeaderDataTable->setModel(headerDataModel);
    ui->unpackerHeaderDataTable->horizontalHeader()->setSectionResizeMode(0,  QHeaderView::ResizeMode::ResizeToContents);
    ui->unpackerHeaderDataTable->horizontalHeader()->setSectionResizeMode(1,  QHeaderView::ResizeMode::Stretch);
}

void MainWindow::enableExtractionButtons()
{
    ui->unpackerExtractorGbx->setEnabled(true);
    ui->unpackerExtraGbx->setEnabled(true);
    if (ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr,16) == 0)
    {
        ui->unpackerDumpArm9OverlayBtn->setEnabled(false);
        ui->unpackerDumpArm9OverlayFilesBtn->setEnabled(false);
    }
    else
	{
		ui->unpackerDumpArm9OverlayBtn->setEnabled(true);
		ui->unpackerDumpArm9OverlayFilesBtn->setEnabled(true);
	}
    if (ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr,16) == 0)
    {
        ui->unpackerDumpArm7OverlayBtn->setEnabled(false);
        ui->unpackerDumpArm7OverlayFilesBtn->setEnabled(false);
    }
    else
    {
		ui->unpackerDumpArm7OverlayBtn->setEnabled(true);
		ui->unpackerDumpArm7OverlayFilesBtn->setEnabled(true);
    }
}

void MainWindow::disableExtractionButtons()
{
    ui->unpackerExtractorGbx->setEnabled(false);
    ui->unpackerExtraGbx->setEnabled(false);
}

NFResult MainWindow::dumpHeader(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                0,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::HeaderSize, 1).data().toString().toUInt(nullptr,16));
}

NFResult MainWindow::dumpArm9Bin(const std::string& dirPath, bool dumpExtraBytes)
{
    uint32_t size = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9Size, 1).data().toString().toUInt(nullptr,16);
    if (dumpExtraBytes)
        size += 12;
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9RomAddress, 1).data().toString().toUInt(nullptr,16),
                size);
}

NFResult MainWindow::dumpArm7Bin(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7RomAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7Size, 1).data().toString().toUInt(nullptr,16));
}

NFResult MainWindow::dumpFnt(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableSize, 1).data().toString().toUInt(nullptr,16));
}

NFResult MainWindow::dumpFat(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FATAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FATSize, 1).data().toString().toUInt(nullptr,16));
}

NFResult MainWindow::dumpArm9Overlay(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlaySize, 1).data().toString().toUInt(nullptr,16));
}

NFResult MainWindow::dumpArm9OverlayFiles(const std::string& dirPath)
{
    uint32_t startAddr = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr, 16) +
        ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlaySize, 1).data().toString().toUInt(nullptr, 16);
	uint32_t size = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7RomAddress, 1).data().toString().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.dumpDataFromFile(
        ui->loadedRomPath->text().toStdString(),
        dirPath,
        startAddr,
        size);
}

NFResult MainWindow::dumpArm7Overlay(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlaySize, 1).data().toString().toUInt(nullptr,16));
}

NFResult MainWindow::dumpArm7OverlayFiles(const std::string& dirPath)
{
    uint32_t startAddr = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr, 16) +
        ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlaySize, 1).data().toString().toUInt(nullptr, 16);
    uint32_t size = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableAddress, 1).data().toString().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.dumpDataFromFile(
        ui->loadedRomPath->text().toStdString(),
        dirPath,
        startAddr,
        size);
}

NFResult MainWindow::dumpIconTitle(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::IconTitleAddress, 1).data().toString().toUInt(nullptr,16),
                ICON_TITLE_SIZE);
}

NFResult MainWindow::dumpFatFiles(const std::string& dirPath)
{
    uint32_t startAddr = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::IconTitleAddress, 1).data().toString().toUInt(nullptr,16) + IconTitleSize ;
    uint32_t size = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::UsedRomSize, 1).data().toString().toUInt(nullptr,16) - startAddr;

    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                startAddr,
                size);
}


NFResult MainWindow::dumpEverything(QString dirPath)
{
    NFResult nfResult;
    nfResult = dumpHeader(QDir::toNativeSeparators(dirPath + "/header.bin").toStdString());
	if (!nfResult.result) return nfResult;
    nfResult = dumpArm9Bin(QDir::toNativeSeparators(dirPath+"/arm9.bin").toStdString(), true);
    if (!nfResult.result) return nfResult;
    nfResult = dumpArm7Bin(QDir::toNativeSeparators(dirPath+"/arm7.bin").toStdString());
    if (!nfResult.result) return nfResult;
    nfResult = dumpFnt(QDir::toNativeSeparators(dirPath+"/fnt.bin").toStdString());
    if (!nfResult.result) return nfResult;
    nfResult = dumpFat(QDir::toNativeSeparators(dirPath+"/fat.bin").toStdString());
    if (!nfResult.result) return nfResult;
    if(ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr,16) != 0) {
        nfResult = dumpArm9Overlay(QDir::toNativeSeparators(dirPath+"/a9ovr.bin").toStdString());
        if (!nfResult.result) return nfResult;
        nfResult = dumpArm9OverlayFiles(QDir::toNativeSeparators(dirPath+"/a9ovr_data.bin").toStdString());
        if (!nfResult.result) return nfResult;
	}
    if(ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr,16) != 0) {
        nfResult = dumpArm7Overlay(QDir::toNativeSeparators(dirPath+"/a7ovr.bin").toStdString());
        if (!nfResult.result) return nfResult;
        nfResult = dumpArm7OverlayFiles(QDir::toNativeSeparators(dirPath+"/a7ovr_data.bin").toStdString());
        if (!nfResult.result) return nfResult;
    }
    nfResult = dumpIconTitle(QDir::toNativeSeparators(dirPath+"/itl.bin").toStdString());
    if (!nfResult.result) return nfResult;
    nfResult = dumpFatFiles(QDir::toNativeSeparators(dirPath+"/fat_data.bin").toStdString());
    if (!nfResult.result) return nfResult;
	return { true, "" };
}
