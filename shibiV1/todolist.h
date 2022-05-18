#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include<QDebug>
//make a struct for each obj
struct ToDoItem{
    bool done;
    QString description;
};

class ToDoList : public QObject
{
    Q_OBJECT
public:
   Q_INVOKABLE explicit ToDoList(QObject *parent = nullptr);

  Q_INVOKABLE  QVector<ToDoItem> items() const;
    //this will allow the model to modify the
    // todo list data
  Q_INVOKABLE  bool setItemAt(int index, const ToDoItem &item);
//signals send signals to slots
signals:
    //signal functions don't need definitions

    //need to notify before something happens to
    // data and after that
  Q_INVOKABLE  void  cs1();
  Q_INVOKABLE  void  cs2();


 Q_INVOKABLE   void preItemAppend();
 Q_INVOKABLE   void postItemAppended();

 Q_INVOKABLE   void preItemRemoved(int index);
 Q_INVOKABLE   void postItemRemoved();

public slots:
    Q_INVOKABLE void appendItemA();
    Q_INVOKABLE void removeCompletedItemsA();

private:
    QVector<ToDoItem> mItems;
    QSqlDatabase db;
    //QSqlQuery query;
};

#endif // TODOLIST_H
