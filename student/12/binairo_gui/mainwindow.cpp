#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    this->setStyleSheet("background-color: black; color: white;");

    // Symbols used in the gameboard grid UI. Colors are self explanatory.
    CIRCLE = QPixmap(":/Resources/circle.png"); // symbol == '0'
    CIRCLE_GREEN = QPixmap(":/Resources/circlegreen.png"); // correct
    CIRCLE_RED = QPixmap(":/Resources/circlered.png"); // incorrect
    CROSS = QPixmap(":/Resources/cross.png"); // symbol == '1'
    CROSS_GREEN = QPixmap(":/Resources/crossgreen.png"); // correct
    CROSS_RED = QPixmap(":/Resources/crossred.png"); // incorrect

    // Font used for most buttons.
    button_font_.setPixelSize(32);

    // Game is paused until user starts the game.
    is_game_paused_ = true;

    // Create a GameBoard object with game logic. UI reads from this object and is only updated.
    gameboard_ = new GameBoard();

    // Create and setup the UI.
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
    // Create the grid for the gameboard UI component
    QWidget* central = new QWidget(this);
    gameboard_grid_ = new QGridLayout(central);
    gameboard_grid_->setSizeConstraint(QLayout::SetFixedSize);
    gameboard_grid_->setHorizontalSpacing(0);
    gameboard_grid_->setVerticalSpacing(0);

    // Add QPushButtons to SIZExSIZE QGridLayout
    for(int row = 0; row < SIZE; row++)
    {
        for(int column = 0; column < SIZE; column++)
        {
            // Create a gridspace button and add it to (column, row) in gameboard grid.
            QPushButton* gridspace = new QPushButton(" ", this);
            gridspace->setStyleSheet("border: 1px solid #333333;");
            gridspace->setEnabled(false);
            gridspace->setFixedWidth(BOARD_SIZE / SIZE);
            gridspace->setFixedHeight(BOARD_SIZE / SIZE);

            // Add pointer to the button to vecor gridspaces_ for other methods access.
            gridspaces_.push_back(gridspace);

            gameboard_grid_->addWidget(gridspace, row, column);
            // On click, calls handle_gameboard_clicks().
            connect(gridspace, &QPushButton::clicked,
                    this, &MainWindow::handle_gameboard_clicks);
        }
    }
    setCentralWidget(central);
}

void MainWindow::init_symbol_button()
{
    // Create the symbol button
    symbol_ = '0';
    symbol_button_ = new QPushButton(this);
    symbol_button_->setIcon(CIRCLE); // CIRCLE = '0', CROSS = '1'
    symbol_button_->setGeometry(BOARD_MARGIN + 2*DEFAULT_BUTTON_WIDTH + 2*BUTTON_MARGIN,
                                BOARD_SIZE + 2*BOARD_MARGIN, SYMBOL_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT);
    symbol_button_->setStyleSheet("border: 1px solid white;");
    // On click, call handle_symbol_button_clicks
    connect(symbol_button_, &QPushButton::clicked,
            this, &MainWindow::handle_symbol_button_clicks);
}

