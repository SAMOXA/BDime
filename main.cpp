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
    w.show();
    return a.exec();
}
