#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <qpaintbox.h>
#include <QtMath>

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
    void onQTimer1();

private:
    Ui::MainWindow *ui;
    QTimer *QTimer1;
    QPaintBox *QPaintBox1;
};
#endif // MAINWINDOW_H
