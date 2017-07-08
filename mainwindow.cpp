#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include <wrongargumentsexception.h>
#include <QLineEdit>
#include <QPushButton>
#include <QShortcut>
#include <QDir>
#include <iostream>

MainWindow::MainWindow(Params params_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir dir;
    ui->setupUi(this);

    params = params_;
    //widgets configuration
    ui->command_push_button->setText("Run");
    ui->result_search_push_button->setText("Search");
    ui->grep_case_check_box->setText("case sensitive");
    ui->result_case_checkbox->setText("case sensitive");
    ui->grep_label->setText("grep -iRn");

    ui->working_directory->setText(dir.absolutePath());
    ui->working_directory->setText("/home/pierre/dev/DORSAL/tensorflow_compil/tensorflow"); // to debug

    // hide pushbuttons
    ui->command_push_button->hide();
    ui->result_search_push_button->hide();

    //connections
    //buttons and checkbox
    connect(ui->command_push_button, SIGNAL (clicked()), this, SLOT (HandleMainButton()));
    connect(ui->grep_case_check_box, SIGNAL(toggled(bool)), this, SLOT(HandleCheckbox()));
    connect(ui->result_search_push_button, SIGNAL (clicked()), this, SLOT(HandleSecondButton()));

    //enter in lineedit
    connect(ui->command_line_edit, SIGNAL(returnPressed()), ui->command_push_button, SIGNAL(clicked()));
    connect(ui->grep_arg_line_edit, SIGNAL(returnPressed()), ui->command_push_button, SIGNAL(clicked()));
    connect(ui->result_line_edit, SIGNAL(returnPressed()), ui->result_search_push_button, SIGNAL(clicked()));

    // dynamic grep search
    connect(ui->grep_arg_line_edit, SIGNAL(textChanged(QString)), ui->command_push_button, SIGNAL(clicked()));

    //keyboard shortcuts
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), ui->grep_arg_line_edit, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_I), ui->grep_case_check_box, SLOT(toggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_K), ui->result_line_edit, SLOT(setFocus()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_J), ui->result_case_checkbox, SLOT(toggle()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_W), ui->working_directory, SLOT(setFocus()));

    // configuration of the thread and worker
    worker_thread = new QThread();
    worker = new Worker(params);
    worker->moveToThread(worker_thread);
    // connections
    connect(worker_thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &MainWindow::operate, worker, &Worker::doWork);
    connect(worker, &Worker::resultReady, this, &MainWindow::HandleWorkerResult);
    // start the worker thread
    worker_thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HandleMainButton() {

    Command* cmd = nullptr;
    QString command;
    QStringList arguments;

    // if command line is used
    if(ui->command_line_edit->text().size() > 0) {
        arguments = ui->command_line_edit->text().split(" ");
        if(!arguments.isEmpty()) {
            command = arguments.front();
            arguments.pop_front();
            cmd = new OtherCommand();
        }
    }
    // grep command line is used
    else {
        if(ui->grep_arg_line_edit->text().size() > 0) {
            command = "grep";
            QString arg;
            if(ui->grep_case_check_box->isChecked()) arg = "-Rn";
            else arg = "-iRn";
            arguments.push_back(arg);
            arguments.push_back(ui->grep_arg_line_edit->text());
            cmd = new GrepCommand();
        }
    }
    // work well if we set a min ize limit otherwise too many matches
    if(cmd && (ui->command_line_edit->text().size() > 0 || ui->grep_arg_line_edit->text().size() > params.min_nb_letter_dynamic_grep)) {
        worker->PrepareWorker(cmd, command, arguments, ui->working_directory->text());
        operate("");
    }
}


void MainWindow::HandleWorkerResult(const QString &str) {
    ui->results_plain_text->document()->clear();
    ui->results_plain_text->document()->setHtml(str);
}


// highlight word in line with color and bold and add end of line
void MainWindow::SearchHighlightToHTML(QString& line, const QString& word, const QString& color, Qt::CaseSensitivity cs) {
    line.replace(word, "<b><font color=" + color + "> " + word + "</font></b>", cs);
    line += "<br/>";
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
            SearchHighlightToHTML(strs[i], ui->result_line_edit->text(), params.highlight_color, cs);
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
