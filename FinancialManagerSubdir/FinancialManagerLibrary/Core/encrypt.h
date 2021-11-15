#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <QString>
#include <QByteArray>

#define PASSWORDREGEX "^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{8,32}$"
#define COMPRESSIONLEVEL 2

/**
 * Returns the base64 encoded version of the parameter given QString
*/
inline QString encodeData(const QString& data);
/**
 * Returns the decoded version of the parameter given base64 QString
*/
inline QString decodeData(const QString& data);

/**
 * Returns the comprassed version of the parameter given QByteArray data
*/
inline QByteArray compressData(const QByteArray& data);
/**
 * Returns the uncomprassed version of the parameter given QByteArray data
*/
inline QByteArray uncompressData(const QByteArray& data);


inline QString encodeData(const QString& data)
{
    return data.toUtf8().toBase64();
}

inline QString decodeData(const QString& data)
{
    return QByteArray::fromBase64(data.toUtf8());
}

inline QByteArray compressData(const QByteArray& data)
{
    return qCompress(data, COMPRESSIONLEVEL);
}

inline QByteArray uncompressData(const QByteArray& data)
{
    return qUncompress(data);
}

#endif // ENCRYPT_H
