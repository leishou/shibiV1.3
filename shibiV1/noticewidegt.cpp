#include "noticewidget.h"

NoticeWidget::NoticeWidget(QWidget *parent)
    : mParentPtr(parent)
    , mTimerPtr(nullptr)
    , mTimerCount(NOTICE_DEF_DELAY_CNT)
    , mBaseWidth(0)
    , mBaseHeight(0)
    , mTransparentVal(TRANSPARENT_MAX_VAL)

{
    //文字居中
    setAlignment(Qt::AlignCenter);

    //定时器，定时消失
    mTimerPtr = new QTimer(this);
    connect(mTimerPtr, SIGNAL(timeout()), this, SLOT(OnTimerTimeout()), Qt::UniqueConnection);
}

NoticeWidget::~NoticeWidget()
{
    if (mTimerPtr->isActive()) {
        mTimerPtr->stop();
    }
    deleteLater();
}

void NoticeWidget::OnTimerTimeout()
{
    --mTimerCount;
    if (0 < mTimerCount) {
        //重新定位(窗口大小和位置可能变化)
        if (nullptr != mParentPtr) {
            QPoint pt((mParentPtr->width() - width()) >> 1, (mParentPtr->height() - height()) >> 1);
            if (pos() != pt) {//父窗口位置变化
                ChangeSize();
                move(pt);
            }
        }
        //最后1s开始渐变消失
        if (mTimerCount <= NOTICE_DEF_DELAY_CNT && 0 < mTransparentVal) {
            mTransparentVal -= TRANSPARENT_CUT_VAL;
            if (0 > mTransparentVal) {
                mTransparentVal = 0;
            }
            //控制透明度
            setStyleSheet(QString(STYLE_SHEET).arg(mTransparentVal));
        }
    } else {//显示结束
        mTimerPtr->stop();
        setVisible(false);
    }
}

//设置要显示的消息
void NoticeWidget::SetMesseage(const QString &msg, int delay_ms)
{
    mParentPtr = parentWidget();

    QFontMetrics fontMetrics(font());
    mBaseWidth = fontMetrics.width(msg);
    mBaseHeight = fontMetrics.height() + PADDING;

    //设置宽高
    ChangeSize();

    //换行
    setWordWrap(true);

    //设置显示内容
    setText(msg);

    //居中
    if (nullptr != mParentPtr) {
        move((mParentPtr->width() - width()) >> 1, (mParentPtr->height() - height()) >> 1);
    }

    setVisible(true);//显示
    setStyleSheet(QString(STYLE_SHEET).arg(TRANSPARENT_MAX_VAL));//设置样式，不透明
    mTimerCount = delay_ms/TIMER_INTERVAL_MS + 1;//延时计数计算
    mTransparentVal = TRANSPARENT_MAX_VAL;
}

//跟随父窗口大小变化
void NoticeWidget::ChangeSize()
{
    if (nullptr != mParentPtr) {
        double wd = mParentPtr->width() * SIZE_SCALE;//宽度占父窗口的80%
        setFixedSize((int)wd, mBaseHeight*(mBaseWidth/wd + 1));
    }
}

//显示消息，可通过设置delay_ms=0来立即关闭显示
void NoticeWidget::Notice(QWidget *parent, const QString &msg, const int delay_ms)
{
    if (mTimerPtr->isActive()) {
        mTimerPtr->stop();
        setVisible(false);
    }

    //消息为空直接返回
    if (msg.isEmpty() || 0 >= delay_ms) {
        return;
    }

    setParent(parent);
    SetMesseage(msg, delay_ms);
    mTimerPtr->start(TIMER_INTERVAL_MS);//开始计数
}