void MainWindow::init_gameboard_setup_menu()
{
    // Creating the title/header for the setup menu.
    QLabel* board_setup_label = new QLabel("SETUP GAMEBOARD TO START GAME", this);
    board_setup_label->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN,
                                   BOARD_MARGIN + TOP_MARGIN, SETUP_MENU_WIDTH, DEFAULT_LABEL_HEIGHT);
    board_setup_label->setAlignment(Qt::AlignCenter);

    // Creating the label for the randomize QRadioButton.
    QLabel* randomize_label = new QLabel("Randomize", this);
    randomize_label->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN + SETUP_MENU_WIDTH/4 - DEFAULT_LABEL_WIDTH/2,
                                 BOARD_MARGIN + TOP_MARGIN + DEFAULT_LABEL_HEIGHT + LABEL_MARGIN, DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT);
    randomize_label->setAlignment(Qt::AlignCenter);
    // Creating the randomize radio button. On click, calls handle_board_setup_tooltip()
    randomize_button_ = new QRadioButton(this);
    randomize_button_->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN + SETUP_MENU_WIDTH/4 - RADIO_BUTTON_SIZE/2,
                                   BOARD_MARGIN + TOP_MARGIN + 2*DEFAULT_LABEL_HEIGHT + LABEL_MARGIN, RADIO_BUTTON_SIZE, RADIO_BUTTON_SIZE);
    randomize_button_->setStyleSheet("background: none; color: default;");
    connect(randomize_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_board_setup_tooltip);

    // Creating the label for the manual input QRadioButton
    QLabel* manual_input_label = new QLabel("Manual input", this);
    manual_input_label->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN + 3*SETUP_MENU_WIDTH/4 - DEFAULT_LABEL_WIDTH/2,
                                    BOARD_MARGIN + TOP_MARGIN + DEFAULT_LABEL_HEIGHT + LABEL_MARGIN, DEFAULT_LABEL_WIDTH, DEFAULT_LABEL_HEIGHT);
    manual_input_label->setAlignment(Qt::AlignCenter);
    // Creating the manual input QRadioButton. On click, call handle_board_setup_tooltip().
    manual_input_button_ = new QRadioButton(this);
    manual_input_button_->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN + 3*SETUP_MENU_WIDTH/4 - RADIO_BUTTON_SIZE/2,
                                       BOARD_MARGIN + TOP_MARGIN + 2*DEFAULT_LABEL_HEIGHT + LABEL_MARGIN, RADIO_BUTTON_SIZE, RADIO_BUTTON_SIZE);
    manual_input_button_->setStyleSheet("background: none; color: default");
    connect(manual_input_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_board_setup_tooltip);

    // Creating the input_field QLineEdit, which allow the user to input the random seed / manually inputeed board.
    // Disabled until user selects one of the QRadioButtons for selecting the setup method.
    seed_input_field_ = new QLineEdit("Select setup method", this);
    seed_input_field_->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN,
                                   BOARD_MARGIN + TOP_MARGIN + 2*DEFAULT_LABEL_HEIGHT + 2*LABEL_MARGIN + RADIO_BUTTON_SIZE,
                                   SETUP_MENU_WIDTH, SEED_INPUT_FIELD_HEIGHT);
    seed_input_field_->setStyleSheet("color: white; border: 1px solid #333333;");
    seed_input_field_->setEnabled(false);

    // Creating the setup board QPushButton, which allows the user to start the game.
    // Disabled until user selects one of the QRadioButtons for selecting the setup method.
    // On click, calls handle_setup_board_button_clicks().
    setup_board_button_ = new QPushButton("Start", this);
    setup_board_button_->setGeometry(BOARD_SIZE + 2*BOARD_MARGIN + RIGHT_MARGIN + SETUP_MENU_WIDTH/2 - DEFAULT_BUTTON_WIDTH/2,
                                     BOARD_MARGIN + TOP_MARGIN + 2*DEFAULT_LABEL_HEIGHT + 3*LABEL_MARGIN + RADIO_BUTTON_SIZE + SEED_INPUT_FIELD_HEIGHT,
                                     DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT/2);
    setup_board_button_->setEnabled(false);
    setup_board_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    connect(setup_board_button_, &QRadioButton::clicked,
            this, &MainWindow::handle_setup_board_button_clicks);
}

void MainWindow::init_timer()
{
    // Create the display for the timer
    timer_display_ = new QLabel("00:00", this);
    timer_display_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    timer_display_->setGeometry(BOARD_MARGIN, BOARD_SIZE + 2*BOARD_MARGIN,
                                DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT);
    timer_display_->setAlignment(Qt::AlignCenter);
    timer_display_->setFont(button_font_);

    // Create the QTimer, which calls handle_timer_timeout() every second
    seconds_ = 0;
    timer_ = new QTimer(this);
    timer_->setInterval(1000);
    connect(timer_, &QTimer::timeout, this, &MainWindow::handle_timer_timeout);
}

