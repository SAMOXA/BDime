#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QClipboard>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
signals:
    void SIGNALaddPrice(const QString &path);
public slots:
    void SLOTaddPrice();
    void SLOTgetArts();
};

#endif // MAINWINDOW_H
