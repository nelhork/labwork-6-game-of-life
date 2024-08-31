#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    model = new Model(50, 30);

    connect(ui->pushButtonPause, &QPushButton::clicked, this, [this]() {
        if (model->getCancelFlag()) {
            model->setCancelFlag(false);
        } else {
            model->setCancelFlag(true);
        }
    });

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateModel);
    timer->start(100);

    updateModel();
}

void MainWindow::updateScene()
{
    scene->clear();
    for (int y = 0; y < model->getHeight(); y++) {
        for (int x = 0; x < model->getWidth(); x++) {
            if (model->isAlive(x, y)) {
                scene->addRect(x * 10, y * 10, 10, 10, QPen(Qt::black), QBrush(Qt::red));
            } else {
                scene->addRect(x * 10, y * 10, 10, 10, QPen(Qt::black), QBrush(Qt::white));
            }
        }
    }
}

void MainWindow::updateModel() {
    model->update();
    updateScene();
}


MainWindow::~MainWindow()
{
    delete ui;
}
