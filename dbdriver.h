#ifndef DBDRIVER_H
#define DBDRIVER_H

#include <QObject>
#include <QtSql>
#include <QMap>
#include "tablerow.h"

class dbDriver : public QObject
{
    Q_OBJECT
public:
    explicit dbDriver(QObject *parent = 0);
    void init(const QString &path);
    QSqlRelationalTableModel *dbModel;
signals:
    void SIGNALdbError(const QString &);
    void SIGNALdbMessage(const QString &);
    void SIGNALtoModel(const QString, QString, float, int);
    void SIGNALrepaint();
    void SIGNALvendor(int, QString);
public slots:
    void SLOTaddItem(const QString &art, const QString &desc, const float price);
    void SLOTsetVendor(const QString &vendorName);
    void SLOTgetItems(const QStringList list);
    void SLOTgetVendors();
    void SLOTfinalAdding();
private:
    bool status;
    QSqlDatabase dbase;
    int vendorId;
    int numberOfInserts;
    QString multipleQuery;
    QSqlQuery *addQuery;
    QVariantList arts;
    QVariantList descs;
    QVariantList prices;
    QVariantList vendorIds;
};

#endif // DBDRIVER_H
