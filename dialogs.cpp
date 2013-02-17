#include "dialogs.h"

dialogs::dialogs(QWidget *parent) :
    QWidget(parent)
{
}

QString dialogs::getText()
{
    QString text = QInputDialog::getText(this, QString::fromUtf8("Введите имя поставщика"),
                                         QString::fromUtf8("Имя поставщика"));
    return text;

}
