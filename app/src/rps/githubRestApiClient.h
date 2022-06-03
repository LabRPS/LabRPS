#ifndef GITHUBRESTAPICLIENT_H
#define GITHUBRESTAPICLIENT_H

#include <QtNetwork>
#include <QObject>

class GitHubRestApiClient : public QObject
{
    Q_OBJECT
public:
    GitHubRestApiClient();
    virtual ~GitHubRestApiClient();

    /**
     * @brief getLatestReleaseVersion
     * @param owner The owner of the repository, as in github.com/bitbloq would be bitbloq
     * @param project The name of the project, as in github.com/bitbloq/bitbloqlibs would be bitbloqlibs
     * @param timeout timeout to get the version number (in case there is no internet connection or it is too slow
     * @return JSON object with the last version info (includir zip-ball and tar-ball files)
     */
    QJsonObject getLatestReleaseVersion(QString owner, QString project, int timeout = 5000);

    /**
     * @brief getLatestTagVersion
     * @param owner The owner of the repository, as in github.com/bitbloq would be bitbloq
     * @param project The name of the project, as in github.com/bitbloq/bitbloqlibs would be bitbloqlibs
     * @param timeout timeout to get the version number (in case there is no internet connection or it is too slow
     * @return JSON object with the last tag version info (includir zip-ball and tar-ball files)
     */
    QJsonObject getLatestTagVersion(QString owner, QString project, int timeout = 5000);

    /**
     * @brief downloadFile
     * @param url where the files is
     * @param path where the files must be stored
     * @param filename name of the file
     * @param timeout timeout to succeed
     * @return
     */
    bool downloadFile(QString url, QString path, QString filename, int timeout=5000);

private:
    QJsonDocument get(const QUrl & url, const QString & header, int timeout);
    bool saveToDisk(const QString &dir, QString &filename, QIODevice *data);

    QTimer* _timer;
    bool _timeout;

public slots:
    void setTimeOut();
};

#endif // GITHUBRESTAPICLIENT_H
