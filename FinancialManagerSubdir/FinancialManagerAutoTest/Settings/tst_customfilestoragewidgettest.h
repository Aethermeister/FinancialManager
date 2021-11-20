#ifndef CUSTOMFILESTORAGEWIDGETTEST_H
#define CUSTOMFILESTORAGEWIDGETTEST_H

#include <QTest>

class CustomFileStorageWidgetTest : public QObject
{
    Q_OBJECT
public:
    CustomFileStorageWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_uiInitialization();
    void test_changeStoragePath();
};

#endif // CUSTOMFILESTORAGEWIDGETTEST_H
