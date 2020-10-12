#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "guandangamespace.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setGuanDanGamespace();     //创建游戏空间

private:

    Ui::MainWindow *ui;
    guanDanGamespace* gamespace;    //掼蛋游戏空间

};

#endif // MAINWINDOW_H
