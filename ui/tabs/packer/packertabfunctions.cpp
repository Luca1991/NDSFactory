#include <QDir>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include "./../../mainwindow.h"
#include "./../../ui_mainwindow.h"
#include "../commons/headernames.h"
#include "../../models/ndsheadermodel.h"


void MainWindow::populatePackerSectionHeader(NDSHeader *ndsHeader)
{
    auto* headerDataModel = new NDSHeaderModel(ndsHeader);
      headerDataModel->setValueRowEditable(true);
    ui->packerHeaderDataTable->setModel(headerDataModel);
    ui->packerHeaderDataTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->packerHeaderDataTable->horizontalHeader()->setSectionResizeMode(0,  QHeaderView::ResizeMode::ResizeToContents);
    ui->packerHeaderDataTable->horizontalHeader()->setSectionResizeMode(1,  QHeaderView::ResizeMode::Stretch);
}

void MainWindow::enableCalcCrcButton()
{
    ui->packerCalcHeaderCrcBtn->setEnabled(true);
}

void MainWindow::enableBuildRomButton()
{
    ui->packerBuildNDSRomBtn->setEnabled(true);
}

void MainWindow::generateHeader(NDSHeader* pRomHeader)
{
    std::copy_n(extractPackerHeaderTableData(NDSHeaderNames::GameTitle).toLatin1().data(), 0xc, std::begin(pRomHeader->GameTitle));


    std::copy_n(extractPackerHeaderTableData(NDSHeaderNames::GameCode).toLatin1().data(), 0x4, std::begin(pRomHeader->GameCode));
    std::copy_n(extractPackerHeaderTableData(NDSHeaderNames::MakerCode).toLatin1().data(), 0x2, std::begin(pRomHeader->MakerCode));
    pRomHeader->UnitCode = static_cast<unsigned char>(extractPackerHeaderTableData(NDSHeaderNames::UnitCode).toUInt(nullptr, 16));

    pRomHeader->DeviceType = static_cast<unsigned char>(extractPackerHeaderTableData(NDSHeaderNames::DeviceCode).toUInt(nullptr, 16));
    pRomHeader->DeviceSize = static_cast<unsigned char>(extractPackerHeaderTableData(NDSHeaderNames::CardSize).toUInt(nullptr, 16));

    std::fill(std::begin(pRomHeader->Reserved1), std::end(pRomHeader->Reserved1), 0);

    pRomHeader->RomVersion = static_cast<unsigned char>(extractPackerHeaderTableData(NDSHeaderNames::CardInfo).toUInt(nullptr, 16));
    pRomHeader->Flags = static_cast<unsigned char>(extractPackerHeaderTableData(NDSHeaderNames::Flags).toUInt(nullptr, 16));

    pRomHeader->Arm9RomAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9RomAddress).toUInt(nullptr, 16);
    pRomHeader->Arm9EntryAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9EntryAddress).toUInt(nullptr, 16);
    pRomHeader->Arm9RamAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9RamAddress).toUInt(nullptr, 16);
    pRomHeader->Arm9Size = extractPackerHeaderTableData(NDSHeaderNames::ARM9Size).toUInt(nullptr, 16);

    pRomHeader->Arm7RomAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7RomAddress).toUInt(nullptr, 16);
    pRomHeader->Arm7EntryAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7EntryAddress).toUInt(nullptr, 16);
    pRomHeader->Arm7RamAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7RamAddress).toUInt(nullptr, 16);
    pRomHeader->Arm7Size = extractPackerHeaderTableData(NDSHeaderNames::ARM7Size).toUInt(nullptr, 16);

    pRomHeader->FilenameTableAddr = extractPackerHeaderTableData(NDSHeaderNames::FilenameTableAddress).toUInt(nullptr, 16);
    pRomHeader->FilenameSize = extractPackerHeaderTableData(NDSHeaderNames::FilenameTableSize).toUInt(nullptr, 16);
    pRomHeader->FATAddr = extractPackerHeaderTableData(NDSHeaderNames::FATAddress).toUInt(nullptr, 16);
    pRomHeader->FATSize = extractPackerHeaderTableData(NDSHeaderNames::FATSize).toUInt(nullptr, 16);

    pRomHeader->Arm9OverlayAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlayAddress).toUInt(nullptr, 16);
    pRomHeader->Arm9OverlaySize = extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlaySize).toUInt(nullptr, 16);
    pRomHeader->Arm7OverlayAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlayAddress).toUInt(nullptr, 16);
    pRomHeader->Arm7OverlaySize = extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlaySize).toUInt(nullptr, 16);

    pRomHeader->NormalCommandsSettings = extractPackerHeaderTableData(NDSHeaderNames::Port40001A4hNC).toUInt(nullptr, 16);
    pRomHeader->Key1CommandsSettings = extractPackerHeaderTableData(NDSHeaderNames::Port40001a4hKC).toUInt(nullptr, 16);
    pRomHeader->IconTitleAddr = extractPackerHeaderTableData(NDSHeaderNames::IconTitleAddress).toUInt(nullptr, 16);
    pRomHeader->SecureAreaCRC16 =  extractPackerHeaderTableData(NDSHeaderNames::SecureAreaCRC16).toUShort(nullptr, 16);

    pRomHeader->SecureAreaLoadingTimeout = extractPackerHeaderTableData(NDSHeaderNames::SecureAreaTimeout).toUShort(nullptr, 16);
    pRomHeader->ARM9AutoLoadListRamAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9ALRamAddress).toUInt(nullptr, 16);
    pRomHeader->ARM7AutoLoadListRamAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7ALRamAddress).toUInt(nullptr, 16);
    pRomHeader->SecureAreaDisable = extractPackerHeaderTableData(NDSHeaderNames::SecureAreaDisable).toULong(nullptr, 16);

    pRomHeader->RomSize = extractPackerHeaderTableData(NDSHeaderNames::UsedRomSize).toUInt(nullptr, 16);
    pRomHeader->HeaderSize = extractPackerHeaderTableData(NDSHeaderNames::HeaderSize).toUInt(nullptr, 16);

    std::fill(std::begin(pRomHeader->Reserved2), std::end(pRomHeader->Reserved2), 0);
    std::copy_n(std::begin(QByteArray::fromHex(extractPackerHeaderTableData(NDSHeaderNames::NintendoLogo).toUtf8())), 0x9C, std::begin(pRomHeader->NintendoLogo));
    pRomHeader->NintendoLogoCRC = extractPackerHeaderTableData(NDSHeaderNames::NintendoLogoCRC).toUShort(nullptr, 16);

    pRomHeader->HeaderCRC16 = extractPackerHeaderTableData(NDSHeaderNames::HeaderCRC).toUShort(nullptr, 16);
    pRomHeader->DebugRomAddr = extractPackerHeaderTableData(NDSHeaderNames::DebugRomAddress).toUInt(nullptr, 16);
    pRomHeader->DebugSize = extractPackerHeaderTableData(NDSHeaderNames::DebugSize).toUInt(nullptr, 16);
    pRomHeader->DebugRamAddr = extractPackerHeaderTableData(NDSHeaderNames::DebugRamAddress).toUInt(nullptr, 16);

    std::fill(std::begin(pRomHeader->Reserved3), std::end(pRomHeader->Reserved3), 0);
    std::fill(std::begin(pRomHeader->Reserved4), std::end(pRomHeader->Reserved4), 0);
}

