#include "dialogs.h"

dialogs::dialogs(QWidget *parent) :
    QWidget(parent)
{
}

QString dialogs::getText()
{
    QString text = QInputDialog::getText(this, QString::fromLocal8Bit("������� ��� ����������"),
                                         QString::fromLocal8Bit("��� ����������"));
    return text;

}
