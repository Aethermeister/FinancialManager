#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "authenticationcomponent.h"

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>

namespace Ui {
class LoginWidget;
}

namespace Authentication
{
    /**
     * Ui class to handle login related user interactions
     * Part of the AuthenticationWidget as content widget
    */
    class LIB_EXPORT LoginWidget : public QWidget, public AuthenticationComponent
    {
        Q_OBJECT

    public:
        explicit LoginWidget(QWidget *parent = nullptr);
        ~LoginWidget();

        /**
         * Returns the Login widget's username QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* usernameLineEdit();
        /**
         * Returns the Login widget's password QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* passwordLineEdit();
        /**
         * Returns the Login widget's remember me QCheckBox
         * Used so test project(s) can access it
        */
        QCheckBox* rememberMeCheckBox();
        /**
         * Returns the Login widget's login QPushButton
         * Used so test project(s) can access it
        */
        QPushButton* loginButton();

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
         * The signal's parameters hold the user related authentication information
        */
        void sig_loggedIn(const QString& username, const QString& password, const QString& id);
    };
}

#endif // LOGINWIDGET_H
