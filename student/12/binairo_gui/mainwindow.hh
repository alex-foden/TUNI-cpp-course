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

enum BOARD_SETUP {RANDOM, MANUAL};

const int BOARD_SIZE = 800;

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
    GameBoard* gameboard_;
    QGridLayout* gameboard_grid_;
    std::vector<QPushButton*> gridspaces_;

    QString symbol_;
    QPushButton* symbol_button_;

    QRadioButton* randomize_button_;
    QRadioButton* manual_input_button_;
    QLineEdit* seed_input_field_;
    QPushButton* setup_board_button_;
    QTextBrowser* board_setup_status_;

    QLabel* timer_display_;
    QTimer* timer_;

    int seconds_;

    QPushButton* reset_button_;

    QPushButton* pause_button_;
    bool is_game_paused_;

    QPushButton* close_button_;

    QFont button_font_;

    void init_gameboard();
    void init_symbol_button();
    void init_gameboard_setup_menu();
    void init_timer();
    void init_reset_button();
    void init_pause_button();
    void init_close_button();

    void handle_gameboard_clicks();
    void handle_symbol_button_clicks();
    void handle_board_setup_tooltip();
    void handle_setup_board_button_clicks();
    void handle_timer_timeout();
    void handle_reset_button_clicks();
    void handle_pause_button_clicks();
    void handle_close_button_clicks();

    QString get_time();

    void setup_board();
    void update_board(QPushButton* gridspace, int column, int row);
    void reset_board();
    void end_game();
};
#endif // MAINWINDOW_HH
