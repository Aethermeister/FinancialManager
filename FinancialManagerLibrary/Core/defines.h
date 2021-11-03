#ifndef DEFINES_H
#define DEFINES_H

#include "global_defines.h"
#include "widgetdefines.h"
#include "encrypt.h"
#include "Settings/settingsmanager.h"

#include <QDebug>

#include <QStandardPaths>
#include <QDir>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


#define USERSFILE APPLICATIONFOLDER() + "/users.json"

/**
 * Returns the path to the currently used application files (e.g.: users.json)
*/
inline const QString APPLICATIONFOLDER();

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


inline const QString APPLICATIONFOLDER()
{
    //'folderPath' holds the path to the currently used application files
    QString folderPath = QString();
    //Get the FILE_STORAGE settings data
    const auto fileStorage = Settings::SettingsManager::instance()->data<Settings::FileStorage>(Settings::SettingsData::FILE_STORAGE);

    //Set the 'folderPath' variable according to the set FILE_STORAGE value
    if(fileStorage == Settings::FileStorage::LOCAL)
    {
        folderPath = APPDATALOCATION();
    }
    else if(fileStorage == Settings::FileStorage::CUSTOM)
    {
        //If CUSTOM FILE_STORAGE is used than retrieve the CUSTOM_STORAGE_PATH from the settings
        folderPath = Settings::SettingsManager::instance()->data<QString>(Settings::SettingsData::CUSTOM_STORAGE_PATH);
    }

    return folderPath;
}

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
        //Create a compressed version of the json content before saving it to the file
        const auto jsonContent = content.toJson();
        const auto compressedJsonContent = compressData(jsonContent);

        file.write(compressedJsonContent);
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
        //After reading the content of the file uncompress it so the data can be processed
        const auto fileContent = file.readAll();
        const auto uncompressedFileContent = uncompressData(fileContent);

        //Get the JSON content of the opened file and return it
        content = QJsonDocument::fromJson(uncompressedFileContent);

        file.close();
    }

    return content;
}

#endif // DEFINES_H
