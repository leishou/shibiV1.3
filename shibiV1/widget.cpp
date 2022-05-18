#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    b_ui(new Ui::Widget)
{
    b_ui->setupUi(this);
    isPlay=true;
    isSilence=false;

    b_ui->startBtn->setIcon(QIcon(":/image/PlayMusic.png"));// 暂停时候显示播放图标
    b_ui->startBtn->setIconSize(QSize(50,50));
    b_ui->startBtn->setFlat(true);
    b_ui->startBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
    b_ui->startBtn->setToolTip(tr("播放"));// 鼠标停留时显示播放文字

    b_ui->lastBtn->setIcon(QIcon(":/image/circle_previous.png"));// 显示上一曲图标
    b_ui->lastBtn->setIconSize(QSize(50,50));
    b_ui->lastBtn->setFlat(true);
    b_ui->lastBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
    b_ui->lastBtn->setToolTip(tr("上一曲"));// 鼠标停留时显示上一曲文字

    b_ui->nextBtn->setIcon(QIcon(":/image/circle_next.png"));// 显示下一曲图标
    b_ui->nextBtn->setIconSize(QSize(50,50));
    b_ui->nextBtn->setFlat(true);
    b_ui->nextBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
    b_ui->nextBtn->setToolTip(tr("下一曲"));// 鼠标停留时显示下一曲文字

    b_ui->addBtn->setIcon(QIcon(":/image/addIcon.png"));// 显示加大音量图标
    b_ui->addBtn->setIconSize(QSize(30,30));
    b_ui->addBtn->setFlat(true);
    b_ui->addBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
    b_ui->addBtn->setToolTip(tr("加大音量"));// 鼠标停留时显示加大音量文字


    b_ui->loseBtn->setIcon(QIcon(":/image/loseIcon.png"));// 显示减小音量图标
    b_ui->loseBtn->setIconSize(QSize(30,30));
    b_ui->loseBtn->setFlat(true);
    b_ui->loseBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
    b_ui->loseBtn->setToolTip(tr("减小音量"));// 鼠标停留时显示减小音量文字


    //fileList = getFileNames(this->MusicPath);

    QImage *img=new QImage;
    img->load(":/image/soundOn.png");
    *img=img->scaled(20,20,Qt::KeepAspectRatio);
    b_ui->label->setPixmap(QPixmap::fromImage(*img));

    player = new QMediaPlayer;
    playerlist = new QMediaPlaylist(player);

    //b_ui->strTime->setText("00:00");

    b_ui->volumeSlider->setRange(0,100);
    b_ui->volumeSpinBox->setRange(0,100);

    b_ui->volumeSlider->setValue(5);
    b_ui->volumeSpinBox->setValue(5);
    player->setVolume(5);
    Vposition=5;

    playerlist->addMedia(QUrl("qrc:/bgm1.mp3"));
    playerlist->addMedia(QUrl("qrc:/bgm2.mp3"));
     playerlist->addMedia(QUrl("qrc:/bgm3.mp3"));
    playerlist->setCurrentIndex(0);
    player->setPlaylist(playerlist);

    // 切换歌曲的同时改变歌曲名和歌曲图片
    //connect(player, SIGNAL(metaDataChanged()), this, SLOT(musicInfo()));
    connect(b_ui->volumeSlider, SIGNAL(valueChanged(int)), b_ui->volumeSpinBox, SLOT(setValue(int)));
   // connect(b_ui->volumeSpinBox, SIGNAL(valueChanged(int)), b_ui->volumeSlider, SLOT(setValue(int)));
    connect(b_ui->volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(volumChange(int)));
    //connect(b_ui->volumeSpinBox, SIGNAL(valueChanged(int)), this, SLOT(volumChange(int)));
    connect(b_ui->startBtn,SIGNAL(clicked(bool)),this,SLOT(play_pause_music()));
    //connect(b_ui->listWidget,SIGNAL(currentRowChanged(int)),this,SLOT(play_list_music(int)));
    //进度条改变时播放位置随着改变
    //connect(b_ui->progressBar,SIGNAL(sliderMoved(int)),this,SLOT(setPlayerPosition(int)));
    //当播放歌曲位置改变时progressBar设置对应的位置 对应的播放时间与总时间的显示
    //connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    // 当progressBar改变时  构造歌曲总时间
    //connect(player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    //connect(player,&QMediaPlayer::currentMediaChanged,lrc,&LyricWidget::slotShowCurrentLrc);
    //connect(player,&QMediaPlayer::currentMediaChanged,lrc,&LyricWidget::cleanmap);
    connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(skipFirst(QMediaPlayer::State)));
}



