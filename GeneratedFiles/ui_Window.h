/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "file.h"

QT_BEGIN_NAMESPACE

class Ui_WindowClass
{
public:
    QAction *actionTo_leave_Ctrl_Q;
    QAction *actionInput_PAN_Image;
    QAction *actionInput_XS_Image;
    QAction *actionOutput_Image;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpinBox *spinBox_Blue;
    QSpinBox *spinBox_Green;
    QSpinBox *spinBox_Red;
    QSpinBox *spinBox_NIR;
    file *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu_Open_Image_Ctrl_O;
    QMenu *menuEdition;
    QMenu *menuView;
    QMenu *menuHelp;
    QMenu *menuSave;

    void setupUi(QMainWindow *WindowClass)
    {
        if (WindowClass->objectName().isEmpty())
            WindowClass->setObjectName(QStringLiteral("WindowClass"));
        WindowClass->resize(1048, 859);
        actionTo_leave_Ctrl_Q = new QAction(WindowClass);
        actionTo_leave_Ctrl_Q->setObjectName(QStringLiteral("actionTo_leave_Ctrl_Q"));
        actionInput_PAN_Image = new QAction(WindowClass);
        actionInput_PAN_Image->setObjectName(QStringLiteral("actionInput_PAN_Image"));
        actionInput_XS_Image = new QAction(WindowClass);
        actionInput_XS_Image->setObjectName(QStringLiteral("actionInput_XS_Image"));
        actionOutput_Image = new QAction(WindowClass);
        actionOutput_Image->setObjectName(QStringLiteral("actionOutput_Image"));
        centralWidget = new QWidget(WindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(560, 250, 141, 161));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 10, 51, 20));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 40, 61, 20));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 70, 71, 16));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 100, 71, 16));
        spinBox_Blue = new QSpinBox(tab);
        spinBox_Blue->setObjectName(QStringLiteral("spinBox_Blue"));
        spinBox_Blue->setGeometry(QRect(80, 10, 51, 22));
        spinBox_Blue->setMinimum(1);
        spinBox_Blue->setMaximum(4);
        spinBox_Green = new QSpinBox(tab);
        spinBox_Green->setObjectName(QStringLiteral("spinBox_Green"));
        spinBox_Green->setGeometry(QRect(80, 40, 51, 22));
        spinBox_Green->setMinimum(1);
        spinBox_Green->setMaximum(4);
        spinBox_Red = new QSpinBox(tab);
        spinBox_Red->setObjectName(QStringLiteral("spinBox_Red"));
        spinBox_Red->setGeometry(QRect(80, 70, 51, 22));
        spinBox_Red->setMinimum(1);
        spinBox_Red->setMaximum(4);
        spinBox_NIR = new QSpinBox(tab);
        spinBox_NIR->setObjectName(QStringLiteral("spinBox_NIR"));
        spinBox_NIR->setGeometry(QRect(80, 100, 51, 22));
        spinBox_NIR->setMinimum(1);
        spinBox_NIR->setMaximum(4);
        tabWidget->addTab(tab, QString());
        WindowClass->setCentralWidget(centralWidget);
        mainToolBar = new file(WindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WindowClass->addToolBar(Qt::LeftToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WindowClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(WindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1048, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menu_Open_Image_Ctrl_O = new QMenu(menuFile);
        menu_Open_Image_Ctrl_O->setObjectName(QStringLiteral("menu_Open_Image_Ctrl_O"));
        menuEdition = new QMenu(menuBar);
        menuEdition->setObjectName(QStringLiteral("menuEdition"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuSave = new QMenu(menuBar);
        menuSave->setObjectName(QStringLiteral("menuSave"));
        WindowClass->setMenuBar(menuBar);

        mainToolBar->addSeparator();
        mainToolBar->addSeparator();
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdition->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuSave->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(menu_Open_Image_Ctrl_O->menuAction());
        menuFile->addAction(actionTo_leave_Ctrl_Q);
        menu_Open_Image_Ctrl_O->addAction(actionInput_PAN_Image);
        menu_Open_Image_Ctrl_O->addAction(actionInput_XS_Image);
        menuSave->addAction(actionOutput_Image);

        retranslateUi(WindowClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowClass)
    {
        WindowClass->setWindowTitle(QApplication::translate("WindowClass", "Window", Q_NULLPTR));
        actionTo_leave_Ctrl_Q->setText(QApplication::translate("WindowClass", " Leave                      Ctrl+Q", Q_NULLPTR));
        actionInput_PAN_Image->setText(QApplication::translate("WindowClass", "Input PAN Image", Q_NULLPTR));
        actionInput_XS_Image->setText(QApplication::translate("WindowClass", "Input XS Image", Q_NULLPTR));
        actionOutput_Image->setText(QApplication::translate("WindowClass", "Output Image", Q_NULLPTR));
        label_3->setText(QApplication::translate("WindowClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#000000;\">Blue</span></p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("WindowClass", "<html><head/><body><p><span style=\" color:#000000;\">Green</span></p></body></html>", Q_NULLPTR));
        label_5->setText(QApplication::translate("WindowClass", "<html><head/><body><p><span style=\" color:#000000;\">Red</span></p></body></html>", Q_NULLPTR));
        label_6->setText(QApplication::translate("WindowClass", "<html><head/><body><p>NIR</p></body></html>", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("WindowClass", "Spectral Resolution", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("WindowClass", "File", Q_NULLPTR));
        menu_Open_Image_Ctrl_O->setTitle(QApplication::translate("WindowClass", " Open Image           Ctrl+O", Q_NULLPTR));
        menuEdition->setTitle(QApplication::translate("WindowClass", "Edition", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("WindowClass", "View", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("WindowClass", "Help", Q_NULLPTR));
        menuSave->setTitle(QApplication::translate("WindowClass", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WindowClass: public Ui_WindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
