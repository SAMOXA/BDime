#include "dialogs.h"

dialogs::dialogs(QWidget *parent) :
    QWidget(parent)
{
}

QString dialogs::getText()
{
    QString text = QInputDialog::getText(this, QString::fromLocal8Bit("Введите имя поставщика"),
                                         QString::fromLocal8Bit("Имя поставщика"));
    return text;

}
