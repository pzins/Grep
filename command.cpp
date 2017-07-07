#include "command.h"
#include <iostream>
#include <QProcess>
#include <wrongargumentsexception.h>

void convertNewLineToHTML(QString& output)
{
    output = output.replace(QRegExp("\n"), "<br/>");
}

QString Command::DoExecute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const {
    QProcess *myProcess = new QProcess();
    myProcess->setWorkingDirectory(working_directory_);

    myProcess->start(command_, arguments_);
    myProcess->waitForFinished();
    QString output(myProcess->readAllStandardOutput());
    return output;

}

QString OtherCommand::Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const {
    QString output = DoExecute(command_, arguments_, working_directory_);
    convertNewLineToHTML(output);
    return output;
}

// Command argument should be -XXX -YYY -ZZZ ... "pattern"
// quotes are no required but all options with "-" should be in first positions
void GrepCommand::PrepareArguments(QStringList& args) const {
    if (!args.empty()) {
        int idx = 0;
        while(idx < args.size() && args.at(idx)[0] == '-') ++idx;
        if(idx >= args.size())
            throw WrongArgumentsException("no pattern found in arguments list");

        QString tmp = "";
        // convert args in List to String
        int sizeList = args.size();
        // loop backward + removeLast
        for(int i = sizeList-1; i >= idx; --i) {
            tmp = " " + args.at(i) + tmp;
            args.removeLast();
        }
        // remove quotes
        tmp.replace(QRegExp("\""), "");
        tmp.replace(QRegExp("\'"), "");
        //remove the first space added
        tmp.remove(0,1);
        // push back in args (just after the "-" options if any)
        args.push_back(tmp);
    }
}

QString GrepCommand::Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const {
    // prepare argument list
    PrepareArguments(arguments_);

    // execute
    QString output = DoExecute(command_, arguments_, working_directory_);

    // highlight the pattern and convert \n to html <br/>
    QString tmp = arguments_.back();
    output = output.replace(tmp, "<b><font color=red> " + tmp + "</font></b>", Qt::CaseInsensitive); //case sensitivity has no effect here
    convertNewLineToHTML(output);
    return output;
}
