#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <interpretor.h>
#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QThread>
#include <QEventLoop>

#include <iostream>

namespace Ui {
class MainWindow;
}

class Worker;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Interpretor interpretor;

    QThread* worker_thread;
    Worker* worker;

private slots:
    void HandleMainButton();
    void HandleSecondButton();
    void HandleCheckbox();

    void HandleComandResult(const QString& str);
    void HandleResult(const QString& str);

signals:
    void operate(const QString& str);

};

//TODO clean, to delete
class Runner : public QThread
{
    Q_OBJECT
public:
    Runner(Command* cmd_, QString& command_, QStringList& args_, QString working_dir_) : cmd(cmd_), command(command_), args(args_), working_dir(working_dir_) {}
private:
    Interpretor interpretor;
    QString command;
    QStringList args;
    QString working_dir;
    Command* cmd;
    void run() override {

        QEventLoop loop;
        connect(this,  SIGNAL(query()), &loop, SLOT(quit()) );
        std::cout << "before exec" << std::endl;
        loop.exec();
        std::cout << "after exec" << std::endl;
        QString res = interpretor.Execute(cmd, command, args, working_dir);
        emit resultReady(res);
    }

signals:
    void resultReady(const QString& res);
//    void query();
};


class Worker : public QObject
{
    Q_OBJECT

public:
    Worker() : is_running(false) {}
    void PrepareWorker(Command* cmd_, QString& command_, QStringList& args_, QString working_dir_) {
        cmd = cmd_;
        command = command_;
        args = args_;
        working_dir = working_dir_;
    }

    bool isRunning() {return is_running;}
private:
    Interpretor interpretor;
    QString command;
    QStringList args;
    QString working_dir;
    Command* cmd;
    bool is_running;

public slots:
    void doWork(const QString &parameter) {
        is_running = true;
        std::cout << "dowork" << std::endl;
        QString res = interpretor.Execute(cmd, command, args, working_dir);
        is_running = false;
        emit resultReady(res);
    }

signals:
    void resultReady(const QString &result);
};

#endif // MAINWINDOW_H
