    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    command_line_edit = ui->lineEdit;
    results = ui->plainTextEdit;
    label = ui->label;
    checkbox = ui->checkBox;
    checkbox->setText("case sensitive");
    ui->checkBox_2->setText("case sensitive");
    label->setText("grep -iRn");
    connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (handleButton()));
    connect(ui->pushButton_2, SIGNAL (clicked()),this, SLOT (handleButton2()));
    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->pushButton,SIGNAL(clicked()));
    connect(ui->lineEdit_2, SIGNAL(returnPressed()),ui->pushButton,SIGNAL(clicked()));
    connect(ui->lineEdit_3, SIGNAL(returnPressed()),ui->pushButton_2,SIGNAL(clicked()));
    connect(ui->checkBox, SIGNAL(toggled(bool)), this, SLOT(handleCheckbox()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO test signal ontextchange to do dynamic research
void MainWindow::handleButton() {
    results->document()->clear();
    QString res;
    if(command_line_edit->text().size() > 0) {

        QStringList str = command_line_edit->text().split(" ");

        QString cmd = "";
        if(!str.isEmpty()){
            cmd = str.front();
        }
        str.pop_front();
        res = interpretor.Execute(cmd, str, "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
    } else {
        QString cmd = "grep";
        QString arg;
        if(ui->checkBox->isChecked()) arg = "-Rn";
        else arg = "-iRn";
        QStringList args;
        args.push_back(arg);
        args.push_back(ui->lineEdit_2->text());
        std::cout << cmd.toStdString() << std::endl;
        std::cout << args.at(0).toStdString() << std::endl;
        res = interpretor.Execute(cmd, args, "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
    }
    results->document()->setHtml(res);

}
//TODO function qui convert to HTML \n <=> <br/> + add color to matches
void MainWindow::handleButton2() {
    QString tmp = results->toPlainText();
    std::cout << tmp.toStdString() << std::endl;
    QStringList strs = tmp.split("\n");

    QString res = "";
    Qt::CaseSensitivity ci = Qt::CaseInsensitive;
    if(ui->checkBox_2->isChecked())
        ci = Qt::CaseSensitive;
    for(int i = 0; i < strs.size(); ++i) {
        if(strs[i].contains(ui->lineEdit_3->text(), ci))
        {
            strs[i].replace(ui->lineEdit_3->text(), "<b><font color=blue> " + ui->lineEdit_3->text() + "</font></b>", ci);
            res += strs[i] + "<br/>";
        }
    }
    results->document()->clear();
    results->document()->setHtml(res);
}
void MainWindow::handleCheckbox() {
    if(checkbox->isChecked()) {
        label->setText("grep -Rn");
    } else {
        label->setText("grep -iRn");
    }
}
