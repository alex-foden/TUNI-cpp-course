#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    label_ = new QLabel("chosen\n  fruit", this);
    label_->setGeometry(MARGIN * 5 + FRUIT_SIZE * 4,
                        MARGIN * 5 + FRUIT_SIZE * 4,
                        FRUIT_SIZE, FRUIT_SIZE);
    draw_fruits();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handle_fruit_clicks()
{
    for (auto& imaged_button : buttons_)
    {
        if (imaged_button.button == sender())
        {
            label_->setPixmap(imaged_button.image);
            return; // For efficiency reasons
                    // (only one button can be clicked at a time)
        }
    }
}

void MainWindow::draw_fruits()
{
    // Vector of fruit names
    const std::vector<std::string>
            fruits = {"cherries", "strawberry", "orange", "pear", "apple",
                      "bananas", "tomato", "grapes", "eggplant"};

    // Defining where the images can be found and what kind of images they are
    const std::string PREFIX(":/");
    const std::string SUFFIX(".png");

    for(unsigned int i = 0; i < fruits.size(); ++i)
    {
        // Converting image (png) to a pixmap
        std::string filename = PREFIX + fruits.at(i) + SUFFIX;
        QPixmap image(QString::fromStdString(filename));

        // Scaling the pixmap
        image = image.scaled(FRUIT_SIZE, FRUIT_SIZE);

        // Setting the pixmap for a label
        QLabel* label = new QLabel("test", this);
        label->setGeometry(MARGIN + i * (FRUIT_SIZE + MARGIN),
                           MARGIN,
                           FRUIT_SIZE, FRUIT_SIZE);
        label->setPixmap(image);

        // Setting the pixmap for the icon of a push button
        QPushButton* button = new QPushButton(this);
        button->setGeometry(MARGIN + i * (FRUIT_SIZE + MARGIN),
                            MARGIN + FRUIT_SIZE + MARGIN,
                            FRUIT_SIZE, FRUIT_SIZE);
        button->setIcon(image);

        // Connecting all buttons to the same slot
        connect(button, &QPushButton::clicked,
                this, &MainWindow::handle_fruit_clicks);

        // Pushing the button and the image to the vector attribute
        ImagedButton imaged_button = {button, image};
        buttons_.push_back(imaged_button);
    }
}
