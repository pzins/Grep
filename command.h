#ifndef COMMAND_H
#define COMMAND_H
#include <QString>

class Command
{
public:
    Command(const QString& name_, const QString& args_, const QString& working_dir_);
    const QString& Name() const;
    const QString& WorkingDir() const;
    const QString& Arguments() const;

private:
    QString name;
    QString args;
    QString working_dir;
};

#endif // COMMAND_H
