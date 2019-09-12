#include <QFileDialog>
#include <vector>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


void MainWindow::on_loadRomBtn_clicked()
{
    std::vector<char> romHeader;
    NDSHeader *pNDSHeader;

    QString romPath =  QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Rom",
          QDir::currentPath(),
          "NDS Rom (*.nds)");

    if( !romPath.isNull() )
    {
      ui->loadedRomPath->setText(romPath.toUtf8());
    }

    if (ndsFactory.loadRomHeader(ui->loadedRomPath->text().toStdString(), romHeader))
    {
        pNDSHeader = reinterpret_cast<NDSHeader*>(romHeader.data());
        populateHeader(pNDSHeader);
        enableExtractionButtons();
    }
    else
    {
        disableExtractionButtons();
    }
}

void MainWindow::on_unpackerDumpHeaderBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS Header",
          "header.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpHeader(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                          : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpArm9Btn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS ARM9",
          "arm9.bin",
          "Binary (*.bin)");

    QMessageBox::StandardButton dumpExtraBytes = QMessageBox::question(
                this,
                "NDS Factory",
                "Do you want to dump the extra 12 bytes? (click yes if you want a 1:1 arm9 dump)",
                QMessageBox::Yes|QMessageBox::No);

    if (!dirPath.isNull())
    {
        dumpArm9Bin(dirPath.toStdString(), dumpExtraBytes == QMessageBox::Yes ? true : false)
                ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpArm7Btn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS ARM7",
          "arm7.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpArm7Bin(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                           : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpFntBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS FNT",
          "fnt.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpFnt(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                       : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpFatBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS FAT",
          "fat.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpFat(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                       : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpArm9OverlayBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS ARM9 Overlay",
          "a9ovr.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpArm9Overlay(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                               : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpArm7OverlayBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS ARM7 Overlay",
          "a7ovr.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpArm7Overlay(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                               : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpIconTitleLogoBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS IconTitleLogo",
          "itl.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpIconTitle(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                             : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpFatFilesBtn_clicked()
{
    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS FAT Files",
          "fat_data.bin",
          "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        dumpFatFiles(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                            : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDumpArm9OverlayFilesBtn_clicked()
{
    QMessageBox::warning(this, tr("NDS Factory"), tr("This function is currently not implemented!"));
    //dumpArm9OverlayFiles()
}

void MainWindow::on_unpackerDumpArm7OverlayFilesBtn_clicked()
{
    QMessageBox::warning(this, tr("NDS Factory"), tr("This function is currently not implemented!"));
    //dumpArm7OverlayFiles()
}

void MainWindow::on_unpackerDumpEverythingBtn_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(
                this, tr("Select Directory"),
                "",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isNull())
    {
        dumpEverything(dirPath) ? QMessageBox::information(this, tr("NDS Factory"), tr("Extraction completed!"))
                                : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the extraction!"));
    }
}

void MainWindow::on_unpackerDecodeFatFilesBtn_clicked()
{
    QMessageBox::warning(this, tr("NDS Factory"), tr("This function is currently not implemented!"));
    decodeFatFiles();
}

