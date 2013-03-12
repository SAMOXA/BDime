#include "tablerow.h"

tableRow::tableRow()
{
    desc = "";
    price = 0.0;
    vendorName = 0;
    selected = false;
    count = 0;
}

tableRow::tableRow(QString _desc, float _price, int _vendorName)
{
    desc = _desc;
    price = _price;
    vendorName = _vendorName;
    selected = false;
    count = 0;
}

tableRow::tableRow(int _vendorName, bool _selected)
{
    desc = "";
    price = 0;
    vendorName = _vendorName;
    selected = _selected;
    count = 0;
}

tableRow::tableRow(int _vendorName)
{
    desc = "";
    price = 0;
    vendorName = _vendorName;
    selected = false;
    count = 0;
}

tableRow::tableRow(bool _selected)
{
    desc = "";
    price = 0;
    vendorName = 0;
    selected = _selected;
    count = 0;
}

bool operator ==(const tableRow &left, const tableRow &right)
{
    return left.selected == right.selected;
}

QDebug operator <<(QDebug d, const tableRow &data)
{
    d << data.count << " " << data.desc << " " << data.price << " " << data.selected << " " << data.vendorName;
    return d;
}
