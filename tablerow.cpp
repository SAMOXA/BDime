#include "tablerow.h"

tableRow::tableRow()
{
    desc = "";
    price = 0.0;
}

tableRow::tableRow(QString &_desc, float _price)
{
    desc = _desc;
    price = _price;
}
