#include "tablerow.h"

tableRow::tableRow()
{
    desc = "";
    price = 0.0;
    vendorName = 0;
}

tableRow::tableRow(QString _desc, float _price, int _vendorName)
{
    desc = _desc;
    price = _price;
    vendorName = _vendorName;
}

bool operator ==(const tableRow &left, const tableRow &right)
{
    return left.vendorName == right.vendorName;
}
