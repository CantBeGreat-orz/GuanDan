#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置主窗口
    setFixedSize(WINWIDTH,WINHEIGHT);                                        //固定窗口大小
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);   //禁用最大化按钮
    //创建掼蛋游戏空间
    setGuanDanGamespace();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGuanDanGamespace()
{
    gamespace= new guanDanGamespace(this);
}
