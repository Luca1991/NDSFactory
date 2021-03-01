#include <QDir>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "./../../mainwindow.h"
#include "./../../ui_mainwindow.h"


void MainWindow::populateHeader(NDSHeader* ndsHeader)
{

    ui->unpackerGameTitleEdt->setText(QString::fromUtf8(ndsHeader->GameTitle, 0xC));
    ui->unpackerGameCodeEdt->setText(QString::fromUtf8(ndsHeader->GameCode, 0x4));
    ui->unpackerMakerCodeEdt->setText(QString::fromUtf8(reinterpret_cast<char*>(ndsHeader->MakerCode), 0x2));
    ui->unpackerUnitCodeEdt->setText(QString::number(ndsHeader->UnitCode, 16));

    ui->unpackerDeviceCodeEdt->setText(QString::number(ndsHeader->DeviceType, 16));
    ui->unpackerCardSizeEdt->setText(QString::number(ndsHeader->DeviceSize, 16));
    ui->unpackerCardInfoEdt->setText(QString::number(ndsHeader->RomVersion, 16));
    ui->unpackerFlagsEdt->setText(QString::number(ndsHeader->Flags, 16));

    ui->unpackerARM9RomAddrEdt->setText(QString::number(ndsHeader->Arm9RomAddr,16));
    ui->unpackerARM9EntryAddrEdt->setText(QString::number(ndsHeader->Arm9EntryAddr,16));
    ui->unpackerARM9RamAddrEdt->setText(QString::number(ndsHeader->Arm9RamAddr,16));
    ui->unpackerARM9SizeEdt->setText(QString::number(ndsHeader->Arm9Size,16));

    ui->unpackerARM7RomAddrEdt->setText(QString::number(ndsHeader->Arm7RomAddr,16));
    ui->unpackerARM7EntryAddrEdt->setText(QString::number(ndsHeader->Arm7EntryAddr,16));
    ui->unpackerARM7RamAddrEdt->setText(QString::number(ndsHeader->Arm7RamAddr,16));
    ui->unpackerARM7SizeEdt->setText(QString::number(ndsHeader->Arm7Size,16));

    ui->unpackerFilenameTableAddrEdt->setText(QString::number(ndsHeader->FilenameTableAddr,16));
    ui->unpackerFilenameTableSizeEdt->setText(QString::number(ndsHeader->FilenameSize,16));
    ui->unpackerFATAddrEdt->setText(QString::number(ndsHeader->FATAddr,16));
    ui->unpackerFATSizeEdt->setText(QString::number(ndsHeader->FATSize,16));

    ui->unpackerARM9OverlayAddrEdt->setText(QString::number(ndsHeader->Arm9OverlayAddr,16));
    ui->unpackerARM9OverlaySizeEdt->setText(QString::number(ndsHeader->Arm9OverlaySize,16));
    ui->unpackerARM7OverlayAddrEdt->setText(QString::number(ndsHeader->Arm7OverlayAddr,16));
    ui->unpackerARM7OverlaySizeEdt->setText(QString::number(ndsHeader->Arm7OverlaySize,16));

    ui->unpackerPortNCEdt->setText(QString::number(ndsHeader->NormalCommandsSettings,16));
    ui->unpackerPortKCEdt->setText(QString::number(ndsHeader->Key1CommandsSettings,16));
    ui->unpackerIconTitleEdt->setText(QString::number(ndsHeader->IconTitleAddr,16));
    ui->unpackerSecureAreaCRC16Edt->setText(QString::number(ndsHeader->SecureAreaCRC16,16));

    ui->unpackerSecureAreaTimeoutEdt->setText(QString::number(ndsHeader->SecureAreaLoadingTimeout,16));
    ui->unpackerARM9AURamAddrEdt->setText(QString::number(ndsHeader->ARM9AutoLoadListRamAddr,16));
    ui->unpackerARM7AURamAddrEdt->setText(QString::number(ndsHeader->ARM7AutoLoadListRamAddr,16));
    ui->unpackerSecureAreaDisableEdt->setText(QString::number(ndsHeader->SecureAreaDisable,16));

    ui->unpackerUsedRomSizeEdt->setText(QString::number(ndsHeader->RomSize,16));
    ui->unpackerHeaderSizeEdt->setText(QString::number(ndsHeader->HeaderSize,16));

    ui->unpackerNintendoLogoEdt->setText(QByteArray::fromRawData(reinterpret_cast<char*>(ndsHeader->NintendoLogo), 0x9C).toHex());
    ui->unpackerNintendoLogoCRCEdt->setText(QString::number(ndsHeader->NintendoLogoCRC,16));

    ui->unpackerHeaderCRCEdt->setText(QString::number(ndsHeader->HeaderCRC16,16));
    ui->unpackerDebugRomAddrEdt->setText(QString::number(ndsHeader->DebugRomAddr,16));
    ui->unpackerDebugSizeEdt->setText(QString::number(ndsHeader->DebugSize,16));
    ui->unpackerDebugRamAddrEdt->setText(QString::number(ndsHeader->DebugRamAddr,16));

    ui->unpackerFatFilesOriginalAddrEdt->setText(QString::number((ndsHeader->IconTitleAddr+IconTitleSize),16));
}

