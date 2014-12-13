#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <QWSServer> //used by setCursorVisible()
#include <QPointF>
#include <math.h>
#define PERI 20

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint); //hide title bar
    QWSServer::setCursorVisible(false); //hide cursor

    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
    timer->start(PERI);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::timerUpDate()
{
    int fd;
    char buf[MAX_BUF];
    char ch[10];
    float x;

    QString tmp="";

    snprintf(buf,sizeof(buf),SYSFS_TEMP"/temp0_input");
    fd = open(buf, O_RDONLY);
    read(fd,ch,10);
    x=atoi(ch);
    tmp.sprintf("%f",x / 10);
    ui->lineEdit->setText(tmp);

    ::close(fd);

    update();
}

void MainWindow::on_pushButton_clicked()
{
    QApplication* app;
    app->quit();
}
