#include <QFileDialog>
#include <QMessageBox>
#include "./../../mainwindow.h"
#include "./../../ui_mainwindow.h"


void MainWindow::on_packerLoadHeaderBtn_clicked()
{
    std::vector<char> romHeader;
    NDSHeader *pNDSHeader;

    QString headerPath =  QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Header",
          QDir::currentPath(),
          "NDS Header (*.bin)");

    if(headerPath.isNull())
    {
        QMessageBox::critical(this, tr("NDS Factory"), tr("Unable to open file!"));
        return;
    }

    if (ndsFactory.loadRomHeader(headerPath.toStdString(), romHeader))
    {
        pNDSHeader = reinterpret_cast<NDSHeader*>(romHeader.data());
        populatePackerSectionHeader(pNDSHeader);
    }
}

void MainWindow::on_packerLoadArm9BinBtn_clicked()
{
    QString arm9BinPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Arm9Bin",
          QDir::currentPath(),
          "NDS Arm9Bin (*.bin)");

    if(!arm9BinPath.isNull())
    {
        ui->loadedArm9BinPathEdt->setText(arm9BinPath.toUtf8());
    }
}

void MainWindow::on_packerLoadArm7BinBtn_clicked()
{
    QString arm7BinPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Arm7Bin",
          QDir::currentPath(),
          "NDS Arm7Bin (*.bin)");

    if(!arm7BinPath.isNull())
    {
        ui->loadedArm7BinPathEdt->setText(arm7BinPath.toUtf8());
    }
}

void MainWindow::on_packerLoadFntBtn_clicked()
{
    QString fntPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Fnt",
          QDir::currentPath(),
          "NDS Fnt (*.bin)");

    if(!fntPath.isNull())
    {
        ui->loadedFntPathEdt->setText(fntPath.toUtf8());
    }
}

void MainWindow::on_packerLoadFatBtn_clicked()
{
    QString fatPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Fat",
          QDir::currentPath(),
          "NDS Fat (*.bin)");

    if(!fatPath.isNull())
    {
        ui->loadedFatPathEdt->setText(fatPath.toUtf8());
    }
}

void MainWindow::on_packerLoadArm9OverlayBtn_clicked()
{
    QString arm9OverlayPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Arm9Overlay",
          QDir::currentPath(),
          "NDS A9OVR (*.bin)");

    if( !arm9OverlayPath.isNull() )
    {
        ui->loadedArm9OverlayPathEdt->setText(arm9OverlayPath.toUtf8());
    }
}

void MainWindow::on_packerLoadArm9OverlayFilesBtn_clicked()
{
    QString arm9OverlayFilesPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Arm9Overlay Data",
          QDir::currentPath(),
          "NDS A9OVR_DATA (*.bin)");

    if(!arm9OverlayFilesPath.isNull())
    {
        ui->loadedArm9OverlayFilesPathEdt->setText(arm9OverlayFilesPath.toUtf8());
    }
}

void MainWindow::on_packerLoadArm7OverlayBtn_clicked()
{
    QString arm7OverlayPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Arm7Overlay",
          QDir::currentPath(),
          "NDS A7OVR (*.bin)");

    if(!arm7OverlayPath.isNull())
    {
        ui->loadedArm7OverlayPathEdt->setText(arm7OverlayPath.toUtf8());
    }
}

void MainWindow::on_packerLoadArm7OverlayFilesBtn_clicked()
{
    QString arm7OverlayFilesPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Arm7Overlay Data",
          QDir::currentPath(),
          "NDS A7OVR_DATA (*.bin)");

    if(!arm7OverlayFilesPath.isNull())
    {
        ui->loadedArm7OverlayFilesPathEdt->setText(arm7OverlayFilesPath.toUtf8());
    }
}

void MainWindow::on_packerLoadIconTitleBtn_clicked()
{
    QString iconTitlePath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS IconTitleLogo",
          QDir::currentPath(),
          "NDS ITL (*.bin)");

    if(!iconTitlePath.isNull())
    {
        ui->loadedIconTitlePathEdt->setText(iconTitlePath.toUtf8());
    }
}

void MainWindow::on_packerLoadFatFilesBtn_clicked()
{
    QString fatFilesPath = QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Fat Data",
          QDir::currentPath(),
          "NDS FAT_DATA (*.bin)");

    if(!fatFilesPath.isNull())
    {
        ui->loadedFatFilesPathEdt->setText(fatFilesPath.toUtf8());
        ui->packerFatFilesAddrEdt->setText(QString::number((ui->packerIconTitleEdt->text().toUInt(nullptr, 16) + IconTitleSize), 16));
    }
}

void MainWindow::on_packerBuildNDSRomBtn_clicked()
{
    QString dirPath = QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS Rom",
          "rom.nds",
          "NDS ROM (*.nds)");

    if (!dirPath.isNull())
    {
        writeEverything(dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("Creation completed!"))
                                               : QMessageBox::critical(this, tr("NDS Factory"), tr("Error during the creation!"));
    }
}


void MainWindow::on_packerCalcHeaderCrcBtn_clicked()
{
    calcHeaderCrc16();
}
