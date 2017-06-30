#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <interpretor.h>
#include <QMainWindow>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QLabel>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

//TODO remove members not needed
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Interpretor interpretor;
    QLineEdit* command_line_edit;
    QPlainTextEdit* results;
    QLabel* label;
    QCheckBox* checkbox;

private slots:
    void handleButton();
    void handleButton2();
    void handleCheckbox();
};

#endif // MAINWINDOW_H
