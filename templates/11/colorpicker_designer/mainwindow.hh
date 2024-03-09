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

private:
    Ui::MainWindow *ui;

    const int RGB_VALUE_MAX = 255;
};

#endif // MAINWINDOW_HH
