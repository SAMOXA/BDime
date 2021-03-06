#ifndef VENDORDELEGATE_H
#define VENDORDELEGATE_H

#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QListWidget>
#include <QStringList>
#include <QtWidgets/QLineEdit>
#include <QDebug>

class vendorDelegate : public QItemDelegate
{
public:
    vendorDelegate();
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

#endif // VENDORDELEGATE_H
