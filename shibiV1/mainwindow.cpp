#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timerpagewidget.h"
#include "stopwatchpagewidget.h"
#include <QtWidgets>


using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tabWidget = ui->tabWidget;
    tabWidget->setFocusPolicy(Qt::NoFocus);
    timerTabPage = new TimerPageWidget(tabWidget);
    stopwatchTabPage = new StopwatchPageWidget(tabWidget);
    clockTabPage = new fanqie(this);
    alarmTabPage = new QWidget(this);

    tabWidget->addTab(timerTabPage,"Timer");
    tabWidget->addTab(stopwatchTabPage,"Stopwatch");
    tabWidget->addTab(clockTabPage,"Clock");
    tabWidget->addTab(alarmTabPage,"Alarm");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timerTabPage;
    delete clockTabPage;
    delete stopwatchTabPage;
    delete alarmTabPage;
}

