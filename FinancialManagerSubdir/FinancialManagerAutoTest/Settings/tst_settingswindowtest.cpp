#include "tst_settingswindowtest.h"
#include "Settings/settingswindow.h"
#include "Settings/localfilestoragewidget.h"
#include "Settings/customfilestoragewidget.h"

void SettingsWindowTest::initTestCase()
{
    Settings::SettingsManager::instance()->resetSettingsData();
}

void SettingsWindowTest::cleanupTestCase()
{
    Settings::SettingsManager::instance()->resetSettingsData();
}

void SettingsWindowTest::test_settingsWindowUiInitialization()
{
    Settings::SettingsManager::instance()->setData(Settings::SettingsData::FILE_STORAGE, Settings::FileStorage::LOCAL);

    Settings::SettingsWindow* settingsWindow = new Settings::SettingsWindow();
    settingsWindow->show();

    QVERIFY(settingsWindow->localFileStorageRadioButton()->isChecked());
    QVERIFY(settingsWindow->fileStorageContainerWidget()->findChild<Settings::LocalFileStorageWidget*>());

    settingsWindow->deleteLater();

    Settings::SettingsManager::instance()->setData(Settings::SettingsData::FILE_STORAGE, Settings::FileStorage::CUSTOM);

    Settings::SettingsWindow* settingsWindow2 = new Settings::SettingsWindow();
    settingsWindow2->show();

    QVERIFY(settingsWindow2->customFileStorageRadioButton()->isChecked());
    QVERIFY(settingsWindow2->fileStorageContainerWidget()->findChild<Settings::CustomFileStorageWidget*>());

    settingsWindow2->deleteLater();
}
