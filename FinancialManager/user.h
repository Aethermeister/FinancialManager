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

    QString m_username;
    QString m_password;
    QString m_id;

    QString m_userFolder;
    QString m_userRecordsFile;

    QList<Record> m_records;
    QStringList m_locations;
    QStringList m_whatFors;
};

#endif // USER_H
