#include "interpretor.h"
#include <iostream>
#include <QProcess>

Interpretor::Interpretor() {

}

//TODO check size extreme cases, wrong entry
void assembleAndRemoveBrackets(QStringList& args) {
    int idx = 0;
    while(idx < args.size() && args.at(idx)[0] == '-') ++idx;

    QString tmp = "";
    int sizeList = args.size();
    for(int i = sizeList-1; i >= idx; --i) {
        tmp = " " + args.at(i) + tmp;
        args.removeLast();
    }

    tmp.replace(QRegExp("\""), "");
    tmp.replace(QRegExp("\'"), "");
    tmp.remove(0,1);
    args.push_back(tmp);
}

//TODO change command = Command(...) pas brsoin de member je pense
QString Interpretor::Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) {
    command = Command(command_, arguments_, working_directory_);
    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(command.WorkingDir());

    assembleAndRemoveBrackets(arguments_);
    std::cout << arguments_[1].toStdString() << std::endl;
    myProcess->start(command.Name(), arguments_);
//    myProcess->start("grep", l);//command.Arguments());


    myProcess->waitForFinished(); // sets current thread to sleep and waits for pingProcess end
    QString output(myProcess->readAllStandardOutput());
    QString tmp = arguments_.back();
    output = output.replace(tmp, "<b><font color=red> " + tmp + "</font></b>", Qt::CaseInsensitive);
    output = output.replace(QRegExp("\n"), "<br/>");
    return output;
}
