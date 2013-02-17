#ifndef TABLEROW_H
#define TABLEROW_H

#include <QString>
#include <QStringList>

class tableRow
{
public:
    tableRow();
    tableRow(QString &_desc, float _price);
    QString desc;
    float price;
    QString vendorName;
};

#endif // TABLEROW_H
