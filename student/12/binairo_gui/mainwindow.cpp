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
    init_gameboard_setup_menu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_gameboard()
{
    QWidget* central = new QWidget(this);
    gameboard_grid_ = new QGridLayout(central);
    gameboard_grid_->setSizeConstraint(QLayout::SetFixedSize);
    gameboard_grid_->setHorizontalSpacing(0);
    gameboard_grid_->setVerticalSpacing(0);

    for(int row = 0; row < SIZE; row++)
    {
        for(int column = 0; column < SIZE; column++)
        {
            QPushButton* gridspace = new QPushButton(" ", this);
            gridspace->setEnabled(false);
            gridspace->setFixedWidth(BOARD_SIZE / SIZE);
            gridspace->setFixedHeight(BOARD_SIZE / SIZE);

            gridspaces_.push_back(gridspace);
            gameboard_grid_->addWidget(gridspace, row, column);
            connect(gridspace, &QPushButton::clicked,
                    this, &MainWindow::handle_gameboard_clicks);
        }
    }
    setCentralWidget(central);
}

void MainWindow::init_symbol_button()
{
    symbol_ = "0";
    symbol_button_ = new QPushButton(symbol_, this);
    symbol_button_->setGeometry(BOARD_SIZE / 2 - 50 + 10, BOARD_SIZE + 10, 100, 100);
    connect(symbol_button_, &QPushButton::clicked,
            this, &MainWindow::handle_symbol_button_clicks);
}

void MainWindow::init_gameboard_setup_menu()
{
    QLabel* board_setup_label = new QLabel("SETUP GAMEBOARD TO START GAME", this);
    board_setup_label->setGeometry(BOARD_SIZE + 40, 10 + 20, 300, 50);
    board_setup_label->setAlignment(Qt::AlignHCenter);

    QLabel* randomize_label = new QLabel("Randomize", this);
    randomize_label->setGeometry(BOARD_SIZE + 40 + 70 + 16/2 - 100/2, 10 + 55, 100, 40);
    randomize_label->setAlignment(Qt::AlignHCenter);
    randomize_button_ = new QRadioButton(this);
    randomize_button_->setGeometry(BOARD_SIZE + 40 + 70, 10 + 80, 16, 16);
    connect(randomize_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_board_setup_tooltip);

    QLabel* manual_input_label = new QLabel("Manual input", this);
    manual_input_label->setGeometry(BOARD_SIZE + 40 + 300 - 70 - 16/2 - 100/2, 10 + 55, 100, 40);
    manual_input_label->setAlignment(Qt::AlignHCenter);
    manual_input_button_ = new QRadioButton(this);
    manual_input_button_->setGeometry(BOARD_SIZE + 40 + 300 - 70 - 16, 10 + 80, 16, 16);
    connect(manual_input_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_board_setup_tooltip);

    seed_input_field_ = new QLineEdit(this);
    seed_input_field_->setGeometry(BOARD_SIZE + 40, 10 + 105, 230, 20);
    seed_input_field_->setEnabled(false);

    setup_board_button_ = new QPushButton("Generate", this);
    setup_board_button_->setGeometry(BOARD_SIZE + 40 + 230, 10 + 105 - 5, 70, 30);
    setup_board_button_->setEnabled(false);
    connect(setup_board_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_setup_board_button_clicks);

    board_setup_status_ = new QTextBrowser(this);
    board_setup_status_->setGeometry(BOARD_SIZE + 40, 10 + 135, 300, 50);
}

void MainWindow::handle_gameboard_clicks()
{
    int grid_number = 0;
    for(QPushButton* gridspace: gridspaces_)
    {
        int x = grid_number % SIZE;
        int y = grid_number / SIZE;
        if(gridspace == sender())
        {
            update_board(gridspace, x, y);
            return;
        }
        grid_number++;
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

void MainWindow::handle_board_setup_tooltip()
{
    setup_board_button_->setEnabled(true);
    seed_input_field_->setEnabled(true);
    if(randomize_button_->isChecked())
    {
        seed_input_field_->clear();
        seed_input_field_->setPlaceholderText("Input seed");
        return;
    }
    if(manual_input_button_->isChecked())
    {
        seed_input_field_->clear();
        seed_input_field_->setPlaceholderText("Input gameboard");
        return;
    }
}

void MainWindow::handle_setup_board_button_clicks()
{
    if(randomize_button_->isChecked())
    {
        int seed = seed_input_field_->text().toInt();
        if(gameboard_.fill_randomly(seed))
        {
            setup_board();
            setup_board_button_->setEnabled(false);
            seed_input_field_->setEnabled(false);
            randomize_button_->setEnabled(false);
            manual_input_button_->setEnabled(false);
            board_setup_status_->setText("Generating board");
        }

        else
        {
            board_setup_status_->setText("Bad seed");
        }

        return;
    }

    if(manual_input_button_->isChecked())
    {
        std::string input = seed_input_field_->text().toStdString();

        if(gameboard_.fill_from_input(input))
        {
            setup_board();
            setup_board_button_->setEnabled(false);
            seed_input_field_->setEnabled(false);
            randomize_button_->setEnabled(false);
            manual_input_button_->setEnabled(false);
            board_setup_status_->setText("Board generated");
        }
        else
        {
            board_setup_status_->setText("Bad input");
        }

        return;
    }
}

void MainWindow::setup_board()
{
    for(int gridnumber = 0; gridnumber < SIZE * SIZE; gridnumber ++)
    {
        int x = gridnumber % SIZE;
        int y = gridnumber / SIZE;
        switch(gameboard_.get_gridspace(x, y))
        {
            case ZERO:
                gridspaces_.at(gridnumber)->setText("0");
                gridspaces_.at(gridnumber)->setEnabled(false);
                break;

            case ONE:
                gridspaces_.at(gridnumber)->setText("1");
                gridspaces_.at(gridnumber)->setEnabled(false);
                break;

            default:
                gridspaces_.at(gridnumber)->setEnabled(true);
                break;
        }
    }
}

void MainWindow::update_board(QPushButton* gridspace, int x, int y)
{
    char symbol = symbol_.toStdString().at(0);
    if(gameboard_.add_symbol(x, y, symbol))
    {
        gridspace->setText(symbol_);
        gridspace->setEnabled(false);
    }
}
