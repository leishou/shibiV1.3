#ifndef _NoticeWidget_H_
#define _NoticeWidget_H_

#include <QLabel>
#include <QTimer>

//定时器间隔，单位ms
#define TIMER_INTERVAL_MS   50

//默认提示时间1s
#define NOTICE_DEF_DELAY_CNT     (1000/TIMER_INTERVAL_MS)

//透明度最大值255，也就是不透明
#define TRANSPARENT_MAX_VAL 255

//透明度递减值
#define TRANSPARENT_CUT_VAL (TRANSPARENT_MAX_VAL/NOTICE_DEF_DELAY_CNT + 1)

//大小比例
#define SIZE_SCALE  0.8

//间距调整
#define PADDING     4

//样式，字体颜色：白色；圆角；背景色透明度
#define STYLE_SHEET "color:white;border-radius:8px;background-color:rgba(80, 80, 80, %1);"

class NoticeWidget :public QLabel
{
    Q_OBJECT

public:
    void Notice(QWidget *parent, const QString &msg, const int delay_ms = 2000);

public:
    explicit NoticeWidget(QWidget *parent = 0);
    ~NoticeWidget();

private:
    void SetMesseage(const QString &msg, int delay_ms);
    void ChangeSize();

public slots:
    void OnTimerTimeout();

private:
    QWidget *mParentPtr;
    QTimer  *mTimerPtr;
    int mTimerCount;
    int mBaseWidth;  //按一行时算的宽度
    int mBaseHeight; //一行高度
    int mTransparentVal;//透明度0~255，值越小越透明
};

#endif // _NoticeWidget_H_
