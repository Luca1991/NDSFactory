#ifndef NDSHEADERMODEL_H
#define NDSHEADERMODEL_H

#include <QAbstractTableModel>

struct NDSHeader;

class NDSHeaderModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit NDSHeaderModel(NDSHeader *ndsHeader, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
private:
    NDSHeader *ndsHeader;
    QString getDataFromNDSHeader(int index) const;
};

#endif // NDSHEADERMODEL_H
