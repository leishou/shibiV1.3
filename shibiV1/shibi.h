#ifndef SHIBI_H
#define SHIBI_H

#include <QMainWindow>
#include <QDebug>
#include <Windows.h>
#include <Dwmapi.h>
#include"dwmapi.h"
#include <QPushButton>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include<QSlider>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include<QSpinBox>
#include<iostream>
#include<windows.h>
#include<QMessageBox>
#include<QPlainTextEdit>
#include<map>
#include<QTimer>
#include"noticewidget.h"

#include"frmlunarcalendarwidget.h"
#include"lunarcalendarinfo.h"
#include"lunarcalendaritem.h"
#include"lunarcalendarwidget.h"
#include <QApplication>
#include <QTextCodec>


#include"listdo.h"

#include"widget.h"

#include"mainwindow.h"

#include"login.h"
#include"share.h"
QT_BEGIN_NAMESPACE
namespace Ui { class shibi; }
QT_END_NAMESPACE
using namespace  std;
bool setSysVolume(int level);
int sysVolume();
class shibi : public QMainWindow
{
    Q_OBJECT

public:
    shibi(QWidget *parent = nullptr);
    ~shibi();
    void CreateSystemTrayIcon();
    void  init_used();
    int sysVolume();
    bool setSysVolume(int level);
    QMenu* trayMenu;
    QSystemTrayIcon* trayIcon;
    QSpinBox*tp;
    QSlider *pSlider;
    QSlider *pSliderValume;
    QTimer *pTimerListenVolume;
    QTimer*checkBusyT;


public slots:
    void checkBusy();
    void TrayIconAction(QSystemTrayIcon::ActivationReason reason);//对托盘图标操作的槽：本代码实现单机图标恢复窗口功能

private slots:
    void on_btn_log_clicked();

    void on_btn_lun_clicked();

    void on_btn_tod_clicked();

    void on_btn_clo_clicked();

    void on_btn_ing_clicked();

private:
    Ui::shibi *ui;
    QMessageBox*T_warning;
    QPlainTextEdit*WR_warning;
    map<string, bool>used;
    bool change_Busy =false;
    int Busy_Count=0;
    frmLunarCalendarWidget *w;//或许换指针
    ListDo  * todo;
    MainWindow* dow;
    Widget*bgm;
    login*log;
    bool isLog;
};
#endif // SHIBI_H