void MainWindow::calcHeaderCrc16()
{
    std::vector<char> romHeaderBuffer(sizeof(NDSHeader));
    NDSHeader* pRomHeader = reinterpret_cast<NDSHeader*>(romHeaderBuffer.data());

    generateHeader(pRomHeader);

    QModelIndex headerCrcIndex = ui->packerHeaderDataTable->model()->index(NDSHeaderNames::HeaderCRC, 1);
    ui->packerHeaderDataTable->model()->setData(headerCrcIndex, QString::number(ndsFactory.calcHeaderCrc16(romHeaderBuffer), 16), Qt::EditRole);
}

NFResult MainWindow::writeHeader(const std::string& savePath)
{
    std::vector<char> romHeaderBuffer(sizeof(NDSHeader));
    NDSHeader* pRomHeader = reinterpret_cast<NDSHeader*>(romHeaderBuffer.data());

    generateHeader(pRomHeader);

    return ndsFactory.writeBytesToFile(romHeaderBuffer, savePath, 0, sizeof(NDSHeader));
}

NFResult MainWindow::writeHeaderPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = sizeof(NDSHeader);
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::ARM9RomAddress).toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
        paddingType,
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeArm9Bin(const std::string& savePath, bool isArm9FooterPresent)
{
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::ARM9Size).toUInt(nullptr, 16);
    if (isArm9FooterPresent)
        size += Arm9FooterSize;
    return ndsFactory.writeSectionToFile(
                ui->loadedArm9BinPathEdt->text().toStdString(),
                savePath,
                extractPackerHeaderTableData(NDSHeaderNames::ARM9RomAddress).toUInt(nullptr, 16),
                size);
}


