#include "AudioSearchModel.h"
#include "Audioinfo.h"
#include <QJsonDocument>//处理json类
#include <QNetworkReply>//网络请求
#include <QUrlQuery>//处理url查询参数
#include <QJsonObject>//处理json对象
#include <QJsonArray>//处理json数据

namespace {
const QString &k_requestUrl = "https://api.jamendo.com/v3.0/tracks/";//Url地址

const QString &k_clientId = "045084ae";//客户端id
}

AudioSearchModel::AudioSearchModel(QObject *parent)
:QAbstractListModel{parent}
{

}

int AudioSearchModel::rowCount(const QModelIndex &parent) const//将m_audioList列表的大小作为行数
{
    Q_UNUSED(parent);
    return m_audioList.size();
}

QVariant AudioSearchModel::data(const QModelIndex &index, int role) const//从m_audioList列表中获取音频相关信息
{


    if (index.isValid() && index.row() >= 0 && index.row() < m_audioList.size()) {//索引是否有效，并且其行号是否在0和m_audioList.size()之间
        Audioinfo *audioInfo = m_audioList[index.row()];

        switch((Role)role) {
        case AudioNameRole:
            return audioInfo->title();
        case AudioAuthorRole:
            return audioInfo->authorName();
        case AudioImageSourceRole:
            return audioInfo->imageSource();
        case AudioSourceRole:
            return audioInfo->audioSource();

        }
    }

    return {};
}

QHash<int, QByteArray> AudioSearchModel::roleNames() const
{
    //将每个角色与对应的名称进行映射，并返回该哈希表。
    QHash<int, QByteArray> names;

    names[AudioNameRole] = "audioName";
    names[AudioAuthorRole] = "audioAuthor";
    names[AudioImageSourceRole] = "audioImageSource";
    names[AudioSourceRole] = "audioSource";

    return names;
}

bool AudioSearchModel::isSearching() const
{
    return m_isSearching;
}

void AudioSearchModel::setIsSearching(bool newIsSearching)//是否正在进行音频搜素
{
    if (m_isSearching == newIsSearching)
        return;
    m_isSearching = newIsSearching;
    emit isSearchingChanged();

}

void AudioSearchModel::searchSong(const QString &name)//搜索歌曲
{

        if (!name.trimmed().isEmpty()) {//name.trimmed()会去除字符串两端的空格，然后使用isEmpty()检查处理后的字符串是否为空
        if (m_reply) {
            m_reply->abort();//中止网络请求
            m_reply->deleteLater();
            m_reply = nullptr;
        }

        QUrlQuery query;
        query.addQueryItem("client_id", k_clientId);
        query.addQueryItem("namesearch", name);
        query.addQueryItem("format", "json");

        setIsSearching(true);
        m_reply = m_networkManager.get(QNetworkRequest(k_requestUrl + "?" + query.toString()));
        connect(m_reply, &QNetworkReply::finished, this, &AudioSearchModel::parseData);
    }


}

void AudioSearchModel::parseData()//准备分析数据
{

    if (m_reply->error() == QNetworkReply::NoError) {
        beginResetModel();//准备模型数据更改

        qDeleteAll(m_audioList);
        m_audioList.clear();

        QByteArray data = m_reply->readAll();//从网络回应中读取所有数据并将其存储在data字节数组中

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);//解析数据为Json文档
        QJsonObject headers = jsonDocument["headers"].toObject();

        if (headers["status"].toString() == "success") {
            QJsonArray results = jsonDocument["results"].toArray();//从JSON文档中提取"results"字段并将其转换为QJsonArray，然后存储在results中。

            for (const auto &result : results) {
                QJsonObject entry = result.toObject();

                if (entry["audiodownload_allowed"].toBool()) {
                    Audioinfo *audioInfo = new Audioinfo(this);

                    audioInfo->setTitle(entry["name"].toString());
                    audioInfo->setAuthorName(entry["artist_name"].toString());
                    audioInfo->setImageSource(entry["image"].toString());
                    audioInfo->setAudioSource(entry["audiodownload"].toString());
                    m_audioList << audioInfo;
                }
            }
        } else {
            qWarning() << headers["error_string"];
        }

        endResetModel();//刷新
    } else if (m_reply->error() != QNetworkReply::OperationCanceledError) {
        qCritical() << "Reply failed, eror:" << m_reply->errorString();
    }

    setIsSearching(false);
    m_reply->deleteLater();
    m_reply = nullptr;

}
