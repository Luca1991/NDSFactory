#pragma once

#include <QMainWindow>
#include <cstdint>
#include "../ndsfactory/ndsfactory.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadRomBtn_clicked();
    void on_unpackerDumpHeaderBtn_clicked();
    void on_unpackerDumpArm9Btn_clicked();
    void on_unpackerDumpArm7Btn_clicked();
    void on_unpackerDumpFntBtn_clicked();
    void on_unpackerDumpFatBtn_clicked();
    void on_unpackerDumpArm9OverlayBtn_clicked();
    void on_unpackerDumpArm7OverlayBtn_clicked();
    void on_unpackerDumpIconTitleLogoBtn_clicked();
    void on_unpackerDumpFatFilesBtn_clicked();
    void on_unpackerDumpArm9OverlayFilesBtn_clicked();
    void on_unpackerDumpArm7OverlayFilesBtn_clicked();
    void on_unpackerDumpEverythingBtn_clicked();

    void on_actionDark_triggered();
    void on_actionLight_triggered();
    void on_actionDefault_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

    void on_packerLoadHeaderBtn_clicked();
    void on_packerLoadArm9BinBtn_clicked();
    void on_packerLoadArm7BinBtn_clicked();
    void on_packerLoadFntBtn_clicked();
    void on_packerLoadFatBtn_clicked();
    void on_packerLoadArm9OverlayBtn_clicked();
    void on_packerLoadArm9OverlayFilesBtn_clicked();
    void on_packerLoadArm7OverlayBtn_clicked();
    void on_packerLoadArm7OverlayFilesBtn_clicked();
    void on_packerLoadIconTitleBtn_clicked();
    void on_packerLoadFatFilesBtn_clicked();
    void on_packerCalcHeaderCrcBtn_clicked();
    void on_packerBuildNDSRomBtn_clicked();

    void on_fatPatcherLoadFatBtn_clicked();
    void on_fatPatcherPatchFatBtn_clicked();
    void on_fatExtractorLoadFatDataBtn_clicked();
    void on_fatExtractorLoadFatBtn_clicked();
    void on_fatExtractorLoadFntBtn_clicked();
    void on_fatExtractorExtractBtn_clicked();
    void on_fatBuilderOpenFatDataDirBtn_clicked();
	void on_fatBuilderLoadOriginalFatBtn_clicked();
    void on_fatBuilderBuildBtn_clicked();

private:
    Ui::MainWindow *ui;
    NDSFactory ndsFactory;
    std::vector<char> romHeader;
    void populateHeader(NDSHeader* ndsHeader);
    void enableExtractionButtons();
    void disableExtractionButtons();
    NFResult dumpHeader(const std::string& dirPath);
    NFResult dumpArm9Bin(const std::string& dirPath, bool dumpExtraBytes);
    NFResult dumpArm7Bin(const std::string& dirPath);
    NFResult dumpFnt(const std::string& dirPath);
    NFResult dumpFat(const std::string& dirPath);
    NFResult dumpArm9Overlay(const std::string& dirPath);
    NFResult dumpArm9OverlayFiles(const std::string& dirPath);
    NFResult dumpArm7Overlay(const std::string& dirPath);
    NFResult dumpArm7OverlayFiles(const std::string& dirPath);
    NFResult dumpIconTitle(const std::string& dirPath);
    NFResult dumpFatFiles(const std::string& dirPath);
    NFResult dumpEverything(QString dirPath);

    void populatePackerSectionHeader(NDSHeader *ndsHeader);
    void enableCalcCrcButton();
    void enableBuildRomButton();
    void generateHeader(NDSHeader* pRomHeader);
    NFResult writeHeader(const std::string& savePath);
    void calcHeaderCrc16();
    NFResult writeArm9Bin(const std::string& savePath, bool isArm9FooterPresent);
    NFResult writeArm7Bin(const std::string& savePath);
    NFResult writeFnt(const std::string& savePath);
    NFResult writeFat(const std::string& savePath);
    NFResult writeArm9Overlay(const std::string& savePath);
    NFResult writeArm9OverlayFiles(const std::string& savePath);
    NFResult writeArm7Overlay(const std::string& savePath);
    NFResult writeArm7OverlayFiles(const std::string& savePath);
    NFResult writeIconTitle(const std::string& savePath);
    NFResult writeFatFiles(const std::string& savePath);
    NFResult writeEverything(const std::string& savePath);

    NFResult writeHeaderPadding(char paddingByte, const std::string& savePath);
    NFResult writeArm9BinPadding(char paddingByte, const std::string& savePath, bool isArm9FooterPresent);
    NFResult writeArm7BinPadding(char paddingByte, const std::string& savePath);
    NFResult writeFntPadding(char paddingByte, const std::string& savePath);
    NFResult writeFatPadding(char paddingByte, const std::string& savePath);
    NFResult writeRomPadding(const std::string& savePath);

    QString extractPackerHeaderTableData(int index);

    NFResult extractFatData(const std::string& fatDataSectionPath, const std::string& fatSectionPath,
        const std::string& fntSectionPath, uint32_t originalFatDataAddr, const std::string& savePath, bool logFileIDs);
    NFResult patchFat(const std::string& loadPath, uint32_t shiftSize, const std::string& savePath);
    NFResult buildFatData(const std::string& fatDataDirPath, const std::string& originalFatPath, uint32_t fatDataAddr, const std::string& savePath);
};
