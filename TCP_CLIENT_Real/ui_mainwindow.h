/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Thu Apr 15 15:20:09 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit_2;
    QLineEdit *insert;
    QLineEdit *UserName;
    QPushButton *Send;
    QPushButton *Connect;
    QLineEdit *IP_ADDRESS;
    QListWidget *list;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QMenuBar *menuBar;
    QMenu *menuECE469_TCP_Client;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(554, 512);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEnabled(false);
        lineEdit_2->setGeometry(QRect(180, 400, 151, 20));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        lineEdit_2->setFont(font);
        lineEdit_2->setFrame(false);
        lineEdit_2->setAlignment(Qt::AlignCenter);
        insert = new QLineEdit(centralWidget);
        insert->setObjectName(QString::fromUtf8("insert"));
        insert->setEnabled(false);
        insert->setGeometry(QRect(10, 359, 391, 21));
        insert->setAutoFillBackground(false);
        insert->setFrame(true);
        UserName = new QLineEdit(centralWidget);
        UserName->setObjectName(QString::fromUtf8("UserName"));
        UserName->setGeometry(QRect(20, 420, 113, 20));
        Send = new QPushButton(centralWidget);
        Send->setObjectName(QString::fromUtf8("Send"));
        Send->setEnabled(false);
        Send->setGeometry(QRect(400, 359, 141, 23));
        Connect = new QPushButton(centralWidget);
        Connect->setObjectName(QString::fromUtf8("Connect"));
        Connect->setGeometry(QRect(360, 420, 131, 23));
        IP_ADDRESS = new QLineEdit(centralWidget);
        IP_ADDRESS->setObjectName(QString::fromUtf8("IP_ADDRESS"));
        IP_ADDRESS->setGeometry(QRect(200, 420, 113, 20));
        list = new QListWidget(centralWidget);
        list->setObjectName(QString::fromUtf8("list"));
        list->setEnabled(false);
        list->setGeometry(QRect(10, 40, 531, 321));
        list->setFrameShadow(QFrame::Sunken);
        list->setLineWidth(5);
        list->setMidLineWidth(1);
        list->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        list->setAutoScroll(false);
        list->setDragDropMode(QAbstractItemView::DragOnly);
        list->setAlternatingRowColors(false);
        list->setSelectionMode(QAbstractItemView::NoSelection);
        list->setWordWrap(true);
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setEnabled(false);
        lineEdit_3->setGeometry(QRect(0, 400, 151, 20));
        lineEdit_3->setFont(font);
        lineEdit_3->setAutoFillBackground(false);
        lineEdit_3->setFrame(false);
        lineEdit_3->setAlignment(Qt::AlignCenter);
        lineEdit_4 = new QLineEdit(centralWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setEnabled(false);
        lineEdit_4->setGeometry(QRect(10, 10, 531, 20));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Bitstream Charter"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        lineEdit_4->setFont(font1);
        lineEdit_4->setFrame(false);
        lineEdit_4->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 554, 25));
        menuECE469_TCP_Client = new QMenu(menuBar);
        menuECE469_TCP_Client->setObjectName(QString::fromUtf8("menuECE469_TCP_Client"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuECE469_TCP_Client->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        lineEdit_2->setText(QApplication::translate("MainWindow", "Server IP Address", 0, QApplication::UnicodeUTF8));
        Send->setText(QApplication::translate("MainWindow", "Send", 0, QApplication::UnicodeUTF8));
        Send->setShortcut(QApplication::translate("MainWindow", "Return", 0, QApplication::UnicodeUTF8));
        Connect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        lineEdit_3->setText(QApplication::translate("MainWindow", "User Name", 0, QApplication::UnicodeUTF8));
        lineEdit_4->setText(QApplication::translate("MainWindow", "ECE469 TCP Client ", 0, QApplication::UnicodeUTF8));
        menuECE469_TCP_Client->setTitle(QApplication::translate("MainWindow", "ECE469 TCP Client", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
