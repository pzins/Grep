#include "mainwindow.h"
#include <QApplication>
#include <interpretor.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Interpretor in("ls", "-a", "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
//    Interpretor in("grep", "-iRn RunAsync()", "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
//    in.Execute();
    return a.exec();
}
