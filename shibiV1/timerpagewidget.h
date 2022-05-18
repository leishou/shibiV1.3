#ifndef TIMERPAGEWIDGET_H
#define TIMERPAGEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSpinBox>
#include <QTabWidget>
#include <QTime>
#include <QTimer>

namespace Ui {
class TimerPageWidget;
}

class TimerPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimerPageWidget(QTabWidget *parent = nullptr, int idx = 0);
    ~TimerPageWidget();

public slots:
    void startTimer();
    void stopTimer();
    void onTick();

private:
    Ui::TimerPageWidget *ui;
    QPushButton *startButton;
    QPushButton *stopButton;
    QLCDNumber *timeDisplay;
    QSpinBox *hourSpinBox;
    QSpinBox *minSpinBox;
    QSpinBox *secSpinBox;
    QTime clock;
    QTimer ticker;
    int totalSecs;
    int idx;
    void notifyComplete();
};

#endif // TIMERPAGEWIDGET_H
