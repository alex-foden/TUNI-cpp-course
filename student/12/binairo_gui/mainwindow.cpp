#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
    button_font_.setPixelSize(32);
    is_game_paused_ = true;

    gameboard_ = new GameBoard();

    init_gameboard();
    init_symbol_button();
    init_gameboard_setup_menu();
    init_timer();
    init_reset_button();
    init_pause_button();
    init_close_button();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gameboard_;
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
    symbol_button_->setGeometry(10 + 2*170 + 2*5, BOARD_SIZE + 10, 100, 100);
    symbol_button_->setFont(button_font_);
    connect(symbol_button_, &QPushButton::clicked,
            this, &MainWindow::handle_symbol_button_clicks);
}

void MainWindow::init_gameboard_setup_menu()
{
    QLabel* board_setup_label = new QLabel("SETUP GAMEBOARD TO START GAME", this);
    board_setup_label->setGeometry(BOARD_SIZE + 40, 10 + 20, 300, 50);
    board_setup_label->setAlignment(Qt::AlignCenter);

    QLabel* randomize_label = new QLabel("Randomize", this);
    randomize_label->setGeometry(BOARD_SIZE + 40 + 70 + 16/2 - 100/2, 10 + 55, 100, 30);
    randomize_label->setAlignment(Qt::AlignCenter);
    randomize_button_ = new QRadioButton(this);
    randomize_button_->setGeometry(BOARD_SIZE + 40 + 70, 10 + 80, 16, 16);
    connect(randomize_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_board_setup_tooltip);

    QLabel* manual_input_label = new QLabel("Manual input", this);
    manual_input_label->setGeometry(BOARD_SIZE + 40 + 300 - 70 - 16/2 - 100/2, 10 + 55, 100, 30);
    manual_input_label->setAlignment(Qt::AlignCenter);
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

void MainWindow::init_timer()
{
    timer_display_ = new QLabel("00:00", this);
    timer_display_->setGeometry(10, BOARD_SIZE + 10, 170, 100);
    timer_display_->setAlignment(Qt::AlignCenter);
    timer_display_->setFont(button_font_);

    seconds_ = 0;
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &MainWindow::handle_timer_timeout);
}

void MainWindow::init_reset_button()
{
    reset_button_ = new QPushButton("Reset", this);
    reset_button_->setEnabled(false);
    reset_button_->setGeometry(10 + 170 + 5, BOARD_SIZE + 10, 170, 100);
    reset_button_->setFont(button_font_);
    connect(reset_button_, &QPushButton::clicked,
            this, &MainWindow::handle_reset_button_clicks);
}

void MainWindow::init_pause_button()
{
    pause_button_ = new QPushButton("Pause", this);
    pause_button_->setEnabled(false);
    pause_button_->setGeometry(10 + 2*170 + 100 + 3*5, BOARD_SIZE + 10, 170, 100);
    pause_button_->setFont(button_font_);
    connect(pause_button_, &QPushButton::clicked,
            this, &MainWindow::handle_pause_button_clicks);
}

void MainWindow::init_close_button()
{
    close_button_ = new QPushButton("Close", this);
    close_button_->setGeometry(10 + 3*170 + 100 + 4*5, BOARD_SIZE + 10, 170, 100);
    close_button_->setFont(button_font_);
    connect(close_button_, &QPushButton::clicked,
            this, &MainWindow::handle_close_button_clicks);
}

void MainWindow::handle_gameboard_clicks()
{
    int grid_number = 0;

    for(QPushButton* gridspace: gridspaces_)
    {
        int column = grid_number % SIZE;
        int row = grid_number / SIZE;

        if(gridspace == sender())
        {
            update_board(gridspace, column, row);
            return;
        }

        grid_number++;
    }
}

