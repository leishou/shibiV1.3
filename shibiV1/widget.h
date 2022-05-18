#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QIcon>
#include <QTime>
#include <QFile>
#include <QSlider>
#include <QDir>
#include <QListWidget>
#include <QPainter>


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_lastBtn_clicked();

    void play_pause_music();

    void on_nextBtn_clicked();

    void volumChange(int position);


    void on_addBtn_clicked();

    void on_loseBtn_clicked();

    void skipFirst(QMediaPlayer::State MusicState);


private:
    Ui::Widget *b_ui;
    QMediaPlayer *player;
    QMediaPlaylist *playerlist;
    bool isPlay;
    bool isSilence;
    QTime *currentTime;
    QTime *totalTime;
    int time;
    int Vposition;
    int MusicCurrent;
};

#endif // WIDGET_H
