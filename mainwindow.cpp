#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <iostream>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //widgets configuration
    ui->grep_case_check_box->setText("case sensitive");
    ui->result_case_checkbox->setText("case sensitive");
    ui->grep_label->setText("grep -iRn");

    //connections
    //buttons and checkbox
    connect(ui->command_push_button, SIGNAL (clicked()), this, SLOT (HandleMainButton()));
    connect(ui->grep_case_check_box, SIGNAL(toggled(bool)), this, SLOT(HandleCheckbox()));
    connect(ui->result_search_push_button, SIGNAL (clicked()), this, SLOT(HandleSecondButton()));

    //enter in lineedit
    connect(ui->command_line_edit, SIGNAL(returnPressed()), ui->command_push_button, SIGNAL(clicked()));
    connect(ui->grep_arg_line_edit, SIGNAL(returnPressed()), ui->command_push_button, SIGNAL(clicked()));
    connect(ui->result_line_edit, SIGNAL(returnPressed()), ui->result_search_push_button, SIGNAL(clicked()));

    //keyboard shortcuts
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), ui->grep_arg_line_edit, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), ui->grep_case_check_box, SLOT(toggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_K), ui->result_line_edit, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_J), ui->result_case_checkbox, SLOT(toggle()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO test signal ontextchange to do dynamic research
void MainWindow::HandleMainButton() {
    ui->results_plain_text->document()->clear();
    QString res;
    if(ui->command_line_edit->text().size() > 0) {

        QStringList str = ui->command_line_edit->text().split(" ");

        QString cmd = "";
        if(!str.isEmpty()){
            cmd = str.front();
        }
        str.pop_front();
        res = interpretor.Execute(cmd, str, "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
    } else {
        QString cmd = "grep";
        QString arg;
        if(ui->grep_case_check_box->isChecked()) arg = "-Rn";
        else arg = "-iRn";
        QStringList args;
        args.push_back(arg);
        args.push_back(ui->grep_arg_line_edit->text());
        std::cout << cmd.toStdString() << std::endl;
        std::cout << args.at(0).toStdString() << std::endl;
        res = interpretor.Execute(cmd, args, "/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow");
    }
    ui->results_plain_text->document()->setHtml(res);

}
//TODO function qui convert to HTML \n <=> <br/> + add color to matches
void MainWindow::HandleSecondButton() {
    QString tmp = ui->results_plain_text->toPlainText();
    std::cout << tmp.toStdString() << std::endl;
    QStringList strs = tmp.split("\n");

    QString res = "";
    Qt::CaseSensitivity ci = Qt::CaseInsensitive;
    if(ui->result_case_checkbox->isChecked())
        ci = Qt::CaseSensitive;
    for(int i = 0; i < strs.size(); ++i) {
        if(strs[i].contains(ui->result_line_edit->text(), ci))
        {
            strs[i].replace(ui->result_line_edit->text(), "<b><font color=blue> " + ui->result_line_edit->text() + "</font></b>", ci);
            res += strs[i] + "<br/>";
        }
    }
    ui->results_plain_text->document()->clear();
    ui->results_plain_text->document()->setHtml(res);
}


void MainWindow::HandleCheckbox() {
    if(ui->grep_case_check_box->isChecked()) {
        ui->grep_label->setText("grep -Rn");
    } else {
        ui->grep_label->setText("grep -iRn");
    }
}
