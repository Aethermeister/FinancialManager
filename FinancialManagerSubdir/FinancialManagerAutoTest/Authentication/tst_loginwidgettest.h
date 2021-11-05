#ifndef LOGINWIDGETTEST_H
#define LOGINWIDGETTEST_H

#include <QTest>

class LoginWidgetTest : public QObject
{
    Q_OBJECT
public:
    LoginWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_initializeUiDefault();
    void test_initializeUiWithSettingsData();

    void test_loginFalse();
    void test_loginTrue();
};

#endif // LOGINWIDGETTEST_H
