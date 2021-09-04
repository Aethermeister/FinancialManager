#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>
#include <QDate>
#include <QTime>
#include <QCompleter>

/**
 * Struct for the Records
 * The user manages a list of this struct
 * This struct wraps the Record related informations
*/
struct Record
{
public:
    Record(const int amount, const QDate& date, const QTime& time, const QString& location, const QString& whatFor) :
        Amount(amount),
        Date(date),
        Time(time),
        Location(location),
        WhatFor(whatFor)
    {
    }

    int Amount;

    QDate Date;
    QTime Time;

    QString Location;
    QString WhatFor;
};

/**
 * Class to store the user related informations and behaviours
 * The User manages a list of Record which is the essential data source for other operations
 * The User is responsible for getting existing data, managing and persisting them
*/
class User
{
public:
    User(const QString& username, const QString& password, const QString& id);
    ~User();

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
     * Creates a QCompleter for the whatFor QLineEdit in the NewRecordWidget ui class
     * This QCompleter is used so the user does not have to type the already used whatFors
    */
    QCompleter* whatForsCompleter() const;

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

private:
    /**
     * Checks the User related AppData files
     * and creates it if it does not exist
    */
    void checkUserFiles() const;
    /**
     * Read the User records file and parse the contained data
     * Creates the list of Records from the parsed data
    */
    void readRecordsFile();
    /**
     * Updates the source list used by the related QCompleters
     * The lists are appended with the parameter given values
    */
    void updateCompleterSource(const QString& location, const QString& whatFor);

    /**
     * Saves the actual Records list to the Records file in the User AppData folder
    */
    void persistRecordsData() const;

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
     * Path to the user specific folder in the AppData
    */
    QString m_userFolder;
    /**
     * Path to the user specific records file in the AppData
    */
    QString m_userRecordsFile;

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
     * List of the previously used whatFors without duplications
     * Used as source for the corresponding QCompleter
    */
    QStringList m_whatFors;
};

#endif // USER_H
