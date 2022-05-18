#include "frmlunarcalendarwidget.h"
#include "ui_frmlunarcalendarwidget.h"

frmLunarCalendarWidget::frmLunarCalendarWidget(QWidget *parent) : QWidget(parent), ui(new Ui::frmLunarCalendarWidget)
{
    ui->setupUi(this);
}

frmLunarCalendarWidget::~frmLunarCalendarWidget()
{
    delete ui;
}
