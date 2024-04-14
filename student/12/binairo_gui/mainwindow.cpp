#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_gameboard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_gameboard()
{
    QWidget* central = new QWidget(this);
    QGridLayout* gameboard_grid = new QGridLayout(central);
    gameboard_grid->setSizeConstraint(QLayout::SetFixedSize);
    gameboard_grid->setHorizontalSpacing(0);
    gameboard_grid->setVerticalSpacing(0);

    for(int row = 0; row < SIZE; row++)
    {
        for(int column = 0; column < SIZE; column++)
        {
            QPushButton* gridspace = new QPushButton(" ", this);
            gridspace->setFixedWidth(50);
            gridspace->setFixedHeight(50);

            buttons_.push_back(gridspace);
            gameboard_grid->addWidget(gridspace, row, column);
            connect(gridspace, &QPushButton::clicked, this, &MainWindow::handle_button_clicks);
        }
    }
    setCentralWidget(central);
}

void MainWindow::handle_button_clicks()
{

}

