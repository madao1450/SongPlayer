#ifndef AUDIOINFO_H
#define AUDIOINFO_H

#include <QObject>
#include<QUrl>
#include<qqml.h>
class Audioinfo : public QObject
{
    Q_OBJECT
   QML_ELEMENT

    Q_PROPERTY(int songIndex READ songIndex WRITE setSongIndex NOTIFY songIndexChanged REQUIRED)//歌曲索引
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)//标题
    Q_PROPERTY(QString authorName READ authorName WRITE setAuthorName NOTIFY authorNameChanged)//作者
    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)//图片来源
    Q_PROPERTY(QUrl videoSource READ videoSource WRITE setVideoSource NOTIFY videoSourceChanged)//视频来源
    Q_PROPERTY(QUrl audioSource READ audioSource WRITE setAudioSource NOTIFY audioSourceChanged )//声音



public:
    explicit Audioinfo(QObject *parent = nullptr);

    int songIndex() const;
    void setSongIndex(int newSongIndex);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString authorName() const;
    void setAuthorName(const QString &newAuthorName);

    QUrl imageSource() const;
    void setImageSource(const QUrl &newImageSource);

    QUrl videoSource() const;
    void setVideoSource(const QUrl &newVideoSource);

    QUrl audioSource() const;
    void setAudioSource(const QUrl &newAudioSource);

    QString duration() const;
    void setDuration(const QString &newDuration);

signals:
    void songIndexChanged();
    void titleChanged();
    void authorNameChanged();
    void imageSourceChanged();
    void videoSourceChanged();

    void audioSourceChanged();


private:
    int m_songIndex;
    QString m_title;
    QString m_authorName;
    QUrl m_imageSource;
    QUrl m_videoSource;
    QUrl m_audioSource;



};

#endif // AUDIOINFO_H
