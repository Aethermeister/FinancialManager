#include "tst_encrypt.h"

namespace Test::Core
{
    void EncryptTest::initTestCase()
    {

    }

    void EncryptTest::cleanupTestCase()
    {

    }

    void Test::Core::EncryptTest::test_encodeData()
    {
        const QString dataToBeEncoded = "This is a [TEST] message.\n"
                                        "It is used to test the 'QString encodeData(const QString& data)' function'";

        const QString expectedEncodedData = "VGhpcyBpcyBhIFtURVNUXSBtZXNzYWdlLgpJdCBpcyB1c2VkIHRvIHRlc3QgdGhlICdRU3RyaW5nIGVuY29kZURhdGEoY29uc3QgUVN0cmluZyYgZGF0YSknIGZ1bmN0aW9uJw==";
        const auto encodedData = encodeData(dataToBeEncoded);

        QCOMPARE(encodedData, expectedEncodedData);
    }

    void EncryptTest::test_decodeData()
    {
        const QString dataToBeDecoded = "VGhpcyBpcyBhIFtURVNUXSBtZXNzYWdlLgpJdCBpcyB1c2VkIHRvIHRlc3QgdGhlICdRU3RyaW5nIGRlY29kZURhdGEoY29uc3QgUVN0cmluZyYgZGF0YSknIGZ1bmN0aW9uJw==";

        const QString expectedDecodedData = "This is a [TEST] message.\n"
                                        "It is used to test the 'QString decodeData(const QString& data)' function'";
        const auto decodedData = decodeData(dataToBeDecoded);

        QCOMPARE(decodedData, expectedDecodedData);
    }

    void EncryptTest::test_compressDataAndUncompressData()
    {
        const QByteArray dataToBeCompressed = "This is a [TEST] message.\n"
                                        "It is used to test the 'QByteArray uncompressData(const QByteArray& data)' function'";

        const auto compressedData = compressData(dataToBeCompressed);
        const auto uncompressedData = uncompressData(compressedData);

        QCOMPARE(dataToBeCompressed, uncompressedData);
    }
}
