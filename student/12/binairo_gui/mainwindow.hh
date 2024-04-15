#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gameboard.hh>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>

const int BOARD_SIZE = 800;
const std::vector<QString> SYMBOLS = {"0", "1", " "};

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
    std::vector<QPushButton*> buttons_;
    QString symbol_;

    QPushButton* symbol_button_;

    void init_gameboard();
    void init_symbol_button();
    void handle_button_clicks();
    void handle_symbol_button_clicks();
};
#endif // MAINWINDOW_HH