void MainWindow::handle_symbol_button_clicks()
{
    if(symbol_ == "0")
    {
        symbol_ = "1";
        symbol_button_->setText(symbol_);
        return;
    }

    if(symbol_ == "1")
    {
        symbol_ = "0";
        symbol_button_->setText(symbol_);
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

        if(gameboard_->fill_randomly(seed))
        {
            setup_board();

            setup_board_button_->setEnabled(false);
            seed_input_field_->setEnabled(false);
            seed_input_field_->clear();
            seed_input_field_->setPlaceholderText("");

            randomize_button_->setEnabled(false);
            randomize_button_->setAutoExclusive(false);
            randomize_button_->setChecked(false);
            randomize_button_->setAutoExclusive(true);

            manual_input_button_->setEnabled(false);
            manual_input_button_->setAutoExclusive(false);
            manual_input_button_->setChecked(false);
            manual_input_button_->setAutoExclusive(true);

            board_setup_status_->setText("Good luck!");

            timer_->start();
            reset_button_->setEnabled(true);
            pause_button_->setEnabled(true);
            is_game_paused_ = false;
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

        if(gameboard_->fill_from_input(input))
        {
            setup_board();

            setup_board_button_->setEnabled(false);
            seed_input_field_->setEnabled(false);
            seed_input_field_->clear();
            seed_input_field_->setPlaceholderText("");

            randomize_button_->setEnabled(false);
            randomize_button_->setAutoExclusive(false);
            randomize_button_->setChecked(false);
            randomize_button_->setAutoExclusive(true);

            manual_input_button_->setEnabled(false);
            manual_input_button_->setAutoExclusive(false);
            manual_input_button_->setChecked(false);
            manual_input_button_->setAutoExclusive(true);

            board_setup_status_->setText("Good luck!");

            timer_->start();
            reset_button_->setEnabled(true);
            pause_button_->setEnabled(true);
            is_game_paused_ = false;
        }
        else
        {
            board_setup_status_->setText("Bad input");
        }

        return;
    }
}

void MainWindow::handle_timer_timeout()
{
    seconds_++;
    QString time = get_time();
    timer_display_->setText(time);
}

void MainWindow::handle_reset_button_clicks()
{
    reset_button_->setEnabled(false);
    pause_button_->setEnabled(false);
    pause_button_->setText("Pause");

    timer_->stop();
    seconds_ = 0;
    timer_display_->setText("00:00");

    randomize_button_->setEnabled(true);
    manual_input_button_->setEnabled(true);
    board_setup_status_->clear();

    reset_board();
}

void MainWindow::handle_pause_button_clicks()
{
    if(not is_game_paused_)
    {
        timer_->stop();

        for(QPushButton* gridspace: gridspaces_)
        {
            gridspace->setEnabled(false);
        }

        pause_button_->setText("Unpause");
        is_game_paused_ = true;
    }

    else
    {
        timer_->start();
        int grid_number = 0;

        for(QPushButton* gridspace: gridspaces_)
        {
            int column = grid_number % SIZE;
            int row = grid_number / SIZE;

            if(gameboard_->get_gridspace(column, row) == EMPTY)
            {
                gridspace->setEnabled(true);
            }

            grid_number++;
        }

        pause_button_->setText("Pause");
        is_game_paused_ = false;
    }
}

void MainWindow::handle_close_button_clicks()
{
    this->close();
}

QString MainWindow::get_time()
{
    QString minutes = QString::number(seconds_ / 60);
    QString seconds = QString::number(seconds_ % 60);

    if(seconds_ / 60 < 10)
    {
        minutes = "0" + minutes;
    }

    if(seconds_ % 60 < 10)
    {
        seconds = "0" + seconds;
    }

    return minutes + ":" + seconds;
}

void MainWindow::setup_board()
{
    int gridnumber = 0;

    for(QPushButton* gridspace : gridspaces_)
    {
        int column = gridnumber % SIZE;
        int row = gridnumber / SIZE;

        switch(gameboard_->get_gridspace(column, row))
        {
            case ZERO:
                gridspace->setText("0");
                gridspace->setEnabled(false);
                break;

            case ONE:
                gridspace->setText("1");
                gridspace->setEnabled(false);
                break;

            default:
                gridspace->setEnabled(true);
                break;
        }

        gridnumber++;
    }
}

void MainWindow::update_board(QPushButton* gridspace, int column, int row)
{
    char symbol = symbol_.toStdString().at(0);

    if(gameboard_->add_symbol(column, row, symbol))
    {
        gridspace->setText(symbol_);
        gridspace->setEnabled(false);
    }

    if(gameboard_->is_game_over())
    {
        end_game();
    }
}

void MainWindow::reset_board()
{
    gameboard_->clear_board();
    delete gameboard_grid_;
    gridspaces_.clear();
    init_gameboard();
}

void MainWindow::end_game()
{
    timer_->stop();
    QString time = get_time();
    int messageBoxResult = 0;
    messageBoxResult = QMessageBox::question(0,
                                             "You won in " + time + "!",
                                             "Continue playing?",
                                             QMessageBox::Yes,
                                             QMessageBox::No);

    if(messageBoxResult == QMessageBox::Yes)
    {
        pause_button_->setEnabled(false);
        reset_button_->setEnabled(false);
        randomize_button_->setEnabled(true);
        manual_input_button_->setEnabled(true);
        board_setup_status_->clear();

        seconds_ = 0;
        timer_display_->setText("00:00");

        reset_board();
    }
    else
    {
        this->close();
    }
}
