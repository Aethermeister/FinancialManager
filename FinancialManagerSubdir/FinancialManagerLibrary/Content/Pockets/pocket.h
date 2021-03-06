#ifndef POCKET_H
#define POCKET_H
#include "Core/global_defines.h"

#include <QString>
#include <QDateTime>
#include <QDate>
#include <QMap>

namespace Content::Pockets
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
     * Class for the Pockets
     * The user manages a list of Pocket objects
     * This class wraps the Pocket related informations
    */
    class LIB_EXPORT Pocket
    {
    public:
       Pocket(const QString& name, const QString& pocketTypeString, int value);
       Pocket(const QString& name, const PocketType& type, int initialValue, int value, const QDateTime& creationDate, const QDate &lastUsedDate, int recordsCount);

       Pocket(const Pocket& pocket) = default;
       Pocket(Pocket&& pocket) = default;

       Pocket& operator=(const Pocket&) = default;
       Pocket& operator=(Pocket&& other) = default;

       bool operator==(const Pocket& pocket);

       /**
        * Returns the name of the parameter given Pocket type
       */
       static const QString pocketTypeToString(const PocketType& pocketType);
       /**
        * Returns the type of the parameter given Pocket type string
       */
       static const PocketType stringToPocketType(const QString& pocketTypeString);

       /**
        * Returns the name of the Pocket
        */
       const QString &name() const;

       /**
        * Returns the type of the Pocket
        */
       PocketType type() const;

       /**
        * Returns the initial value of the Pocket
        */
       int initialValue() const;

       /**
        * Returns the overall value of the Pocket
        */
       int value() const;
       /**
        * Set the overall value of the Pocket
        */
       void setValue(int newValue);

       /**
        * Returns the creation date of the Pocket
        */
       const QDateTime &creationDate() const;

       /**
        * Set the date of last usage of the Pocket
        */
       void setLastUsedDate(const QDate &newLastUsedDate);
       /**
        * Returns the date of the last usage
        */
       const QDate &lastUsedDate() const;

       /**
        * Returns how many Record is linked to this Pocket
        */
       int recordsCount() const;
       /**
        * Set how many Records is linked to this Pocket
        */
       void setRecordsCount(int newRecordsCount);

    private:
        /**
         * Map of PocketTypes and their names in QString
         * Used to convert PocketType to its QString name and vice versa
        */
        static const QMap<QString, PocketType> TypeNameToPocketType;

        /**
         * Name of the Pocket
        */
        QString m_name;
        /**
         * Type of the Pocket
        */
        PocketType m_type;
        /**
         * Initial value of the Pocket
        */
        int m_initialValue;
        /**
         * Current value of the Pocket
        */
        int m_value;
        /**
         * Date of the Pocket creation
        */
        QDateTime m_creationDate;

        /**
         * Date of the last usage of this Pocket
         * Date of the last created (Record creation date) Record which is linked to this Pocket
        */
        QDate m_lastUsedDate;

        /**
         * Actual count of records linked to this Pocket
        */
        int m_recordsCount = 0;
    };
}

#endif // POCKET_H
