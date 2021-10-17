#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QDate>
#include <QTime>
#include <QCompleter>

/**
 * Struct for the Pockets
 * The user manages a list of this struct
 * This struct wraps the Pocket related informations
*/
struct Pocket
{
    /**
     * Enum holding the possible Pocket types
    */
    enum PocketType
    {
        CASH,
        CARD,

        END_OF_ENUM
    };

    /**
     * Map of PocketTypes and their names in QString
     * Used to convert PocketType to its QString name and vice versa
    */
    static const QMap<QString, Pocket::PocketType> TypeNameToPocketType;

public:
    /**
     * Constructor to create a new Pocket
    */
    Pocket(const QString& name, const QString& pocketTypeString, int value) :
        Name(name),
        Type(stringToPocketType(pocketTypeString)),
        InitialValue(value),
        Value(value),
        CreationDate(QDateTime::currentDateTime())
    {
        qDebug() << "Pocket Constructor";
    }

    /**
     * Constructor to create a new Pocket for an already stored Pocket
    */
    Pocket(const QString& name, const PocketType& type, int initialValue, int value, const QDateTime& creationDate) :
        Name(name),
        Type(type),
        InitialValue(initialValue),
        Value(value),
        CreationDate(creationDate)
    {
        qDebug() << "Pocket Constructor";
    }

    ~Pocket()
    {
        qDebug() << "Pocket Destructor";
    }

    Pocket(const Pocket& pocket) :
        Name(pocket.Name),
        Type(pocket.Type),
        InitialValue(pocket.InitialValue),
        Value(pocket.Value),
        CreationDate(pocket.CreationDate)
    {
        qDebug() << "Pocket Copy Constructor";
    }

    Pocket(Pocket&& pocket) :
        Name(std::move(pocket.Name)),
        Type(pocket.Type),
        InitialValue(pocket.InitialValue),
        Value(pocket.Value),
        CreationDate(std::move(pocket.CreationDate))
    {
        qDebug() << "Pocket Move Constructor";
    }

    bool operator==(const Pocket& pocket)
    {
        return Name == pocket.Name;
    }

    /**
     * Returns the name of the parameter given Pocket type
    */
    static const QString pocketTypeToString(const PocketType& pocketType)
    {
        return TypeNameToPocketType.key(pocketType);
    }

    /**
     * Returns the type of the parameter given Pocket type string
    */
    static const PocketType stringToPocketType(const QString& pocketTypeString)
    {
        return TypeNameToPocketType[pocketTypeString];
    }

    /**
     * Name of the Pocket
    */
    QString Name;
    /**
     * Type of the Pocket
    */
    PocketType Type;
    /**
     * Initial value of the Pocket
    */
    int InitialValue;
    /**
     * Current value of the Pocket
    */
    int Value;
    /**
     * Date of the Pocket creation
    */
    QDateTime CreationDate;
};

/**
 * Struct for the Records
 * The user manages a list of this struct
 * This struct wraps the Record related informations
*/
struct Record
{
public:
    Record(const int amount, const QDate& date, const QTime& time, const QString& location, const QString& item) :
        Amount(amount),
        Date(date),
        Time(time),
        Location(location),
        Item(item)
    {
    }

    bool operator==(const Record &record)
    {
        return (
                    Amount == record.Amount &&
                    Item == record.Item &&
                    Location == record.Location &&
                    Date == record.Date &&
                    Time == record.Time
                );
    }

    int Amount;

    QDate Date;
    QTime Time;

    QString Location;
    QString Item;
};

/**
 * Class to store the user related informations and behaviours
 * The User manages a list of Record which is the essential data source for other operations
 * The User is responsible for getting existing data, managing and persisting them
*/
class User : public QObject
{
    Q_OBJECT

public:
    User(const QString& username, const QString& password, const QString& id, QObject *parent = Q_NULLPTR);
    ~User();

