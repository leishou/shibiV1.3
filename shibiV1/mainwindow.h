#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"fanqie.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QWidget *timerTabPage;
    QWidget *clockTabPage;
    QWidget *stopwatchTabPage;
    QWidget *alarmTabPage;
};

#endif // MAINWINDOW_H
