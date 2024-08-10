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

private:
    Ui::MainWindow *ui;
    NDSFactory ndsFactory;
    std::vector<char> romHeader;
    void populateHeader(NDSHeader* ndsHeader);
    void enableExtractionButtons();
    void disableExtractionButtons();
    bool dumpHeader(const std::string& dirPath);
    bool dumpArm9Bin(const std::string& dirPath, bool dumpExtraBytes);
    bool dumpArm7Bin(const std::string& dirPath);
    bool dumpFnt(const std::string& dirPath);
    bool dumpFat(const std::string& dirPath);
    bool dumpArm9Overlay(const std::string& dirPath);
    bool dumpArm9OverlayFiles(const std::string& dirPath);
    bool dumpArm7Overlay(const std::string& dirPath);
    bool dumpArm7OverlayFiles(const std::string& dirPath);
    bool dumpIconTitle(const std::string& dirPath);
    bool dumpFatFiles(const std::string& dirPath);
    bool dumpEverything(QString dirPath);
    void notifyExtractionResult(bool result);

    void populatePackerSectionHeader(NDSHeader *ndsHeader);
    void enableCalcCrcButton();
    void enableBuildRomButton();
    void generateHeader(NDSHeader* pRomHeader);
    bool writeHeader(const std::string& savePath);
    void calcHeaderCrc16();
    bool writeArm9Bin(const std::string& savePath, bool isArm9FooterPresent);
    bool writeArm7Bin(const std::string& savePath);
    bool writeFnt(const std::string& savePath);
    bool writeFat(const std::string& savePath);
    bool writeArm9Overlay(const std::string& savePath);
    bool writeArm9OverlayFiles(const std::string& savePath);
    bool writeArm7Overlay(const std::string& savePath);
    bool writeArm7OverlayFiles(const std::string& savePath);
    bool writeIconTitle(const std::string& savePath);
    bool writeFatFiles(const std::string& savePath);
    bool writeEverything(const std::string& savePath);

    bool writeHeaderPadding(char paddingByte, const std::string& savePath);
    bool writeArm9BinPadding(char paddingByte, const std::string& savePath, bool isArm9FooterPresent);
    bool writeArm7BinPadding(char paddingByte, const std::string& savePath);
    bool writeFntPadding(char paddingByte, const std::string& savePath);
    bool writeFatPadding(char paddingByte, const std::string& savePath);
    bool writeArm9OverlayPadding(char paddingByte, const std::string& savePath);
    bool writeArm9OverlayFilesPadding(char paddingByte, const std::string& savePath);
    bool writeArm7OverlayPadding(char paddingByte, const std::string& savePath);
    bool writeArm7OverlayFilesPadding(char paddingByte, const std::string& savePath);
    bool writeRomPadding(const std::string& savePath);

    //QString extractUnpackerHeaderTableData(int index);
    QString extractPackerHeaderTableData(int index);

    bool extractFatData(const std::string& fatDataSectionPath, const std::string& fatSectionPath,
        const std::string& fntSectionPath, uint32_t originalFatDataAddr, const std::string& savePath);
    bool patchFat(const std::string& loadPath, uint32_t shiftSize, const std::string& savePath);
};
