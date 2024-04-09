#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <gradecalculator.hh>

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
    void on_spinBoxN_valueChanged(int N_points);

    void on_spinBoxG_valueChanged(int G_points);

    void on_spinBoxP_valueChanged(int P_points);

    void on_spinBoxE_valueChanged(int exam_grade);

    void on_calculatePushButton_clicked();

private:
    Ui::MainWindow *ui;
    int N_points_ = 0;
    int G_points_ = 0;
    int P_points_ = 0;
    int exam_grade_ = 0;
    QString W_grade_;
    QString P_grade_;
    QString total_grade_;
};
#endif // MAINWINDOW_HH
