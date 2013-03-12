#include "temptablemodel.h"

tempTableModel::tempTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    header_data << QString::fromUtf8("Артикль")
                << QString::fromUtf8("Описание")
                << QString::fromUtf8("Колличество")
                << QString::fromUtf8("Цена")
                << QString::fromUtf8("Сумма")
                << QString::fromUtf8("Имя производителя");
}

QVariant tempTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() > keysModelData.size())
        return QVariant();
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        if(index.column() == 0)
            return keysModelData.at(index.row());
        if(index.column() == 1){
            if(modelData.count(keysModelData.at(index.row())) > 1){
                tableRow temp(true);
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()), temp);
                if(tempIter == modelData.end())
                    return QVariant(QString::fromUtf8("Конфликт"));
                else
                    return QVariant(tempIter.value().desc);
            }
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromUtf8("Артикль не найден"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().desc);
        }
        if(index.column() == 2){
            if(modelData.count(keysModelData.at(index.row())) > 1){
                tableRow temp(true);
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()), temp);
                if(tempIter == modelData.end())
                    return QVariant(QString::fromUtf8("Конфликт"));
                else
                    return QVariant(tempIter.value().count);
            }
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromUtf8("Артикль не найден"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().count);
        }
        if(index.column() == 3){
            if(modelData.count(keysModelData.at(index.row())) > 1){
                tableRow temp(true);
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()), temp);
                if(tempIter == modelData.end())
                    return QVariant(QString::fromUtf8("Конфликт"));
                else
                    return QVariant(tempIter.value().price);
            }
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromUtf8("Артикль не найден"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().price);
        }
        if(index.column() == 4){
            if(modelData.count(keysModelData.at(index.row())) > 1){
                tableRow temp(true);
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()), temp);
                if(tempIter == modelData.end())
                    return QVariant(QString::fromUtf8("Конфликт"));
                else
                    return QVariant(tempIter.value().price * tempIter.value().count);
            }
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromUtf8("Артикль не найден"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().price * modelData.find(keysModelData.at(index.row())).value().count);
        }
        if(index.column() == 5){
            if(role == Qt::DisplayRole){
                tableRow tempRow(true);
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()), tempRow);
                if(tempIter == modelData.end()){
                    return QVariant();
                }else{
                    return QVariant(vendors[tempIter.value().vendorName]);
                }
            }
            if(role == Qt::EditRole){
                QStringList temp;
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()));
                if(tempIter != modelData.end()){
                    tempIter = modelData.find(keysModelData.at(index.row()));
                    while(tempIter.key() == keysModelData.at(index.row())){
                        temp << vendors[tempIter.value().vendorName];
                        tempIter++;
                        if(tempIter == modelData.end() || tempIter.key() != keysModelData.at(index.row())){
                            break;
                        }
                    }
                    return QVariant(temp);
                }else{
                    return QVariant();
                }
            }
        }
        return QVariant();
    }
    if(role == Qt::ForegroundRole){
        tableRow tempRow(true);
        QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()), tempRow);
        QBrush brush;
        if(tempIter == modelData.end()){
            tempIter = modelData.find(keysModelData.at(index.row()));
            if(tempIter == modelData.end()){
                brush = QColor(Qt::blue);
            }else{
                brush = QColor(Qt::red);
            }
        }else{
            brush = QColor(Qt::black);
        }
        return QVariant(brush);
    }
    return QVariant();
}

bool tempTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        if(index.column() == 2){
            tableRow temp(vendors.key(keysModelData.at(index.row())), true);
            QMap <QString, tableRow>::iterator tempIter = modelData.find(keysModelData.at(index.row()), temp);
            if(tempIter == modelData.end()){
                return false;
            }else{
                tempIter.value().count = value.toInt();
                qDebug() << tempIter.value().count;
            }
        }
        if(index.column()==5){
            QMap <QString, tableRow>::iterator tempIter = modelData.find(keysModelData.at(index.row()));
            while(tempIter.key() == keysModelData.at(index.row())){
                tempIter.value().selected = false;
                if(tempIter.value().vendorName == vendors.key(value.toString())){
                    tempIter.value().selected = true;
                }
                tempIter++;
                if(tempIter == modelData.end()){
                    break;
                }
            }
        }
        return true;
    }
    return false;
}

int tempTableModel::rowCount(const QModelIndex &parent) const
{
    return keysModelData.size();
}

int tempTableModel::columnCount(const QModelIndex &parent) const
{
    return 6;
}

int tempTableModel::columnCount() const
{
    return 6;
}

QVariant tempTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
           return QVariant();
   if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
       return header_data.at(section); // заголовки столбцов
   }else{
       return QString("%1").arg( section + 1 ); // возвращаем номера строк
   }
}

Qt::ItemFlags tempTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

void tempTableModel::SLOTgetItems()
{
    emit SIGNALgetVendors();
    QClipboard *clipboard = QApplication::clipboard();
    QString text(clipboard->text());
    QTextStream stream(&text);
    QStringList list;
    while(!stream.atEnd()){
        list << stream.readLine();
    }
    emit SIGNALgetItems(list);
}

void tempTableModel::SLOTtoModel(const QString art, QString desc, float price, int vendorId)
{
    int row = keysModelData.size();
    if(!keysModelData.contains(art)){
        beginInsertRows( QModelIndex(), row, row );
        keysModelData.push_back(art);
        endInsertRows();
    }
    if(vendorId == 0){
        return;
    }
    tableRow temp(desc, price, vendorId);
    modelData.insert(art, temp);
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
}

void tempTableModel::SLOTvendor(int id, QString name)
{
    vendors.insert(id, name);
}
