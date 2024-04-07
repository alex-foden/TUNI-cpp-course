#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onColorChanged();

    void on_horizontalSliderRed_valueChanged(int value);

    void on_spinBoxRed_valueChanged(int value);

    void on_horizontalSliderGreen_valueChanged(int value);

    void on_spinBoxGreen_valueChanged(int value);

    void on_horizontalSliderBlue_valueChanged(int value);

    void on_spinBoxBlue_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    const int RGB_VALUE_MAX = 255;
};

#endif // MAINWINDOW_HH
