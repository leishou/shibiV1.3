/********************************************************************************
** Form generated from reading UI file 'listdo.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTDO_H
#define UI_LISTDO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListDo
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ListDo)
    {
        if (ListDo->objectName().isEmpty())
            ListDo->setObjectName(QString::fromUtf8("ListDo"));
        ListDo->resize(800, 600);
        centralwidget = new QWidget(ListDo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ListDo->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ListDo);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        ListDo->setMenuBar(menubar);
        statusbar = new QStatusBar(ListDo);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ListDo->setStatusBar(statusbar);

        retranslateUi(ListDo);

        QMetaObject::connectSlotsByName(ListDo);
    } // setupUi

    void retranslateUi(QMainWindow *ListDo)
    {
        ListDo->setWindowTitle(QCoreApplication::translate("ListDo", "ListDo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ListDo: public Ui_ListDo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTDO_H
