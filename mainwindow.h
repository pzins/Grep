#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <worker.h>

#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QCheckBox>
#include <QThread>
#include <QEventLoop>
#include <params.h>

#include <iostream>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Params params_, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QThread* worker_thread;
    Worker* worker;
    Params params;

private slots:
    void HandleMainButton();
    void HandleSecondButton();
    void HandleCheckbox();

    void HandleWorkerResult(const QString &str);

signals:
    void operate(const QString& str);

};




#endif // MAINWINDOW_H
