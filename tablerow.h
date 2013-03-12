#ifndef TABLEROW_H
#define TABLEROW_H

#include <QString>
#include <QStringList>
#include <QDebug>

class tableRow
{
public:
    tableRow();
    tableRow(QString _desc, float _price, int _vendorName);
    tableRow(int _vendorName, bool _selected);
    tableRow(int _vendorName);
    QString desc;
    float price;
    int vendorName;
    int count;
    bool selected;
    friend bool operator==(const tableRow& left, const tableRow& right);
    friend QDebug operator <<(QDebug d, const tableRow &data);
    tableRow(bool _selected);
};

#endif // TABLEROW_H
