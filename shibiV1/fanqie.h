#ifndef FANQIE_H
#define FANQIE_H

#include <QWidget>
#include <QDialog>
#include <QLCDNumber>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtGui>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class fanqie; }
QT_END_NAMESPACE

class fanqie : public QWidget
{
    Q_OBJECT

public:
    fanqie(QWidget *parent = nullptr);
    ~fanqie();

private:
    Ui::fanqie *ui;
public slots:
    void onTimeout();
    void clickOnButton();
private:
    QLCDNumber *lcd;
    QTimer *timer;
    int minute=25,second=0;
    QVBoxLayout *layout;
    QPushButton *startbutton;
};
#endif // FANQIE_H
