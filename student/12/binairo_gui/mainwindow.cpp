#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(this->windowState() ^ Qt::WindowMaximized);

    init_gameboard();
    init_symbol_button();
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
            gridspace->setFixedWidth(BOARD_SIZE / SIZE);
            gridspace->setFixedHeight(BOARD_SIZE / SIZE);

            buttons_.push_back(gridspace);
            gameboard_grid->addWidget(gridspace, row, column);
            connect(gridspace, &QPushButton::clicked,
                    this, &MainWindow::handle_button_clicks);
        }
    }
    setCentralWidget(central);
}

void MainWindow::init_symbol_button()
{
    symbol_ = "0";
    symbol_button_ = new QPushButton("0", this);
    symbol_button_->setGeometry(BOARD_SIZE / 2 - 40, BOARD_SIZE + 10, 100, 100);
    connect(symbol_button_, &QPushButton::clicked,
            this, &MainWindow::handle_symbol_button_clicks);
}

void MainWindow::handle_button_clicks()
{
    for(QPushButton* gridspace: buttons_)
    {
        if(gridspace == sender())
        {
            gridspace->setText(symbol_);
            return;
        }
    }
}

void MainWindow::handle_symbol_button_clicks()
{
    if(symbol_ == "0")
    {
        symbol_button_->setText("1");
        symbol_ = "1";
        return;
    }

    if(symbol_ == "1")
    {
        symbol_button_->setText("0");
        symbol_ = "0";
        return;
    }
}
