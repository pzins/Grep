#include "mainwindow.h"
#include <QApplication>
#include <interpretor.h>

//TODO add unit test to learn
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
