#ifndef COMMAND_H
#define COMMAND_H
#include <QString>
#include <QStringList>

class Command
{
public:
    Command();
    Command(const QString& name_, const QStringList& args_, const QString& working_dir_);
    const QString& Name() const;
    const QString& WorkingDir() const;
    const QStringList& Arguments() const;

private:
    QString name;
    QStringList args;
    QString working_dir;
};

#endif // COMMAND_H
