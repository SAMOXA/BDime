#ifndef TEMPTABLEMODEL_H
#define TEMPTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QStringList>
#include <QMultiMap>
#include <QClipboard>
#include <QtWidgets/QApplication>
#include <QTextStream>
#include <QBrush>
#include <QDebug>
#include "tablerow.h"

class tempTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit tempTableModel(QObject *parent = 0);

    QMultiMap <QString, tableRow> modelData;
    QList <QString> keysModelData;
    QStringList header_data;
    QMap <int, QString> vendors;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    int columnCount() const;
    QVariant headerData(int section,Qt::Orientation orientation, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

signals:
    void SIGNALgetItems(QStringList);
    void SIGNALgetVendors();
public slots:
    void SLOTgetItems();
    void SLOTtoModel(const QString, QString, float, int);
    void SLOTvendor(int, QString);
private:

};

#endif // TEMPTABLEMODEL_H