void MainWindow::init_reset_button()
{
    // Create the reset button. Resets the timer and clears the board of symbols. Disabled until user starts the game.
    reset_button_ = new QPushButton("Reset", this);
    reset_button_->setEnabled(false);
    reset_button_->setGeometry(BOARD_MARGIN + DEFAULT_BUTTON_WIDTH + BUTTON_MARGIN,
                               BOARD_SIZE + 2*BOARD_MARGIN, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT);
    reset_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    reset_button_->setFont(button_font_);
    // On click, calls handle_reset_button_clicks().
    connect(reset_button_, &QPushButton::clicked,
            this, &MainWindow::handle_reset_button_clicks);
}

void MainWindow::init_pause_button()
{
    // Create the pause button. Disables gameboard_grid and stops the timer until user unpauses. Disabled until user starts the game.
    pause_button_ = new QPushButton("Pause", this);
    pause_button_->setEnabled(false);
    pause_button_->setGeometry(BOARD_MARGIN + 2 * DEFAULT_BUTTON_WIDTH + SYMBOL_BUTTON_WIDTH + 3 * BUTTON_MARGIN,
                               BOARD_SIZE + 2*BOARD_MARGIN, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT);
    pause_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    pause_button_->setFont(button_font_);
    // On click, calls handle_pause_button_clicks().
    connect(pause_button_, &QPushButton::clicked,
            this, &MainWindow::handle_pause_button_clicks);
}

void MainWindow::init_close_button()
{
    // Create the close button. On click, closes the window.
    close_button_ = new QPushButton("Close", this);
    close_button_->setGeometry(BOARD_MARGIN + 3 * DEFAULT_BUTTON_WIDTH + SYMBOL_BUTTON_WIDTH + 4 * BUTTON_MARGIN,
                               BOARD_SIZE + 2*BOARD_MARGIN, DEFAULT_BUTTON_WIDTH, DEFAULT_BUTTON_HEIGHT);
    close_button_->setStyleSheet("color: white; border: 1px solid white;");
    close_button_->setFont(button_font_);
    connect(close_button_, &QPushButton::clicked,
            this, &MainWindow::handle_close_button_clicks);
}

void MainWindow::handle_gameboard_clicks()
{
    int grid_number = 0;

    // Iterate through gridspaces vector to find the gridspace user clicked.
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
    if(symbol_ == '0')
    {
        symbol_ = '1';
        symbol_button_->setIcon(CROSS);
        return;
    }

    if(symbol_ == '1')
    {
        symbol_ = '0';
        symbol_button_->setIcon(CIRCLE);
        return;
    }
}

void MainWindow::handle_board_setup_tooltip()
{
    setup_board_button_->setEnabled(true);
    setup_board_button_->setStyleSheet("color: white; border: 1px solid white");
    seed_input_field_->setEnabled(true);
    seed_input_field_->setStyleSheet("border: 1px solid white");

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

        // Check if seed is valid. Also fills the GameBoard objects board.
        if(gameboard_->fill_randomly(seed))
        {
            // Disable the setup menu
            setup_board_button_->setEnabled(false);
            seed_input_field_->setEnabled(false);
            seed_input_field_->clear();
            seed_input_field_->setPlaceholderText("Good luck!");
            seed_input_field_->setStyleSheet("border: 1px solid #333333;");
            setup_board_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");

            randomize_button_->setEnabled(false);
            randomize_button_->setAutoExclusive(false);
            randomize_button_->setChecked(false);
            randomize_button_->setAutoExclusive(true);

            manual_input_button_->setEnabled(false);
            manual_input_button_->setAutoExclusive(false);
            manual_input_button_->setChecked(false);
            manual_input_button_->setAutoExclusive(true);

            // Enable the reset and pause button
            reset_button_->setEnabled(true);
            reset_button_->setStyleSheet("color: white; border: 1px solid white;");
            pause_button_->setEnabled(true);
            pause_button_->setStyleSheet("color: white; border: 1px solid white;");
            symbol_button_->setStyleSheet("border: 1px solid white;");

            // Start the timer
            timer_->start();
            timer_display_->setStyleSheet("color: white; border: 1px solid white;");
            is_game_paused_ = false;

            // Setup the board
            setup_board();
        }
        else // Seed was invalid
        {
            seed_input_field_->clear();
            seed_input_field_->setPlaceholderText("Bad seed");
        }

        return;
    }


    if(manual_input_button_->isChecked())
    {
        std::string input = seed_input_field_->text().toStdString();

        // Check if user inputted the board correctly. Also fills the GameBoard objects board.
        if(gameboard_->fill_from_input(input))
        {
            // Disable the setup menu
            setup_board_button_->setEnabled(false);
            seed_input_field_->setEnabled(false);
            seed_input_field_->clear();
            seed_input_field_->setPlaceholderText("Good luck!");
            seed_input_field_->setStyleSheet("border: 1px solid #333333;");
            setup_board_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");

            randomize_button_->setEnabled(false);
            randomize_button_->setAutoExclusive(false);
            randomize_button_->setChecked(false);
            randomize_button_->setAutoExclusive(true);

            manual_input_button_->setEnabled(false);
            manual_input_button_->setAutoExclusive(false);
            manual_input_button_->setChecked(false);
            manual_input_button_->setAutoExclusive(true);

            // Enable the reset and pause button
            reset_button_->setEnabled(true);
            reset_button_->setStyleSheet("color: white; border: 1px solid white;");
            pause_button_->setEnabled(true);
            pause_button_->setStyleSheet("color: white; border: 1px solid white;");
            symbol_button_->setStyleSheet("border: 1px solid white;");

            // Start the timer
            timer_->start();
            timer_display_->setStyleSheet("color: white; border: 1px solid white;");
            is_game_paused_ = false;

            // Setup the board
            setup_board();
        }
        else // Input was invalid
        {
            seed_input_field_->clear();
            seed_input_field_->setPlaceholderText("Bad input");
        }

        return;
    }
}

