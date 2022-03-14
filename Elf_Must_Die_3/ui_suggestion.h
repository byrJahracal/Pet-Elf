/********************************************************************************
** Form generated from reading UI file 'suggestion.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUGGESTION_H
#define UI_SUGGESTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_suggestion
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *suggestion)
    {
        if (suggestion->objectName().isEmpty())
            suggestion->setObjectName(QStringLiteral("suggestion"));
        suggestion->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font.setPointSize(16);
        suggestion->setFont(font);
        centralwidget = new QWidget(suggestion);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        horizontalLayout->addWidget(radioButton);

        radioButton_2 = new QRadioButton(centralwidget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        horizontalLayout->addWidget(radioButton_2);


        verticalLayout->addLayout(horizontalLayout);

        suggestion->setCentralWidget(centralwidget);
        menubar = new QMenuBar(suggestion);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 33));
        suggestion->setMenuBar(menubar);
        statusbar = new QStatusBar(suggestion);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        suggestion->setStatusBar(statusbar);

        retranslateUi(suggestion);

        QMetaObject::connectSlotsByName(suggestion);
    } // setupUi

    void retranslateUi(QMainWindow *suggestion)
    {
        suggestion->setWindowTitle(QApplication::translate("suggestion", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("suggestion", "\346\270\270\346\210\217\350\257\264\346\230\216", Q_NULLPTR));
        label_2->setText(QApplication::translate("suggestion", "\346\210\230\346\226\227\347\211\271\346\225\210\351\200\211\351\241\271", Q_NULLPTR));
        radioButton->setText(QApplication::translate("suggestion", "\345\274\200\345\220\257\346\210\230\346\226\227\347\211\271\346\225\210", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("suggestion", "\345\205\263\351\227\255\346\210\230\346\226\227\347\211\271\346\225\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class suggestion: public Ui_suggestion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUGGESTION_H
