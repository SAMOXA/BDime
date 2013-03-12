#include "dbdriver.h"

dbDriver::dbDriver(QObject *parent) :
    QObject(parent)
{
    dbase = QSqlDatabase::addDatabase("QSQLITE");
    status = false;
    numberOfInserts = 0;
    multipleQuery = "INSERT INTO main( art, desc, price, vendor_id) "
                        "SELECT '%1', '%2', '%3', '%4' ";
}

void dbDriver::init(const QString &path)
{
    if(! QFile::exists(path)){
        emit SIGNALdbMessage(QString::fromUtf8("Была создана новая база данных"));
    }else{
        emit SIGNALdbMessage(QString::fromUtf8("База данных была перезаписана"));
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
        emit SIGNALdbError(QString::fromUtf8("Ощибка при открытии базы данных ") + dbase.lastError().text());
        globalError = true;
    }
    QSqlQuery a_query;
    QString str;
    bool flag;
    str = "CREATE TABLE IF NOT EXISTS vendors (id INTEGER PRIMARY KEY NOT NULL, name TEXT);";
    a_query.exec(str);
    flag = a_query.exec(str);
    if(!flag){
        emit SIGNALdbError(QString::fromUtf8("Ощибка при создании таблицы vendors ") + a_query.lastError().text());
        globalError = true;
    }
    if(!a_query.exec("PRAGMA foreign_keys = ON;")){
        emit SIGNALdbError(QString::fromUtf8("Ощибка при установке связных ключей ") + a_query.lastError().text());
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
        emit SIGNALdbError(QString::fromUtf8("Ощибка при создании таблицы main ") + a_query.lastError().text());
        globalError = true;
    }
    str = "CREATE INDEX main_id_index on main(id)";
    if(!a_query.exec(str)){
        emit SIGNALdbError(QString::fromUtf8("Ощибка при создании индекса ") + a_query.lastError().text());
        globalError = true;
    }
    dbModel = new QSqlRelationalTableModel;
    dbModel->setTable("main");
    dbModel->setEditStrategy(QSqlTableModel::OnRowChange);
    dbModel->setRelation(4, QSqlRelation("vendors", "id", "name"));
    dbModel->select();
    if(globalError){
        emit SIGNALdbError(QString::fromUtf8("Ощибка базы данных"));
        status = false;
    }else{
        status = true;
    }
}

void dbDriver::SLOTaddItem(const QString &art, const QString &desc, const float price)
{
    QString str;
    str = QString::fromUtf8("Добавлен артикль %1 - %2");
    str = str.arg(art).arg(desc);
    emit SIGNALdbMessage(str);
    if(numberOfInserts < 400){
        if(numberOfInserts == 0){
            multipleQuery = multipleQuery.arg(art).arg(desc).arg(price).arg(vendorId);
            numberOfInserts++;
        }else{
            str = "UNION ALL SELECT '%1', '%2', '%3', '%4' ";
            str = str.arg(art).arg(desc).arg(price).arg(vendorId);
            multipleQuery += str;
            numberOfInserts++;
        }
    }else{
        QSqlQuery a_query;
        str = "UNION ALL SELECT '%1', '%2', '%3', '%4'";
        str = str.arg(art).arg(desc).arg(price).arg(vendorId);
        multipleQuery += str;
        if(!a_query.exec(multipleQuery)){
            emit SIGNALdbError(QString::fromUtf8("Ощибка при добавлении данных ") + a_query.lastError().text());
        }
        multipleQuery = "INSERT INTO main( art, desc, price, vendor_id) "
                            "SELECT '%1', '%2', '%3', '%4' ";
        numberOfInserts = 0;
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

void dbDriver::SLOTgetItems(const QStringList list)
{
    QSqlQuery a_query;
    QString str;
    QStringList::const_iterator iter = list.begin();
    QSqlRecord rec;
    bool flag;
    for(;iter!=list.end();iter++){
        str = "SELECT * FROM main WHERE art = '%1';";
        str = str.arg(*iter);
        a_query.exec(str);
        rec = a_query.record();
        flag = false;
        while(a_query.next()){
            flag = true;
            emit SIGNALtoModel(*iter, a_query.value(rec.indexOf("desc")).toString(), a_query.value(rec.indexOf("price")).toFloat(), a_query.value(rec.indexOf("vendor_id")).toInt());
        }
        if(!flag){
            emit SIGNALtoModel(*iter, QString(""), 0, 0);
        }
    }
}

void dbDriver::SLOTgetVendors()
{
    QSqlQuery a_query;
    QString str;
    str = "SELECT * FROM vendors";
    a_query.exec(str);
    QSqlRecord rec;
    rec = a_query.record();
    while(a_query.next()){
        emit SIGNALvendor(a_query.value(rec.indexOf("id")).toInt(), a_query.value(rec.indexOf("name")).toString());
    }
}

void dbDriver::SLOTfinalAdding()
{
    QSqlQuery a_query;
    if(!a_query.exec(multipleQuery)){
        emit SIGNALdbError(QString::fromUtf8("Ощибка при добавлении данных ") + a_query.lastError().text());
    }
    multipleQuery = "INSERT INTO main( art, desc, price, vendor_id) "
                        "SELECT '%1', '%2', '%3', '%4' ";
    numberOfInserts = 0;
}
