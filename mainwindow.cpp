#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wrongargumentsexception.h>
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
    ui->command_push_button->setText("Run");
    ui->result_search_push_button->setText("Search");
    ui->grep_case_check_box->setText("case sensitive");
    ui->result_case_checkbox->setText("case sensitive");
    ui->grep_label->setText("grep -iRn");
    ui->working_directory->setText("/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow"); // TODO get by working dir when run grep

    //connections
    //buttons and checkbox
    connect(ui->command_push_button, SIGNAL (clicked()), this, SLOT (HandleMainButton()));
    connect(ui->grep_case_check_box, SIGNAL(toggled(bool)), this, SLOT(HandleCheckbox()));
    connect(ui->result_search_push_button, SIGNAL (clicked()), this, SLOT(HandleSecondButton()));

    //enter in lineedit
    connect(ui->command_line_edit, SIGNAL(returnPressed()), ui->command_push_button, SIGNAL(clicked()));
    connect(ui->grep_arg_line_edit, SIGNAL(returnPressed()), ui->command_push_button, SIGNAL(clicked()));
    connect(ui->result_line_edit, SIGNAL(returnPressed()), ui->result_search_push_button, SIGNAL(clicked()));

    //TODO to see if it is possible to accelerate process because now too slow + need threshold because 1 letter for grep => problems
    connect(ui->grep_arg_line_edit, SIGNAL(textChanged(QString)), ui->command_push_button, SIGNAL(clicked()));

    //keyboard shortcuts
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), ui->grep_arg_line_edit, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), ui->grep_case_check_box, SLOT(toggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_K), ui->result_line_edit, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_J), ui->result_case_checkbox, SLOT(toggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), ui->working_directory, SLOT(setFocus()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//TODO test signal ontextchange to do dynamic research
void MainWindow::HandleMainButton() {
    ui->results_plain_text->document()->clear();
    QString res="";

    // if command line is used
    if(ui->command_line_edit->text().size() > 0) {
        QStringList str = ui->command_line_edit->text().split(" ");
        if(!str.isEmpty()) {
            QString cmd = str.front();
            str.pop_front();
            res = interpretor.Execute(cmd, str, ui->working_directory->text());
        }
    }
    // grep command line is used
    else {
        if(ui->grep_arg_line_edit->text().size() > 0) {
            QString cmd = "grep";
            QString arg;
            if(ui->grep_case_check_box->isChecked()) arg = "-Rn";
            else arg = "-iRn";
            QStringList args;
            args.push_back(arg);
            args.push_back(ui->grep_arg_line_edit->text());
            try {
                res = interpretor.Execute(cmd, args, ui->working_directory->text());
            } catch(WrongArgumentsException e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
    ui->results_plain_text->document()->setHtml(res);
}


// highlight word in line with color and bold and add end of line
void HighlightToHTML(QString& line, const QString& word, const QString& color, Qt::CaseSensitivity cs) {
    line.replace(word, "<b><font color=" + color + "> " + word + "</font></b>", cs);
    line + "<br/>";
}

void MainWindow::HandleSecondButton() {
    QString tmp = ui->results_plain_text->toPlainText();
    // split line by line into a list
    QStringList strs = tmp.split("\n");

    // set Case sensitivity
    Qt::CaseSensitivity cs = Qt::CaseInsensitive;
    if(ui->result_case_checkbox->isChecked())
        cs = Qt::CaseSensitive;

    QString res = "";
    for(int i = 0; i < strs.size(); ++i) {
        if(strs[i].contains(ui->result_line_edit->text(), cs))
        {
            HighlightToHTML(strs[i], ui->result_line_edit->text(), "blue", cs);
            res += strs[i] ;
        }
    }
    ui->results_plain_text->document()->setHtml(res);
}


void MainWindow::HandleCheckbox() {
    if(ui->grep_case_check_box->isChecked()) {
        ui->grep_label->setText("grep -Rn");
    } else {
        ui->grep_label->setText("grep -iRn");
    }
}
