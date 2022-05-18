#include "fanqie.h"
#include "ui_fanqie.h"

fanqie::fanqie(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::fanqie)
{
    ui->setupUi(this);
    lcd=new QLCDNumber();
        lcd->setDigitCount(5);
        lcd->setMode(QLCDNumber::Dec);
        lcd->setSegmentStyle(QLCDNumber::Flat);

        timer=new QTimer();
        timer->setInterval(1000);
        timer->start();

        startbutton=new QPushButton("开始工作");
        connect(startbutton,SIGNAL(clicked(bool)),this,SLOT(clickOnButton()));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(lcd);
        layout->addWidget(startbutton);

        this->setLayout(layout);
        this->resize(400,200);
        this->setWindowFlag(Qt::WindowStaysOnTopHint);
}

fanqie::~fanqie()
{
    delete ui;
}

void fanqie::onTimeout()
{
    QString s_minute=QString::number(minute);
       QString s_second=QString::number(second);
       if (s_minute.length()==1)   s_minute="0"+s_minute;
       if(s_second.length()==1)    s_second="0"+s_second;
       QString disp=s_minute+":"+s_second;
       lcd->display(disp);
       if((minute!=0)|(second!=0)){
           if(second==0){
               second=59;
               minute--;}
           else
               second--;
       }
       else
           lcd->setStyleSheet("background-color:red");
}

void fanqie::clickOnButton()
{
        this->minute=25;
        this->second=0;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
        connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
        this->lcd->setStyleSheet("background-color:white");
}

