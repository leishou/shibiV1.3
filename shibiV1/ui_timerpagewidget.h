/********************************************************************************
** Form generated from reading UI file 'timerpagewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMERPAGEWIDGET_H
#define UI_TIMERPAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimerPageWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QLCDNumber *timeDisplay;
    QHBoxLayout *horizontalLayout;
    QSpinBox *hourSpinBox;
    QSpinBox *minSpinBox;
    QSpinBox *secSpinBox;
    QVBoxLayout *verticalLayout_8;
    QPushButton *startButton;
    QPushButton *stopButton;

    void setupUi(QWidget *TimerPageWidget)
    {
        if (TimerPageWidget->objectName().isEmpty())
            TimerPageWidget->setObjectName(QString::fromUtf8("TimerPageWidget"));
        TimerPageWidget->resize(400, 300);
        verticalLayout_4 = new QVBoxLayout(TimerPageWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        timeDisplay = new QLCDNumber(TimerPageWidget);
        timeDisplay->setObjectName(QString::fromUtf8("timeDisplay"));
        timeDisplay->setDigitCount(8);
        timeDisplay->setMode(QLCDNumber::Hex);
        timeDisplay->setProperty("value", QVariant(0.000000000000000));

        verticalLayout_4->addWidget(timeDisplay);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        hourSpinBox = new QSpinBox(TimerPageWidget);
        hourSpinBox->setObjectName(QString::fromUtf8("hourSpinBox"));
        hourSpinBox->setMaximum(23);

        horizontalLayout->addWidget(hourSpinBox);

        minSpinBox = new QSpinBox(TimerPageWidget);
        minSpinBox->setObjectName(QString::fromUtf8("minSpinBox"));
        minSpinBox->setMaximum(59);

        horizontalLayout->addWidget(minSpinBox);

        secSpinBox = new QSpinBox(TimerPageWidget);
        secSpinBox->setObjectName(QString::fromUtf8("secSpinBox"));
        secSpinBox->setMaximum(59);

        horizontalLayout->addWidget(secSpinBox);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        startButton = new QPushButton(TimerPageWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout_8->addWidget(startButton);

        stopButton = new QPushButton(TimerPageWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout_8->addWidget(stopButton);


        horizontalLayout->addLayout(verticalLayout_8);


        verticalLayout_4->addLayout(horizontalLayout);


        retranslateUi(TimerPageWidget);

        QMetaObject::connectSlotsByName(TimerPageWidget);
    } // setupUi

    void retranslateUi(QWidget *TimerPageWidget)
    {
        TimerPageWidget->setWindowTitle(QCoreApplication::translate("TimerPageWidget", "Form", nullptr));
        hourSpinBox->setSuffix(QCoreApplication::translate("TimerPageWidget", " Hours", nullptr));
        minSpinBox->setSuffix(QCoreApplication::translate("TimerPageWidget", " Minutes", nullptr));
        secSpinBox->setSuffix(QCoreApplication::translate("TimerPageWidget", " Seconds", nullptr));
        startButton->setText(QCoreApplication::translate("TimerPageWidget", "Start Button", nullptr));
        stopButton->setText(QCoreApplication::translate("TimerPageWidget", "Stop Button", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimerPageWidget: public Ui_TimerPageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMERPAGEWIDGET_H