NFResult MainWindow::writeArm9BinPadding(char paddingType, const std::string& savePath, bool isFooterPresent)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9RomAddress).toUInt(nullptr, 16) +
        extractPackerHeaderTableData(NDSHeaderNames::ARM9Size).toUInt(nullptr, 16);
    uint32_t size;
    if (extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlayAddress).toUInt(nullptr, 16) != 0)
        size = extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlayAddress).toUInt(nullptr, 16) - startAddr;
    else
        size = extractPackerHeaderTableData(NDSHeaderNames::ARM7RomAddress).toUInt(nullptr, 16) - startAddr;

    if (isFooterPresent)
    {
        startAddr += Arm9FooterSize;
        size -= Arm9FooterSize;
    }

    return ndsFactory.writePaddingToFile(
        paddingType,
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeArm9Overlay(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
        ui->loadedArm9OverlayPathEdt->text().toStdString(),
        savePath,
        extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlayAddress).toUInt(nullptr, 16),
        extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlaySize).toUInt(nullptr, 16));
}

NFResult MainWindow::writeArm9OverlayFiles(const std::string& savePath)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlayAddress).toUInt(nullptr, 16) +
        extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlaySize).toUInt(nullptr, 16);
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::ARM7RomAddress).toUInt(nullptr, 16) - startAddr;
    return ndsFactory.writeSectionToFile(
        ui->loadedArm9OverlayFilesPathEdt->text().toStdString(),
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeArm7Bin(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedArm7BinPathEdt->text().toStdString(),
                savePath,
                extractPackerHeaderTableData(NDSHeaderNames::ARM7RomAddress).toUInt(nullptr, 16),
                extractPackerHeaderTableData(NDSHeaderNames::ARM7Size).toUInt(nullptr, 16));
}

NFResult MainWindow::writeArm7BinPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7RomAddress).toUInt(nullptr, 16) +
        extractPackerHeaderTableData(NDSHeaderNames::ARM7Size).toUInt(nullptr, 16);
    uint32_t size;
    if (extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlayAddress).toUInt(nullptr, 16) != 0)
        size = extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlayAddress).toUInt(nullptr, 16) - startAddr;
    else
        size = extractPackerHeaderTableData(NDSHeaderNames::FilenameTableAddress).toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
        paddingType,
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeArm7Overlay(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
        ui->loadedArm7OverlayPathEdt->text().toStdString(),
        savePath,
        extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlayAddress).toUInt(nullptr, 16),
        extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlaySize).toUInt(nullptr, 16));
}

NFResult MainWindow::writeArm7OverlayFiles(const std::string& savePath)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlayAddress).toUInt(nullptr, 16) +
        extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlaySize).toUInt(nullptr, 16);
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::FilenameTableAddress).toUInt(nullptr, 16) - startAddr;
    return ndsFactory.writeSectionToFile(
        ui->loadedArm7OverlayFilesPathEdt->text().toStdString(),
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeFnt(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedFntPathEdt->text().toStdString(),
                savePath,
                extractPackerHeaderTableData(NDSHeaderNames::FilenameTableAddress).toUInt(nullptr, 16),
                extractPackerHeaderTableData(NDSHeaderNames::FilenameTableSize).toUInt(nullptr, 16));
}

NFResult MainWindow::writeFntPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::FilenameTableAddress).toUInt(nullptr, 16) +
        extractPackerHeaderTableData(NDSHeaderNames::FilenameTableSize).toUInt(nullptr, 16);
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::FATAddress).toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
        paddingType,
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeFat(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedFatPathEdt->text().toStdString(),
                savePath,
                extractPackerHeaderTableData(NDSHeaderNames::FATAddress).toUInt(nullptr, 16),
                extractPackerHeaderTableData(NDSHeaderNames::FATSize).toUInt(nullptr, 16));
}

