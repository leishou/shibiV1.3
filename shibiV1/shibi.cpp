#include "shibi.h"
#include "ui_shibi.h"
int nMin = 0;
int nMax = 100;
int nSingleStep = 1;
shibi::shibi(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::shibi)
{
    ui->setupUi(this);
    isLog=false;
    w =new frmLunarCalendarWidget;
    todo =new ListDo;
    dow =new MainWindow;
    bgm = new Widget;
    log =new login;
    ui->stackedWidget->addWidget(w);
    ui->stackedWidget->addWidget(todo);
    ui->stackedWidget->addWidget(dow);
    ui->stackedWidget_2->addWidget(bgm);
    ui->stackedWidget->addWidget(log);
    ui->stackedWidget->setCurrentIndex(3);
    ui->stackedWidget_2->setCurrentIndex(0);
    WR_warning=new QPlainTextEdit();
    WR_warning->setPlainText("勿扰模式结束！请继续保持");

    checkBusyT=new QTimer();
    checkBusyT->setTimerType(Qt::PreciseTimer);
    setWindowFlags(Qt::Tool);
    CreateSystemTrayIcon();    //创建托盘
}

shibi::~shibi()
{
    delete ui;
}

void shibi::CreateSystemTrayIcon()
{
    //初始化两个项目
        QAction* showAction = new QAction(QStringLiteral("显示"));//项1
        QAction* exitAction = new QAction(QStringLiteral("退出"));//项2
        //项1的点击槽函数
        connect(showAction, &QAction::triggered, this, [=]()
        {
            this->show();
        });
        //项2的点击槽函数
        connect(exitAction , &QAction::triggered, this, [=]()
        {
            qDebug()<<"exit";
            QApplication::exit(0);
        });
        //初始化菜单并添加项
//           QMenu* trayMenu = new QMenu(this);//菜单
            trayMenu = new QMenu(this);//菜单
           trayMenu->addAction(showAction);
           trayMenu->addAction(exitAction );

           //创建一个系统托盘
//           QSystemTrayIcon* trayIcon = new QSystemTrayIcon(this);
           trayIcon = new QSystemTrayIcon(this);
//           trayIcon->setIcon(QIcon("C:\\Users\\15818\\Desktop\\ce.ico"));
           trayIcon->setIcon(QIcon(":/title.ico")); //设置托盘图标
           trayIcon->setContextMenu(trayMenu);                                     //设置菜单
           trayIcon->show();
           QObject::connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(TrayIconAction(QSystemTrayIcon::ActivationReason)));//连接信号与槽，实现单击图标恢复窗口的功能，槽是自定义的槽
}

void shibi::init_used()
{
    auto hwnd = GetDesktopWindow();
        //获取桌面子窗口句柄
        hwnd = GetWindow(hwnd, GW_CHILD);

        auto counter = 0;
        while (hwnd != NULL)
        {
            RECT rect;
            //获取窗口大小
            DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));
            //获取窗口名
            char name[255];
            GetWindowTextA(hwnd, name, 255);

            if (!std::string(name).empty())
            {
//                std::string::size_type idx;
                auto iterator_find = used.find(string(name));
                if (iterator_find == used.end())
                {
                    used.insert(pair <string, bool>(string(name), true));
                }
            }
            hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);

        }
        return ;
}

int shibi::sysVolume()
{
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator=0;
    IMMDevice* pDevice=0;
    IAudioEndpointVolume* pAudioEndpointVolume=0;
    IAudioClient* pAudioClient=0;

    try{
        hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_ALL,__uuidof(IMMDeviceEnumerator),(void**)&pDeviceEnumerator);
        if(FAILED(hr)) throw "CoCreateInstance";
        hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender,eMultimedia,&pDevice);
        if(FAILED(hr)) throw "GetDefaultAudioEndpoint";
        hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_ALL,NULL,(void**)&pAudioEndpointVolume);
        if(FAILED(hr)) throw "pDevice->Active";
        hr = pDevice->Activate(__uuidof(IAudioClient),CLSCTX_ALL,NULL,(void**)&pAudioClient);
        if(FAILED(hr)) throw "pDevice->Active";

        float fVolume;

        hr = pAudioEndpointVolume->GetMasterVolumeLevelScalar(&fVolume);

        if(FAILED(hr)) throw "SetMasterVolumeLevelScalar";

        pAudioClient->Release();
        pAudioEndpointVolume->Release();
        pDevice->Release();
        pDeviceEnumerator->Release();

        int  intVolume = fVolume*100+1;
        if(fVolume>100)
        {
            fVolume =100;
        }
        return intVolume;

    }

    catch(...){
        if(pAudioClient) pAudioClient->Release();
        if(pAudioEndpointVolume) pAudioEndpointVolume->Release();
        if(pDevice) pDevice->Release();
        if(pDeviceEnumerator) pDeviceEnumerator->Release();
        throw;
    }
}

