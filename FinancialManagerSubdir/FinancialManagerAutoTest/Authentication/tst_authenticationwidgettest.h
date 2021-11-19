#ifndef AUTHENTICATIONWIDGETTEST_H
#define AUTHENTICATIONWIDGETTEST_H

#include <QTest>

class AuthenticationWidgetTest : public QObject
{
    Q_OBJECT
public:
    AuthenticationWidgetTest() = default;

private slots:
    void test_showAuthenticationWidgetContent();

};

#endif // AUTHENTICATIONWIDGETTEST_H
