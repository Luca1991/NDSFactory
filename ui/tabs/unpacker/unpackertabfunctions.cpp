#include <QDir>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include "../../mainwindow.h"
#include "../../ui_mainwindow.h"
#include "../commons/headernames.h"
#include "../../models/ndsheadermodel.h"
#include "../../../ndsfactory/fatstruct.h"


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
    if (ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr,16) == 0){
        ui->unpackerDumpArm9OverlayBtn->setEnabled(false);
        ui->unpackerDumpArm9OverlayFilesBtn->setEnabled(false);
    }
    if (ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr,16) == 0){
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
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::HeaderSize, 1).data().toString().toUInt(nullptr,16));
}

bool MainWindow::dumpArm9Bin(const std::string& dirPath, bool dumpExtraBytes)
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

bool MainWindow::dumpArm7Bin(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7RomAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7Size, 1).data().toString().toUInt(nullptr,16));
}

bool MainWindow::dumpFnt(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableSize, 1).data().toString().toUInt(nullptr,16));
}

bool MainWindow::dumpFat(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FATAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FATSize, 1).data().toString().toUInt(nullptr,16));
}

bool MainWindow::dumpArm9Overlay(const std::string& dirPath)
{
    return ndsFactory.dumpDataFromFile(
                ui->loadedRomPath->text().toStdString(),
                dirPath,
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlaySize, 1).data().toString().toUInt(nullptr,16));
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
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr,16),
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlaySize, 1).data().toString().toUInt(nullptr,16));
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
                ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::IconTitleAddress, 1).data().toString().toUInt(nullptr,16),
                0xA00);
}

