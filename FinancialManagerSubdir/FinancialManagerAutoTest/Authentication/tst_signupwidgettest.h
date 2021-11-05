#ifndef SIGNUPWIDGETTEST_H
#define SIGNUPWIDGETTEST_H

#include <QTest>

#include "Authentication/signupwidget.h"

class SignUpWidgetTest : public QObject
{
    Q_OBJECT
public:
    SignUpWidgetTest() = default;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    void test_initializeUi();
    void test_signUpFalse();
    void test_signUpTrue();
};

#endif // SIGNUPWIDGETTEST_H
