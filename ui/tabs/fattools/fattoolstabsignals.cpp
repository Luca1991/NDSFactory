#include <QFileDialog>
#include <QMessageBox>
#include "./../../mainwindow.h"
#include "./../../ui_mainwindow.h"
#include "./../../utils/filepicker.h"

void MainWindow::on_fatExtractorLoadFatDataBtn_clicked()
{
    QString FatDataPath = QFileDialog::getOpenFileName(
        Q_NULLPTR,
        "NDS Fat Data",
        "",
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
		"",
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
		"",
		"NDS FNT (*.bin)");

	if (!FntPath.isNull())
	{
		ui->fatExtractorFntPathEdt->setText(FntPath.toUtf8());
	}
}

void MainWindow::on_fatExtractorExtractBtn_clicked()
{
	ui->fatExtractorExtractBtn->setEnabled(false);

    QString dirPath = QFileDialog::getExistingDirectory(
        this, tr("Select Directory"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isNull()) {
        NFResult nfResult = extractFatData(ui->fatExtractorFatDataPathEdt->text().toStdString(),
            ui->fatExtractorFatPathEdt->text().toStdString(),
            ui->fatExtractorFntPathEdt->text().toStdString(),
            ui->fatExtractorOriginalFatFilesAddrEdt->text().toUInt(nullptr, 16),
            dirPath.toStdString(),
            ui->fatExtractorSaveFileIDsCbx->isChecked());
        nfResult.result? QMessageBox::information(this, tr("NDSFactory"), tr("FAT files extraction completed!"))
            : QMessageBox::critical(this, tr("NDSFactory"), nfResult.message.c_str());
    }

    ui->fatExtractorExtractBtn->setEnabled(true);

}

void MainWindow::on_fatPatcherLoadFatBtn_clicked()
{
    QString fatPath =  QFileDialog::getOpenFileName(
          Q_NULLPTR,
          "NDS Fat",
          "",
          "NDS Fat (*.bin)");

    if(!fatPath.isNull())
        ui->fatPatcherFatPathEdt->setText(fatPath.toUtf8());
}

void MainWindow::on_fatPatcherPatchFatBtn_clicked()
{
	ui->fatPatcherPatchFatBtn->setEnabled(false);

    uint32_t positionDiff = 0;
    uint32_t originalPos = ui->fatPatcherOriginalFatFilesAddrEdt->text().toUInt(nullptr, 16);
    uint32_t newPos = ui->fatPatcherNewFatFilesAddrEdt->text().toUInt(nullptr, 16);

    QString dirPath = customSaveFileDialog("NDS FAT",
        "fat.bin",
        "Binary (*.bin)");

    if (!dirPath.isNull())
    {
        if(originalPos < newPos)
            positionDiff = newPos - originalPos;
        else
            positionDiff = originalPos - newPos;

        NFResult nfResult = patchFat(ui->fatPatcherFatPathEdt->text().toStdString(), positionDiff, dirPath.toStdString());
        nfResult.result ? QMessageBox::information(this, tr("NDSFactory"), tr("FAT patching completed!"))
            : QMessageBox::critical(this, tr("NDSFactory"), nfResult.message.c_str());
    }

    ui->fatPatcherPatchFatBtn->setEnabled(true);
}

void MainWindow::on_fatBuilderOpenFatDataDirBtn_clicked()
{
    QString fatDirPat = QFileDialog::getExistingDirectory(
        this, tr("Select Directory"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!fatDirPat.isNull())
        ui->fatBuilderFatDirPathEdt->setText(fatDirPat.toUtf8());
}

void MainWindow::on_fatBuilderLoadOriginalFatBtn_clicked()
{
	QString fatPath = QFileDialog::getOpenFileName(
		Q_NULLPTR,
		"NDS Fat",
		"",
		"NDS Fat (*.bin)");

	if (!fatPath.isNull())
		ui->fatBuilderOriginalFatPathEdt->setText(fatPath.toUtf8());
}

void MainWindow::on_fatBuilderBuildBtn_clicked()
{
    ui->fatBuilderOpenFatDataDirBtn->setEnabled(false);

    QString dirPath = QFileDialog::getExistingDirectory(
        this, tr("Select Directory"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (!dirPath.isNull())
    {
        NFResult nfResult = buildFatData(ui->fatBuilderFatDirPathEdt->text().toStdString(),
            ui->fatBuilderOriginalFatPathEdt->text().toStdString(),
            ui->fatBuilderFatAddrEdt->text().toUInt(nullptr, 16),
            dirPath.toStdString());
        nfResult.result? QMessageBox::information(this, tr("NDSFactory"), tr("fat_data.bin and fat.bin correctly built!"))
            : QMessageBox::critical(this, tr("NDSFactory"), nfResult.message.c_str());
    }

    ui->fatBuilderOpenFatDataDirBtn->setEnabled(true);
}