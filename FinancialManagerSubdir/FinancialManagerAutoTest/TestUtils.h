#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QString>
#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QJsonObject>

inline void deleteFile(const QString& filename)
{
    QFile file(filename);
    if(file.exists())
    {
        file.remove();
    }
}

inline void deleteFolder(const QString& folderPath)
{
    QDir(folderPath).removeRecursively();
}

inline void makeFolder(const QString& folderPath)
{
    QDir folder(folderPath);
    if(!folder.exists())
    {
        folder.mkpath(folderPath);
    }
}

inline const QString username = "test_user";
inline const QString password = "test_user";
inline const QJsonObject testData
{
    {
        username, QJsonObject
        {
            {"id", username},
            {"password", QString(password.toUtf8().toBase64())}
        }}
};

#endif // TESTUTILS_H
