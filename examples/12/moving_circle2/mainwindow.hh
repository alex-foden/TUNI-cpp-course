#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    // Moves the circle a small step to a desired direction
    void circle_move();

    // Obvious slots
    void on_moveButton_clicked();
    void on_verticalButton_pressed();
    void on_horizontalButton_pressed();
    void on_upRadioButton_toggled(bool checked);
    void on_downRadioButton_toggled(bool checked);
    void on_leftRadioButton_toggled(bool checked);
    void on_rightRadioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui_;

    QGraphicsScene* scene_;         // a surface for
    QGraphicsEllipseItem* circle_;  // drawing a circle

    QTimer timer_;                  // for continuous moving

    const int STEP = 20;            // how much to move at a time
    const int DURATION = 1000;      // how many milliseconds a move takes
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 260;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 680;


    bool is_right_;     // is_horizontal
    bool is_down_;      // is_vertical

    // Checks if moving is possible and turns the move button
    // either enabled or disabled
    void update_move_button();
};

#endif // MAINWINDOW_HH
