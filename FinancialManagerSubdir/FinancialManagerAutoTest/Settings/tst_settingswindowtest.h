#ifndef SETTINGSWINDOWTEST_H
#define SETTINGSWINDOWTEST_H

#include <QTest>

class SettingsWindowTest : public QObject
{
    Q_OBJECT
public:
    SettingsWindowTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_settingsWindowUiInitialization();
};

#endif // SETTINGSWINDOWTEST_H
