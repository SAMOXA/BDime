#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new tempTableModel;
    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 400);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 100);
    ui->tableView->setColumnWidth(4, 100);
    ui->tableView->setColumnWidth(5, 150);
    ui->tableView->setItemDelegate(new vendorDelegate);
    ui->tableView->verticalHeader()->setDefaultSectionSize(50);
    QObject::connect(ui->addPriceButton, SIGNAL(clicked()), this, SLOT(SLOTaddPrice()));
    QObject::connect(ui->getClipboardButton, SIGNAL(clicked()), model, SLOT(SLOTgetItems()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SLOTaddPrice()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("Укажите файл с прайсом"),"","csv (*.csv)");
    if(fileName != ""){
        emit SIGNALaddPrice(fileName);
    }
}

void MainWindow::SLOTgetArts()
{
    QClipboard *clipboard = QApplication::clipboard();
}

void MainWindow::SLOTrepaint()
{
    ui->tableView->repaint();
}

void MainWindow::SLOTerrorMsg(const QString &str)
{
    ui->msgList->append("<font color='RED'><b>" + str + "</b></font>");
}

void MainWindow::SLOTmsg(const QString &str)
{
    ui->msgList->append(str);
}

void MainWindow::SLOTuodateLabelCount(int n, int N)
{
    QString str = QString::fromUtf8("Колличество обработанных записей %1 из %2");
    str = str.arg(n).arg(N);
    ui->recordCountLabel->setText(str);
}

void MainWindow::SLOTupDateProgressBar()
{
    ui->parserProgressBar->setValue(ui->parserProgressBar->value() + 1);
}

void MainWindow::SLOTstartParsing(int n)
{
    ui->parserProgressBar->setValue(1);
    QString str = QString::fromUtf8("Колличество обработанных записей %1 из %2");
    str = str.arg(0).arg(n);
    ui->recordCountLabel->setText(str);
}

void MainWindow::SLOTfinalParsing()
{
    ui->parserProgressBar->setValue(0);
}
