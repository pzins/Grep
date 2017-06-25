#include "command.h"

Command::Command() : name(""), args(""), working_dir("") {

}

Command::Command(const QString &name_, const QStringList &args_, const QString &working_dir_) :
    name(name_), args(args_), working_dir(working_dir_)
{

}


const QString& Command::Name() const {
    return name;
}


const QStringList &Command::Arguments() const {
    return args;
}


const QString& Command::WorkingDir() const {
    return working_dir;
}
