#include <QFileDialog>
#include <vector>
#include <QMessageBox>
#include "./../../mainwindow.h"
#include "./../../ui_mainwindow.h"
#include "./../../utils/filepicker.h"
#include "./../../utils/ui.h"


void MainWindow::on_loadRomBtn_clicked()
{
    NDSHeader *pNDSHeader;

    QString romPath =  QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Rom",
          QDir::currentPath(),
          "NDS Rom (*.nds)");

    if (romPath.isNull()) return;

    ui->loadedRomPath->setText(romPath.toUtf8());

    if (ndsFactory.loadRomHeader(ui->loadedRomPath->text().toStdString(), romHeader).result)
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
	ui->unpackerDumpHeaderBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS Header", "header.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpHeader(dirPath.toStdString()));

	ui->unpackerDumpHeaderBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpArm9Btn_clicked()
{
	ui->unpackerDumpArm9Btn->setEnabled(false);

	QString dirPath = customSaveFileDialog("NDS ARM9", "arm9.bin", "Binary (*.bin)");

    QMessageBox::StandardButton dumpExtraBytes = QMessageBox::question(
                this,
                "NDSFactory",
                "Do you want to dump the extra 12 bytes? (click yes if you want a 1:1 arm9 dump)",
                QMessageBox::Yes|QMessageBox::No);

    if (!dirPath.isNull())
        notifyExtractionResult(dumpArm9Bin(dirPath.toStdString(), dumpExtraBytes == QMessageBox::Yes ? true : false));

	ui->unpackerDumpArm9Btn->setEnabled(true);
}

void MainWindow::on_unpackerDumpArm7Btn_clicked()
{
	ui->unpackerDumpArm7Btn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS ARM7", "arm7.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpArm7Bin(dirPath.toStdString()));

	ui->unpackerDumpArm7Btn->setEnabled(true);
}

void MainWindow::on_unpackerDumpFntBtn_clicked()
{
	ui->unpackerDumpFntBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS FNT", "fnt.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpFnt(dirPath.toStdString()));

	ui->unpackerDumpFntBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpFatBtn_clicked()
{
	ui->unpackerDumpFatBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS FAT", "fat.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpFat(dirPath.toStdString()));

	ui->unpackerDumpFatBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpArm9OverlayBtn_clicked()
{
	ui->unpackerDumpArm9OverlayBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS ARM9 Overlay", "a9ovr.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpArm9Overlay(dirPath.toStdString()));

	ui->unpackerDumpArm9OverlayBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpArm7OverlayBtn_clicked()
{
	ui->unpackerDumpArm7OverlayBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS ARM7 Overlay", "a7ovr.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpArm7Overlay(dirPath.toStdString()));

	ui->unpackerDumpArm7OverlayBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpIconTitleLogoBtn_clicked()
{
	ui->unpackerDumpIconTitleLogoBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS IconTitleLogo", "itl.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpIconTitle(dirPath.toStdString()));

	ui->unpackerDumpIconTitleLogoBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpFatFilesBtn_clicked()
{
	ui->unpackerDumpFatFilesBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS FAT Files", "fat_data.bin", "Binary (*.bin)");

    if (!dirPath.isNull())
        notifyExtractionResult(dumpFatFiles(dirPath.toStdString()));

	ui->unpackerDumpFatFilesBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpArm9OverlayFilesBtn_clicked()
{
	ui->unpackerDumpArm9OverlayFilesBtn->setEnabled(false);

    QString dirPath = customSaveFileDialog("NDS ARM9 Overlay Data", "a9ovr_data.bin", "Binary (*.bin)");

	if (!dirPath.isNull())
		notifyExtractionResult(dumpArm9OverlayFiles(dirPath.toStdString()));

	ui->unpackerDumpArm9OverlayFilesBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpArm7OverlayFilesBtn_clicked()
{
    ui->unpackerDumpArm7OverlayFilesBtn->setEnabled(false);

	QString dirPath = customSaveFileDialog("NDS ARM7 Overlay Data", "a7ovr_data.bin", "Binary (*.bin)");

	if (!dirPath.isNull())
		notifyExtractionResult(dumpArm7OverlayFiles(dirPath.toStdString()));

    ui->unpackerDumpArm7OverlayFilesBtn->setEnabled(true);
}

void MainWindow::on_unpackerDumpEverythingBtn_clicked()
{
    ui->unpackerDumpEverythingBtn->setEnabled(false);
    QString dirPath = QFileDialog::getExistingDirectory(
                this, tr("Select Directory"),
                "",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isNull())
        notifyExtractionResult(dumpEverything(dirPath));
    ui->unpackerDumpEverythingBtn->setEnabled(true);
}
