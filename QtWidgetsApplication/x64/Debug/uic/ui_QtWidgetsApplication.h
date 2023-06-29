/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION_H
#define UI_QTWIDGETSAPPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glview.h"

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplicationClass
{
public:
    QAction *action;
    QAction *FileImport;
    QAction *Exit;
    QWidget *centralWidget;
    GLview *openGLWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplicationClass)
    {
        if (QtWidgetsApplicationClass->objectName().isEmpty())
            QtWidgetsApplicationClass->setObjectName(QString::fromUtf8("QtWidgetsApplicationClass"));
        QtWidgetsApplicationClass->resize(1023, 840);
        action = new QAction(QtWidgetsApplicationClass);
        action->setObjectName(QString::fromUtf8("action"));
        FileImport = new QAction(QtWidgetsApplicationClass);
        FileImport->setObjectName(QString::fromUtf8("FileImport"));
        Exit = new QAction(QtWidgetsApplicationClass);
        Exit->setObjectName(QString::fromUtf8("Exit"));
        centralWidget = new QWidget(QtWidgetsApplicationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new GLview(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(50, 40, 861, 711));
        QtWidgetsApplicationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtWidgetsApplicationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1023, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        QtWidgetsApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplicationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtWidgetsApplicationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtWidgetsApplicationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtWidgetsApplicationClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action);
        menu->addAction(FileImport);
        menu->addAction(Exit);

        retranslateUi(QtWidgetsApplicationClass);
        QObject::connect(Exit, SIGNAL(triggered()), QtWidgetsApplicationClass, SLOT(close()));

        QMetaObject::connectSlotsByName(QtWidgetsApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplicationClass)
    {
        QtWidgetsApplicationClass->setWindowTitle(QCoreApplication::translate("QtWidgetsApplicationClass", "QtWidgetsApplication", nullptr));
        action->setText(QCoreApplication::translate("QtWidgetsApplicationClass", "\346\211\223\345\274\200", nullptr));
        FileImport->setText(QCoreApplication::translate("QtWidgetsApplicationClass", "\345\257\274\345\205\245", nullptr));
        Exit->setText(QCoreApplication::translate("QtWidgetsApplicationClass", "\351\200\200\345\207\272", nullptr));
        menu->setTitle(QCoreApplication::translate("QtWidgetsApplicationClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplicationClass: public Ui_QtWidgetsApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION_H
