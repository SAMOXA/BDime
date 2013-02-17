#include <QtGui/QApplication>
#include "mainwindow.h"
#include "parser.h"
#include "dbdriver.h"
#include "dialogs.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    parser parserManager;
    dialogs dialogsManager;
    parserManager.setDialogManager(&dialogsManager);
    dbDriver dbManager;
    dbManager.init("test.sqlite");
    QObject::connect(&w, SIGNAL(SIGNALaddPrice(QString)), &parserManager, SLOT(SLOTparse(QString)));
    QObject::connect(&parserManager, SIGNAL(SIGNALaddToDb(QString,QString,float)), &dbManager, SLOT(SLOTaddItem(QString,QString,float)));
    QObject::connect(&parserManager, SIGNAL(SIGNALsetVendor(QString)), &dbManager, SLOT(SLOTsetVendor(QString)));
    QObject::connect(w.model, SIGNAL(SIGNALgetItems(QStringList)), &dbManager, SLOT(SLOTgetItems(QStringList)));
    QObject::connect(&dbManager, SIGNAL(SIGNALtoModel(QString,QString,float,int)), w.model, SLOT(SLOTtoModel(QString,QString,float,int)));
    QObject::connect(w.model, SIGNAL(SIGNALgetVendors()), &dbManager, SLOT(SLOTgetVendors()));
    QObject::connect(&dbManager, SIGNAL(SIGNALvendor(int,QString)), w.model, SLOT(SLOTvendor(int,QString)));
    //QObject::connect(&dbManager, SIGNAL(SIGNALrepaint()), &w, SLOT(SLOTrepaint()));
    w.show();
    return a.exec();
}
