#include "tst_authenticationwidgettest.h"
#include "Authentication/authenticationwidget.h"
#include "Authentication/loginwidget.h"
#include "Authentication/signupwidget.h"

void AuthenticationWidgetTest::test_showAuthenticationWidgetContent()
{
    Authentication::AuthenticationWidget* authenticationWidget = new Authentication::AuthenticationWidget();
    authenticationWidget->show();

    auto loginWidget = authenticationWidget->findChild<Authentication::LoginWidget*>();
    QVERIFY(loginWidget);

    loginWidget->createAccountButton()->click();

    auto signUpWidget = authenticationWidget->findChild<Authentication::SignUpWidget*>();
    QVERIFY(signUpWidget);

    signUpWidget->backToLoginButton()->click();

    auto loginWidget2 = authenticationWidget->findChild<Authentication::LoginWidget*>();
    QVERIFY(loginWidget2);

    authenticationWidget->deleteLater();
}
