#include "dbdriver.h"

dbDriver::dbDriver(QObject *parent) :
    QObject(parent)
{
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    status = false;
}

void dbDriver::init(const QString &path)
{
    if(! QFile::exists(path)){
        emit SIGNALdbMessage(QString::fromLocal8Bit("Была создана новая база данных"));
    }else{
        /*
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("Перезапись БД"));
        msgBox.setText(QString::fromLocal8Bit("Перезаписать БД?"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setInformativeText(QString::fromLocal8Bit("Обнаружена ранее созданая база данных перезаписать её для нового голосования?"));
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Cancel:
                break;
            case QMessageBox::Ok:
                QFile(path).remove();
                emit SIGNALdbMessage(QString::fromLocal8Bit("База данных была перезаписана"));
                break;
            default:
                break;
        }
        */
    }
    dbase.setDatabaseName(path);
    bool globalError = false;
    if(!dbase.open()){
        emit SIGNALdbError(QString::fromLocal8Bit("Ощибка при открытии базы данных") + dbase.lastError().text());
        globalError = true;
    }
    QSqlQuery a_query;
    QString str;
    bool flag;
    str = "CREATE TABLE IF NOT EXISTS vendors (id INTEGER PRIMARY KEY NOT NULL, name TEXT);";
    a_query.exec(str);
    flag = a_query.exec(str);
    if(!flag){
        emit SIGNALdbError(QString::fromLocal8Bit("Ощибка при создании таблицы vendors") + a_query.lastError().text());
        globalError = true;
    }
    if(!a_query.exec("PRAGMA foreign_keys = ON;")){
        emit SIGNALdbError(QString::fromLocal8Bit("Ощибка при установке связных ключей") + a_query.lastError().text());
        globalError = true;
    }
    str = "CREATE TABLE IF NOT EXISTS main ("
            "id INTEGER PRIMARY KEY NOT NULL, "
            "art TEXT NOT NULL, "
            "desc TEXT, "
            "price REAL, "
            "vendor_id INTEGER, "
            "FOREIGN KEY(vendor_id) REFERENCES vendors(id)"
          ");";
    a_query.exec(str);
    flag = a_query.exec(str);
    if(!flag){
        emit SIGNALdbError(QString::fromLocal8Bit("Ощибка при создании таблицы main") + a_query.lastError().text());
        globalError = true;
    }
    dbModel = new QSqlRelationalTableModel;
    dbModel->setTable("main");
    dbModel->setEditStrategy(QSqlTableModel::OnRowChange);
    dbModel->setRelation(4, QSqlRelation("vendors", "id", "name"));
    dbModel->select();
    if(globalError){
        emit SIGNALdbError(QString::fromLocal8Bit("Ощибка базы данных"));
        status = false;
    }else{
        status = true;
    }
}

void dbDriver::SLOTaddItem(const QString &art, const QString &desc, const float price)
{
    QSqlQuery a_query;
    QString str;
    str = "SELECT vendor_id FROM main WHERE art = '%1' AND vendor_id = '%2';";
    str = str.arg(art).arg(vendorId);
    a_query.exec(str);
    if(!a_query.next()){
        str = "INSERT INTO main (id, art, desc, price, vendor_id) VALUES (NULL, '%1', '%2', '%3', '%4')";
        str = str.arg(art).arg(desc).arg(price).arg(vendorId);
        a_query.exec(str);
    }else{
        str = "UPDATE main SET desc = '%1', price = '%2' WHERE art = '%3' AND vendor_id = '%4';";
        str = str.arg(desc).arg(price).arg(art).arg(vendorId);
        a_query.exec(str);
    }
}

void dbDriver::SLOTsetVendor(const QString &vendorName)
{
    QSqlQuery a_query;
    QString str;
    str = "SELECT id FROM vendors WHERE name = '%1';";
    str = str.arg(vendorName);
    a_query.exec(str);
    QSqlRecord rec = a_query.record();
    if(!a_query.next()) {
        str = "INSERT INTO vendors(id, name) VALUES (NULL, '%1');";
        str = str.arg(vendorName);
        a_query.exec(str);
    }
    str = "SELECT id FROM vendors WHERE name = '%1';";
    str = str.arg(vendorName);
    a_query.exec(str);
    rec = a_query.record();
    a_query.next();
    vendorId = a_query.value(rec.indexOf("id")).toInt();
}
