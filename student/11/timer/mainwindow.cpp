#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setInterval(1000);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::on_startButton_clicked);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::on_stopButton_clicked);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::on_resetButton_clicked);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::on_closeButton_clicked);

    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);

    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);

    QPalette* lcdpalette1 = new QPalette();
    QPalette* lcdpalette2 = new QPalette();

    lcdpalette1->setColor(QPalette::Window, QColor(50, 100, 170));
    lcdpalette2->setColor(QPalette::Window, QColor(50, 170, 80));

    ui->lcdNumberMin->setPalette(*lcdpalette1);
    ui->lcdNumberSec->setPalette(*lcdpalette2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start();
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    seconds_ = 0;
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::on_closeButton_clicked()
{
    this->close();
}

void MainWindow::on_timeout()
{
    ui->lcdNumberMin->display(seconds_/60);
    ui->lcdNumberSec->display(seconds_%60);

    seconds_++;
}

