#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gameboard.hh>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <vector>

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

    void init_gameboard();
    void handle_button_clicks();
};
#endif // MAINWINDOW_HH
