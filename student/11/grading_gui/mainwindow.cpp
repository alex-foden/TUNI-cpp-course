#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);
    ui->spinBoxE->setMaximum(5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxN_valueChanged(int N_points)
{
    N_points_ = N_points;
}

void MainWindow::on_spinBoxG_valueChanged(int G_points)
{
    G_points_ = G_points;
}

void MainWindow::on_spinBoxP_valueChanged(int P_points)
{
    P_points_ = P_points;
}

void MainWindow::on_spinBoxE_valueChanged(int exam_grade)
{
    exam_grade_ = exam_grade;
}

void MainWindow::on_calculatePushButton_clicked()
{
    W_grade_ = QString::number(score_from_weekly_exercises(N_points_, G_points_));
    P_grade_ = QString::number(score_from_projects(P_points_));
    total_grade_ = QString::number(calculate_total_grade(N_points_, G_points_,
                                                         P_points_, exam_grade_));

    ui->textBrowser->setText("W-Score: " + W_grade_ + "\n" +
                             "P-Score: " + P_grade_ + "\n" +
                             "Total grade: " + total_grade_);
}
