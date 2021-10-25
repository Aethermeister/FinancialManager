#include "pocket.h"

#include <QDebug>

namespace Content::Pockets
{
    Pocket::Pocket(const QString& name, const QString& pocketTypeString, int value) :
        m_name(name),
        m_type(stringToPocketType(pocketTypeString)),
        m_initialValue(value),
        m_value(value),
        m_creationDate(QDateTime::currentDateTime())
    {
    }

    Pocket::Pocket(const QString &name, const PocketType &type, int initialValue, int value, const QDateTime &creationDate, const QDate &lastUsedDate, int recordsCount) :
        m_name(name),
        m_type(type),
        m_initialValue(initialValue),
        m_value(value),
        m_creationDate(creationDate),
        m_lastUsedDate(lastUsedDate),
        m_recordsCount(recordsCount)
    {
    }

    bool Pocket::operator==(const Pocket &pocket)
    {
        return m_name == pocket.m_name;
    }

    const QMap<QString, PocketType> Pocket::TypeNameToPocketType
    {
        {"Cash", PocketType::CASH},
        {"Card", PocketType::CARD}
    };

    const QString Pocket::pocketTypeToString(const PocketType &pocketType)
    {
        return TypeNameToPocketType.key(pocketType);
    }

    const PocketType Pocket::stringToPocketType(const QString &pocketTypeString)
    {
        return TypeNameToPocketType[pocketTypeString];
    }

    const QString &Pocket::name() const
    {
        return m_name;
    }

    PocketType Pocket::type() const
    {
        return m_type;
    }

    int Pocket::initialValue() const
    {
        return m_initialValue;
    }

    int Pocket::value() const
    {
        return m_value;
    }

    void Pocket::setValue(int newValue)
    {
        m_value = newValue;
    }

    const QDateTime &Pocket::creationDate() const
    {
        return m_creationDate;
    }

    int Pocket::recordsCount() const
    {
        return m_recordsCount;
    }

    void Pocket::setRecordsCount(int newRecordsCount)
    {
        m_recordsCount = newRecordsCount;
    }

    const QDate &Pocket::lastUsedDate() const
    {
        return m_lastUsedDate;
    }

    void Pocket::setLastUsedDate(const QDate &newLastUsedDate)
    {
        m_lastUsedDate = newLastUsedDate;
    }
}
