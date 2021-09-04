#ifndef DEFINES_H
#define DEFINES_H

#include "widgetdefines.h"

#include <QDebug>

#include <QStandardPaths>
#include <QDir>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>



#define USERSFILE APPDATALOCATION() + "/users.json"

/**
 * Returns the path to this application's AppData folder
*/
inline const QString APPDATALOCATION();

/**
 * Checks the existence of parameter given folder
 * and creates it if it does not exist
*/
inline void checkFolderExistence(const QString& folderPath);
/**
 * Checks the existence of the parameter given file
 * and creates it if it does not exist with the default or provided content
*/
inline void checkFileExistence(const QString& filename, const QJsonDocument& defaultContent = QJsonDocument());

/**
 * Writes the parameter given JSON content to the parameter given file
*/
inline void writeJSONFile(const QString& filename, const QJsonDocument& content);
/**
 * Returns the JSON content of the parameter given file
*/
inline const QJsonDocument readJSONFile(const QString& filename);



inline const QString APPDATALOCATION()
{
    //Get the AppData folder path
    const auto locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    //The 0. element of the QStringList is the general AppData folder path appended with the Organization name and Application name
    const auto appdataFolder = locations.at(0);

    return appdataFolder;
}

inline void checkFolderExistence(const QString& folderPath)
{
    //Check whether the parameter given folder exists
    //and create it if it does not
    QDir folder(folderPath);
    if(!folder.exists())
    {
        folder.mkpath(folderPath);
    }
}

inline void checkFileExistence(const QString& filename, const QJsonDocument& defaultContent)
{
    //Check whether the parameter given JSON file exists
    //and create it if it does not
    if(!QFileInfo::exists(filename))
    {
        QJsonDocument jsonDocument;
        if(defaultContent.isNull())
        {
            QJsonObject rootObject;
            jsonDocument = QJsonDocument(rootObject);
        }
        else
        {
           jsonDocument = defaultContent;
        }


        writeJSONFile(filename, jsonDocument);
    }
}

inline void writeJSONFile(const QString& filename, const QJsonDocument& content)
{
    //Open the parameter given file
    //and write the parameter given content in it
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(content.toJson());
        file.close();
    }
}

inline const QJsonDocument readJSONFile(const QString& filename)
{
    QJsonDocument content;

    //Open the parameter given file
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        //Get the JSON content of the opened file and return it
        content = QJsonDocument::fromJson(file.readAll());

        file.close();
    }

    return content;
}

#endif // DEFINES_H
