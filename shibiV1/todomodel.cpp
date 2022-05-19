#include "todomodel.h"
#include<QString>
#include "todolist.h"

ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ToDoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    // safe gaurd against null pointer accesses
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ToDoItem item = mList->items().at(index.row());

    switch (role) {
        case DoneRole:
            /*
             * QVariant class acts like a union
             * for most common qt data types
             */
            return QVariant(item.done);
        case DescriptionRole:
            return QVariant(item.description);//得到数据 找调用函数
    }
    return QVariant();
}
//这个函数赋值 value得到的work
bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList){
        return false;
    }
    ToDoItem item = mList->items().at(index.row());
    QSqlDatabase db;//成功了
    //检测已连接的方式 - 默认连接名
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("sqltest.db");
    if(db.open()){
          // qDebug()<<"open success";
       }
    switch (role) {

        case DoneRole:
            //now we convert back the QVariant by typecasting
        if(item.done!=value.toBool())
        {

            QSqlQuery query1;
            query1.exec("update todo set isfinshed='"+QString::number(value.toBool())+"' "+"where id= '"+QString::number(index.row())+"'");
        }
            item.done = value.toBool();//256 toBool

            break;
        case DescriptionRole://这里
            item.description = value.toString();
            if(item.done!=value.toBool())
            {
                QString tmp=value.toString();
                QSqlQuery query2;
                query2.exec("update todo set work='"+tmp+"' "+"where id= '"+QString::number(index.row())+"'");
            }
            break;
    }

    //check whether data has changed
    if (mList->setItemAt(index.row(),item)) {
        emit dataChanged(index, index, QVector<int>() << role);//256数值改变
        return true;
    }
    return false;
}

Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ToDoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    return names;
}

ToDoList *ToDoModel::list() const
{
    return mList;
}

void ToDoModel::setList(ToDoList *list)
{
    beginResetModel();

    if(mList){
        //disconnet from the old list when assigning to
        // a new list
        mList->disconnect(this);
    }
    mList = list;

    if(mList){
        connect(mList, &ToDoList::preItemAppend, this, [=](){
           const int index = mList->items().size();
           beginInsertRows(QModelIndex(), index, index);
        });

        connect(mList, &ToDoList::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(mList, &ToDoList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mList, &ToDoList::postItemRemoved, this, [=](){
           endRemoveRows();
        });

    }

    endResetModel();
}
