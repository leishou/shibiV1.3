#ifndef FRMLUNARCALENDARWIDGET_H
#define FRMLUNARCALENDARWIDGET_H

#include <QWidget>

namespace Ui
{
class frmLunarCalendarWidget;
}

class frmLunarCalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frmLunarCalendarWidget(QWidget *parent = 0);
    ~frmLunarCalendarWidget();

private:
    Ui::frmLunarCalendarWidget *ui;
};

#endif // FRMLUNARCALENDARWIDGET_H
