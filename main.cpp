#include "widget.h"
#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtDebug>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    //if windows
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={MySQL ODBC8.2.0 ANSI Driver};DATABASE=foot;"); */

    db.setDatabaseName("foot");
    db.setUserName("sofiane");
    db.setPassword("Crif2024sn");
    if(db.open())
    {
        qDebug()<<"Vous etes maintenant connecte a "<<db.userName();
        QSqlQuery query;
        query.exec("select * FROM `footeux`");
        while (query.next())
        {
            QString id = query.value(3).toString();
            QString name = query.value(0).toString();
            QString prenom = query.value(5).toString();
            QString club = query.value(2).toString();
            QString note = query.value(4).toString();
            QString number = query.value(1).toString();
            qDebug()<<"-----------------------------------------------";
            qDebug()<<prenom<<name<<id<<club<<note<<number<<"\t";
        }
        qDebug()<<"-----------------------------------------------";
        qDebug()<<"requete ok!;) ";
        //db.close();
    }
    else
    {
        qDebug()<<"La connexion a echouee, desole "<<db.lastError().text();
    }

    QSqlTableModel table;
    table.clear();
    table.setTable("footeux");
    table.select();

    QTableView view;
    view.setModel(&table);
    QPushButton afficher("afficher");

    //QObject::connect(&afficher,QPushButton::clicked,[&](){
    view.setColumnHidden(0,false);
    view.setColumnHidden(1,false);
    view.setColumnHidden(2,false);
    view.setColumnHidden(3,false);
    view.setColumnHidden(4,false);
    view.setColumnHidden(5,false);
      //});
    table.setHeaderData(0,Qt::Horizontal,"name");
    table.setHeaderData(3,Qt::Horizontal,"id");
    table.setHeaderData(5,Qt::Horizontal,"prenom");
    table.setHeaderData(2,Qt::Horizontal,"club");
    table.setHeaderData(4,Qt::Horizontal,"note");
    table.setHeaderData(1,Qt::Horizontal,"number");



    QHBoxLayout layout;
    layout.addWidget(&view);
    layout.addWidget(&afficher);
    w.setLayout(&layout);
    /*QObject::connect(&afficher,&QPushButton::clicked,[&](){
        table.select();
    });*/
    w.show();
    return a.exec();
}

