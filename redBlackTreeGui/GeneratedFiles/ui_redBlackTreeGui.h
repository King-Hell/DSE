/********************************************************************************
** Form generated from reading UI file 'redBlackTreeGui.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REDBLACKTREEGUI_H
#define UI_REDBLACKTREEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_redBlackTreeGuiClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *redBlackTreeGuiClass)
    {
        if (redBlackTreeGuiClass->objectName().isEmpty())
            redBlackTreeGuiClass->setObjectName(QStringLiteral("redBlackTreeGuiClass"));
        redBlackTreeGuiClass->resize(600, 400);
        centralWidget = new QWidget(redBlackTreeGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(250, 140, 75, 23));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(230, 220, 104, 71));
        redBlackTreeGuiClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(redBlackTreeGuiClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        redBlackTreeGuiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(redBlackTreeGuiClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        redBlackTreeGuiClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(redBlackTreeGuiClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        redBlackTreeGuiClass->setStatusBar(statusBar);

        retranslateUi(redBlackTreeGuiClass);

        QMetaObject::connectSlotsByName(redBlackTreeGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *redBlackTreeGuiClass)
    {
        redBlackTreeGuiClass->setWindowTitle(QApplication::translate("redBlackTreeGuiClass", "redBlackTreeGui", nullptr));
        pushButton->setText(QApplication::translate("redBlackTreeGuiClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class redBlackTreeGuiClass: public Ui_redBlackTreeGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDBLACKTREEGUI_H