NFResult MainWindow::writeFatPadding(char paddingType, const std::string& savePath)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::FATAddress).toUInt(nullptr, 16) +
        extractPackerHeaderTableData(NDSHeaderNames::FATSize).toUInt(nullptr, 16);
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::IconTitleAddress).toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writePaddingToFile(
        paddingType,
        savePath,
        startAddr,
        size);
}

NFResult MainWindow::writeIconTitle(const std::string& savePath)
{
    return ndsFactory.writeSectionToFile(
                ui->loadedIconTitlePathEdt->text().toStdString(),
                savePath,
                extractPackerHeaderTableData(NDSHeaderNames::IconTitleAddress).toUInt(nullptr, 16),
                IconTitleSize);
}

NFResult MainWindow::writeFatFiles(const std::string& savePath)
{
    uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::IconTitleAddress).toUInt(nullptr, 16) + IconTitleSize;
    uint32_t size = extractPackerHeaderTableData(NDSHeaderNames::UsedRomSize).toUInt(nullptr, 16) - startAddr;

    return ndsFactory.writeSectionToFile(
                ui->loadedFatFilesPathEdt->text().toStdString(),
                savePath,
                startAddr,
                size);
}

NFResult MainWindow::writeRomPadding(const std::string& savePath)
{
     uint32_t startAddr = extractPackerHeaderTableData(NDSHeaderNames::UsedRomSize).toUInt(nullptr, 16);
     uint32_t size = static_cast<uint32_t>(ndsFactory.getCardSizeInBytes(extractPackerHeaderTableData(NDSHeaderNames::CardSize).toInt())) - startAddr;

     return ndsFactory.writePaddingToFile(
                 static_cast<char>('\xff'),
                 savePath,
                 startAddr,
                 size);
}

NFResult MainWindow::writeEverything(const std::string& savePath)
{
	NFResult nfResult;
    char paddingType;
    bool isArm9FooterPresent = ndsFactory.checkArm9FooterPresence(ui->loadedArm9BinPathEdt->text().toStdString(),
        extractPackerHeaderTableData(NDSHeaderNames::ARM9Size).toUInt(nullptr, 16));
    if (ui->packerPadType00RdBtn->isChecked())
        paddingType = static_cast<char>('\x00');
    else
        paddingType = static_cast<char>('\xff');

    std::remove(savePath.c_str());

    nfResult = writeHeader(savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeHeaderPadding(paddingType, savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeArm9Bin(savePath, isArm9FooterPresent);
    if (!nfResult.result) return nfResult;
    nfResult = writeArm9BinPadding(paddingType, savePath, isArm9FooterPresent);
    if (!nfResult.result) return nfResult;
    if (extractPackerHeaderTableData(NDSHeaderNames::ARM9OverlayAddress).toUInt(nullptr, 16) != 0)
    {
        nfResult = writeArm9Overlay(savePath);
        if (!nfResult.result) return nfResult;
        nfResult = writeArm9OverlayFiles(savePath);
        if (!nfResult.result) return nfResult;
    }
    nfResult = writeArm7Bin(savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeArm7BinPadding(paddingType, savePath);
    if (!nfResult.result) return nfResult;
    if (extractPackerHeaderTableData(NDSHeaderNames::ARM7OverlayAddress).toUInt(nullptr, 16) != 0) {
        nfResult = writeArm7Overlay(savePath);
        if (!nfResult.result) return nfResult;
        nfResult = writeArm7OverlayFiles(savePath);
        if (!nfResult.result) return nfResult;
    }
    nfResult = writeFnt(savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeFntPadding(paddingType, savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeFat(savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeFatPadding(paddingType, savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeIconTitle(savePath);
    if (!nfResult.result) return nfResult;
    nfResult = writeFatFiles(savePath);
    if (!nfResult.result) return nfResult;
    if(!ui->packerTrimRomsCbx->isChecked())
    {
        nfResult = writeRomPadding(savePath);
        if (!nfResult.result) return nfResult;
    }
	return { true, "" };
}

QString MainWindow::extractPackerHeaderTableData(int index)
{
    return ui->packerHeaderDataTable->model()->index(index, 1).data().toString();
}
