#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::JiaSpeed()//加速战斗
{
    my_timer->stop();
    if(speed<=475){
        speed+=25;
        speed_fight=speed;
    }
    my_timer->start(5000/speed);
}

void MainWindow::JianSpeed()//减慢战斗
{
    my_timer->stop();
    if(speed>=30){
        speed-=25;
        speed_fight=speed;
    }
    my_timer->start(5000/speed);
}

void MainWindow::InitSpeed()//初始化速度
{
    my_timer->stop();
    speed=20;
    my_timer->start(5000/speed);
}

void MainWindow::SetSpeed()//切换到战斗界面设置速度
{
    my_timer->stop();
    speed=speed_fight;
    my_timer->start(5000/speed);
}


