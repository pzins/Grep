#include "mainwindow.h"
#include <QApplication>
#include <interpretor.h>
#include <gtest/gtest.h>


//TODO separate test from app execution + add more tests
TEST(ol, lyon) {

    Command* cmd = new GrepCommand();
    Interpretor* interpretor = new Interpretor("blue");
    QStringList args;
    args.push_back("-iRn");
    args.push_back("azertyuiop");
    QString res = interpretor->Execute(cmd, "grep", args, "/home/pierre/Desktop");
    std::cout << res.toStdString() << std::endl;
    ASSERT_TRUE((res.compare("") == 0));
}

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
