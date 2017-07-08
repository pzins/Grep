#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <interpretor.h>
#include <params.h>

class Worker : public QObject
{
    Q_OBJECT

public:

    explicit Worker(Params params_, QObject *parent = 0);
    void PrepareWorker(Command *cmd_, QString &command_, QStringList &args_, QString working_dir_);

private:
    Interpretor* interpretor;
    QString command;
    QStringList args;
    QString working_dir;
    Command* cmd;
    Params params;

public slots:
    void doWork(const QString &parameter);

signals:
    void resultReady(const QString &result);
};

#endif // WORKER_H
