#include "interpretor.h"
#include <iostream>
#include <QProcess>


Interpretor::Interpretor(const QString &command_, const QString &arguments_, const QString &working_directory_) :
    command(command_, arguments_, working_directory_) {

}

void Interpretor::Execute() {
    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(command.WorkingDir());
    myProcess->start(command.Name(), command.Arguments().split(" "));
    myProcess->waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString output(myProcess->readAllStandardOutput());
    std::cout << output.toStdString() << std::endl;

}
