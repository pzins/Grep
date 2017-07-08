#include "mainwindow.h"
#include <QApplication>
#include <interpretor.h>
#include <gtest/gtest.h>


//TODO separate test from app execution + add more tests


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    testing::InitGoogleTest(&argc, argv);

    Params p;
    MainWindow w(p);
    w.show();
    RUN_ALL_TESTS();
    return a.exec();
}
