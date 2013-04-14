#ifndef DIALOGS_H
#define DIALOGS_H

#include <QtWidgets/QWidget>
#include <QString>
#include <QtWidgets/QInputDialog>

class dialogs : public QWidget
{
    Q_OBJECT
public:
    explicit dialogs(QWidget *parent = 0);
    QString getText();
signals:
    
public slots:
    
};

#endif // DIALOGS_H
