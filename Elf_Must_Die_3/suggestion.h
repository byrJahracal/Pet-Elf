#ifndef SUGGESTION_H
#define SUGGESTION_H

#include <QMainWindow>
#include "global.h"
#include <QFile>
#include <QTextStream>

namespace Ui {
class suggestion;
}

class suggestion : public QMainWindow//游戏说明窗口
{
    Q_OBJECT

public:
    explicit suggestion(QWidget *parent = 0);
    ~suggestion();
public slots:
    void OpenTexiao(bool f);//开特效
    void CloseTexiao(bool f);//关特效
private:
    Ui::suggestion *ui;
};

#endif // SUGGESTION_H
