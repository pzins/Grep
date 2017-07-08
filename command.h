#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <QStringList>

class Command
{
public:
    virtual QString Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const = 0;
    virtual bool ShouldHighlight() const =0;
    QString DoExecute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const ;
};

class OtherCommand : public Command
{
public:
    virtual QString Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const;
    virtual bool ShouldHighlight() const { return false;}
};

class GrepCommand : public Command
{
//private:
//    Params params;
public:
//    GrepCommand(Params params_);
    virtual QString Execute(const QString &command_, QStringList &arguments_, const QString &working_directory_) const;
    virtual bool ShouldHighlight() const { return true;}
    void PrepareArguments(QStringList& args) const;
};

#endif // COMMAND_H
