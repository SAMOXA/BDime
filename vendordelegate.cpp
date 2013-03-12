#include "vendordelegate.h"

vendorDelegate::vendorDelegate()
{

}

QWidget *vendorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0){
        QLineEdit *editor = new QLineEdit(parent);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    if(index.column() == 1){
        QLineEdit *editor = new QLineEdit(parent);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    if(index.column() == 2){
        QLineEdit *editor = new QLineEdit(parent);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    if(index.column() == 3){
        QLineEdit *editor = new QLineEdit(parent);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    if(index.column() == 4){
        QLineEdit *editor = new QLineEdit(parent);
        QString currentText = index.model()->data(index, Qt::DisplayRole).toString();
        editor->setText(currentText);
        return editor;
    }
    if(index.column() == 5){
        QListWidget *vendors = new QListWidget(parent);
        return vendors;
    }
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void vendorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0){
        QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
            textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
        }
    }
    if(index.column() == 1){
        QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
            textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
        }
    }
    if(index.column() == 2){
        QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
            textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
        }
    }
    if(index.column() == 3){
        QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
            textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
        }
    }
    if(index.column() == 4){
        QLineEdit *textEditor = qobject_cast<QLineEdit *>(editor);
        if (textEditor) {
            textEditor->setText(index.model()->data(index, Qt::EditRole).toString());
        }
    }
    if(index.column() == 5){
        QListWidget *vendors = qobject_cast<QListWidget *>(editor);
        if (vendors) {
            QStringList temp = index.model()->data(index, Qt::EditRole).toStringList();
            vendors->insertItems(0, temp);
        }
    }
}

void vendorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 2){
        QLineEdit *count = qobject_cast<QLineEdit *>(editor);
        if(count){
            model->setData(index, count->text().toInt());
        }
    }
    if(index.column() == 5){
        QListWidget *vendors = qobject_cast<QListWidget *>(editor);
        if (vendors) {
            QList <QListWidgetItem *> temp = vendors->selectedItems();
            if(temp.empty()){
                return;
            }
            model->setData(index, temp.at(0)->text());
        }
    }
}
