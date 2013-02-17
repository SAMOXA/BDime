#include "temptablemodel.h"

tempTableModel::tempTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    header_data << QString::fromLocal8Bit("Артикль")
                << QString::fromLocal8Bit("Описание")
                << QString::fromLocal8Bit("Цена")
                << QString::fromLocal8Bit("Производитель");
}

QVariant tempTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() > modelData.size())
        return QVariant();
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        if(index.column() == 0)
            return keysModelData.at(index.row());
        if(index.column() == 1){
            if(modelData.count(keysModelData.at(index.row())) > 1)
                return QVariant(QString::fromLocal8Bit("<font color='red'><b>Конфликт</b></font>"));
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromLocal8Bit("<b>Артикль не найден</b>"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().desc);
        }
        if(index.column() == 2){
            if(modelData.count(keysModelData.at(index.row())) > 1)
                return QVariant(QString::fromLocal8Bit("<font color='red'><b>Конфликт</b></font>"));
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromLocal8Bit("<b>Артикль не найден</b>"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().price);
        }
        if(index.column() == 3){
            if(modelData.count(keysModelData.at(index.row())) > 1){
                QStringList temp;
                QMap <QString, tableRow>::const_iterator tempIter = modelData.find(keysModelData.at(index.row()));
                while(tempIter.key() == keysModelData.at(index.row())){
                    temp << tempIter.value().vendorName;
                }
                return QVariant(temp);
            }
            if(modelData.count(keysModelData.at(index.row())) < 1)
                return QVariant(QString::fromLocal8Bit("<b>Артикль не найден</b>"));
            return QVariant(modelData.find(keysModelData.at(index.row())).value().vendorName);
        }
    }
    return QVariant();
}

void tempTableModel::getItems()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString text(clipboard->text());
    QTextStream stream(&text);
    QString line;
    line = stream.readLine();
    qDebug() << line;
}
