#include "mainwindow.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("172.28.100.3");
    db.setDatabaseName("mviougea_contact");
    db.setUserName("mviougea");
    db.setPassword("elini01");

    bool ok=db.open();
    qDebug()<<ok;

    MainWindow w;
    w.show();
    return a.exec();
}
