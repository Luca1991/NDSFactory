#include <QDir>
#include <cstring>
#include <algorithm>
#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::populatePackerSectionHeader(NDSHeader *ndsHeader)
{
    ui->packerGameTitleEdt->setText(QString::fromUtf8(ndsHeader->GameTitle, 0xC));
    ui->packerGameCodeEdt->setText(QString::fromUtf8(ndsHeader->GameCode, 0x4));
    ui->packerMakerCodeEdt->setText(QString::fromUtf8(reinterpret_cast<char*>(ndsHeader->MakerCode), 0x2));
    ui->packerUnitCodeEdt->setText(QString::number(ndsHeader->UnitCode, 16));

    ui->packerDeviceCodeEdt->setText(QString::number(ndsHeader->DeviceType, 16));
    ui->packerCardSizeEdt->setText(QString::number(ndsHeader->DeviceSize, 16));
    ui->packerCardInfoEdt->setText(QString::number(ndsHeader->RomVersion, 16));
    ui->packerFlagsEdt->setText(QString::number(ndsHeader->Flags, 16));

    ui->packerARM9RomAddrEdt->setText(QString::number(ndsHeader->Arm9RomAddr, 16));
    ui->packerARM9EntryAddrEdt->setText(QString::number(ndsHeader->Arm9EntryAddr, 16));
    ui->packerARM9RamAddrEdt->setText(QString::number(ndsHeader->Arm9RamAddr, 16));
    ui->packerARM9SizeEdt->setText(QString::number(ndsHeader->Arm9Size, 16));

    ui->packerARM7RomAddrEdt->setText(QString::number(ndsHeader->Arm7RomAddr, 16));
    ui->packerARM7EntryAddrEdt->setText(QString::number(ndsHeader->Arm7EntryAddr, 16));
    ui->packerARM7RamAddrEdt->setText(QString::number(ndsHeader->Arm7RamAddr, 16));
    ui->packerARM7SizeEdt->setText(QString::number(ndsHeader->Arm7Size, 16));

    ui->packerFilenameTableAddrEdt->setText(QString::number(ndsHeader->FilenameTableAddr, 16));
    ui->packerFilenameTableSizeEdt->setText(QString::number(ndsHeader->FilenameSize, 16));
    ui->packerFATAddrEdt->setText(QString::number(ndsHeader->FATAddr, 16));
    ui->packerFATSizeEdt->setText(QString::number(ndsHeader->FATSize, 16));

    ui->packerARM9OverlayAddrEdt->setText(QString::number(ndsHeader->Arm9OverlayAddr, 16));
    ui->packerARM9OverlaySizeEdt->setText(QString::number(ndsHeader->Arm9OverlaySize, 16));
    ui->packerARM7OverlayAddrEdt->setText(QString::number(ndsHeader->Arm7OverlayAddr, 16));
    ui->packerARM7OverlaySizeEdt->setText(QString::number(ndsHeader->Arm7OverlaySize, 16));

    ui->packerPortNCEdt->setText(QString::number(ndsHeader->NormalCommandsSettings, 16));
    ui->packerPortKCEdt->setText(QString::number(ndsHeader->Key1CommandsSettings, 16));
    ui->packerIconTitleEdt->setText(QString::number(ndsHeader->IconTitleAddr, 16));
    ui->packerSecureAreaCRC16Edt->setText(QString::number(ndsHeader->SecureAreaCRC16, 16));

    ui->packerSecureAreaTimeoutEdt->setText(QString::number(ndsHeader->SecureAreaLoadingTimeout, 16));
    ui->packerARM9AURamAddrEdt->setText(QString::number(ndsHeader->ARM9AutoLoadListRamAddr, 16));
    ui->packerARM7AURamAddrEdt->setText(QString::number(ndsHeader->ARM7AutoLoadListRamAddr, 16));
    ui->packerSecureAreaDisableEdt->setText(QString::number(ndsHeader->SecureAreaDisable, 16));

    ui->packerUsedRomSizeEdt->setText(QString::number(ndsHeader->RomSize, 16));
    ui->packerHeaderSizeEdt->setText(QString::number(ndsHeader->HeaderSize, 16));
    ui->packerNintendoLogoEdt->setText(QByteArray::fromRawData(reinterpret_cast<char*>(ndsHeader->NintendoLogo), 0x9C).toHex());
    ui->packerNintendoLogoCRCEdt->setText(QString::number(ndsHeader->NintendoLogoCRC, 16));

    ui->packerHeaderCRCEdt->setText(QString::number(ndsHeader->HeaderCRC16, 16));
    ui->packerDebugRomAddrEdt->setText(QString::number(ndsHeader->DebugRomAddr, 16));
    ui->packerDebugSizeEdt->setText(QString::number(ndsHeader->DebugSize, 16));
    ui->packerDebugRamAddrEdt->setText(QString::number(ndsHeader->DebugRamAddr, 16));
}