void MainWindow::enableExtractionButtons()
{
    ui->unpackerExtractorGbx->setEnabled(true);
    ui->unpackerExtraGbx->setEnabled(true);
    if (ui->unpackerARM9OverlayAddrEdt->text().toUInt(nullptr, 16) == 0){
        ui->unpackerDumpArm9OverlayBtn->setEnabled(false);
        ui->unpackerDumpArm9OverlayFilesBtn->setEnabled(false);
    }
    if (ui->unpackerARM7OverlayAddrEdt->text().toUInt(nullptr, 16) == 0){
        ui->unpackerDumpArm7OverlayBtn->setEnabled(false);
        ui->unpackerDumpArm7OverlayFilesBtn->setEnabled(false);
    }
}

void MainWindow::disableExtractionButtons()
{
    ui->unpackerExtractorGbx->setEnabled(false);
    ui->unpackerExtraGbx->setEnabled(false);
}

bool MainWindow::dumpHeader(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                0,
                ui->unpackerHeaderSizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::dumpArm9Bin(const std::string& dirPath, bool dumpExtraBytes)
{
    uint32_t size = ui->unpackerARM9SizeEdt->text().toUInt(nullptr, 16);
    if (dumpExtraBytes)
        size += 12;
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerARM9RomAddrEdt->text().toUInt(nullptr, 16),
                size);
}

bool MainWindow::dumpArm7Bin(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerARM7RomAddrEdt->text().toUInt(nullptr, 16),
                ui->unpackerARM7SizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::dumpFnt(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerFilenameTableAddrEdt->text().toUInt(nullptr, 16),
                ui->unpackerFilenameTableSizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::dumpFat(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerFATAddrEdt->text().toUInt(nullptr, 16),
                ui->unpackerFATSizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::dumpArm9Overlay(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerARM9OverlayAddrEdt->text().toUInt(nullptr, 16),
                ui->unpackerARM9OverlaySizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::dumpArm9OverlayFiles(const std::string& dirPath)
{
    return false; // TODO: implement me!
}

bool MainWindow::dumpArm7Overlay(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerARM7OverlayAddrEdt->text().toUInt(nullptr, 16),
                ui->unpackerARM7OverlaySizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::dumpArm7OverlayFiles(const std::string& dirPath)
{
    return false; // TODO: implement me!
}

bool MainWindow::dumpIconTitle(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerIconTitleEdt->text().toUInt(nullptr, 16),
                0xA00);
}

bool MainWindow::dumpFatFiles(const std::string& dirPath)
{
    uint32_t startAddr = ui->unpackerIconTitleEdt->text().toUInt(nullptr, 16) + IconTitleSize;
    uint32_t size = ui->unpackerUsedRomSizeEdt->text().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                startAddr,
                size);
}


bool MainWindow::dumpEverything(QString dirPath)
{

    if(!dumpHeader(QDir::toNativeSeparators(dirPath+"/header.bin").toStdString()))
        return false;
    if(!dumpArm9Bin(QDir::toNativeSeparators(dirPath+"/arm9.bin").toStdString(), true))
        return false;
    if(!dumpArm7Bin(QDir::toNativeSeparators(dirPath+"/arm7.bin").toStdString()))
        return false;
    if(!dumpFnt(QDir::toNativeSeparators(dirPath+"/fnt.bin").toStdString()))
        return false;
    if(!dumpFat(QDir::toNativeSeparators(dirPath+"/fat.bin").toStdString()))
        return false;
    if(ui->unpackerARM9OverlayAddrEdt->text().toUInt(nullptr, 16) != 0) {
        if(!dumpArm9Overlay(QDir::toNativeSeparators(dirPath+"/a9ovr.bin").toStdString()))
            return false;
        if(!dumpArm9OverlayFiles(QDir::toNativeSeparators(dirPath+"/a9ovr_data.bin").toStdString()))
            return false;
    }
    if(ui->unpackerARM7OverlayAddrEdt->text().toUInt(nullptr, 16) != 0) {
        if(!dumpArm7Overlay(QDir::toNativeSeparators(dirPath+"/a7ovr.bin").toStdString()))
            return false;
        if(!dumpArm7OverlayFiles(QDir::toNativeSeparators(dirPath+"/a7ovr_data.bin").toStdString()))
            return false;
    }
    if(!dumpIconTitle(QDir::toNativeSeparators(dirPath+"/itl.bin").toStdString()))
        return false;
    if(!dumpFatFiles(QDir::toNativeSeparators(dirPath+"/fat_data.bin").toStdString()))
        return false;

    return true;
}

bool MainWindow::decodeFatFiles()
{
    // TODO: implement me!
    return false;
}
