#ifndef STOPWATCHPAGEWIDGET_H
#define STOPWATCHPAGEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QLCDNumber>

namespace Ui {
class StopwatchPageWidget;
}

enum Stopwatch_State { stopped, started, paused };

class StopwatchPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StopwatchPageWidget(QWidget *parent = nullptr);
    ~StopwatchPageWidget();
public slots:
    void onTick();
    void startPauseSW();
    void resetSW();

private:
    Ui::StopwatchPageWidget *ui;
    QPushButton *startPauseButton;
    QPushButton *resetButton;
    QLCDNumber *timeDisplay;
    QTime clock;
    QTimer ticker;
    Stopwatch_State swState;
    int pausedMS;

};

#endif // STOPWATCHPAGEWIDGET_H
