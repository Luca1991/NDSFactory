#include "ndsheadermodel.h"
#include "../../ndsfactory/ndsheader.h"
#include "../tabs/commons/headernames.h"


NDSHeaderModel::NDSHeaderModel(NDSHeader *ndsHeader, QObject *parent) : QAbstractTableModel(parent)
{
    this->ndsHeader = ndsHeader;
}

int NDSHeaderModel::rowCount(const QModelIndex &parent) const
{
    return static_cast<int>(ndsHeaderNamesArr.size());
}

int NDSHeaderModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant NDSHeaderModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
       if(index.column() == 0)
            return QString::fromStdString(ndsHeaderNamesArr.at(static_cast<size_t>(index.row())));
       else if(index.column() == 1) {
           return getDataFromNDSHeader(index.row());
       }
    }
    return QVariant();
}

QVariant NDSHeaderModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
        {
            switch(section)
            {
            case 0:
                return "Name";
            case 1:
                return "Value";
            }
        }
    }
    return QVariant();
}

QString NDSHeaderModel::getDataFromNDSHeader(int index) const
{
    switch (index) {
    case 0:
        return QString::fromUtf8(ndsHeader->GameTitle, 0xC);
    case 1:
        return QString::fromUtf8(ndsHeader->GameCode, 0x4);
    case 2:
        return QString::fromUtf8(reinterpret_cast<char*>(ndsHeader->MakerCode), 0x2);
    case 3:
        return QString::number(ndsHeader->UnitCode, 16);
    case 4:
        return QString::number(ndsHeader->DeviceType, 16);
    case 5:
        return QString::number(ndsHeader->DeviceSize, 16);
    case 6:
        return QString::number(ndsHeader->RomVersion, 16);
    case 7:
        return QString::number(ndsHeader->Flags, 16);
    case 8:
        return QString::number(ndsHeader->Arm9RomAddr,16);
    case 9:
        return QString::number(ndsHeader->Arm9EntryAddr,16);
    case 10:
        return QString::number(ndsHeader->Arm9RamAddr,16);
    case 11:
        return QString::number(ndsHeader->Arm9Size,16);
    case 12:
        return QString::number(ndsHeader->Arm7RomAddr,16);
    case 13:
        return QString::number(ndsHeader->Arm7EntryAddr,16);
    case 14:
        return QString::number(ndsHeader->Arm7RamAddr,16);
    case 15:
        return QString::number(ndsHeader->Arm7Size,16);
    case 16:
        return QString::number(ndsHeader->FilenameTableAddr,16);
    case 17:
        return QString::number(ndsHeader->FilenameSize,16);
    case 18:
        return QString::number(ndsHeader->FATAddr,16);
    case 19:
        return QString::number(ndsHeader->FATSize,16);
    case 20:
        return QString::number(ndsHeader->Arm9OverlayAddr,16);
    case 21:
        return QString::number(ndsHeader->Arm9OverlaySize,16);
    case 22:
        return QString::number(ndsHeader->Arm7OverlayAddr,16);
    case 23:
        return QString::number(ndsHeader->Arm7OverlaySize,16);
    case 24:
        return QString::number(ndsHeader->NormalCommandsSettings,16);
    case 25:
        return QString::number(ndsHeader->Key1CommandsSettings,16);
    case 26:
        return QString::number(ndsHeader->IconTitleAddr,16);
    case 27:
        return QString::number(ndsHeader->SecureAreaCRC16,16);
    case 28:
        return QString::number(ndsHeader->SecureAreaLoadingTimeout,16);
    case 29:
        return QString::number(ndsHeader->ARM9AutoLoadListRamAddr,16);
    case 30:
        return QString::number(ndsHeader->ARM7AutoLoadListRamAddr,16);
    case 31:
        return QString::number(ndsHeader->SecureAreaDisable,16);
    case 32:
        return QString::number(ndsHeader->RomSize,16);
    case 33:
        return QString::number(ndsHeader->HeaderSize,16);
    case 34:
        return QByteArray::fromRawData(reinterpret_cast<char*>(ndsHeader->NintendoLogo), 0x9C).toHex();
    case 35:
        return QString::number(ndsHeader->NintendoLogoCRC,16);
    case 36:
        return QString::number(ndsHeader->HeaderCRC16,16);
    case 37:
        return QString::number(ndsHeader->DebugRomAddr,16);
    case 38:
        return QString::number(ndsHeader->DebugSize,16);
    case 39:
        return QString::number(ndsHeader->DebugRamAddr,16);
    case 40:
        return QString::number((ndsHeader->IconTitleAddr+IconTitleSize),16);
    default:
        return nullptr;
    }
}











