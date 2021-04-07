#include <QMessageBox>
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
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
       if(index.column() == 0)
           return QString::fromStdString(ndsHeaderNamesArr.at(static_cast<size_t>(index.row())));
       else if(index.column() == 1) {
           switch (index.row())
           {
           case 0: return QString::fromUtf8(ndsHeader->GameTitle, 0xC);
           case 1: return QString::fromUtf8(ndsHeader->GameCode, 0x4);
           case 2: return QString::fromUtf8(reinterpret_cast<char*>(ndsHeader->MakerCode), 0x2);
           case 3: return QString::number(ndsHeader->UnitCode, 16);
           case 4: return QString::number(ndsHeader->DeviceType, 16);
           case 5: return QString::number(ndsHeader->DeviceSize, 16);
           case 6: return QString::number(ndsHeader->RomVersion, 16);
           case 7: return QString::number(ndsHeader->Flags, 16);
           case 8: return QString::number(ndsHeader->Arm9RomAddr,16);
           case 9: return QString::number(ndsHeader->Arm9EntryAddr,16);
           case 10: return QString::number(ndsHeader->Arm9RamAddr,16);
           case 11: return QString::number(ndsHeader->Arm9Size,16);
           case 12: return QString::number(ndsHeader->Arm7RomAddr,16);
           case 13: return QString::number(ndsHeader->Arm7EntryAddr,16);
           case 14: return QString::number(ndsHeader->Arm7RamAddr,16);
           case 15: return QString::number(ndsHeader->Arm7Size,16);
           case 16: return QString::number(ndsHeader->FilenameTableAddr,16);
           case 17: return QString::number(ndsHeader->FilenameSize,16);
           case 18: return QString::number(ndsHeader->FATAddr,16);
           case 19: return QString::number(ndsHeader->FATSize,16);
           case 20: return QString::number(ndsHeader->Arm9OverlayAddr,16);
           case 21: return QString::number(ndsHeader->Arm9OverlaySize,16);
           case 22: return QString::number(ndsHeader->Arm7OverlayAddr,16);
           case 23: return QString::number(ndsHeader->Arm7OverlaySize,16);
           case 24: return QString::number(ndsHeader->NormalCommandsSettings,16);
           case 25: return QString::number(ndsHeader->Key1CommandsSettings,16);
           case 26: return QString::number(ndsHeader->IconTitleAddr,16);
           case 27: return QString::number(ndsHeader->SecureAreaCRC16,16);
           case 28: return QString::number(ndsHeader->SecureAreaLoadingTimeout,16);
           case 29: return QString::number(ndsHeader->ARM9AutoLoadListRamAddr,16);
           case 30: return QString::number(ndsHeader->ARM7AutoLoadListRamAddr,16);
           case 31: return QString::number(ndsHeader->SecureAreaDisable,16);
           case 32: return QString::number(ndsHeader->RomSize,16);
           case 33: return QString::number(ndsHeader->HeaderSize,16);
           case 34: return QByteArray::fromRawData(reinterpret_cast<char*>(ndsHeader->NintendoLogo), 0x9C).toHex();
           case 35: return QString::number(ndsHeader->NintendoLogoCRC,16);
           case 36: return QString::number(ndsHeader->HeaderCRC16,16);
           case 37: return QString::number(ndsHeader->DebugRomAddr,16);
           case 38: return QString::number(ndsHeader->DebugSize,16);
           case 39: return QString::number(ndsHeader->DebugRamAddr,16);
           case 40: return QString::number((ndsHeader->IconTitleAddr+IconTitleSize),16);
           default: return QString("");
           }
       }
    }
    return QVariant();
}

