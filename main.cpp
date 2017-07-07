#include "mainwindow.h"
#include <QApplication>
#include <interpretor.h>
#include <gtest/gtest.h>


TEST(ol, lyon) {
    int i = 0;
    ASSERT_GE(i, 0);
}

//TODO add unit test to learn
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    testing::InitGoogleTest(&argc, argv);

    MainWindow w;
    w.show();
    RUN_ALL_TESTS();
    return a.exec();
}
