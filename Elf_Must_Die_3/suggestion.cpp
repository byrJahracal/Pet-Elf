#include "suggestion.h"
#include "ui_suggestion.h"

suggestion::suggestion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::suggestion)//游戏说明及设置
{
    ui->setupUi(this);
    QFile inputFile("://说明.txt");
    inputFile.open(QIODevice::ReadOnly);
    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();
    ui->textBrowser->setText(line);
    /*开关特效的槽函数*/
    connect(ui->radioButton,SIGNAL(clicked(bool)),this,SLOT(OpenTexiao(bool)));
    connect(ui->radioButton_2,SIGNAL(clicked(bool)),this,SLOT(CloseTexiao(bool)));
}

suggestion::~suggestion()
{
    delete ui;
}

void suggestion::OpenTexiao(bool f)
{
    if(f)
        g_open_texiao=1;
}

void suggestion::CloseTexiao(bool f)
{
    if(f)
        g_open_texiao=0;
}
