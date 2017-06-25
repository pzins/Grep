#include "interpretor.h"
#include <iostream>
#include <QProcess>

Interpretor::Interpretor() {

}

QString Interpretor::Execute(const QString &command_, const QStringList &arguments_, const QString &working_directory_) {
    command = Command(command_, arguments_, working_directory_);
    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(command.WorkingDir());


    /*
    QString a("-iRn");
    QString b("\"class Device\"");
    QStringList l;
    l.push_back(a);
    l.push_back(b);
    for(auto i : l)
        std::cout << i.toStdString();
    std::cout << std::endl;

    for(auto i : command.Arguments())
        std::cout << i.toStdString();
    std::cout << std::endl;
    std::cout << l.size() << std::endl;
    std::cout << command.Arguments().size() << std::endl;
    std::cout << (l == command.Arguments()) << std::endl;
*/


    myProcess->start(command.Name(), command.Arguments());
//    myProcess->start(command.Name(), l);//command.Arguments());


    myProcess->waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString output(myProcess->readAllStandardOutput());
    std::cout << "..." << std::endl;
    std::cout << output.toStdString() << std::endl;
    return output;

}
