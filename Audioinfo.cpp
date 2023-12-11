#include "Audioinfo.h"
//管理音频信息
Audioinfo::Audioinfo(QObject *parent)
    : QObject{parent}
{

}

int Audioinfo::songIndex() const
{
    return m_songIndex;
}

void Audioinfo::setSongIndex(int newSongIndex)
{
    if (m_songIndex == newSongIndex)
        return;
    m_songIndex = newSongIndex;
   emit songIndexChanged();
}

QString Audioinfo::title() const
{
    return m_title;
}

void Audioinfo::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

QString Audioinfo::authorName() const
{
    return m_authorName;
}

void Audioinfo::setAuthorName(const QString &newAuthorName)
{
    if (m_authorName == newAuthorName)
        return;
    m_authorName = newAuthorName;
    emit authorNameChanged();
}

QUrl Audioinfo::imageSource() const
{
    return m_imageSource;
}

void Audioinfo::setImageSource(const QUrl &newImageSource)
{
    if (m_imageSource == newImageSource)
        return;
    m_imageSource = newImageSource;
    emit imageSourceChanged();
}

QUrl Audioinfo::videoSource() const
{
    return m_videoSource;
}

void Audioinfo::setVideoSource(const QUrl &newVideoSource)
{
    if (m_videoSource == newVideoSource)
        return;
    m_videoSource = newVideoSource;
    emit videoSourceChanged();
}

QUrl Audioinfo::audioSource() const
{
    return m_audioSource;
}

void Audioinfo::setAudioSource(const QUrl &newAudioSource)
{
    if (m_audioSource == newAudioSource)
        return;
    m_audioSource = newAudioSource;
    emit audioSourceChanged();
}