void MainWindow::generateHeader(NDSHeader* pRomHeader)
{
    std::copy_n(ui->packerGameTitleEdt->text().toLatin1().data(), 0xc, std::begin(pRomHeader->GameTitle));
    std::copy_n(ui->packerGameCodeEdt->text().toStdString().data(), 0x4, std::begin(pRomHeader->GameCode));
    std::copy_n(ui->packerMakerCodeEdt->text().toStdString().data(), 0x2, std::begin(pRomHeader->MakerCode));
    pRomHeader->UnitCode = static_cast<unsigned char>(ui->packerUnitCodeEdt->text().toUInt(nullptr, 16));

    pRomHeader->DeviceType = static_cast<unsigned char>(ui->packerDeviceCodeEdt->text().toUInt(nullptr, 16));
    pRomHeader->DeviceSize = static_cast<unsigned char>(ui->packerCardSizeEdt->text().toUInt(nullptr, 16));

    std::fill(std::begin(pRomHeader->Reserved1), std::end(pRomHeader->Reserved1), 0);

    pRomHeader->RomVersion = static_cast<unsigned char>(ui->packerCardInfoEdt->text().toUInt(nullptr, 16));
    pRomHeader->Flags = static_cast<unsigned char>(ui->packerFlagsEdt->text().toUInt(nullptr, 16));

    pRomHeader->Arm9RomAddr = ui->packerARM9RomAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm9EntryAddr = ui->packerARM9EntryAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm9RamAddr = ui->packerARM9RamAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm9Size = ui->packerARM9SizeEdt->text().toUInt(nullptr, 16);

    pRomHeader->Arm7RomAddr = ui->packerARM7RomAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm7EntryAddr = ui->packerARM7EntryAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm7RamAddr = ui->packerARM7RamAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm7Size = ui->packerARM7SizeEdt->text().toUInt(nullptr, 16);

    pRomHeader->FilenameTableAddr = ui->packerFilenameTableAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->FilenameSize = ui->packerFilenameTableSizeEdt->text().toUInt(nullptr, 16);
    pRomHeader->FATAddr = ui->packerFATAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->FATSize = ui->packerFATSizeEdt->text().toUInt(nullptr, 16);

    pRomHeader->Arm9OverlayAddr = ui->packerARM9OverlayAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm9OverlaySize = ui->packerARM9OverlaySizeEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm7OverlayAddr = ui->packerARM7OverlayAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->Arm7OverlaySize = ui->packerARM7OverlaySizeEdt->text().toUInt(nullptr, 16);

    pRomHeader->NormalCommandsSettings = ui->packerPortNCEdt->text().toUInt(nullptr, 16);
    pRomHeader->Key1CommandsSettings = ui->packerPortKCEdt->text().toUInt(nullptr, 16);
    pRomHeader->IconTitleAddr = ui->packerIconTitleEdt->text().toUInt(nullptr, 16);
    pRomHeader->SecureAreaCRC16 =  ui->packerSecureAreaCRC16Edt->text().toUShort(nullptr, 16);

    pRomHeader->SecureAreaLoadingTimeout = ui->packerSecureAreaTimeoutEdt->text().toUShort(nullptr, 16);
    pRomHeader->ARM9AutoLoadListRamAddr = ui->packerARM9AURamAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->ARM7AutoLoadListRamAddr = ui->packerARM7AURamAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->SecureAreaDisable = ui->packerSecureAreaDisableEdt->text().toULong(nullptr, 16);

    pRomHeader->RomSize = ui->packerUsedRomSizeEdt->text().toUInt(nullptr, 16);
    pRomHeader->HeaderSize = ui->packerHeaderSizeEdt->text().toUInt(nullptr, 16);

    std::fill(std::begin(pRomHeader->Reserved2), std::end(pRomHeader->Reserved2), 0);
    std::copy_n(std::begin(QByteArray::fromHex(ui->packerNintendoLogoEdt->text().toUtf8())), 0x9C, std::begin(pRomHeader->NintendoLogo));
    pRomHeader->NintendoLogoCRC = ui->packerNintendoLogoCRCEdt->text().toUShort(nullptr, 16);

    pRomHeader->HeaderCRC16 = ui->packerHeaderCRCEdt->text().toUShort(nullptr, 16);
    pRomHeader->DebugRomAddr = ui->packerDebugRomAddrEdt->text().toUInt(nullptr, 16);
    pRomHeader->DebugSize = ui->packerDebugSizeEdt->text().toUInt(nullptr, 16);
    pRomHeader->DebugRamAddr = ui->packerDebugRamAddrEdt->text().toUInt(nullptr, 16);

    std::fill(std::begin(pRomHeader->Reserved3), std::end(pRomHeader->Reserved3), 0);
    std::fill(std::begin(pRomHeader->Reserved4), std::end(pRomHeader->Reserved4), 0);
}


