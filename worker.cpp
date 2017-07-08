#include "worker.h"
#include <wrongargumentsexception.h>
#include <iostream>


Worker::Worker(Params params_, QObject *parent) : params(params_), interpretor(new Interpretor(params_.command_color)) {

}

void Worker::PrepareWorker(Command* cmd_, QString& command_, QStringList& args_, QString working_dir_) {
    cmd = cmd_;
    command = command_;
    args = args_;
    working_dir = working_dir_;
}


void Worker::doWork(const QString &parameter) {
    QString res = "";
    try {
        res = interpretor->Execute(cmd, command, args, working_dir);
    } catch(WrongArgumentsException e) {
        std::cout << e.what() << std::endl;
    }
    emit resultReady(res);
}
