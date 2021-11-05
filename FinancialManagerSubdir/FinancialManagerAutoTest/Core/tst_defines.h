#ifndef TST_DEFINES_H
#define TST_DEFINES_H
#include <QTest>

#include "Core/defines.h"

namespace Test::Core
{
    class DefinesTest : public QObject
    {
        Q_OBJECT

    public:
        DefinesTest() = default;

    private:
        const QString m_testFilesFolder = "TestFiles";
        const QString m_JSONFile  = m_testFilesFolder + "/test_read_write_file.json";
        const QString m_JSONFileDefaultContent  = m_testFilesFolder + "/test_check_file_default_content.json";
        const QString m_JSONFileWithContent  = m_testFilesFolder + "/test_check_file_content.json";

        const QJsonArray testArray
        {
            "item1",
            "item2",
            "item3"
        };

    private slots:
        void initTestCase();
        void cleanupTestCase();

        void test_writeAndReadJSONFile();
        void test_checkFileExistenceDefault();
        void test_checkFileExistenceWithContent();
        void test_checkFolderExistence();
    };
}

#endif // TST_DEFINES_H
