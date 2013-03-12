#include <QtGui/QApplication>
#include "mainwindow.h"
#include "parser.h"
#include "dbdriver.h"
#include "dialogs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    parser parserManager(&a);
    dialogs dialogsManager;
    parserManager.setDialogManager(&dialogsManager);
    dbDriver dbManager;
    dbManager.init("test.sqlite");
    QObject::connect(&w, SIGNAL(SIGNALaddPrice(QString)), &parserManager, SLOT(SLOTparse(QString)));
    QObject::connect(&parserManager, SIGNAL(SIGNALaddToDb(QString,QString,float)), &dbManager, SLOT(SLOTaddItem(QString,QString,float)));
    QObject::connect(&parserManager, SIGNAL(SIGNALsetVendor(QString)), &dbManager, SLOT(SLOTsetVendor(QString)));
    QObject::connect(&parserManager, SIGNAL(SIGNALfinalParsing()), &dbManager, SLOT(SLOTfinalAdding()));
    QObject::connect(&parserManager, SIGNAL(SIGNALfinalParsing()), &w, SLOT(SLOTfinalParsing()));
    QObject::connect(w.model, SIGNAL(SIGNALgetItems(QStringList)), &dbManager, SLOT(SLOTgetItems(QStringList)));
    QObject::connect(&dbManager, SIGNAL(SIGNALtoModel(QString,QString,float,int)), w.model, SLOT(SLOTtoModel(QString,QString,float,int)));
    QObject::connect(w.model, SIGNAL(SIGNALgetVendors()), &dbManager, SLOT(SLOTgetVendors()));
    QObject::connect(&dbManager, SIGNAL(SIGNALvendor(int,QString)), w.model, SLOT(SLOTvendor(int,QString)));
    QObject::connect(&dbManager, SIGNAL(SIGNALdbMessage(QString)), &w, SLOT(SLOTmsg(QString)));
    QObject::connect(&dbManager, SIGNAL(SIGNALdbError(QString)), &w, SLOT(SLOTerrorMsg(QString)));
    QObject::connect(&parserManager, SIGNAL(SIGNALstartParsing(int)), &w, SLOT(SLOTstartParsing(int)));
    QObject::connect(&parserManager, SIGNAL(SIGNALuodateLabelCount(int,int)), &w, SLOT(SLOTuodateLabelCount(int,int)));
    QObject::connect(&parserManager, SIGNAL(SIGNALupDateProgressBar()), &w, SLOT(SLOTupDateProgressBar()));
    w.show();
    return a.exec();
}