bool shibi::setSysVolume(int level)
{
    HRESULT hr;
    IMMDeviceEnumerator* pDeviceEnumerator=0;
    IMMDevice* pDevice=0;
    IAudioEndpointVolume* pAudioEndpointVolume=0;
    IAudioClient* pAudioClient=0;

    try{
      hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),NULL,CLSCTX_ALL,__uuidof(IMMDeviceEnumerator),(void**)&pDeviceEnumerator);
      if(FAILED(hr)) throw "CoCreateInstance";
      hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender,eMultimedia,&pDevice);
      if(FAILED(hr)) throw "GetDefaultAudioEndpoint";
      hr = pDevice->Activate(__uuidof(IAudioEndpointVolume),CLSCTX_ALL,NULL,(void**)&pAudioEndpointVolume);
      if(FAILED(hr)) throw "pDevice->Active";
      hr = pDevice->Activate(__uuidof(IAudioClient),CLSCTX_ALL,NULL,(void**)&pAudioClient);
      if(FAILED(hr)) throw "pDevice->Active";

      if(level==-2){
        hr = pAudioEndpointVolume->SetMute(FALSE,NULL);
        if(FAILED(hr)) throw "SetMute";
      }else if(level==-1){
        hr = pAudioEndpointVolume->SetMute(TRUE,NULL);
        if(FAILED(hr)) throw "SetMute";
      }else{
        if(level<0 || level>100){
          hr = E_INVALIDARG;
          throw "Invalid Arg";
        }

        float fVolume;
        fVolume = level/100.0f;
        hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume,&GUID_NULL);
        if(FAILED(hr)) throw "SetMasterVolumeLevelScalar";

        pAudioClient->Release();
        pAudioEndpointVolume->Release();
        pDevice->Release();
        pDeviceEnumerator->Release();
        return true;
      }
    }
    catch(...){
      if(pAudioClient) pAudioClient->Release();
      if(pAudioEndpointVolume) pAudioEndpointVolume->Release();
      if(pDevice) pDevice->Release();
      if(pDeviceEnumerator) pDeviceEnumerator->Release();
      throw;
    }
    return false;
}

void shibi::checkBusy()
{
    //获取桌面句柄
        auto hwnd = GetDesktopWindow();
        //获取桌面子窗口句柄
        hwnd = GetWindow(hwnd, GW_CHILD);


        while (hwnd != NULL)
        {
            RECT rect;
            //获取窗口大小
            DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rect, sizeof(RECT));

            //获取窗口名
            char name[255];
            GetWindowTextA(hwnd, name, 255);

            if (!std::string(name).empty())
            {
                auto iterator_find = used.find(string(name));
                if (iterator_find != used.end())
                { }
                else
                {

                    if(string(name)=="勿扰中止")
                        continue;
                    ::PostMessage(hwnd, WM_CLOSE, 0, 0);//关闭成功了
                    Sleep(500);
                   Busy_Count++;

                    if(Busy_Count>2)
                       {
                            checkBusyT->stop();
                             trayIcon->showMessage(tr("勿扰中止"), tr("请调整学习状态"), QSystemTrayIcon::Information, 1000);
                    }
                }
            }
            hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
        }
}

void shibi::TrayIconAction(QSystemTrayIcon::ActivationReason reason)
{
    if (reason==QSystemTrayIcon::Trigger)
        this->showNormal();//如果对图标进行单击，则显示正常大小的窗口
}


void shibi::on_btn_log_clicked()
{

ui->stackedWidget->setCurrentIndex(3);

}

void shibi::on_btn_lun_clicked()
{
if(isLog)
ui->stackedWidget->setCurrentIndex(0);
}

void shibi::on_btn_tod_clicked()
{
    if(T2)
ui->stackedWidget->setCurrentIndex(1);
}

void shibi::on_btn_clo_clicked()
{
    if(T2)
ui->stackedWidget->setCurrentIndex(2);
}

void shibi::on_btn_ing_clicked()
{
    if(isLog)
    {
    if(!change_Busy)
    {
        init_used();
        setSysVolume(0);
        trayIcon->showMessage(tr("勿扰模式"), tr("快进入学习状态吧"), QSystemTrayIcon::Information, 0.5);
        connect(checkBusyT,SIGNAL(timeout()),this,SLOT(checkBusy()));
        hide();
    }
    change_Busy=!change_Busy;
    if(change_Busy)
    checkBusyT->start(500);
    else
    {
        checkBusyT->stop();
        static NoticeWidget noticeWin;
        noticeWin.Notice(this, WR_warning->toPlainText(), 1000);
    }
    }
}
