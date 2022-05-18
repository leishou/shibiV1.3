#ifndef LOGIN_H
#define LOGIN_H
#include <QWidget>
#include<QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>
#include"share.h"
QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
private slots:
    void read_data(QNetworkReply *reply);
public:
    bool T1;
private:
    Ui::login *log_ui;
    QString R_name ;
    QString R_pwd;
    QNetworkAccessManager manager;
};
#endif // LOGIN_H
