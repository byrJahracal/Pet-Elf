#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Mythread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QTcpSocket tcp_socket;

private:
    Ui::MainWindow *ui;

public slots:
    void OpenThread();//新的用户连接，打开新的线程
};

#endif // MAINWINDOW_H
