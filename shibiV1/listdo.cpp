#include "listdo.h"
#include "ui_listdo.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include "todolist.h"
#include "todomodel.h"
#include <QApplication>
ListDo::ListDo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ListDo)
{
    ui->setupUi(this);
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");
    qmlRegisterType<ToDoList>("ToDo",1,0,"ToDoList");
    ToDoList tmpp;//设置大小，跟随布局大小
    tmp = new QQuickWidget(this);	//新建QQuickWidget布局
    tmp->setResizeMode(QQuickWidget::SizeRootObjectToView);
    tmp->rootContext()->setContextProperty(QStringLiteral("tmpp"),&tmpp);
    tmp->setFocus();
    tmp->setSource(QUrl("qrc:///ToDoList.qml"));
    tmp->show();
}

ListDo::~ListDo()
{
    delete ui;
}

