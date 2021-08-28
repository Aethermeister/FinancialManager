#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "authenticationcomponent.h"

#include <QWidget>

namespace Ui {
class LoginWidget;
}

namespace Authentication
{
    /**
     * Ui class to handle login related user interactions
     * Part of the AuthenticationWidget as content widget
    */
    class LoginWidget : public QWidget, public AuthenticationComponent
    {
        Q_OBJECT

    public:
        explicit LoginWidget(QWidget *parent = nullptr);
        ~LoginWidget();

    private:
        Ui::LoginWidget *ui;

        /**
         * Sets the initial state of the Ui
        */
        void initializeUi();
        /**
         * Sets the common connections related to this class
        */
        void initializeConnections() const;

    private slots:
        /**
         * Checks the user given login informations
         * and proceeds with the login procedure
         * if the user gives valid authentication data
        */
        void slot_login();

    signals:
        /**
         * Signal emitted when the user want to go to the SignUpWidget
        */
        void sig_createAccount();
        /**
         * Signal emitted when the login procedure finishes with success
        */
        void sig_loggedIn();
    };
}

#endif // LOGINWIDGET_H
