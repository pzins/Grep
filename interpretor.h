#ifndef INTERPRETOR_H
#define INTERPRETOR_H
#include <command.h>

class Interpretor
{
public:
    Interpretor(const QString& command_, const QString& arguments_, const QString& working_directory_);
    void Execute();
private:
    Command command;
};

#endif // INTERPRETOR_H
