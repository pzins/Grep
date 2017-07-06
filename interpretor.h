#ifndef INTERPRETOR_H
#define INTERPRETOR_H
#include <command.h>
#include <QStringList>

class Interpretor
{
public:
    Interpretor();
    QString Execute(Command* cmd, const QString& command_, QStringList &arguments_, const QString& working_directory_);
};

#endif // INTERPRETOR_H
