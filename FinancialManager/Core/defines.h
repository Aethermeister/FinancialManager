#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>

#include <QStandardPaths>
#include <QDir>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>

#include <QWidget>
#include <QLayout>

#define USERSFILE APPDATALOCATION() + "/users.json"

inline const QString APPDATALOCATION();

inline void checkAppDataFolder();
inline void checkUsersFile();

inline void writeJSONFile(const QString& filename, const QJsonDocument content);
inline const QJsonDocument readJSONFile(const QString& filename);

inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout);



inline const QString APPDATALOCATION()
{
    QString appdataFolder = QString();

    const auto locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    appdataFolder = locations.at(0);

    return appdataFolder;
}

inline void checkAppDataFolder()
{
    QDir appdataDir(APPDATALOCATION());
    if(!appdataDir.exists())
    {
        appdataDir.mkpath(APPDATALOCATION());
    }
}

inline void checkUsersFile()
{
    if(!QFileInfo::exists(USERSFILE))
    {
        QJsonObject rootObject;
        QJsonDocument jsonDocument(rootObject);

        writeJSONFile(USERSFILE, jsonDocument);
    }
}

inline void writeJSONFile(const QString& filename, const QJsonDocument content)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(content.toJson());
    file.close();
}

inline const QJsonDocument readJSONFile(const QString& filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QJsonDocument content = QJsonDocument::fromJson(file.readAll());

    file.close();

    return content;
}

inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout)
{
    auto activeWidget = parentWidget->findChild<QWidget*>();
    if(activeWidget)
    {
        parentLayout->removeWidget(activeWidget);
        activeWidget->deleteLater();
    }
}

#endif // DEFINES_H
