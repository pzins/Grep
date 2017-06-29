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
    connect(ui->pushButton, SIGNAL (clicked()),this, SLOT (handleButton()));
    connect(ui->lineEdit, SIGNAL(returnPressed()),ui->pushButton,SIGNAL(clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton() {
    results->document()->clear();
    QStringList str = command_line_edit->text().split(" ");

    for(auto i : str) std::cout << "- " << i.toStdString() <<std::endl;
    QString cmd = "";
    if(!str.isEmpty()){
        cmd = str.front();
    }
    str.pop_front();
    QString res = interpretor.Execute(cmd, str, "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
    results->document()->setHtml(res);

}
