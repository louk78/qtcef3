/********************************************************************************
** Form generated from reading UI file 'qtcef3.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTCEF3_H
#define UI_QTCEF3_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtcef3Class
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtcef3Class)
    {
        if (qtcef3Class->objectName().isEmpty())
            qtcef3Class->setObjectName(QStringLiteral("qtcef3Class"));
        qtcef3Class->resize(600, 400);
        centralWidget = new QWidget(qtcef3Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qtcef3Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qtcef3Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtcef3Class->setStatusBar(statusBar);

        retranslateUi(qtcef3Class);

        QMetaObject::connectSlotsByName(qtcef3Class);
    } // setupUi

    void retranslateUi(QMainWindow *qtcef3Class)
    {
        qtcef3Class->setWindowTitle(QApplication::translate("qtcef3Class", "qtcef3", 0));
    } // retranslateUi

};

namespace Ui {
    class qtcef3Class: public Ui_qtcef3Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTCEF3_H
