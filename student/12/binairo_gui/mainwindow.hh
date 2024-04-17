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

private slots:

private:
    Ui::MainWindow *ui;
    GameBoard gameboard_;
    QGridLayout* gameboard_grid_;
    std::vector<QPushButton*> gridspaces_;

    QString symbol_;
    QPushButton* symbol_button_;
    QRadioButton* randomize_button_;
    QRadioButton* manual_input_button_;
    QLineEdit* seed_input_field_;
    QPushButton* setup_board_button_;
    QTextBrowser* board_setup_status_;

    void init_gameboard();
    void init_symbol_button();
    void init_gameboard_setup_menu();

    void handle_gameboard_clicks();
    void handle_symbol_button_clicks();
    void handle_board_setup_tooltip();
    void handle_setup_board_button_clicks();

    void setup_board();
};
#endif // MAINWINDOW_HH
