#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_fileLineEdit_editingFinished()
{
    file_name_ = ui->fileLineEdit->text().toStdString();
}


void MainWindow::on_keyLineEdit_editingFinished()
{
    key_ = ui->keyLineEdit->text().toStdString();
}


void MainWindow::on_findPushButton_clicked()
{
    std::ifstream file(file_name_);

    if(not file)
    {
        ui->textBrowser->setText("File not found");
        return;
    }

    if(key_ == "")
    {
        ui->textBrowser->setText("File found");
        return;
    }

    std::string line;
    std::string tmp;
    bool key_found = false;
    while(getline(file, line))
    {
        tmp = line;

        if(ui->matchCheckBox->isChecked() == false)
        {
            fix_string(tmp);
            fix_string(key_);
        }

        if(tmp.find(key_)!=std::string::npos)
        {
            key_found = true;
            break;
        }
    }

    if(key_found)
    {
        ui->textBrowser->setText("Word found");
    }
    else
    {
        ui->textBrowser->setText("Word not found");
    }
}


void MainWindow::on_closePushButton_clicked()
{
    this->close();
}

void MainWindow::fix_string(std::string &s)
{
    for(char& c : s)
    {
        c = tolower(c);
    }
}