void MainWindow::handle_timer_timeout()
{
    // Increase seconds by 1 and update the timer display
    seconds_++;
    QString time = get_time();
    timer_display_->setText(time);
}

void MainWindow::handle_reset_button_clicks()
{
    // Disable the reset and pause button
    reset_button_->setEnabled(false);
    reset_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    pause_button_->setEnabled(false);
    pause_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    pause_button_->setText("Pause");

    // Reset the timer
    timer_->stop();
    seconds_ = 0;
    timer_display_->setText("00:00");
    timer_display_->setStyleSheet("color: #444444; border: 1px solid #333333;");
    is_game_paused_ = true; // Game is now paused

    // Enable the setup menu
    randomize_button_->setEnabled(true);
    manual_input_button_->setEnabled(true);
    seed_input_field_->setPlaceholderText("Select setup method");
    seed_input_field_->clear();

    // Reset the gameboard grid UI and the GameBoard object
    reset_board();
}

void MainWindow::handle_pause_button_clicks()
{
    if(not is_game_paused_) // Pause
    {
        // Stop the timer
        timer_->stop();
        timer_display_->setStyleSheet("color: #444444; border: 1px solid #333333;");

        // Disable the gameboard grid UI
        for(QPushButton* gridspace: gridspaces_)
        {
            gridspace->setEnabled(false);
            gridspace->setStyleSheet("border: 1px solid #333333;");
        }

        pause_button_->setText("Unpause");
        is_game_paused_ = true; // Game is now paused
        return;
    }

    else // Unpause
    {
        // Start the timer
        timer_->start();
        timer_display_->setStyleSheet("color: white; border: 1px solid white;");
        int grid_number = 0;

        // Enable all EMPTY gridspaces
        for(QPushButton* gridspace: gridspaces_)
        {
            gridspace->setStyleSheet("border: 1px solid #888888;");
            int x = grid_number % SIZE;
            int y = grid_number / SIZE;

            if(gameboard_->get_gridspace(x, y) == EMPTY)
            {
                gridspace->setEnabled(true);
            }

            grid_number++;
        }

        pause_button_->setText("Pause");
        is_game_paused_ = false; // Game is now not paused
        return;
    }
}

void MainWindow::handle_close_button_clicks()
{
    this->close(); // Closes the window
}

