#include "tst_defines.h"

namespace Test::Core
{
    void DefinesTest::initTestCase()
    {
        QDir().mkdir(m_testFilesFolder);
    }

    void DefinesTest::cleanupTestCase()
    {
        QDir(m_testFilesFolder).removeRecursively();
    }

    void DefinesTest::test_writeAndReadJSONFile()
    {

        const auto document = QJsonDocument(testArray);

        writeJSONFile(m_JSONFile, document);
        const auto JSONContent = readJSONFile(m_JSONFile);

        QCOMPARE(JSONContent, document);
    }

    void DefinesTest::test_checkFileExistenceDefault()
    {
        checkFileExistence(m_JSONFileDefaultContent);
        const auto jsonFileContent = readJSONFile(m_JSONFileDefaultContent);

        QVERIFY(jsonFileContent.isObject());
    }

    void DefinesTest::test_checkFileExistenceWithContent()
    {
        checkFileExistence(m_JSONFileWithContent, QJsonDocument(testArray));
        const auto jsonFileContent = readJSONFile(m_JSONFileWithContent);

        QCOMPARE(jsonFileContent.array(), testArray);
    }

    void DefinesTest::test_checkFolderExistence()
    {
        const QString folder = m_testFilesFolder + "/test_folder";
        QVERIFY(!QDir(folder).exists());

        checkFolderExistence(folder);
        QVERIFY(QDir(folder).exists());

        qDebug() << APPDATALOCATION();
    }
}
