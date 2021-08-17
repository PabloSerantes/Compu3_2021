#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer1 = new QTimer(this);
    QPaintBox1 = new QPaintBox(0, 0, ui->widget);
    connect(QTimer1, &QTimer::timeout, this, &MainWindow::onQTimer1);
    QTimer1->start(50);
    ui->lcdNumber->setStyleSheet("color: red;");
}

MainWindow::~MainWindow()
{
    delete QTimer1;
    delete QPaintBox1;
    delete ui;
}

void MainWindow::onQTimer1(){
    QDateTime dt;
    QPen pen;
    QBrush brush;
    QPainter paint(QPaintBox1 -> getCanvas());

    int w, h, r, hour, minute, second = 9, x, y;

    w = QPaintBox1 -> width();
    h = QPaintBox1 -> height();
    r = h/2;

    hour = dt.currentDateTime().time().hour();

    second = ((dt.currentDateTime().time().second()) * 6) + ((dt.currentDateTime().time().msec()) * 0.006);
    minute = ((dt.currentDateTime().time().minute()) * 6) + ((dt.currentDateTime().time().second()) * 0.08);

    if(hour > 12){
        hour = hour - 12;
    }
    if(hour == 0){
        hour = 12;
    }
    hour = ((hour * 100) + ((dt.currentDateTime().time().minute())*60)) / 20;

    ui->lcdNumber->display(dt.currentDateTime().toString("dd-MM-yyyy"));

    pen.setColor(Qt::blue);
    pen.setWidth(3);
    paint.setPen(pen);
    paint.drawEllipse(w/2 - r, h/2 - r, 2*r, 2*r);

    brush.setColor(Qt::white);
    brush.setStyle(Qt::SolidPattern);
    paint.setBrush(brush);
    paint.drawEllipse((w+3)/2 - r, (h+3)/2 - r, (2*r)-3, (2*r)-3);

    //hour
    x = qFloor((qCos((((hour * 6) * M_PI) / 180) - (M_PI / 2))) * (r - 90) + 0.5);
    y = qFloor((qSin((((hour * 6) * M_PI) / 180) - (M_PI / 2))) * (r - 90) + 0.5);
    pen.setWidth(5);
    paint.setPen(pen);
    paint.drawLine(w/2, r, (w/2) + x, r + y);

    //min
    x = qFloor((qCos(((minute * M_PI) / 180) - (M_PI / 2))) * (r - 30) + 0.5);
    y = qFloor((qSin(((minute * M_PI) / 180) - (M_PI / 2))) * (r - 30) + 0.5);
    pen.setColor(Qt::red);
    pen.setWidth(3);
    paint.setPen(pen);
    paint.drawLine(w/2, r, (w/2) + x, r + y);

    //sec
    x = qFloor((qCos(((second * M_PI) / 180) - (M_PI / 2))) * (r - 5) + 0.5);
    y = qFloor((qSin(((second * M_PI) / 180) - (M_PI / 2))) * (r - 5) + 0.5);
    pen.setColor(Qt::magenta);
    pen.setWidth(2);
    paint.setPen(pen);
    paint.drawLine(w/2, r, (w/2) + x, r + y);

    QPaintBox1 -> update();
}
