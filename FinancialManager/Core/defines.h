#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>

#include <QStandardPaths>
#include <QDir>
#include <QFile>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QStyle>

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>

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

/**
 * Removes the child QWidget of the parameter given parentWidget and parentLayout
 * and deletes the removed QWidget
*/
inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout);

/**
 * Sets the error property for the parameter given QLineEdit
 * After the new property value is set updates the QLineEdit style
 * so the ui changes are applied
*/
inline void setLineEditErrorState(QLineEdit* lineEdit, bool error);
/**
 * Sets the isNegative property for the parameter given QLabel
 * After the new property value is set updates the QLabel style
 * so the ui changes are applied
*/
inline void setLabelNegativeState(QLabel* label, bool isNegative);

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

inline void deleteActiveContentWidget(QWidget* parentWidget, QLayout* parentLayout)
{
    //Get the current QWidget child to the parameter given parentWidget
    //and remove it from parameter given parentLayout if it is valid
    //and delete it
    auto activeWidget = parentWidget->findChild<QWidget*>();
    if(activeWidget)
    {
        parentLayout->removeWidget(activeWidget);
        activeWidget->deleteLater();
    }
}

inline void setLineEditErrorState(QLineEdit* lineEdit, bool error)
{
    lineEdit->setProperty("error", error);

    //Update the style of the QLineEdit
    //so the dynamic property dependent changes are applied
    lineEdit->style()->unpolish(lineEdit);
    lineEdit->style()->polish(lineEdit);
}

inline void setLabelNegativeState(QLabel* label, bool isNegative)
{
    label->setProperty("isNegative", isNegative);

    //Update the style of the QLabel
    //so the dynamic property dependent changes are applied
    label->style()->unpolish(label);
    label->style()->polish(label);
}

#endif // DEFINES_H
