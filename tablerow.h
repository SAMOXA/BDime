#ifndef TABLEROW_H
#define TABLEROW_H

#include <QString>
#include <QStringList>

class tableRow
{
public:
    tableRow();
    tableRow(QString _desc, float _price, int _vendorName);
    QString desc;
    float price;
    int vendorName;
    friend bool operator==(const tableRow& left, const tableRow& right);
};

#endif // TABLEROW_H
