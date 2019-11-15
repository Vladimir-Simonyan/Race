//   Copyright © 2019 | Vladimir Simonyan | simonyan.vlad@gmail.com | GPL v3.0   //


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
