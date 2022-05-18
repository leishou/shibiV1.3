/********************************************************************************
** Form generated from reading UI file 'stopwatchpagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOPWATCHPAGEWIDGET_H
#define UI_STOPWATCHPAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StopwatchPageWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLCDNumber *timeDisplay;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *startPauseButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *StopwatchPageWidget)
    {
        if (StopwatchPageWidget->objectName().isEmpty())
            StopwatchPageWidget->setObjectName(QString::fromUtf8("StopwatchPageWidget"));
        StopwatchPageWidget->resize(400, 300);
        verticalLayout = new QVBoxLayout(StopwatchPageWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        timeDisplay = new QLCDNumber(StopwatchPageWidget);
        timeDisplay->setObjectName(QString::fromUtf8("timeDisplay"));
        timeDisplay->setDigitCount(8);

        verticalLayout->addWidget(timeDisplay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        startPauseButton = new QPushButton(StopwatchPageWidget);
        startPauseButton->setObjectName(QString::fromUtf8("startPauseButton"));

        horizontalLayout->addWidget(startPauseButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        resetButton = new QPushButton(StopwatchPageWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        horizontalLayout->addWidget(resetButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(StopwatchPageWidget);

        QMetaObject::connectSlotsByName(StopwatchPageWidget);
    } // setupUi

    void retranslateUi(QWidget *StopwatchPageWidget)
    {
        StopwatchPageWidget->setWindowTitle(QCoreApplication::translate("StopwatchPageWidget", "Form", nullptr));
        startPauseButton->setText(QCoreApplication::translate("StopwatchPageWidget", "Start", nullptr));
        resetButton->setText(QCoreApplication::translate("StopwatchPageWidget", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StopwatchPageWidget: public Ui_StopwatchPageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOPWATCHPAGEWIDGET_H
