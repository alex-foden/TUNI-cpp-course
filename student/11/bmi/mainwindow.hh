#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>

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
    void on_weightLineEdit_textChanged(const QString &weight);

    void on_heightLineEdit_textChanged(const QString &height);

    void on_countButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::MainWindow *ui;
    double Calculate_BMI(double weight, double height);

    double weight_;
    double height_;
};
#endif // MAINWINDOW_HH
