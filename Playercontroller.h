#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include<QtMultimedia>
#include <QtMultimedia/QMediaPlayer>
#include<QAbstractListModel>

class Audioinfo;
class Playercontroller : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(bool playing READ playing  NOTIFY playingChanged )
    Q_PROPERTY(AudioInfo* currentSong READ currentSong WRITE setCurrentSong NOTIFY currentSongChanged )
public:

    enum Role{//管理音频数据
        AudioTitleRole = Qt::UserRole,
        AudioAuthorNameRole,
        AudioSourceRole,
        AudioImageSourceRole,
        AudioVideoSourceRole,

    };

    explicit Playercontroller(QObject *parent = nullptr);

    Audioinfo *currentSong() const;
    void setCurrentSong(Audioinfo *newCurrentSong);
    Q_INVOKABLE void switchToNextSong();

    bool playing() const;

    virtual int rowCount(const QModelIndex &parent) const;
    virtual  QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
public slots:
    void switchToPreviousSong();//上一首
    void playPause();//播放/暂停
    void changeAudioSource(const QUrl &source);//改变音频源
    void addAudio(const QString& title,
                  const QString& authorName,
                  const QUrl& audioSource,
                  const QUrl& imageSource,
                  const QUrl& videoSource = QUrl());//添加新的音频

    void removeAudio(int index);//移除
    void switchToAudioByIndex(int index);//切换


signals:

void currentSongChanged();
    void playingChanged();


private:

    bool m_playing = false;
   QMediaPlayer m_mediaPlayer;//播放器

    QList<Audioinfo*>m_audioList;//音频信息列表
   Audioinfo *m_currentSong = nullptr;


};

#endif // PLAYERCONTROLLER_H
