#include "Core/defines.h"
#include "authenticationwidget.h"
#include "loginwidget.h"
#include "signupwidget.h"

#include "ui_authenticationwidget.h"

namespace Authentication
{
    AuthenticationWidget::AuthenticationWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::AuthenticationWidget)
    {
        ui->setupUi(this);

        //Always show the LoginWidget first
        showLoginWidget();
    }

    AuthenticationWidget::~AuthenticationWidget()
    {
        delete ui;
    }

    void AuthenticationWidget::showLoginWidget()
    {
        //Delete the current widget from the container widget
        deleteActiveContentWidget(ui->m_authenticationContainer_widget, ui->m_authenticationContainer_layout);

        //Create a new LoginWidget and add it to the container widget
        LoginWidget* loginWidget = new LoginWidget(ui->m_authenticationContainer_widget);
        ui->m_authenticationContainer_layout->addWidget(loginWidget);

        //Connect the corresponding signals and slots
        connect(loginWidget, &LoginWidget::sig_createAccount, this, &AuthenticationWidget::showSignUpWidget);
        connect(loginWidget, &LoginWidget::sig_loggedIn, this, &AuthenticationWidget::sig_authenticated);
    }

    void AuthenticationWidget::showSignUpWidget()
    {
        //Delete the current widget from the container widget
        deleteActiveContentWidget(ui->m_authenticationContainer_widget, ui->m_authenticationContainer_layout);

        //Create a new SignUpWidget and add it to the container widget
        SignUpWidget* signUpWidget = new SignUpWidget(ui->m_authenticationContainer_widget);
        ui->m_authenticationContainer_layout->addWidget(signUpWidget);

        //Connect the corresponding signals and slots
        connect(signUpWidget, &SignUpWidget::sig_backToLogin, this, &AuthenticationWidget::showLoginWidget);
        connect(signUpWidget, &SignUpWidget::sig_signedUp, this, &AuthenticationWidget::sig_authenticated);
    }
}
