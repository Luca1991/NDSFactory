#pragma once

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT
    public:
        AboutDialog(QWidget *parent = nullptr);
        ~AboutDialog();

    private:
        Ui::AboutDialog *ui;

};