bool NDSHeaderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role != Qt::EditRole)
        return QAbstractTableModel::setData(index, value, role);

    switch (index.row())
    {
    case 0:
    {
        std::fill_n(ndsHeader->GameTitle, 0xC, 0x0);
        QString gameTitleStr = value.toString().toUpper();
        size_t size = std::min<size_t>(gameTitleStr.size(), 0xC);
        std::copy_n(qUtf8Printable(gameTitleStr), size, ndsHeader->GameTitle);
        break;
    }
    case 1:
    {
        std::fill_n(ndsHeader->GameCode, 0x4, 0x0);
        QString gameCodeStr = value.toString().toUpper();
        size_t size = std::min<size_t>(gameCodeStr.size(), 0x4);
        std::copy_n(qUtf8Printable(gameCodeStr), size, ndsHeader->GameCode);
        break;
    }
    case 2:
    {
        std::fill_n(ndsHeader->MakerCode, 0x2, 0x0);
        QString makerCodeStr = value.toString().toUpper();
        size_t size = std::min<size_t>(makerCodeStr.size(), 0x2);
        std::copy_n(qUtf8Printable(makerCodeStr), size, ndsHeader->MakerCode);
        break;
    }
    case 3: ndsHeader->UnitCode = static_cast<unsigned char>(value.toString().toUInt(nullptr, 16)); break;
    case 4: ndsHeader->DeviceType = static_cast<unsigned char>(value.toString().toUInt(nullptr, 16)); break;
    case 5: ndsHeader->DeviceSize = static_cast<unsigned char>(value.toString().toUInt(nullptr, 16)); break;
    case 6: ndsHeader->RomVersion = static_cast<unsigned char>(value.toString().toUInt(nullptr, 16)); break;
    case 7: ndsHeader->Flags = static_cast<unsigned char>(value.toString().toUInt(nullptr, 16)); break;
    case 8: ndsHeader->Arm9RomAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 9: ndsHeader->Arm9EntryAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 10: ndsHeader->Arm9RamAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 11: ndsHeader->Arm9Size = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 12: ndsHeader->Arm7RomAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 13: ndsHeader->Arm7EntryAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 14: ndsHeader->Arm7RamAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 15: ndsHeader->Arm7Size = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 16: ndsHeader->FilenameTableAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 17: ndsHeader->FilenameSize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 18: ndsHeader->FATAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 19: ndsHeader->FATSize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 20: ndsHeader->Arm9OverlayAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 21: ndsHeader->Arm9OverlaySize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 22: ndsHeader->Arm7OverlayAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 23: ndsHeader->Arm7OverlaySize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 24: ndsHeader->NormalCommandsSettings = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 25: ndsHeader->Key1CommandsSettings = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 26: ndsHeader->IconTitleAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 27: ndsHeader->SecureAreaCRC16 = static_cast<uint16_t>(value.toString().toUInt(nullptr, 16)); break;
    case 28: ndsHeader->SecureAreaLoadingTimeout = static_cast<uint16_t>(value.toString().toUInt(nullptr, 16)); break;
    case 29: ndsHeader->ARM9AutoLoadListRamAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 30: ndsHeader->ARM7AutoLoadListRamAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 31: ndsHeader->SecureAreaDisable = static_cast<uint64_t>(value.toString().toUInt(nullptr, 16)); break;
    case 32: ndsHeader->RomSize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 33: ndsHeader->HeaderSize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 34:
    {
        std::fill_n(ndsHeader->NintendoLogo, 0x9C, 0x0);
        QByteArray nintendoLogoBytes = QByteArray::fromHex(qUtf8Printable(value.toString()));
        size_t size = std::min<size_t>(nintendoLogoBytes.size(), 0x9C);
        std::copy_n(std::begin(nintendoLogoBytes), size, ndsHeader->NintendoLogo);
        break;
    }
    case 35: ndsHeader->NintendoLogoCRC = static_cast<uint16_t>(value.toString().toUInt(nullptr, 16)); break;
    case 36: ndsHeader->HeaderCRC16 = static_cast<uint16_t>(value.toString().toUInt(nullptr, 16)); break;
    case 37: ndsHeader->DebugRomAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 38: ndsHeader->DebugSize = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 39: ndsHeader->DebugRamAddr = static_cast<uint32_t>(value.toString().toUInt(nullptr, 16)); break;
    case 40: QMessageBox::information(nullptr, tr("NDS Factory"), tr("FAT files address is automatically calculated based on Icon/Title address!")); break;
    default: return false;
    }
    Q_EMIT this->dataChanged(index, index);
    return true;
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

Qt::ItemFlags NDSHeaderModel::flags(const QModelIndex &index) const
{
    if (index.isValid() && index.column() == 1 && isValueRowEditable)
           return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;

       return QAbstractItemModel::flags(index);
}

void NDSHeaderModel::setValueRowEditable(bool isEditable)
{
    isValueRowEditable = isEditable;
}
