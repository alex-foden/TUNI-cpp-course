#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gameboard.hh>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextBrowser>
#include <QTimer>
#include <QMessageBox>
#include <vector>

// Each way you can setup the board to start the game
enum BOARD_SETUP {RANDOM, MANUAL};

// Constants for setting the UI
const int BOARD_SIZE = 800; // Width and height of the board
const int BOARD_MARGIN = 8; // Distance of the edge of the window and the board
const int RIGHT_MARGIN = 30; // Extra distance of the board and ui components to its right
const int TOP_MARGIN = 20; // Extra distance from the top of the window for ui components to the right of the board
const int BUTTON_MARGIN = 5; // Distance between the buttons below the board
const int DEFAULT_BUTTON_HEIGHT = 100; // Default button height
const int DEFAULT_BUTTON_WIDTH = 170; // Default button width
const int SYMBOL_BUTTON_WIDTH = 100; // Symbol_button width
const int SETUP_MENU_WIDTH = 300; // Width of the setup menu
const int DEFAULT_LABEL_HEIGHT = 20; // Default label height
const int DEFAULT_LABEL_WIDTH = 100; // Default label width
const int LABEL_MARGIN = 15; // Vertical distance betweeen label and any object
const int RADIO_BUTTON_SIZE = 16; // Width and height of all radio buttons
const int SEED_INPUT_FIELD_HEIGHT = 25; // Seed_input_field height


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameBoard* gameboard_; // contains the vector and methods for the game to work

    // shows the state of the game in the ui and allows the user to interact with game through the ui
    QGridLayout* gameboard_grid_;
    std::vector<QPushButton*> gridspaces_; // pointers to every gridspace in the gameboard

    // Symbols used in gameboard.
    QPixmap CIRCLE; // symbol = '0'
    QPixmap CIRCLE_GREEN; // todo: go green when row/column is correct
    QPixmap CIRCLE_RED; // incorrect input
    QPixmap CROSS; // symbol = '1'
    QPixmap CROSS_GREEN; // todo: go green when row/column is correct
    QPixmap CROSS_RED; // incorrect input

    // Selected symbol user will add to board
    char symbol_;
    // Button for picking which symbol to add to board
    QPushButton* symbol_button_;

    // Board setup menu UI components
    QRadioButton* randomize_button_;
    QRadioButton* manual_input_button_;
    QLineEdit* seed_input_field_;
    QPushButton* setup_board_button_;

    // Timer
    QLabel* timer_display_;
    QTimer* timer_;
    int seconds_;

    // Button for resetting the board during game
    QPushButton* reset_button_;

    // Button for pausing the game during the game
    QPushButton* pause_button_;
    bool is_game_paused_;

    // Button for closing the window
    QPushButton* close_button_;

    // Default font for buttons
    QFont button_font_;


    // Inits the gameboard UI, i.e. creates GameBoard SIZE * SIZE QGridLayout of QPushButtons
    // When a QPushButton (gridspace) is clicked, call handle_gameboard_clicks()
    void init_gameboard();

    // Inits symbol button, which decides what symbol user will add to board.
    // On click, calls handle_symbol_button_clicks()
    void init_symbol_button();

    // Inits all UI components for the board setup menu.
    void init_gameboard_setup_menu();

    // Inits QTimer object, which updates the timer_display label every second
    // On timeout (every second game is not paused), calls handle_timer_timeout
    void init_timer();

    // Inits reset button. on click, calls handle_reset_button_clicks()
    void init_reset_button();

    // Inits pause button. on click, calls handle_pause_button_clicks()
    void init_pause_button();

    // Inits close button. on click, calls handle_close_button_clicks()
    void init_close_button();

    // Finds x and y coordinated of clicked gridspace.
    // Calls update_board with pointer to clicked button and its x and y coordinated as arguments
    void handle_gameboard_clicks();

    // When current symbol = '0', set it to '1' and vice versa.
    void handle_symbol_button_clicks();

    // When user has selected how to setup the board, enable seed_input_field and update
    // the placeholder text in it to tell the user what they are supposed to input to start the game.
    void handle_board_setup_tooltip();

    // When user has set the seed/board and clicked start, call the GameBoard method
    // fill_randomly/fill_from_input accordingly and call the MainWindow method setup_board().
    // Disables setup menu since its not needed during the game.
    // Enables the pause and reset buttons and starts the timer.
    void handle_setup_board_button_clicks();

    // Increases seconds_ by 1. calls get_time() to get the current time and
    // update the timer_display_ label with the current time.
    void handle_timer_timeout();

    // Calls reset_board. Disables the reset and pause buttons and resets the timer, turning it off.
    // Enables the setup menu.
    void handle_reset_button_clicks();

    // Pauses/Unpauses the game.
    // if game is not paused, stop the timer and disable the gameboard
    // if game is paused, start the timer and enable the gameboard
    void handle_pause_button_clicks();

    // Closes the window
    void handle_close_button_clicks();

    // Takes the current time used and formats it into standard mm:ss format (f.ex 02:43).
    // Returns the current time used in the game as a QString.
    QString get_time();

    // Reads the GameBoard objects board vector and updates the gameboard_grid UI component.
    // Disables all non empty buttons and enables all empty buttons.
    void setup_board();

    // Calls GameBoard class's add_symbol method with the x and y coordinated of the button that
    // the user clicked, and the symbol the user has chosen.
    // If the symbol was added succesfully (rules were followed), update the gameboard_grid UI
    // component with the symbol, otherwise update it with a red symbol and border to visualise
    // for the user that the input was incorrect.
    // Call end_game(), if the gameboard is succefully filled.
    void update_board(QPushButton* gridspace, int x, int y);

    // Resets the board by deleting the gameboard_grid UI component, initialising a new
    // gameboard_grid, emptying the gridspaces vector and
    // calling GameBoard.clear_board, which empties the Gameboard vector.
    void reset_board();

    // Creates a QMessageBox popup, which shows the time it took to win and asks the user
    // to either continue playing or quit.
    // If user continues, disable pause and close buttons, reset the timer and enable the setup menu.
    // Otherwise close the window.
    void end_game();
};
#endif // MAINWINDOW_HH
