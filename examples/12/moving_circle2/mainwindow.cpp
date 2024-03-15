#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow), is_right_(false), is_down_(false)
{
    ui_->setupUi(this);

    // We need a graphics scene in which to draw a circle
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates:
    int left_margin = 10; // x coordinate
    int top_margin = 270; // y coordinate
    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui_->graphicsView->setGeometry(left_margin, top_margin,
                                   BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui_->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1,
    // because the circle is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Defining the color and outline of the circle
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(2);
    circle_ = scene_->addEllipse(0, 0, STEP, STEP, blackPen, redBrush);

    // Initial values for radio buttons and push buttons
    ui_->upRadioButton->setChecked(true);
    ui_->leftRadioButton->setChecked(true);

    ui_->verticalButton->setText("Set down");
    ui_->horizontalButton->setText("Set right");

    ui_->moveButton->setDisabled(true);

    // A non-singleshot timer fires every interval
    // (DURATION much milliseconds), which makes circle_move function
    // to be called until the timer is stopped
    timer_.setSingleShot(false);
    connect(&timer_, &QTimer::timeout, this, &MainWindow::circle_move);

    // Clearing the status label makes the text given in ui file to disappear
    ui_->statusLabel->clear();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    // changing the color of the circle between red and blue
    if(event->key() == Qt::Key_C) {
        if(circle_->brush().color() == Qt::red) {
            circle_->setBrush(QBrush(Qt::blue));
        } else {
            circle_->setBrush(QBrush(Qt::red));
        }
        ui_->statusLabel->setText("Color");
        return;
    }

    // moving the circle to south (down) by STEP
    if(event->key() == Qt::Key_S) {
        if(scene_->sceneRect().contains(circle_->x(), circle_->y() + STEP)) {
            circle_->moveBy(0, STEP);
            ui_->statusLabel->setText("South");
        }
        update_move_button();
        return;
    }

    // moving the circle to north (up) by STEP
    if(event->key() == Qt::Key_N) {
        if(scene_->sceneRect().contains(circle_->x(), circle_->y() - STEP)) {
            circle_->moveBy(0, -STEP);
            ui_->statusLabel->setText("North");
        }
        update_move_button();
        return;
    }
}

void MainWindow::circle_move()
{
    // Making the earlier text to disappear
    ui_->statusLabel->clear();

    // Current position of the circle
    qreal current_x = circle_->x();
    qreal current_y = circle_->y();

    //qDebug() << current_x << " and " << current_y;

    // Calculating the displacement that can be either
    // positive or negative, depending on the direction
    qreal deltaX, deltaY;
    if(is_right_) {
        deltaX = static_cast<qreal>(STEP);  // right (positive step)
    } else {
        deltaX = static_cast<qreal>(-STEP); // left (negative step)
    }
    if(is_down_) {
        deltaY = static_cast<qreal>(STEP);  // down (positive step)
    } else {
        deltaY = static_cast<qreal>(-STEP); // up (negative step)
    }

    // New position of the circle
    current_x += deltaX;
    current_y += deltaY;

    // If the new position is in the scene, the circle can be moved there
    // otherwise moving stops
    QRectF rect = scene_->sceneRect();
    if(rect.contains(current_x, current_y)) {
        circle_->moveBy(deltaX, deltaY);
        ui_->statusLabel->setText("Moving");
    } else {
        timer_.stop();
        ui_->moveButton->setDisabled(true);
        ui_->statusLabel->setText("Blocked");
    }
}

void MainWindow::update_move_button()
{
    // The circle is trying to move down, but it is already as down as possible
    if(is_down_ and circle_->y() == BORDER_DOWN) {
        ui_->moveButton->setEnabled(false);
        return;
    }

    // The circle is trying to move up, but it is already as up as possible
    if(!is_down_ and circle_->y() == BORDER_UP) {
        ui_->moveButton->setEnabled(false);
        return;
    }

    // The circle is trying to move right, but it is as right as possible
    if(is_right_ and circle_->x() == BORDER_RIGHT) {
        ui_->moveButton->setEnabled(false);
        return;
    }

    // The circle is trying to move left, but it is as left as possible
    if(!is_right_ and circle_->x() == BORDER_LEFT) {
        ui_->moveButton->setEnabled(false);
        return;
    }

    // Otherwise moving is enabled
    ui_->moveButton->setEnabled(true);
}

void MainWindow::on_moveButton_clicked()
{
    ui_->moveButton->setDisabled(true);
    timer_.start(DURATION);
}

// The rest of the functions handle push button presses
// and radio button togglings and keep them consistent
void MainWindow::on_verticalButton_pressed()
{
    is_down_ = !is_down_; // change vertical
    if(is_down_) {
        ui_->verticalButton->setText("Set up");
        ui_->downRadioButton->setChecked(true);
    } else {
        ui_->verticalButton->setText("Set down");
        ui_->upRadioButton->setChecked(true);
    }
    update_move_button();
}

void MainWindow::on_horizontalButton_pressed()
{
    is_right_ = !is_right_; // change horizontal
    if(is_right_) {
        ui_->horizontalButton->setText("Set left");
        ui_->rightRadioButton->setChecked(true);
    } else {
        ui_->horizontalButton->setText("Set right");
        ui_->leftRadioButton->setChecked(true);
    }
    update_move_button();
}

void MainWindow::on_upRadioButton_toggled(bool checked)
{
    ui_->upRadioButton->setChecked(checked);
    is_down_ = false;
    ui_->verticalButton->setText("Set down");
    update_move_button();
}

void MainWindow::on_downRadioButton_toggled(bool checked)
{
    ui_->downRadioButton->setChecked(checked);
    is_down_ = true;
    ui_->verticalButton->setText("Set up");
    update_move_button();
}

void MainWindow::on_leftRadioButton_toggled(bool checked)
{
    ui_->leftRadioButton->setChecked(checked);
    is_right_ = false;
    ui_->horizontalButton->setText("Set right");
    update_move_button();
}

void MainWindow::on_rightRadioButton_toggled(bool checked)
{
    ui_->rightRadioButton->setChecked(checked);
    is_right_ = true;
    ui_->horizontalButton->setText("Set left");
    update_move_button();
}