bool MainWindow::writeHeader(const std::string& savePath)
{
    std::vector<char> romHeader(sizeof(NDSHeader));
    NDSHeader* pRomHeader = reinterpret_cast<NDSHeader*>(romHeader.data());

    generateHeader(pRomHeader);

    return ndsFactory.writeBytesToFile(romHeader, savePath, 0, sizeof(NDSHeader));;
}

void MainWindow::calcHeaderCrc16()
{
    std::vector<char> romHeader(sizeof(NDSHeader));
    NDSHeader* pRomHeader = reinterpret_cast<NDSHeader*>(romHeader.data());

    generateHeader(pRomHeader);

    ui->packerHeaderCRCEdt->setText(QString::number(ndsFactory.calcHeaderCrc16(romHeader), 16));

}

bool MainWindow::writeArm9Bin(const std::string& savePath, bool isArm9FooterPresent)
{
    uint32_t size =  ui->packerARM9SizeEdt->text().toUInt(nullptr, 16);
    if (isArm9FooterPresent)
        size += Arm9FooterSize;
    return ndsFactory.writeSectionToFile(
                ui->loadedArm9BinPathEdt->text().toStdString(),
                savePath,
                ui->packerARM9RomAddrEdt->text().toUInt(nullptr, 16),
                size);
}

bool MainWindow::writeArm7Bin(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedArm7BinPathEdt->text().toStdString(),
                savePath,
                ui->packerARM7RomAddrEdt->text().toUInt(nullptr, 16),
                ui->packerARM7SizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::writeFnt(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedFntPathEdt->text().toStdString(),
                savePath,
                ui->packerFilenameTableAddrEdt->text().toUInt(nullptr, 16),
                ui->packerFilenameTableSizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::writeFat(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedFatPathEdt->text().toStdString(),
                savePath,
                ui->packerFATAddrEdt->text().toUInt(nullptr, 16),
                ui->packerFATSizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::writeArm9Overlay(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedArm9OverlayPathEdt->text().toStdString(),
                savePath,
                ui->packerARM9OverlayAddrEdt->text().toUInt(nullptr, 16),
                ui->packerARM9OverlaySizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::writeArm9OverlayFiles(const std::string& savePath)
{
    return false; // TODO: implement me!
}

bool MainWindow::writeArm7Overlay(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedArm7OverlayPathEdt->text().toStdString(),
                savePath,
                ui->packerARM7OverlayAddrEdt->text().toUInt(nullptr, 16),
                ui->packerARM7OverlaySizeEdt->text().toUInt(nullptr, 16));
}

bool MainWindow::writeArm7OverlayFiles(const std::string& savePath)
{
    return false; // TODO: implement me!
}

bool MainWindow::writeIconTitle(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedIconTitlePathEdt->text().toStdString(),
                savePath,
                ui->packerIconTitleEdt->text().toUInt(nullptr, 16),
                IconTitleSize);
}

bool MainWindow::writeFatFiles(const std::string& savePath)
{
    uint32_t startAddr = ui->packerIconTitleEdt->text().toUInt(nullptr, 16) + IconTitleSize;
    uint32_t size = ui->packerUsedRomSizeEdt->text().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writeSectionToFile(
                ui->loadedFatFilesPathEdt->text().toStdString(),
                savePath,
                startAddr,
                size);
}

bool MainWindow::writeHeaderPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = sizeof(NDSHeader);
    uint32_t size = ui->packerARM9RomAddrEdt->text().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
                paddingType,
                savePath,
                startAddr,
                size);
}

