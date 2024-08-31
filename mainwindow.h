#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateScene();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Model *model;

private slots:
    void updateModel();

signals:
    void modelUpdated();
};
#endif // MAINWINDOW_H