    /**
     * Stores the parameter given Pocket in the Pocket list
     * This operation stores the new Pocket only in memory
    */
    void addNewPocket(Pocket& newPocket);

    /**
     * Stores the parameter given Record in the Record list
     * This operation stores the new Record only in memory
    */
    void persistNewRecord(const Record& newRecord);

    /**
     * Creates a QCompleter for the location QLineEdit in the NewRecordWidget ui class
     * This QCompleter is used so the user does not have to type the already used locations
    */
    QCompleter* locationsCompleter() const;
    /**
     * Creates a QCompleter for the item QLineEdit in the NewRecordWidget ui class
     * This QCompleter is used so the user does not have to type the already used items
    */
    QCompleter* itemsCompleter() const;

    /**
     * Returns the username
    */
    const QString username() const;
    /**
     * Returns the user id
    */
    const QString id() const;
    /**
     * Returns the user password
    */
    const QString password() const;
    /**
     * Sets the user password with the parameter given value
    */
    void setPassword(const QString& password);

    /**
     * Returns whether the user account will be deleted
    */
    bool isMarkedForDeletion() const;
    /**
     * Sets the deletion state of the user account
    */
    void setMarkedForDeletion(bool marked);

    /**
     * Returns the list of Pockets
    */
    const std::vector<Pocket>& pockets();

    /**
     * Removes the parameter given Record from the list of Records
    */
    void deleteRecord(const Record &record);

    /**
     * Returns the list of Records
    */
    QList<Record> records();

private:
    /**
     * Checks the User related AppData files
     * and creates it if it does not exist
    */
    void checkUserFiles() const;

    /**
     * Read the User pockets file and parse the contained data
     * Creates the list of Pockets from the parsed data
    */
    void readPocketsFile();

    /**
     * Read the User records file and parse the contained data
     * Creates the list of Records from the parsed data
    */
    void readRecordsFile();
    /**
     * Updates the source list used by the related QCompleters
     * The lists are appended with the parameter given values
    */
    void updateCompleterSource(const QString& location, const QString& item);

    /**
     * Saves the actual Pockets list to the Pockets file in the User AppData folder
    */
    void persistPocketsData() const;

    /**
     * Saves the actual Records list to the Records file in the User AppData folder
    */
    void persistRecordsData() const;

    /**
     * Returns the index of the new Record among the existing Records according to the new Record's date time values
    */
    int searchForNewRecordPosition(const QDate &searchedDate, const QTime &searchedTime);

    /**
     * Deletes the user related files and the user data from the users file
    */
    void deleteUser() const;

    /**
     * Username of the user
    */
    QString m_username;
    /**
     * Password of the user
    */
    QString m_password;
    /**
     * User id of the user
    */
    QString m_id;

    /**
     * Flag which indicates whether the user has to be deleted
    */
    bool m_isMarkedForDeletion = false;

    /**
     * Path to the user specific folder
    */
    QString m_userFolder;
    /**
     * Path to the user specific pockets file
    */
    QString m_userPocketsFile;
    /**
     * Path to the user specific records file
    */
    QString m_userRecordsFile;

    /**
     * List of the user's pockets
    */
    std::vector<Pocket> m_pockets;

    /**
     * List of the user's records
    */
    QList<Record> m_records;
    /**
     * List of the previously used locations without duplications
     * Used as source for the corresponding QCompleter
    */
    QStringList m_locations;
    /**
     * List of the previously used items without duplications
     * Used as source for the corresponding QCompleter
    */
    QStringList m_items;

signals:
    /**
     * Emitted when the user creates a new record
     * The first integer parameter is the index of the new Record in the history
     * The other parameter is the newly created Record
    */
    void sig_recordAdded(int index, const Record &record);
    /**
     * Emitted when the user deletes a record either by reverting a record creation
     * or deleting an existing record from the history
     * The parameter is the deleted Record
    */
    void sig_recordDeleted(const Record &record);
};

#endif // USER_H
