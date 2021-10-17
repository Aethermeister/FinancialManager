#ifndef POCKET_H
#define POCKET_H

#include <QString>
#include <QDateTime>
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
    class Pocket
    {
    public:
       Pocket(const QString& name, const QString& pocketTypeString, int value);
       Pocket(const QString& name, const PocketType& type, int initialValue, int value, const QDateTime& creationDate);

       Pocket(const Pocket& pocket);
       Pocket(Pocket&& pocket);

       bool operator==(const Pocket& pocket);

       /**
        * Returns the name of the parameter given Pocket type
       */
       static const QString pocketTypeToString(const PocketType& pocketType);

       /**
        * Returns the type of the parameter given Pocket type string
       */
       static const PocketType stringToPocketType(const QString& pocketTypeString);

       const QString &name() const;

       PocketType type() const;

       int initialValue() const;

       int value() const;

       const QDateTime &creationDate() const;

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
    };
}

#endif // POCKET_H