bool MainWindow::writeArm9BinPadding(char paddingType, const std::string& savePath, bool isFooterPresent)
{ // FIXME check ARM9 Overlay
    uint32_t startAddr = ui->packerARM9RomAddrEdt->text().toUInt(nullptr, 16) + ui->packerARM9SizeEdt->text().toUInt(nullptr, 16);
    uint32_t size = ui->packerARM7RomAddrEdt->text().toUInt(nullptr, 16) - startAddr;

    if (isFooterPresent)
        size -= Arm9FooterSize;

    return ndsFactory.writePaddingToFile(
                paddingType,
                savePath,
                startAddr,
                size);
}

bool MainWindow::writeArm7BinPadding(char paddingType, const std::string& savePath)
{  // FIXME check ARM7 Overlay
    uint32_t startAddr = ui->packerARM7RomAddrEdt->text().toUInt(nullptr, 16) + ui->packerARM7SizeEdt->text().toUInt(nullptr, 16);
    uint32_t size = ui->packerFilenameTableAddrEdt->text().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
                paddingType,
                savePath,
                startAddr,
                size);
}

bool MainWindow::writeFntPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = ui->packerFilenameTableAddrEdt->text().toUInt(nullptr, 16) + ui->packerFilenameTableSizeEdt->text().toUInt(nullptr, 16);
    uint32_t size = ui->packerFATAddrEdt->text().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
                paddingType,
                savePath,
                startAddr,
                size);
}

bool MainWindow::writeFatPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = ui->packerFATAddrEdt->text().toUInt(nullptr, 16) + ui->packerFATSizeEdt->text().toUInt(nullptr, 16);
    uint32_t size = ui->packerIconTitleEdt->text().toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
                paddingType,
                savePath,
                startAddr,
                size);
}

bool MainWindow::writeArm9OverlayPadding(char paddingType, const std::string& savePath)
{   // FIXME TODO
    return true;
}

bool MainWindow::writeArm9OverlayFilesPadding(char paddingType, const std::string& savePath)
{   // FIXME TODO
    return true;
}

bool MainWindow::writeArm7OverlayPadding(char paddingType, const std::string& savePath)
{   // FIXME TODO
    return true;
}


bool MainWindow::writeArm7OverlayFilesPadding(char paddingType, const std::string& savePath)
{   // FIXME TODO
    return true;
}

bool MainWindow::writeRomPadding(const std::string& savePath)
{
     uint32_t startAddr = ui->packerUsedRomSizeEdt->text().toUInt(nullptr, 16);
     uint32_t size = static_cast<uint32_t>(ndsFactory.getCardSizeInBytes(ui->packerCardSizeEdt->text().toInt())) - startAddr;

     return ndsFactory.writePaddingToFile(
                 static_cast<char>('\xff'),
                 savePath,
                 startAddr,
                 size);
}

bool MainWindow::writeEverything(const std::string& savePath)
{
    bool res = true;
    char paddingType;
    bool isArm9FooterPresent = ndsFactory.checkArm9FooterPresence(ui->loadedArm9BinPathEdt->text().toStdString(),
                                                                  ui->packerARM9SizeEdt->text().toUInt(nullptr, 16));
    if (ui->packerPadType00RdBtn->isChecked())
        paddingType = static_cast<char>('\x00');
    else
        paddingType = static_cast<char>('\xff');

    res &= writeHeader(savePath);
    res &= writeHeaderPadding(paddingType, savePath);
    res &= writeArm9Bin(savePath, isArm9FooterPresent);
    res &= writeArm9BinPadding(paddingType, savePath, isArm9FooterPresent);
    res &= writeArm7Bin(savePath);
    res &= writeArm7BinPadding(paddingType, savePath);
    res &= writeFnt(savePath);
    res &= writeFntPadding(paddingType, savePath);
    res &= writeFat(savePath);
    res &= writeFatPadding(paddingType, savePath);
    if(ui->packerARM9OverlayAddrEdt->text().toUInt(nullptr, 16) != 0) {
        res &= writeArm9Overlay(savePath);
        res &= writeArm9OverlayPadding(paddingType, savePath);
        res &= writeArm9OverlayFiles(savePath);
        res &= writeArm9OverlayFilesPadding(paddingType, savePath);
    }
    if(ui->packerARM7OverlayAddrEdt->text().toUInt(nullptr, 16) != 0) {
        res &= writeArm7Overlay(savePath);
        res &= writeArm7OverlayPadding(paddingType, savePath);
        res &= writeArm7OverlayFiles(savePath);
        res &= writeArm7OverlayFilesPadding(paddingType, savePath);
    }
    res &= writeIconTitle(savePath);
    res &= writeFatFiles(savePath);
    if(!ui->packerTrimRomsCbx->isChecked())
    {
        res &= writeRomPadding(savePath);
    }
    return res;
}
