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
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "glview.h"

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplicationClass
{
public:
    QWidget *centralWidget;
    GLview *openGLWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplicationClass)
    {
        if (QtWidgetsApplicationClass->objectName().isEmpty())
            QtWidgetsApplicationClass->setObjectName(QString::fromUtf8("QtWidgetsApplicationClass"));
        QtWidgetsApplicationClass->resize(1023, 840);
        centralWidget = new QWidget(QtWidgetsApplicationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new GLview(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(50, 40, 861, 711));
        QtWidgetsApplicationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtWidgetsApplicationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1023, 26));
        QtWidgetsApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplicationClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtWidgetsApplicationClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtWidgetsApplicationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtWidgetsApplicationClass->setStatusBar(statusBar);

        retranslateUi(QtWidgetsApplicationClass);

        QMetaObject::connectSlotsByName(QtWidgetsApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplicationClass)
    {
        QtWidgetsApplicationClass->setWindowTitle(QCoreApplication::translate("QtWidgetsApplicationClass", "QtWidgetsApplication", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplicationClass: public Ui_QtWidgetsApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION_H
