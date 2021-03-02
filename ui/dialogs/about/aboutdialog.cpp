#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "revision.h"


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QString currentVersion = ui->aboutSoftwareNameLbl->text();
    QString currentRevision = QString("Rev: %1").arg(GIT_COMMIT_HASH);
    ui->aboutSoftwareNameLbl->setText(currentVersion + " " + currentRevision);
    QString buildInfo = QString("Build Date: %1 Time: %2").arg(__DATE__, __TIME__);
    ui->aboutSoftwareBuildLbl->setText(buildInfo);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
