#include "stopwatchpagewidget.h"
#include "ui_stopwatchpagewidget.h"
#include <QTime>
#include <iostream>
#include <cmath>

using namespace std;

StopwatchPageWidget::StopwatchPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StopwatchPageWidget),
    ticker(this),
    swState(stopped)
{
    ui->setupUi(this);
    startPauseButton = ui->startPauseButton;
    resetButton = ui->resetButton;
    timeDisplay = ui->timeDisplay;
    timeDisplay->display("00:00:00");

    //time = QTime(0,0,0,0);
    //cout << "Time: " << clock.toString("HH:mm:ss").toStdString() << endl;
    connect(startPauseButton, &QPushButton::clicked,this,&StopwatchPageWidget::startPauseSW);
    connect(&ticker, &QTimer::timeout, this, &StopwatchPageWidget::onTick);
    connect(resetButton, &QPushButton::clicked, this, &StopwatchPageWidget::resetSW);
}

StopwatchPageWidget::~StopwatchPageWidget()
{
    delete ui;
}

void StopwatchPageWidget::startPauseSW()
{
    if (swState == stopped) {
        swState = started;
        clock = QTime(0,0,0,0);
        clock.start();
        ticker.start(1000);
        ui->startPauseButton->setText("Pause");
    } else if (swState == paused)
    {
        swState = started;
        clock.start();
        clock = clock.addMSecs(-1000 * (pausedMS / 1000));
        ticker.start(1000);
        ui->startPauseButton->setText("Pause");
        //cout << "pausedMS: " << pausedMS << endl;
        //cout << "pausedMS: " << (pausedMS / 1000) * 1000 << endl;
        //int secsElapsed = static_cast<int>(round(clock.elapsed() / 1000.0));
    } else if (swState == started)
    {
        swState = paused;
        pausedMS = clock.elapsed();
        clock = QTime(0,0,0);
        ticker.stop();
        ui->startPauseButton->setText("Start");
    }
}
void StopwatchPageWidget::resetSW()
{
    swState = stopped;
    //cout << "resetSW" << endl;
    clock = QTime();
    timeDisplay->display("00:00:00");
    ticker.stop();
    ui->startPauseButton->setText("Start");
}
void StopwatchPageWidget::onTick()
{
    //cout << "onTick()" << endl;
    int secsElapsed = static_cast<int>(round(clock.elapsed() / 1000.0));

    int secs = secsElapsed % 60;
    int mins = (secsElapsed / 60) % 60;
    int hrs = secsElapsed / 3600;
    QString timeString = QString("%1:%2:%3")
                    .arg(hrs, 2, 10, QLatin1Char('0'))
                    .arg(mins,2, 10 ,QLatin1Char('0'))
                    .arg(secs,2, 10 ,QLatin1Char('0'));
    timeDisplay->display(timeString);

}
