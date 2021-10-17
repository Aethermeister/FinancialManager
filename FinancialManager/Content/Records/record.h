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
        Record(const int value, const QDate& date, const QTime& time, const QString& location, const QString& item);

        const bool operator==(const Record& record) const;

        int value() const;

        const QDate &date() const;

        const QTime &time() const;

        const QString &location() const;
        void setLocation(const QString &newLocation);

        const QString &item() const;

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
    };
}

#endif // RECORD_H