bool MainWindow::dumpFatFiles(const std::string& dirPath)
{
    uint32_t startAddr = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::IconTitleAddress, 1).data().toString().toUInt(nullptr,16) + IconTitleSize ;
    uint32_t size = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::UsedRomSize, 1).data().toString().toUInt(nullptr,16) - startAddr;

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
    if(ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM9OverlayAddress, 1).data().toString().toUInt(nullptr,16) != 0) {
        if(!dumpArm9Overlay(QDir::toNativeSeparators(dirPath+"/a9ovr.bin").toStdString()))
            return false;
        if(!dumpArm9OverlayFiles(QDir::toNativeSeparators(dirPath+"/a9ovr_data.bin").toStdString()))
            return false;
    }
    if(ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::ARM7OverlayAddress, 1).data().toString().toUInt(nullptr,16) != 0) {
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

bool MainWindow::decodeFatFiles(QString dirPath)
{
    // Prepare necessary info from ROM

    std::string romPath = ui->loadedRomPath->text().toStdString(); // ROM itself

    // Addresses of the file allocation table and file name table

    uint32_t fatAddr = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FATAddress, 1).data().toString().toUInt(nullptr,16);
    uint32_t fatSize = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FATSize, 1).data().toString().toUInt(nullptr,16);

    // Sizes of these tables

    uint32_t fntAddr = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableAddress, 1).data().toString().toUInt(nullptr,16);
    uint32_t fntSize = ui->unpackerHeaderDataTable->model()->index(NDSHeaderNames::FilenameTableSize, 1).data().toString().toUInt(nullptr,16);

    // Buffers to receive the contents of the FAT and FNT

    std::vector<char> fatBytes(static_cast<unsigned long>(fatSize));
    std::vector<char> fntBytes(static_cast<unsigned long>(fntSize));

    // Fill them

    if(!ndsFactory.readBytesFromFile(fatBytes, romPath, fatAddr, fatSize)) return false;
    if(!ndsFactory.readBytesFromFile(fntBytes, romPath, fntAddr, fntSize)) return false;

    // Use the available FAT range struct and read the FAT bytes as such

    FatRange* pfatrange = reinterpret_cast<FatRange*>(fatBytes.data());

    // Recursive function that looks up FNT info to find file names and directory structures,
    // And writes the ROM data in the ranges indicated by the FAT simultaneously.

    auto parseFolder = [this, fntBytes, pfatrange, romPath](uint32_t folderId, std::string curPath, auto& parseFolder){

        if(false) return false; // this is stupid, but it's C++
        // If we take it out, the compiler will complain because it doesn't known the return type of the lambda
        // But we can't make the lambda bool either...so this is the best option...

        QDir curDir(QString::fromStdString(curPath)); // useful a bit later

        uint32_t currentOffset = 8 * (folderId & 0xFFF); // offset for the current directory's info in the FNT header
        // Only the lower 12 bit of the given offset are relevant

        // ---------------------------------------------------------------------
        // About how the FAT and FNT work :

        // The FNT has two sections :
        // a "header" where every entry contains :
          // - a 4-byte address where the corresponding directory's data starts in the body
          // - a 2-byte offset that is the index of the first file of the directory in the FAT
          // (e.g. : if the offset is 42, the first file in the directory is situated at the ROM addresses stored in the 42nd FAT entry)
          // (and its second will be 43, etc.)
        // a "body" where every entry contains :
         // - a length+status/control byte : lower 7 bits (control byte & 0x7F) are a length, highest bit (control byte & 0x80) is set if entry is a directory, and not set if it's a file
         // - a name which length is the length portion of the previous control byte (e.g. : if the control byte was 0x83, the name is three bytes long)
         // - if the entry is a directory, a 2-byte address (where only the lower 12 bit are relevant for some reason) at which this directory's info is located in the FNT header

        // Thus, the FNT reading operation will consist in bouncing back and forth between body and header every time we must process a subdirectory
        // Thank Heavens for random-access containers !

        // ---------------------------------------------------------------------

        // Get the 4-byte address for the folder data

        uint32_t fntBodyOffset = (uint32_t)((unsigned char) fntBytes[currentOffset+3] << (uint32_t) 24 |
          (unsigned char) fntBytes[currentOffset+2] << (uint32_t) 16 |
          (unsigned char) fntBytes[currentOffset + 1] << (uint32_t) 8 |
          (unsigned char) fntBytes[currentOffset]);
        currentOffset+=4;

        // Get the 2-byte offset for the folder's first file in the FAT

        uint16_t fatOffset = (uint16_t)((unsigned char) fntBytes[currentOffset+1] << 8 | (unsigned char) fntBytes[currentOffset]);

        // Jump to FNT body a specified address

        currentOffset = fntBodyOffset;

        uint8_t controlByte = 0xFF;

        while(true){

            controlByte = fntBytes[currentOffset]; // Entry's control byte
            if(controlByte==0) break; // A control byte of 0 terminates the directory's contents
            currentOffset++;

            uint8_t nameLength = controlByte & 0x7F; // length of entry name
            bool isDir = controlByte & 0x80; // set if entry is a directory

            // Reconstitute name from bytes
            // Btw I wish I could use the actual byte type but I have to comply with the software's choice of using char

            std::vector<char> nameString;
            for(size_t i = 0 ; i<nameLength ; i++) nameString.push_back(fntBytes[currentOffset++]);
            std::string name(&nameString[0], (size_t)nameLength);

            // We'll need this either way

            QString newPath(QDir::toNativeSeparators(QString::fromStdString(curPath+"/"+name)));

            if(isDir){

                // Get the 2-byte address for this folder's info in the FNT header
                uint16_t subFolderId = ((unsigned char) fntBytes[currentOffset+1] << 8 | (unsigned char) fntBytes[currentOffset]);
                currentOffset+=2;

                // Now the QDir we created earlier comes into play :
                // C++ doesn't automatically create directories (!!!) so we have to rely on QT to do that manually.
                // Otherwise, the ofstream will not open,
                // And even if we force it open, it will just write into nothingness !!!

                if(!curDir.exists(newPath)) curDir.mkdir(newPath); // I don't think the check is even necessary, actually

                // Jump back to the FNT header and repeat the process for subdirectory !

                if(!parseFolder(subFolderId,newPath.toStdString(),parseFolder)) return false;

            }
            else{

                // Remember we have the offset for the directory's first file in the FAT.
                // From then, every file is just the next entry.
                // So we just have to use that offset and increment it every time.

                if(!ndsFactory.writeFatSectionToFile(
                  romPath,
                  pfatrange+fatOffset,
                  newPath.toStdString()))
                  return false;
                fatOffset++;

            }
        }

        return true;
    };

    // The root folder's ID is, obviously, 0 (only the lower 12-bit count!)

    return parseFolder(0xF000,dirPath.toStdString(),parseFolder);
}
