#include "record.h"

namespace Content::Records
{
    Record::Record(const int value, const QDate &date, const QTime &time, const QString &location, const QString &item, const QString& pocketName) :
        m_value(value),
        m_date(std::move(date)),
        m_time(std::move(time)),
        m_location(location),
        m_item(item),
        m_pocketName(pocketName)
    {

    }

    const bool Record::operator==(const Record &record) const
    {
        return (
                    m_value == record.m_value &&
                    m_item == record.m_item &&
                    m_location == record.m_location &&
                    m_date == record.m_date &&
                    m_time == record.m_time &&
                    m_pocketName == record.m_pocketName
                );
    }

    int Record::value() const
    {
        return m_value;
    }

    const QDate &Record::date() const
    {
        return m_date;
    }

    const QTime &Record::time() const
    {
        return m_time;
    }

    const QString &Record::location() const
    {
        return m_location;
    }

    const QString &Record::item() const
    {
        return m_item;
    }

    const QString &Record::pocketName() const
    {
        return m_pocketName;
    }
}
