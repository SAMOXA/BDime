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
    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 500);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 200);
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
    qDebug() << clipboard->text();
}

void MainWindow::SLOTrepaint()
{
    ui->tableView->repaint();
}
