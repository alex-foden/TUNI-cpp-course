#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <cmath>
#include <iostream>

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

double MainWindow::Calculate_BMI(double weight, double height)
{
    double bmi = weight / pow(height/100, 2);
    return bmi;
}


void MainWindow::on_weightLineEdit_textChanged(const QString &weight)
{
    weight_ = weight.toInt();
}


void MainWindow::on_heightLineEdit_textChanged(const QString &height)
{
    height_ = height.toInt();
}


void MainWindow::on_countButton_clicked()
{
    if(height_ == 0)
    {
        ui->resultLabel->setText("Cannot count");
        return;
    }

    double bmi = Calculate_BMI(weight_, height_);
    std::cout << weight_ << " " << weight_ << " " << bmi;
    QString bmi_text = QString::number(bmi, 'f', 4);

    ui->resultLabel->setText(bmi_text);

    if(bmi < 18.5)
    {
        ui->infoTextBrowser->setText("Underweight");
    }

    if(bmi >= 18.5 and bmi <= 25)
    {
        ui->infoTextBrowser->setText("Normal range");
    }

    if(bmi > 25)
    {
        ui->infoTextBrowser->setText("Overweight");
    }
}


void MainWindow::on_closeButton_clicked()
{
    this->close();
}

