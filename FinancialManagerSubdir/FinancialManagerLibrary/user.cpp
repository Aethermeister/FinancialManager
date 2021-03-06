#include "user.h"
#include "Core/defines.h"
#include "Notification/notificationwidget.h"
#include "Content/contentwidget.h"

User::User(const QString &username, const QString &password, const QString &id, QObject *parent) :
    QObject(parent), m_username(username), m_password(password), m_id(id)
{
    m_userFolder = APPLICATIONFOLDER() + "/" + m_id;
    m_userPocketsFile = m_userFolder + "/pockets.json";
    m_userRecordsFile = m_userFolder + "/records.json";

    checkUserFiles();
    readPocketsFile();
    readRecordsFile();

    initializeAutoSaveTimer();
}

User::~User()
{
    //Stop and delete the auto save QTimer manually
    m_autoSaveTimer->stop();
    m_autoSaveTimer->deleteLater();

    //Delete the user and the user related files if the deletion mark was previously set
    if(m_isMarkedForDeletion)
    {
        deleteUser();
    }
    else //Otherwise save the records data to the corresponding file
    {
        persistPocketsData();
        persistRecordsData();
    }
}

void User::addNewPocket(Content::Pockets::Pocket &newPocket)
{
    m_pockets.push_back(std::move(newPocket));
    m_shouldSaveUserData = true;
}

void User::deletePocket(const Content::Pockets::Pocket &deletedPocket)
{
    //Removing records is only possible if the container vector is not empty
    if(!m_records.empty())
    {
        //Remove the records which are linked to the parameter given Pocket
        m_records.erase(
            std::remove_if(m_records.begin(), m_records.end(),[=](const Content::Records::Record& record)
            {
                return record.pocketName() == deletedPocket.name();
            }), m_records.end()
        );
    }
    m_records.shrink_to_fit();

    //Remove the pocket itself
    m_pockets.erase(std::find(m_pockets.begin(), m_pockets.end(), deletedPocket));

    m_shouldSaveUserData = true;
}

void User::persistNewRecord(const Content::Records::Record& newRecord)
{
    //Update the completer source lists
    updateCompleterSource(newRecord.location(), newRecord.item());

    //Search for the index where the new Record should be inserted
    //and store the new Record in memory at the correct position
    const auto indexOfNewRecord = searchForNewRecordPosition(newRecord.date(), newRecord.time());
    m_records.insert(m_records.begin() + indexOfNewRecord, newRecord);

    //Find the Record's Pocket
    auto foundPocket = std::find_if(m_pockets.begin(), m_pockets.end(), [=](const Content::Pockets::Pocket& pocket)
    {
        return pocket.name() == newRecord.pocketName();
    });

    //Adjust the Pocket values
    foundPocket->setRecordsCount(foundPocket->recordsCount() + 1);
    foundPocket->setValue(foundPocket->value() + newRecord.value());
    //If the index is 0 than this new Record is the latest
    //Update the Pocket last usage date with the Record's date
    if(indexOfNewRecord == 0)
    {
        foundPocket->setLastUsedDate(newRecord.date());
    }

    emit sig_recordAdded(indexOfNewRecord, newRecord);
    m_shouldSaveUserData = true;
}

QCompleter *User::locationsCompleter() const
{
    return new QCompleter(m_locations);
}

