#ifndef AUDIOSEARCHMODEL_H
#define AUDIOSEARCHMODEL_H

#include <QAbstractListModel>//列表模型
#include <QObject>
#include <QNetworkAccessManager>//用于处理 HTTP 和 FTP 协议的客户端请求

class  Audioinfo;
class AudioSearchModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isSearching READ isSearching NOTIFY isSearchingChanged)

public:
    enum Role {//获取相关数据
        AudioNameRole = Qt::UserRole + 1,
        AudioAuthorRole,
        AudioImageSourceRole,
        AudioSourceRole,
        AudioinfoLangRole,

    };

    explicit AudioSearchModel(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex &parent) const override;//行数
    virtual QVariant data(const QModelIndex &index, int role) const override;//索引和角色的数据
    virtual QHash<int, QByteArray> roleNames() const override;//该哈希表将角色名称映射到整数角色值

    bool isSearching() const;
    void setIsSearching(bool newIsSearching);

public slots:
    void searchSong(const QString &name);
    void parseData();//解析数据

signals:
    void isSearchingChanged();

private:
    QList<Audioinfo*> m_audioList;//存储音频信息列表
    QNetworkAccessManager m_networkManager;//获取网络资源
    QNetworkReply *m_reply = nullptr;
    bool m_isSearching;
};

#endif // AUDIOSEARCHMODEL_H
