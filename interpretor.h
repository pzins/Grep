#ifndef INTERPRETOR_H
#define INTERPRETOR_H
#include <command.h>
#include <QStringList>

class Interpretor
{
public:
    Interpretor();
    QString Execute(const QString& command_, const QStringList& arguments_, const QString& working_directory_);
private:
    Command command;
};

#endif // INTERPRETOR_H
