#ifndef TST_ENCRYPT_H
#define TST_ENCRYPT_H
#include <QTest>

#include "Core/encrypt.h"

namespace Test::Core
{
    class EncryptTest : public QObject
    {
        Q_OBJECT

    public:
        EncryptTest() = default;

    private slots:
        void initTestCase();
        void cleanupTestCase();

        void test_encodeData();
        void test_decodeData();
        void test_compressDataAndUncompressData();
    };
}

#endif // TST_ENCRYPT_H
