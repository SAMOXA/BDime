#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->addPriceButton, SIGNAL(clicked()), this, SLOT(SLOTaddPrice()));
    QObject::connect(ui->getClipboardButton, SIGNAL(clicked()), this, SLOT(SLOTgetArts()));
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
