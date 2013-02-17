#ifndef DIALOGS_H
#define DIALOGS_H

#include <QWidget>
#include <QString>
#include <QInputDialog>

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
