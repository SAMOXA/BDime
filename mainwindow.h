#ifndef MAINWINDOW_H_BDIME
#define MAINWINDOW_H_BDIME

#include <QMainWindow>
#include <QFileDialog>
#include <QClipboard>
#include <QDebug>
#include "temptablemodel.h"
#include "vendordelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    tempTableModel *model;

private:
    Ui::MainWindow *ui;

signals:
    void SIGNALaddPrice(const QString &path);
public slots:
    void SLOTaddPrice();
    void SLOTgetArts();
    void SLOTrepaint();
    void SLOTerrorMsg(const QString &);
    void SLOTmsg(const QString &);
    void SLOTuodateLabelCount(int n, int N);
    void SLOTupDateProgressBar();
    void SLOTstartParsing(int);
    void SLOTfinalParsing();
};

#endif // MAINWINDOW_H
