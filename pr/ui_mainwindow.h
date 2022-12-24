/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionSave_Project;
    QAction *actionPrint;
    QAction *actionQuit;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionAbout;
    QAction *actionAbout_QT;
    QAction *actionDelete_Item;
    QAction *actionBring_To_Front;
    QAction *actionSend_Item_To_Back;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTool_bars;
    QMenu *menuAbout;
    QMenu *menuDock_Widgets;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(400, 200));
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName("actionNew_Project");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/New_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Project->setIcon(icon);
        actionOpen_Project = new QAction(MainWindow);
        actionOpen_Project->setObjectName("actionOpen_Project");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/Open_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Project->setIcon(icon1);
        actionSave_Project = new QAction(MainWindow);
        actionSave_Project->setObjectName("actionSave_Project");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/Save_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project->setIcon(icon2);
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/Print_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrint->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/Exit_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Icons/Cut_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon5);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Icons/Copy_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon6);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Icons/Paste_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon7);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        actionAbout_QT = new QAction(MainWindow);
        actionAbout_QT->setObjectName("actionAbout_QT");
        actionDelete_Item = new QAction(MainWindow);
        actionDelete_Item->setObjectName("actionDelete_Item");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Icons/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_Item->setIcon(icon8);
        actionBring_To_Front = new QAction(MainWindow);
        actionBring_To_Front->setObjectName("actionBring_To_Front");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/Icons/bringtofront.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionBring_To_Front->setIcon(icon9);
        actionSend_Item_To_Back = new QAction(MainWindow);
        actionSend_Item_To_Back->setObjectName("actionSend_Item_To_Back");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/Icons/sendtoback.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionSend_Item_To_Back->setIcon(icon10);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuTool_bars = new QMenu(menubar);
        menuTool_bars->setObjectName("menuTool_bars");
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName("menuAbout");
        menuDock_Widgets = new QMenu(menubar);
        menuDock_Widgets->setObjectName("menuDock_Widgets");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuTool_bars->menuAction());
        menubar->addAction(menuDock_Widgets->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project);
        menuFile->addAction(actionPrint);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuAbout->addAction(actionAbout);
        menuAbout->addAction(actionAbout_QT);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Presentation Maker", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("MainWindow", "New Project", nullptr));
#if QT_CONFIG(statustip)
        actionNew_Project->setStatusTip(QCoreApplication::translate("MainWindow", "Create new project", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionNew_Project->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_Project->setText(QCoreApplication::translate("MainWindow", "Open Project", nullptr));
#if QT_CONFIG(statustip)
        actionOpen_Project->setStatusTip(QCoreApplication::translate("MainWindow", "Open an existing file", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionOpen_Project->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Project->setText(QCoreApplication::translate("MainWindow", "Save Project", nullptr));
#if QT_CONFIG(statustip)
        actionSave_Project->setStatusTip(QCoreApplication::translate("MainWindow", "Save the project to disk", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionSave_Project->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
#if QT_CONFIG(statustip)
        actionPrint->setStatusTip(QCoreApplication::translate("MainWindow", "Print", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionPrint->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(statustip)
        actionQuit->setStatusTip(QCoreApplication::translate("MainWindow", "Quit the application", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
#if QT_CONFIG(statustip)
        actionCut->setStatusTip(QCoreApplication::translate("MainWindow", "Cut the current selection's contents to the clipboard", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
#if QT_CONFIG(statustip)
        actionCopy->setStatusTip(QCoreApplication::translate("MainWindow", "Copy the current selection's contents to the clipboard", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Past", nullptr));
#if QT_CONFIG(statustip)
        actionPaste->setStatusTip(QCoreApplication::translate("MainWindow", "Paste the clipboard's contents into the current selection", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(statustip)
        actionAbout->setStatusTip(QCoreApplication::translate("MainWindow", "Show the application's About box", nullptr));
#endif // QT_CONFIG(statustip)
        actionAbout_QT->setText(QCoreApplication::translate("MainWindow", "About QT", nullptr));
#if QT_CONFIG(statustip)
        actionAbout_QT->setStatusTip(QCoreApplication::translate("MainWindow", "Show the Qt library's About box", nullptr));
#endif // QT_CONFIG(statustip)
        actionDelete_Item->setText(QCoreApplication::translate("MainWindow", "Delete Item", nullptr));
#if QT_CONFIG(statustip)
        actionDelete_Item->setStatusTip(QCoreApplication::translate("MainWindow", "Delete item from diagram", nullptr));
#endif // QT_CONFIG(statustip)
#if QT_CONFIG(shortcut)
        actionDelete_Item->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBring_To_Front->setText(QCoreApplication::translate("MainWindow", "Bring To Front", nullptr));
#if QT_CONFIG(statustip)
        actionBring_To_Front->setStatusTip(QCoreApplication::translate("MainWindow", "Bring item to front", nullptr));
#endif // QT_CONFIG(statustip)
        actionSend_Item_To_Back->setText(QCoreApplication::translate("MainWindow", "Send Item To Back", nullptr));
#if QT_CONFIG(statustip)
        actionSend_Item_To_Back->setStatusTip(QCoreApplication::translate("MainWindow", "Send item to back", nullptr));
#endif // QT_CONFIG(statustip)
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuTool_bars->setTitle(QCoreApplication::translate("MainWindow", "Tool bars", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "About", nullptr));
        menuDock_Widgets->setTitle(QCoreApplication::translate("MainWindow", "Dock Widgets", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
