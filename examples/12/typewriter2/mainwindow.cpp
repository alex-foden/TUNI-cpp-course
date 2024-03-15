#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_alphabets();
    init_numbers();
    init_text_browser();
    init_clear_button();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handle_clear_button_clicks()
{
    written_text_ = "";
    text_browser_->setText(written_text_);
}

void MainWindow::handle_character_clicks()
{
    for (auto& button : buttons_)
    {
        if (button == sender())
        {
            written_text_ += button->text();
            text_browser_->setText(written_text_);
            return; // For efficiency reasons
                    // (only one button can be clicked at a time)
        }
    }
}

void MainWindow::init_alphabets()
{
    // Grid layout for letter buttons
    QWidget* central = new QWidget(this);
    QGridLayout* gLayout = new QGridLayout(central);

    // Defining red brush and palette for letters
    QBrush brush(Qt::red);
    QPalette palette;
    palette.setBrush(QPalette::Button, brush);

    // Setting letter buttons in the grid layout and connecting all of
    // them to the same slot (no coordinates needed)
    for(char c = 'A'; c <= 'Z'; ++c)
    {
        QString letter = "";
        letter += c;
        QPushButton* pushButton = new QPushButton(letter, this);
        pushButton->setFixedWidth(NARROW_BUTTON_WIDTH);
        pushButton->setPalette(palette); // Setting colored palette

        buttons_.push_back(pushButton);
        // Using only a single row in the grid layout
        gLayout->addWidget(pushButton, 0, c - 'A');

        connect(pushButton, &QPushButton::clicked,
                this, &MainWindow::handle_character_clicks);
    }

    setCentralWidget(central);
}

void MainWindow::init_numbers()
{
    // Setting number buttons directly on Main Window without any layout and
    // connecting all of them to the same slot (specific coordinates required)
    for(char c = '0', i = 0; c <= '9'; ++c, ++i)
    {
        QString number = "";
        number += c;
        QPushButton* pushButton = new QPushButton(number, this);
        pushButton->setGeometry(2 * MARGIN + i * (NARROW_BUTTON_WIDTH + MARGIN),
                                MARGIN + VIEW_Y,
                                NARROW_BUTTON_WIDTH,
                                DEFAULT_BUTTON_HEIGTH);
        pushButton->setStyleSheet("background-color: blue"); // Setting color
        buttons_.push_back(pushButton);

        connect(pushButton, &QPushButton::clicked,
                this, &MainWindow::handle_character_clicks);
    }
}

void MainWindow::init_text_browser()
{
    text_browser_ = new QTextBrowser(this);
    text_browser_->setGeometry(MARGIN, MARGIN, DISPLAY_WIDTH, DISPLAY_HEIGTH);
}

void MainWindow::init_clear_button()
{
    clear_button_ = new QPushButton(this);
    clear_button_->setText("Clear");
    int width = clear_button_->width(); // We don't want to change width
    clear_button_->setGeometry(MARGIN,
                               MARGIN + DISPLAY_HEIGTH + MARGIN,
                               width,
                               DEFAULT_BUTTON_HEIGTH);
    clear_button_->setStyleSheet("color: green"); // Setting text color

    connect(clear_button_, SIGNAL(clicked()),
            this, SLOT(handle_clear_button_clicks()));
}
