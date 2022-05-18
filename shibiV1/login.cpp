#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent)
    : QWidget(parent)
    , log_ui(new Ui::login)
{
    log_ui->setupUi(this);
    T1 =false;
    R_name="今日事";
    R_pwd="今日毕";
    connect(&manager, &QNetworkAccessManager::finished,this, &login::read_data);
    QString num ="101200101";
    QUrl url("http://t.weather.sojson.com/api/weather/city/" + num);
    //创建一个请求对象
    QNetworkRequest request(url);
    //发送请求
    manager.get(request);
    connect(log_ui->btn_log,&QPushButton::clicked,this,[=](){
        QString usert;
        usert=log_ui->L_id->text();
        QString passwdt;
        passwdt = log_ui->L_pw->text();

        //设立判断标志
        if(usert==R_name&&passwdt==R_pwd)
        {

            T1=true;
            T2=true;
        }
        if(T1 == true){
            QMessageBox::information(this,"成功","登录成功");
        }else {
            QMessageBox::information(this,"警告","用户名或密码错误");
        }
    });
}

login::~login()
{
    delete log_ui;
}

void login::read_data(QNetworkReply *reply)
{
    QByteArray array = reply->readAll();//读取所有数据

    //json解析
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(array, &error);
    if(error.error != QJsonParseError::NoError)//校验格式是否有错
    {
        qDebug()<<"json error";
        return ;
    }

    QJsonObject obj = doc.object();
    QJsonObject weatherObj = obj.value("data").toObject();
    QJsonArray forecast = weatherObj.value("forecast").toArray();
    for(int i=0; i<1; i++)
    {
        QJsonObject o = forecast.at(i).toObject();
        log_ui->l_h->setText(o.value("high").toString());
        log_ui->l_l->setText(o.value("low").toString());
        log_ui->l_week->setText(o.value("week").toString());
        log_ui->l_weather->setText(o.value("type").toString());
    }
}

