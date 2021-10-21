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
        qDebug() << "Pocket Constructor";
    }

    Pocket::Pocket(const QString &name, const PocketType &type, int initialValue, int value, const QDateTime &creationDate) :
        m_name(name),
        m_type(type),
        m_initialValue(initialValue),
        m_value(value),
        m_creationDate(creationDate)
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

    int Pocket::recordCount() const
    {
        return m_recordCount;
    }

    void Pocket::setRecordCount(int newRecordCount)
    {
        m_recordCount = newRecordCount;
    }
}
