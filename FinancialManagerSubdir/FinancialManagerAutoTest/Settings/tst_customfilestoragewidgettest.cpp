#include "tst_customfilestoragewidgettest.h"
#include "Settings/customfilestoragewidget.h"
#include "Settings/settingsmanager.h"

void CustomFileStorageWidgetTest::initTestCase()
{
    Settings::SettingsManager::instance()->resetSettingsData();
}

void CustomFileStorageWidgetTest::cleanupTestCase()
{
    Settings::SettingsManager::instance()->resetSettingsData();
}

void CustomFileStorageWidgetTest::init()
{
    Settings::SettingsManager::instance()->resetSettingsData();
}

void CustomFileStorageWidgetTest::cleanup()
{
    Settings::SettingsManager::instance()->resetSettingsData();
}

void CustomFileStorageWidgetTest::test_uiInitialization()
{
    const QString testPath = "test_path";
    Settings::SettingsManager::instance()->setData(Settings::SettingsData::CUSTOM_STORAGE_PATH, testPath);

    Settings::CustomFileStorageWidget* customFileStorageWidget = new Settings::CustomFileStorageWidget();
    customFileStorageWidget->show();

    QCOMPARE(customFileStorageWidget->managedApplicationFolderLineEdit()->text(), testPath);

    customFileStorageWidget->deleteLater();
}

void CustomFileStorageWidgetTest::test_changeStoragePath()
{
    Settings::CustomFileStorageWidget* customFileStorageWidget = new Settings::CustomFileStorageWidget();
    customFileStorageWidget->show();

    QCOMPARE(customFileStorageWidget->managedApplicationFolderLineEdit()->text(), QString());

    const QString testPath = "test_path";
    customFileStorageWidget->managedApplicationFolderLineEdit()->setText(testPath);
    emit customFileStorageWidget->managedApplicationFolderLineEdit()->editingFinished();

    QCOMPARE(Settings::SettingsManager::instance()->data<QString>(Settings::SettingsData::CUSTOM_STORAGE_PATH), testPath);

    customFileStorageWidget->deleteLater();
}