QCompleter *User::itemsCompleter() const
{

    return new QCompleter(m_items);
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

const std::vector<Content::Pockets::Pocket>& User::pockets() const
{
    return m_pockets;
}

void User::deleteRecord(const Content::Records::Record &record)
{
    //Find the Record's Pocket
    auto foundPocket = std::find_if(m_pockets.begin(), m_pockets.end(), [=](const Content::Pockets::Pocket& pocket)
    {
        return pocket.name() == record.pocketName();
    });

    //Adjust the Pocket values
    foundPocket->setRecordsCount(foundPocket->recordsCount() - 1);
    foundPocket->setValue(foundPocket->value() - record.value());

    //Remove the pocket itself
    m_records.erase(std::find(m_records.begin(), m_records.end(), record));
    emit sig_recordDeleted(record);

    m_shouldSaveUserData = true;
}

const std::vector<Content::Records::Record>& User::records() const
{
    return m_records;
}

void User::initializeAutoSaveTimer()
{
    //Create a non-singleshot QTimer with 10 sec interval
    m_autoSaveTimer = new QTimer();
    m_autoSaveTimer->setInterval(10000);
    m_autoSaveTimer->setSingleShot(false);

    //Save teh modified user data on timeout
    connect(m_autoSaveTimer, &QTimer::timeout, [=]
    {
        //Check whether the user data should be saved
        if(m_shouldSaveUserData)
        {
            //Save the user data
            persistPocketsData();
            persistRecordsData();

            m_shouldSaveUserData = false;

            //Show notification about the auto saved user data
            Notification::NotificationWidget* autoSaveNotification =
                    new Notification::NotificationWidget("User data has been saved", Content::ContentWidget::instance());
            autoSaveNotification->show();
        }
    });

    m_autoSaveTimer->start();
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

void User::readPocketsFile()
{
    //Get the raw content of the Pockets file
    const auto pocketsDocument = readJSONFile(m_userPocketsFile);
    const auto pocketsRootArray = pocketsDocument.array();

    //Parse the Pocket data one by one
    for(const auto& pocketData : pocketsRootArray)
    {
        const auto pocketObject = pocketData.toObject();

        const auto name = pocketObject.value("name").toString();
        const auto type = Content::Pockets::Pocket::stringToPocketType(pocketObject.value("type").toString());
        const auto initialValue = pocketObject.value("initialValue").toInt();
        const auto value = pocketObject.value("value").toInt();
        const auto creationDate = QDateTime::fromString(pocketObject.value("creationDate").toString());
        const auto lastUsedDate = QDate::fromString(pocketObject.value("lastUsedDate").toString());
        const auto recordsCount = pocketObject.value("recordsCount").toInt();

        m_pockets.emplace_back(name, type, initialValue, value, creationDate, lastUsedDate, recordsCount);
    }
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

        const auto value = recordObject.value("value").toInt();
        const auto date = QDate::fromString(recordObject.value("date").toString());
        const auto time = QTime::fromString(recordObject.value("time").toString());
        const auto location = recordObject.value("location").toString();
        const auto item = recordObject.value("item").toString();
        const auto pocket = recordObject.value("pocket").toString();

        //Update the completer source lists
        updateCompleterSource(location, item);

        //Put the Record to the beginning of the list so the latest Record will be the first element
        m_records.emplace_back(value, date, time, location, item, pocket);
    }

    std::reverse(m_records.begin(), m_records.end());
}

void User::updateCompleterSource(const QString &location, const QString &item)
{
    //Remove the new location before adding it to the QList to prevent duplications
    m_locations.removeOne(location);
    m_locations.prepend(location);

    //Remove the new item before adding it to the QList to prevent duplications
    m_items.removeOne(item);
    m_items.prepend(item);
}

void User::persistPocketsData() const
{
    //Create an array from the actual Pockets list
    QJsonArray pocketsArray;

    //Iterate over the Pockets list and create a json object for each pocket
    for(const auto& pocket : m_pockets)
    {
        QJsonObject pocketObject
        {
            {"name", pocket.name()},
            {"type", Content::Pockets::Pocket::pocketTypeToString(pocket.type())},
            {"initialValue", pocket.initialValue()},
            {"value", pocket.value()},
            {"creationDate", pocket.creationDate().toString()},
            {"lastUsedDate", pocket.lastUsedDate().toString()},
            {"recordsCount", pocket.recordsCount()}
        };

        pocketsArray.append(pocketObject);
    }

    //Save the Pockets to the Pockets file in the AppData folder
    const auto pocketsDocument = QJsonDocument(pocketsArray);
    writeJSONFile(m_userPocketsFile, pocketsDocument);
}

void User::persistRecordsData() const
{
    //Create an array from the actual Records list
    QJsonArray recordsArray;

    //Iterate over the Records list and create a json object for each record
    //Reverse iterator is used so the order of the Records remains during parsing the file
    std::vector<Content::Records::Record>::const_reverse_iterator record;
    for(record = m_records.crbegin(); record != m_records.crend(); ++record)
    {
        QJsonObject recordObject
        {
            {"value", record->value()},
            {"date", record->date().toString()},
            {"time", record->time().toString()},
            {"location", record->location()},
            {"item", record->item()},
            {"pocket", record->pocketName()}
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
        if(searchedDate > record.date())
        {
            break;
        }
        else if(searchedDate == record.date()) //If the new Record is created on a day when there are already Records check the time
        {
            if(searchedTime >= record.time())
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