QString MainWindow::get_time()
{
    // Format the seconds into mm:ss format f.ex. [04:13]
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

    // Update the entire gameboard grid UI by reading the set up GameBoard object
    for(QPushButton* gridspace : gridspaces_)
    {
        int column = gridnumber % SIZE;
        int row = gridnumber / SIZE;
        gridspace->setStyleSheet("border: 1px solid #888888;");

        switch(gameboard_->get_gridspace(column, row))
        {
        // Disable the gridspaces that are already filled
            case ZERO:
                gridspace->setIcon(CIRCLE);
                gridspace->setEnabled(false);
                break;

            case ONE:
                gridspace->setIcon(CROSS);
                gridspace->setEnabled(false);
                break;
        // Enable the EMPTY gridspaces
            default:
                gridspace->setEnabled(true);
                break;
        }

        gridnumber++;
    }
    // for the funny
    if(gameboard_->is_game_over())
    {
        end_game();
    }
}

void MainWindow::update_board(QPushButton* gridspace, int x, int y)
{
    // Check if symbol could be added
    if(gameboard_->add_symbol(x, y, symbol_)) // true = symbol has been added to GameBoard obejct
    {
        // Update the gameboard grid UI
        if(symbol_ == '0')
        {
            gridspace->setIcon(CIRCLE);
        }
        if(symbol_ == '1')
        {
            gridspace->setIcon(CROSS);
        }

        // Disable the now filled button
        gridspace->setEnabled(false);
        gridspace->setStyleSheet("border: 1px solid #888888");
    }
    else // false = symbol was invalid and not been added to GameBoard object
    {
        // Update the gameboard grid UI to reflect the user's mistake. (gridspace goes red)
        if(symbol_ == '0')
        {
            gridspace->setIcon(CIRCLE_RED);
        }
        if(symbol_ == '1')
        {
            gridspace->setIcon(CROSS_RED);
        }

        // Gridspace is NOT disabled. User can fix the mistake.
        gridspace->setStyleSheet("border: 1px solid #FF0000;");
    }

    // If gameboard has been fully filled I.E user has won
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
    // Stop the timer and set everything green for victory
    this->setStyleSheet("color:white; background-color: #002200;");
    timer_->stop();
    timer_display_->setStyleSheet("color: #00FF00; border: 1px solid #00FF00");
    pause_button_->setStyleSheet("color: #00FF00; border: 1px solid #00FF00");

    reset_button_->setStyleSheet("color: #00FF00; border: 1px solid #00FF00");
    close_button_->setStyleSheet("color: #00FF00; border: 1px solid #00FF00");
    symbol_button_->setStyleSheet("color: #00FF00; border: 1px solid #00FF00");
    if(symbol_ == '0')
    {
        symbol_button_->setIcon(CIRCLE_GREEN);
    }
    if(symbol_ == '1')
    {
        symbol_button_->setIcon(CROSS_GREEN);
    }

    // Create pop-up that shows the user the time it took to win and ask the user to quit or continue playing
    QString time = get_time();
    int messageBoxResult = 0;
    messageBoxResult = QMessageBox::question(0,
                                             "You won in " + time + "!",
                                             "Continue playing?",
                                             QMessageBox::Yes,
                                             QMessageBox::No);

    if(messageBoxResult == QMessageBox::Yes)
    {
        // Reset
        this->setStyleSheet("color: white; background-color: black;");

        pause_button_->setEnabled(false);
        pause_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
        reset_button_->setEnabled(false);
        reset_button_->setStyleSheet("color: #444444; border: 1px solid #333333;");
        close_button_->setStyleSheet("color: white; border: 1px solid white");
        symbol_button_->setStyleSheet("border: 1px solid white");
        if(symbol_ == '0')
        {
            symbol_button_->setIcon(CIRCLE);
        }
        if(symbol_ == '1')
        {
            symbol_button_->setIcon(CROSS);
        }

        randomize_button_->setEnabled(true);
        manual_input_button_->setEnabled(true);
        seed_input_field_->clear();
        seed_input_field_->setPlaceholderText("Select setup method");

        seconds_ = 0;
        timer_display_->setText("00:00");
        timer_display_->setStyleSheet("color: #444444; border: 1px solid #333333");

        reset_board();
    }
    else
    {
        this->close();
    }
}