Widget::~Widget()
{
    delete b_ui;
}

void Widget::skipFirst(QMediaPlayer::State MusicState)
{
    //当歌曲播放到最后一首结束时，跳到第一首
    if(MusicState == QMediaPlayer::StoppedState)
    {
        MusicCurrent=0;
        //设置当前的currentIndex
        playerlist->setCurrentIndex(MusicCurrent);
        isPlay=true;
        play_pause_music();
        return;
    }
}

void Widget::on_lastBtn_clicked()
{
    //播放列表为空，按钮不可用，直接返回
    if(playerlist->isEmpty())
        return;
    int MusicCount=playerlist->mediaCount();
    int MusicCurrent=playerlist->currentIndex();
    if(MusicCurrent==0){
        playerlist->setCurrentIndex(MusicCount-1);
        isPlay=true;
        play_pause_music();
        return;
    }
    playerlist->previous();
    isPlay=true;
    play_pause_music();
}

void Widget::play_pause_music()
{
    //如果播放列表为空，按钮不可用，直接返回
    if(playerlist->isEmpty())
        return;
    if(isPlay)
    {
        player->play();
        b_ui->startBtn->setIcon(QIcon(":/image/pause.png"));// 播放时候显示暂停图标
        b_ui->startBtn->setIconSize(QSize(50,50));
        b_ui->startBtn->setFlat(true);
        b_ui->startBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
        b_ui->startBtn->setToolTip(tr("暂停"));
    }
    else
    {
        player->pause();
        b_ui->startBtn->setIcon(QIcon(":/image/PlayMusic.png"));// 暂停时候显示播放图标
        b_ui->startBtn->setIconSize(QSize(50,50));
        b_ui->startBtn->setFlat(true);
        b_ui->startBtn->setStyleSheet("QToolTip{border:1px solid rgb(0, 0, 0); background-color: #ffffff; color:#484848; font-size:12px;}");
        b_ui->startBtn->setToolTip(tr("播放"));
    }
    isPlay=!isPlay;
}

void Widget::on_nextBtn_clicked()
{
    //如果播放列表为空，按钮不可用，直接返回
    if(playerlist->isEmpty())
        return;

    //如果列表到尽头，则回到列表开头
    int MusicCurrent=playerlist->currentIndex();
    if(++MusicCurrent==playerlist->mediaCount())
    {
        MusicCurrent=0;
        //设置当前的currentIndex
        playerlist->setCurrentIndex(MusicCurrent);
        isPlay=true;
        play_pause_music();
        return;
    }
    playerlist->next();
    isPlay=true;
    play_pause_music();
}


void Widget::volumChange(int position)
{  
    Vposition=position;
    player->setVolume(position);
    if(position == 0)
    {
        QImage *img=new QImage;
        img->load(":/image/volumeMuted.png");
        *img=img->scaled(20,20,Qt::KeepAspectRatio);
        b_ui->label->setPixmap(QPixmap::fromImage(*img));
    }
    else
    {
        QImage *img=new QImage;
        img->load(":/image/soundOn.png");
        *img=img->scaled(20,20,Qt::KeepAspectRatio);
        b_ui->label->setPixmap(QPixmap::fromImage(*img));

    }
}
void Widget::on_addBtn_clicked()
{
    Vposition+=1;
    if(Vposition > 100)
    {
        Vposition=100;
    }
    volumChange(Vposition);
    b_ui->volumeSpinBox->setValue(Vposition);
    b_ui->volumeSlider->setValue(Vposition);
}

void Widget::on_loseBtn_clicked()
{
    Vposition-=1;
    if(Vposition < 0)
    {
        Vposition=0;
    }
    volumChange(Vposition);
    b_ui->volumeSpinBox->setValue(Vposition);
    b_ui->volumeSlider->setValue(Vposition);
}

