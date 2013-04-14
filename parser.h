#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QChar>
#include <QtWidgets/QApplication>
#include "dialogs.h"

class parser : public QObject
{
    Q_OBJECT
public:
    explicit parser(QObject *parent = 0);
    void setDialogManager(dialogs *dm);
private:
    dialogs *dialogsManager;

signals:
    void SIGNALaddToDb(const QString &art, const QString &description, const float price);
    void SIGNALsetVendor(const QString &vendorName);
    void SIGNALuodateLabelCount(int, int);
    void SIGNALupDateProgressBar();
    void SIGNALstartParsing(int);
    void SIGNALfinalParsing();
public slots:
    void SLOTparse(const QString &path);
};

#endif // PARSER_H
