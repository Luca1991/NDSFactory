#pragma once

#include <QFileDialog>

inline QString customSaveFileDialog(const QString& title, const QString& defaultName, const QString& filter)
{

    static QString lastUsedPath;

    QString selectedPath = QFileDialog::getSaveFileName(
        Q_NULLPTR,
        title,
        lastUsedPath + defaultName,
        filter);

    if (!selectedPath.isNull())
        lastUsedPath = selectedPath.mid(0, selectedPath.lastIndexOf('/', Qt::CaseInsensitive)+1);

    return selectedPath;
}