#include "parser.h"

parser::parser(QObject *parent) :
    QObject(parent)
{
}

void parser::setDialogManager(dialogs *dm)
{
    dialogsManager = dm;
}

void parser::SLOTparse(const QString &path)
{
    QFile priceList(path);
    QString line;
    if (!priceList.open(QIODevice::ReadOnly | QIODevice::Text)){

    }
    QString vendorName = dialogsManager->getText();
    emit SIGNALsetVendor(vendorName);
    QTextStream stream( &priceList );
    line = stream.readLine();
    QStringList fields = line.split(";");
    QString additionalLine;
    while (!priceList.atEnd()) {
        line = stream.readLine();
        if(line.count(';')<2){
            additionalLine = stream.readLine();
            line += additionalLine;
        }
        fields = line.split(";");
        if(fields.at(0) == "" || fields.at(2) == ""){
            continue;
        }
        emit SIGNALaddToDb(fields.at(0), fields.at(1), fields.at(2).toFloat());
    }
}
