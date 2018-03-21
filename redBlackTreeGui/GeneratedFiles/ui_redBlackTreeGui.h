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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_redBlackTreeGuiClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QPushButton *buttonInsert;
    QPushButton *buttonDelete;
    QPushButton *buttonInitialize;
    QLineEdit *lineEdit;
    QLabel *label;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QGraphicsView *graphicsView;

    void setupUi(QMainWindow *redBlackTreeGuiClass)
    {
        if (redBlackTreeGuiClass->objectName().isEmpty())
            redBlackTreeGuiClass->setObjectName(QStringLiteral("redBlackTreeGuiClass"));
        redBlackTreeGuiClass->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(redBlackTreeGuiClass->sizePolicy().hasHeightForWidth());
        redBlackTreeGuiClass->setSizePolicy(sizePolicy);
        redBlackTreeGuiClass->setMinimumSize(QSize(800, 600));
        redBlackTreeGuiClass->setBaseSize(QSize(800, 600));
        centralWidget = new QWidget(redBlackTreeGuiClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 100));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        buttonInsert = new QPushButton(groupBox);
        buttonInsert->setObjectName(QStringLiteral("buttonInsert"));
        buttonInsert->setGeometry(QRect(160, 40, 91, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonInsert->sizePolicy().hasHeightForWidth());
        buttonInsert->setSizePolicy(sizePolicy1);
        buttonDelete = new QPushButton(groupBox);
        buttonDelete->setObjectName(QStringLiteral("buttonDelete"));
        buttonDelete->setGeometry(QRect(280, 40, 91, 51));
        sizePolicy1.setHeightForWidth(buttonDelete->sizePolicy().hasHeightForWidth());
        buttonDelete->setSizePolicy(sizePolicy1);
        buttonInitialize = new QPushButton(groupBox);
        buttonInitialize->setObjectName(QStringLiteral("buttonInitialize"));
        buttonInitialize->setGeometry(QRect(400, 40, 91, 51));
        sizePolicy1.setHeightForWidth(buttonInitialize->sizePolicy().hasHeightForWidth());
        buttonInitialize->setSizePolicy(sizePolicy1);
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 40, 113, 51));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(510, 0, 291, 20));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);
        label->setTextFormat(Qt::AutoText);
        label->setWordWrap(false);
        label->setMargin(0);

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setFont(font);
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        graphicsView = new QGraphicsView(groupBox_2);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(graphicsView, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        redBlackTreeGuiClass->setCentralWidget(centralWidget);

        retranslateUi(redBlackTreeGuiClass);
        QObject::connect(buttonInitialize, SIGNAL(clicked()), redBlackTreeGuiClass, SLOT(clear()));
        QObject::connect(buttonDelete, SIGNAL(clicked()), redBlackTreeGuiClass, SLOT(erase()));
        QObject::connect(buttonInsert, SIGNAL(clicked()), redBlackTreeGuiClass, SLOT(insert()));

        QMetaObject::connectSlotsByName(redBlackTreeGuiClass);
    } // setupUi

    void retranslateUi(QMainWindow *redBlackTreeGuiClass)
    {
        redBlackTreeGuiClass->setWindowTitle(QApplication::translate("redBlackTreeGuiClass", "\347\272\242\351\273\221\346\240\221\345\233\276\345\275\242\346\274\224\347\244\272", nullptr));
        groupBox->setTitle(QApplication::translate("redBlackTreeGuiClass", "\350\256\276\347\275\256", nullptr));
        buttonInsert->setText(QApplication::translate("redBlackTreeGuiClass", "\346\217\222\345\205\245", nullptr));
        buttonDelete->setText(QApplication::translate("redBlackTreeGuiClass", "\345\210\240\351\231\244", nullptr));
        buttonInitialize->setText(QApplication::translate("redBlackTreeGuiClass", "\345\210\235\345\247\213\345\214\226", nullptr));
        lineEdit->setInputMask(QString());
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QString());
        label->setText(QApplication::translate("redBlackTreeGuiClass", "Copyright \302\251 2018 LiTong. All Rights Reserved.", nullptr));
        groupBox_2->setTitle(QApplication::translate("redBlackTreeGuiClass", "\347\273\230\345\233\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class redBlackTreeGuiClass: public Ui_redBlackTreeGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REDBLACKTREEGUI_H
