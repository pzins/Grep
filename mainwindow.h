#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <interpretor.h>
#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QThread>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Interpretor interpretor;

private slots:
    void HandleMainButton();
    void HandleSecondButton();
    void HandleCheckbox();
};

class Runner : public QThread
{
public:
    Runner(Command* cmd_, QString& command_, QStringList& args_, QString working_dir_, QPlainTextEdit* res_) : cmd(cmd_), command(command_), args(args_), working_dir(working_dir_), res(res_) {}
private:
    Interpretor interpretor;
    QString command;
    QStringList args;
    QString working_dir;
    Command* cmd;
    QPlainTextEdit* res;
    void run() {
        res->document()->setHtml(interpretor.Execute(cmd, command, args, working_dir));
    }
};

#endif // MAINWINDOW_H
