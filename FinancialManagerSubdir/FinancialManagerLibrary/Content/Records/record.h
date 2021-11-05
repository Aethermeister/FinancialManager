#ifndef RECORD_H
#define RECORD_H

#include <QDate>
#include <QTime>

namespace Content::Records
{
    /**
     * Class for the Records
     * The user manages a list of Records
     * This class wraps the Record related informations
    */
    class Record
    {
    public:
        Record(const int value, const QDate& date, const QTime& time, const QString& location, const QString& item, const QString& pocketName);

        Record(const Record& pocket) = default;
        Record(Record&& pocket) = default;

        Record& operator=(const Record&) = default;
        Record& operator=(Record&& other) = default;

        const bool operator==(const Record& record) const;

        /**
         * Returns the Record value
        */
        int value() const;
        /**
         * Returns the creation date of the Record
        */
        const QDate &date() const;
        /**
         * Returns the creation time of the Record
        */
        const QTime &time() const;
        /**
         * Returns the location of the Record
        */
        const QString &location() const;
        /**
         * Returns the item this Record was created for
        */
        const QString &item() const;
        /**
         * Returns the name of the Pocket this Record is linked to
        */
        const QString &pocketName() const;

    private:
        /**
         * Value of the Record
        */
        int m_value;

        /**
         * Creation date of the Record
        */
        QDate m_date;
        /**
         * Creation time of the Record
        */
        QTime m_time;

        /**
         * Location of the Record
        */
        QString m_location;
        /**
         * Item name of the Record
        */
        QString m_item;
        /**
         * Name of the linked Pocket
        */
        QString m_pocketName;
    };
}

#endif // RECORD_H
