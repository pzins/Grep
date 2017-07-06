#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <QStringList>

class Command
{
public:
    virtual QString Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const = 0;
    QString DoExecute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const ;
};

class OtherCommand : public Command
{
public:
    virtual QString Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const;
};

class GrepCommand : public Command
{
public:
    virtual QString Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const;
    void PrepareArguments(QStringList& args) const;
};

#endif // COMMAND_H
