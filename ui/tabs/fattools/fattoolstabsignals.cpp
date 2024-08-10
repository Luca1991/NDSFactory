#include <QFileDialog>
#include <QMessageBox>
#include "./../../mainwindow.h"
#include "./../../ui_mainwindow.h"

void MainWindow::on_fatExtractorLoadFatDataBtn_clicked()
{
    QString FatDataPath = QFileDialog::getOpenFileName(
        Q_NULLPTR,
        "NDS Fat Data",
        QDir::currentPath(),
        "NDS FAT_DATA (*.bin)");

    if (!FatDataPath.isNull())
    {
        ui->fatExtractorFatDataPathEdt->setText(FatDataPath.toUtf8());
    }
}

void MainWindow::on_fatExtractorLoadFatBtn_clicked()
{
	QString FatPath = QFileDialog::getOpenFileName(
		Q_NULLPTR,
		"NDS Fat",
		QDir::currentPath(),
		"NDS FAT (*.bin)");

	if (!FatPath.isNull())
	{
		ui->fatExtractorFatPathEdt->setText(FatPath.toUtf8());
	}
}

void MainWindow::on_fatExtractorLoadFntBtn_clicked()
{
	QString FntPath = QFileDialog::getOpenFileName(
		Q_NULLPTR,
		"NDS Fnt",
		QDir::currentPath(),
		"NDS FNT (*.bin)");

	if (!FntPath.isNull())
	{
		ui->fatExtractorFntPathEdt->setText(FntPath.toUtf8());
	}
}

void MainWindow::on_fatExtractorExtractBtn_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this, tr("Select Directory"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isNull())
        extractFatData(ui->fatExtractorFatDataPathEdt->text().toStdString(),
        ui->fatExtractorFatPathEdt->text().toStdString(),
        ui->fatExtractorFntPathEdt->text().toStdString(),
        ui->fatExtractorOriginalFatFilesAddrEdt->text().toUInt(nullptr, 16),
        dirPath.toStdString()) ? QMessageBox::information(this, tr("NDS Factory"), tr("FAT files extraction completed!"))
        : QMessageBox::critical(this, tr("NDS Factory"), tr("Error extracting FAT files!"));

}

void MainWindow::on_fatPatcherLoadFatBtn_clicked()
{
    QString fatPath =  QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Fat",
          QDir::currentPath(),
          "NDS Fat (*.bin)");

    if( !fatPath.isNull() )
    {
      ui->fatPatcherFatPathEdt->setText(fatPath.toUtf8());
    }
}

void MainWindow::on_fatPatcherPatchFatBtn_clicked()
{
    uint32_t positionDiff = 0;
    uint32_t originalPos = ui->fatPatcherOriginalFatFilesAddrEdt->text().toUInt(nullptr, 16);
    uint32_t newPos = ui->fatPatcherNewFatFilesAddrEdt->text().toUInt(nullptr, 16);

    QString dirPath =  QFileDialog::getSaveFileName(
          Q_NULLPTR,
          "NDS FAT",
          "fat.bin",
          "Binary (*.bin)");

    if(dirPath.isNull())
    {
        return;
    }

    if (originalPos < newPos)
    {
        positionDiff = newPos-originalPos;
    } else {
        positionDiff = originalPos-newPos;
    }

    patchFat(ui->fatPatcherFatPathEdt->text().toStdString(), positionDiff, dirPath.toStdString())
            ? QMessageBox::information(this, tr("NDS Factory"), tr("FAT patching completed!"))
            : QMessageBox::critical(this, tr("NDS Factory"), tr("Error patching FAT!"));

}
