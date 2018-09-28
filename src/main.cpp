#include "mainwidget.h"
#include <QApplication>
#include "squarematrix.h"
#include <iostream>
#include <QtSql/QSqlTableModel>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setGeometry(50, 50, 1024, 600);
    w.setWindowTitle("Commis Voyageur");
    w.show();
    return a.exec();
}
