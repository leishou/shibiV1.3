#include "timerpagewidget.h"
#include "ui_timerpagewidget.h"
#include <QTime>
#include <QTimer>
#include <iostream>
#include <stdio.h>
#include <QTabWidget>
#include <cmath>
#include <QMessageBox>

using namespace std;

TimerPageWidget::TimerPageWidget(QTabWidget *parent, int idx) :
        QWidget(dynamic_cast<QWidget*>(parent)),
        ui(new Ui::TimerPageWidget),
        ticker(this),
        idx(idx)
{
    ui->setupUi(this);

    startButton = ui->startButton;
    stopButton = ui->stopButton;
    timeDisplay = ui->timeDisplay;
    timeDisplay->display("00:00:00");
    hourSpinBox = ui->hourSpinBox;
    minSpinBox = ui->minSpinBox;
    secSpinBox = ui->secSpinBox;

    // Attach Button Handlers
    connect(startButton, &QPushButton::clicked, this, &TimerPageWidget::startTimer);
    connect(stopButton, &QPushButton::clicked, this, &TimerPageWidget::stopTimer);
    // Call Stop upon changing tabs
    connect(parent, &QTabWidget::currentChanged, this, &TimerPageWidget::stopTimer);
    // Attach Tick Handler
    connect(&ticker, &QTimer::timeout, this, &TimerPageWidget::onTick);

}

TimerPageWidget::~TimerPageWidget()
{
    delete ui;
}

void TimerPageWidget::startTimer()
{

    totalSecs = 360 * hourSpinBox->value() + 60 * minSpinBox->value() + secSpinBox->value();
    if (clock.isNull() && totalSecs > 0) {
        //cout << "Starting!!!" << endl;
        clock = QTime::currentTime();
        clock.start();
        onTick();
        ticker.start(1000);
    }
}
void TimerPageWidget::stopTimer()
{
    //cout << "stopTimer()" << endl;
    if (!clock.isNull()) {
        //cout << "stopTimer() not null" << endl;
        //cout << "Stopping!!!" << endl;
        timeDisplay->display("00:00:00");
        clock = QTime();
        ticker.stop();
    } else {
        //cout << "NO" << endl;
    }
}

void TimerPageWidget::onTick()
{
    int el = clock.elapsed();
    int secsElapsed = static_cast<int>(round(el / 1000.0));
    int secsRemaining = totalSecs - secsElapsed;
    //printf("elapsed: %d, secsElapsed: %d, remaining: %d\n", el,secsElapsed,secsRemaining);
    if (secsRemaining <= 0) {
        //cout << "Timer Complete!!!" << endl;
        //cout << "Seconds = 0" <<  endl;
        stopTimer();
        notifyComplete();
    } else {
        int secs = secsRemaining % 60;
        int mins = (secsRemaining / 60) % 60;
        int hrs = secsRemaining / 3600;
        QString timeString = QString("%1:%2:%3")
                        .arg(hrs, 2, 10, QLatin1Char('0'))
                        .arg(mins,2, 10 ,QLatin1Char('0'))
                        .arg(secs,2, 10 ,QLatin1Char('0'));
        timeDisplay->display(timeString);
        //cout << "On tick: " << timeString.toStdString() << endl;
        //cout << endl;
    }
}
void TimerPageWidget::notifyComplete()
{
    //cout << "notifyComplete" << endl;
    QMessageBox::information(this, tr("Timer"), tr("Time's up!"), QMessageBox::Ok);
}
