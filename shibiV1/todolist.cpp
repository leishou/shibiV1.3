#include "todolist.h"
#include<string>
using namespace  std;
ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    //add some initial sample data
    //true false 状态  QStringLiteral 后所跟内容
    QSqlDatabase db;//成功了
    //检测已连接的方式 - 默认连接名
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("sqltest.db");
    if(db.open()){
           //qDebug()<<"open success";
       }
    QSqlQuery query0;
    query0.exec("CREATE TABLE todo(id INTEGER PRIMARY KEY,  isfinshed BOOLEAN DEFAULT (false), work VARCHAR);");

    QSqlQuery query;
    query.exec("select work,isfinshed from todo ");
    while(query.next())
    {
        QString value0 = query.value(0).toString();
        bool value1=query.value(1).toBool();
        mItems.append({value1, value0});
        qDebug() << value0 << value1 ;
    }
    //db.close();

}

QVector<ToDoItem> ToDoList::items() const
{
    return mItems;
}
//returns whether data was successfully modified or not
bool ToDoList::setItemAt(int index, const ToDoItem &item)//传入之前 item.done已改变
{
    /*
     * check if the index is valid
     */
    if(index<0 || index >= mItems.size())
        return false;

    const ToDoItem &oldItem = mItems.at(index);
    /*
     * checks if new item has identical
     * values or not to check whether we are changing
     * the data or not
     */
    if(item.done == oldItem.done && item.description == oldItem.description){
        return false;
    }
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("sqltest.db");
    if(db.open()){
           qDebug()<<"open success";
       }

    QSqlQuery query;
    mItems[index] = item;
    //index从0开始计数
    query.exec("insert into todo values("+QString::number(index)+",false,'"+item.description+"')");
    return true;
}

void ToDoList::appendItemA()
{
    emit preItemAppend();//1发送信号

    ToDoItem item;
    item.done = false;//初始false  通过默认值不需要再调整，只需要解决输入描述
    mItems.append(item);//加到列表

    emit postItemAppended();//2发送序号
}
//check on all items and remove the ones that are done
void ToDoList::removeCompletedItemsA()
{
    for (int i=0;i<mItems.size();) {
        if(mItems.at(i).done){
            emit preItemRemoved(i);
            QSqlDatabase db;
            if(QSqlDatabase::contains("qt_sql_default_connection"))
                db = QSqlDatabase::database("qt_sql_default_connection");
            else
                db = QSqlDatabase::addDatabase("QSQLITE");

            db.setDatabaseName("sqltest.db");
            if(db.open()){
                   qDebug()<<"open success";
               }
            QDateTime curDateTime=QDateTime::currentDateTime();
            QString cur_time=curDateTime.toString("hh:mm:ss");
            QString date=curDateTime.date().toString(("yyyy-MM-dd"));
            fstream oFile;
            oFile.open("shibi-logs.txt",ios::app);
            oFile<<date.toStdString();
            oFile<<" ";
            oFile<<cur_time.toStdString();
            oFile<<" 完成事项： ";
            oFile<<mItems[i].description.toStdString();
            oFile<<"\n";
            oFile.close();
            QSqlQuery query;
             query.exec("delete from todo where work = '"+mItems[i].description+"'");
            mItems.removeAt(i);


            emit postItemRemoved();
        }
        else{
            ++i;
        }
    }
}
