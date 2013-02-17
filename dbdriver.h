#ifndef DBDRIVER_H
#define DBDRIVER_H

#include <QObject>
#include <QtSql>

class dbDriver : public QObject
{
    Q_OBJECT
public:
    explicit dbDriver(QObject *parent = 0);
    void init(const QString &path);
    //int loadSettingsFromFile(QString configPath);
    //int getCompetitionList();
    //int getCourtsList();
    //int getCompetitionStat(QString name);
    //int getCompetitionStat(int id);
    //int getAllStat();
    QSqlRelationalTableModel *dbModel;
signals:
    void SIGNALdbError(const QString &);
    void SIGNALdbMessage(const QString &);
public slots:
    //int addEvaluation();
    void SLOTaddItem(const QString &art, const QString &desc, const float price);
    void SLOTsetVendor(const QString &vendorName);
private:
    bool status;
    QSqlDatabase dbase;
    int vendorId;
};

#endif // DBDRIVER_H
