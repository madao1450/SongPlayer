#include "Playercontroller.h"
#include"Audioinfo.h"

#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioOutput>


Playercontroller::Playercontroller(QObject *parent)
    :QAbstractListModel{parent}
{

    const auto &audioOutputs = QMediaDevices::audioOutputs();//输出设备列表
    if (!audioOutputs.isEmpty()) {
        m_mediaPlayer.setAudioOutput(new QAudioOutput(&m_mediaPlayer));
    }

    addAudio("The Girl That's Underneath",
             "Jake Miller / Jabbar Hakeem",
             QUrl("qrc:/SongPlayer/assets/audio/Jake_Miller__Jabbar_Hakeem.mp3"),
             QUrl("qrc:/SongPlayer/assets/images/song.jpg"));

    addAudio("Love You Like the Movies",
             "Anthem Lights",
             QUrl("qrc:/SongPlayer/assets/audio/Anthem_Lights_-_Love_You_Like_the_Movies.mp3"),
             QUrl("qrc:/SongPlayer/assets/images/sing.jpg"));

    addAudio("golden hour",
             "JVKE",
             QUrl("qrc:/SongPlayer/assets/audio/JVKE_-_golden_hour.mp3"),
             QUrl("qrc:/SongPlayer/assets/images/OIP.jpg"));

}

Audioinfo *Playercontroller::currentSong() const
{
    return m_currentSong;
}

void Playercontroller::setCurrentSong(Audioinfo *newCurrentSong)//更新歌曲
{

   if(m_currentSong == newCurrentSong)return;
    m_currentSong = newCurrentSong;
    emit currentSongChanged();

    if(m_currentSong){
        changeAudioSource(m_currentSong->audioSource());
    }else{
        m_mediaPlayer.stop();
        m_mediaPlayer.setSource(QUrl());
        m_playing = false;
        emit playingChanged();
    }


}
void Playercontroller::switchToPreviousSong()//切换上一首歌曲
{
    const int index = m_audioList.indexOf(m_currentSong);
    if(index - 1 <0){
        setCurrentSong(m_audioList.last());
    }else{
        setCurrentSong(m_audioList[index-1]);
    }
}
void Playercontroller::switchToNextSong()//切换下一首
{
    const int index = m_audioList.indexOf(m_currentSong);//获取索引
    if (index + 1 >= m_audioList.length()) {
        setCurrentSong(m_audioList.first());
    } else {
        setCurrentSong(m_audioList[index + 1]);
    }
}

bool Playercontroller::playing() const
{
    return m_playing;
}

int Playercontroller::rowCount(const QModelIndex &parent) const//显示音频列表
{
    Q_UNUSED(parent);
    return m_audioList.length();
}

QVariant Playercontroller::data(const QModelIndex &index, int role) const//获取对应的数据
{
  if(index.isValid() && index.row() >= 0 && index.row()< m_audioList.length()){//索引的行号大于等于0且小于音频列表的长度
        Audioinfo * audioInfo = m_audioList[index.row()];//音频列表中获取指定索引对应的音频信息

        switch ((Role)role) {
        case AudioTitleRole:
            return audioInfo->title();
        case AudioAuthorNameRole:
            return audioInfo->authorName();
        case AudioSourceRole:
            return audioInfo->audioSource();
        case AudioImageSourceRole:
            return audioInfo->imageSource();
        case AudioVideoSourceRole:
            return audioInfo->videoSource();

        }

    }
    return {};

}

QHash<int, QByteArray> Playercontroller::roleNames() const
{
    QHash<int, QByteArray> result;

    result[AudioAuthorNameRole] = "audioAuthorName";//键是AudioAuthorNameRole，值是audioAuthorName
    result[AudioTitleRole] = "audioTitle";
    result[AudioSourceRole] = "audioSource";
    result[AudioImageSourceRole] = "audioImageSource";
    result[AudioVideoSourceRole] = "audioVideoSource";

    return result;

}


void Playercontroller::playPause()//播放或者暂停
{
    m_playing = !m_playing;
    emit playingChanged();

    if (m_playing) {
        m_mediaPlayer.play();
    } else {
        m_mediaPlayer.pause();
    }

}

void Playercontroller::changeAudioSource(const QUrl &source)//更改播放音源
{
    m_mediaPlayer.stop();
    m_mediaPlayer.setSource(source);

    if (m_playing) {
        m_mediaPlayer.play();
    }
}

void Playercontroller::addAudio(const QString &title, const QString &authorName, const QUrl &audioSource, const QUrl &imageSource, const QUrl &videoSource)//在末尾添加音频信息
{

    beginInsertRows(QModelIndex(), m_audioList.length(), m_audioList.length());//位置，行索引，行数

    Audioinfo *audioInfo = new Audioinfo(this);

    audioInfo->setTitle(title);
    audioInfo->setAuthorName(authorName);
    audioInfo->setAudioSource(audioSource);
    audioInfo->setImageSource(imageSource);
    audioInfo->setVideoSource(videoSource);

    if (m_audioList.isEmpty()) {
        setCurrentSong(audioInfo);
    }

    m_audioList << audioInfo;

    endInsertRows();

}

void Playercontroller::removeAudio(int index)//删除音频信息
{

    if (index >= 0 && index < m_audioList.length()) {
        beginRemoveRows(QModelIndex(), index, index);
        Audioinfo *toRemove = m_audioList[index];

        if (toRemove == m_currentSong) {
            if (m_audioList.length() > 1) {
                if (index != 0) {
                    setCurrentSong(m_audioList[index - 1]);
                } else {
                    setCurrentSong(m_audioList[index + 1]);
                }
            } else {
                setCurrentSong(nullptr);
            }
        }
        qDebug()<<"----------------";
        m_audioList.removeAt(index);//删除位于index指定位置的音频信息。
        toRemove->deleteLater();
        endRemoveRows();
    }



}

void Playercontroller::switchToAudioByIndex(int index)//按照索引切换到音频
{
    if(index >= 0 && index <m_audioList.length()){
        setCurrentSong(m_audioList[index]);
    }

}



