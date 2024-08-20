#pragma once

#include <QApplication>
#include <QPalette>
#include <QSettings>
#include <QMessageBox>

inline void setDarkTheme(QApplication& app)
{
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    app.setPalette(darkPalette);
}

inline void setLightTheme(QApplication& app)
{
    QPalette lightPalette;
    lightPalette.setColor(QPalette::Window, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, QColor(255, 255, 255));
    lightPalette.setColor(QPalette::AlternateBase, QColor(233, 233, 233));
    lightPalette.setColor(QPalette::ToolTipBase, Qt::black);
    lightPalette.setColor(QPalette::ToolTipText, Qt::white);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, QColor(240, 240, 240));
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    lightPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    app.setPalette(lightPalette);
}

inline void setTheme(QString themeValue)
{
    QSettings settings;
    settings.setValue("theme", themeValue);
    QMessageBox::information(nullptr, "NDSFactory", "Restart NDSFactory to change theme!");

}

inline QString getCurrentTheme()
{
	QSettings settings;
    return settings.value("theme", "default").toString();
}