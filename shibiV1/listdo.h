#ifndef LISTDO_H
#define LISTDO_H

#include <QMainWindow>
#include<QQuickWidget>
#include <QWidget>
#include "todolist.h"
#include "todomodel.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ListDo; }
QT_END_NAMESPACE

class ListDo : public QMainWindow
{
    Q_OBJECT

public:
    ListDo(QWidget *parent = nullptr);
    ~ListDo();

private:
    Ui::ListDo *ui;
    QQuickWidget *tmp;
};
#endif // LISTDO_H
