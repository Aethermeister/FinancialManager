#include "user.h"
#include "Core/defines.h"

User::User(const QString &username, const QString &password, const QString &id, QObject *parent) :
    QObject(parent), m_username(username), m_password(password), m_id(id)
{
    m_userFolder = APPLICATIONFOLDER() + "/" + m_id;
    m_userRecordsFile = m_userFolder + "/records.json";

    checkUserFiles();
    readRecordsFile();
}

User::~User()
{
    //Delete the user and the user related files if the deletion mark was previously set
    if(m_isMarkedForDeletion)
    {
        deleteUser();
    }
    else //Otherwise save the records data to the corresponding file
    {
        persistRecordsData();
    }
}

void User::persistNewRecord(const Record& newRecord)
{
    //Update the completer source lists
    updateCompleterSource(newRecord.Location, newRecord.WhatFor);

    //Search for the index where the new Record should be inserted
    //and store the new Record in memory at the correct position
    const auto indexOfNewRecord = searchForNewRecordPosition(newRecord.Date, newRecord.Time);
    m_records.insert(indexOfNewRecord, newRecord);

    emit sig_recordAdded(indexOfNewRecord, newRecord);
}

QCompleter *User::locationsCompleter() const
{
    return new QCompleter(m_locations);
}

QCompleter *User::whatForsCompleter() const
{

    return new QCompleter(m_whatFors);
}

const QString User::username() const
{
    return m_username;
}

const QString User::id() const
{
    return m_id;
}

const QString User::password() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}

bool User::isMarkedForDeletion() const
{
    return m_isMarkedForDeletion;
}

void User::setMarkedForDeletion(bool marked)
{
    m_isMarkedForDeletion = marked;
}

void User::deleteRecord(const Record &record)
{
    m_records.removeOne(record);
    emit sig_recordDeleted(record);
}

QList<Record> User::records()
{
    return m_records;
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
    //Remove the new location before adding it to the QList to prevent duplications
    m_locations.removeOne(location);
    m_locations.prepend(location);

    //Remove the new whatFor before adding it to the QList to prevent duplications
    m_whatFors.removeOne(whatFor);
    m_whatFors.prepend(whatFor);
}

void User::persistRecordsData() const
{
    //Create an array from the actual Records list
    QJsonArray recordsArray;

    QList<Record>::const_reverse_iterator record;
    for(record = m_records.crbegin(); record != m_records.crend(); ++record)
    {
        QJsonObject recordObject
        {
            {"amount", record->Amount},
            {"date", record->Date.toString()},
            {"time", record->Time.toString()},
            {"location", record->Location},
            {"whatFor", record->WhatFor}
        };

        recordsArray.append(recordObject);
    }

    //Save the Records to the Records file in the AppData folder
    const auto recordsDocument = QJsonDocument(recordsArray);
    writeJSONFile(m_userRecordsFile, recordsDocument);
}

int User::searchForNewRecordPosition(const QDate &searchedDate, const QTime &searchedTime)
{
    //Search the for the index of the new Record
    //Iterate over the list of existing Records and compare the date time values
    int counter = 0;
    for(auto& record : m_records)
    {
        //Since the Records are stored in chronological order check whether the new Record's date is greater than the tested one
        if(searchedDate > record.Date)
        {
            break;
        }
        else if(searchedDate == record.Date) //If the new Record is created on a day when there are already Records check the time
        {
            if(searchedTime >= record.Time)
            {
                break;
            }
        }

        counter += 1;
    }

    return counter;
}

void User::deleteUser() const
{
    //Remove the user related files
    QDir dir(m_userFolder);
    dir.removeRecursively();

    //Get the content of the users JSON file
    //and modify it by removing this user
    const auto usersDocument = readJSONFile(USERSFILE);
    auto usersObject = usersDocument.object();
    usersObject.remove(m_username);

    //Save the modified JSON content to the users JSON file
    const auto modifiedUsersDocument = QJsonDocument(usersObject);
    writeJSONFile(USERSFILE, modifiedUsersDocument);
}
