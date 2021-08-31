#include "user.h"
#include "Core/defines.h"

User::User(const QString &username, const QString &password, const QString &id) :
    m_username(username), m_password(password), m_id(id)
{
    m_userFolder = APPDATALOCATION() + "/" + m_id;
    m_userRecordsFile = m_userFolder + "/records.json";

    checkUserFiles();
    readRecordsFile();
}

User::~User()
{
    persistRecordsData();
}

void User::persistNewRecord(const Record& newRecord)
{
    //Update the completer source lists
    updateCompleterSource(newRecord.Location, newRecord.WhatFor);

    //Store the new Record in memory
    m_records.prepend(std::move(newRecord));
}

QCompleter *User::locationsCompleter() const
{
    return new QCompleter(m_locations);
}

QCompleter *User::whatForsCompleter() const
{

    return new QCompleter(m_whatFors);
}

void User::checkUserFiles() const
{
    //Check the User AppData folder
    const auto userFolder = m_userFolder;
    checkFolderExistence(userFolder);

    //Check the existence of the User Records file
    QJsonArray defaultArray;
    QJsonDocument defaultDocument = QJsonDocument(defaultArray);
    checkFileExistence(m_userRecordsFile, defaultDocument);
}

void User::readRecordsFile()
{
    //Get the raw content of the Records file
    const auto recordsDocument = readJSONFile(m_userRecordsFile);
    const auto recordsRootArray = recordsDocument.array();

    //Parse the Record data one by one
    for(const auto& recordData : recordsRootArray)
    {
        const auto recordObject = recordData.toObject();

        const auto amount = recordObject.value("amount").toInt();
        const auto date = QDate::fromString(recordObject.value("date").toString());
        const auto time = QTime::fromString(recordObject.value("time").toString());
        const auto location = recordObject.value("location").toString();
        const auto whatFor = recordObject.value("whatFor").toString();

        //Update the completer source lists
        updateCompleterSource(location, whatFor);

        //Put the Record to the beginning of the list so the latest Record will be the first element
        m_records.prepend(Record(amount, date, time, location, whatFor));
    }
}

void User::updateCompleterSource(const QString &location, const QString &whatFor)
{
    //Check whether the parameter given location is already stored
    //and store it if not
    if(!m_locations.contains(location))
    {
        m_locations.prepend(location);
    }

    //Check whether the parameter given whatFor is already stored
    //and store it if not
    if(!m_whatFors.contains(whatFor))
    {
        m_whatFors.prepend(whatFor);
    }
}

void User::persistRecordsData() const
{
    //Create an array from the actual Records list
    QJsonArray recordsArray;
    for(const auto& record : m_records)
    {
        QJsonObject recordObject
        {
            {"amount", record.Amount},
            {"date", record.Date.toString()},
            {"time", record.Time.toString()},
            {"location", record.Location},
            {"whatFor", record.WhatFor}
        };

        recordsArray.append(recordObject);
    }

    //Save the Records to the Records file in the AppData folder
    const auto recordsDocument = QJsonDocument(recordsArray);
    writeJSONFile(m_userRecordsFile, recordsDocument);
}
