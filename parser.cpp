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
        qDebug() << "LOL";
    }
    QString vendorName = dialogsManager->getText();
    emit SIGNALsetVendor(vendorName);
    int n = 0;
    QByteArray buf = priceList.readLine();
    do {
       buf = priceList.readLine();
       n++;
    } while (!buf.isEmpty());
    int oneProcent = n/100;
    int currentCount = 0;
    int labelCount = 0;
    int allCount = 0;
    priceList.seek(0);
    QTextStream stream( &priceList );
    line = stream.readLine();
    QStringList fields;
    QString additionalLine;
    emit SIGNALstartParsing(n);
    while (!stream.atEnd()) {
        line = stream.readLine();
        if(line.count(';')<2){
            additionalLine = stream.readLine();
            line += additionalLine;
        }
        fields = line.split(";");
        allCount++;
        currentCount++;
        if(currentCount == oneProcent){
            emit SIGNALupDateProgressBar();
            currentCount = 0;
        }
        labelCount++;
        if(labelCount == 5){
            emit SIGNALuodateLabelCount(allCount, n);
            labelCount = 0;
        }
        if(fields.at(0) == "" || fields.at(2) == ""){
            continue;
        }
        emit SIGNALaddToDb(fields.at(0), fields.at(1), fields.at(2).toFloat());
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
}
