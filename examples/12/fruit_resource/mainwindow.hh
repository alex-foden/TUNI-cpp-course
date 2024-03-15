#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
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
    // Handles fruit button clicks,
    // i.e. draws the chosen fruit in the attribute label_
    void handle_fruit_clicks();

private:
    Ui::MainWindow *ui;

    // Consts for all margins and fruits
    const int MARGIN = 20;
    const int FRUIT_SIZE = 50;

    // Vector containing buttons and their images
    struct ImagedButton
    {
        QPushButton* button;
        QPixmap image;
    };
    std::vector<ImagedButton> buttons_;

    // Label showing the chosen fruit
    QLabel* label_ = nullptr;

    // Draws fruits in labels and in buttons
    void draw_fruits();
};
#endif // MAINWINDOW_HH
