#include <QApplication>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/about/aboutdialog.h"
#include "utils/theme.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ndsFactory = NDSFactory();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog;
    aboutDialog.exec();
}

void MainWindow::on_actionDark_triggered()
{
	setTheme("dark");
}

void MainWindow::on_actionLight_triggered()
{
	setTheme("light");
}

void MainWindow::on_actionDefault_triggered()
{
	setTheme("default");
}
