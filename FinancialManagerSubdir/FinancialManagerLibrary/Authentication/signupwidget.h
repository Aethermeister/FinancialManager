#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include "authenticationcomponent.h"

#include <QPushButton>
#include <QWidget>

namespace Ui {
class SignUpWidget;
}

namespace Authentication
{
    /**
     * Ui class to handle sign up related user interactions
     * Part of the AuthenticationWidget as content widget
    */
    class LIB_EXPORT SignUpWidget : public QWidget, public AuthenticationComponent
    {
        Q_OBJECT

    public:
        explicit SignUpWidget(QWidget *parent = nullptr);
        ~SignUpWidget();

        /**
         * Returns the Sign Up widget's sign up QLineEdit
         * Used so test project(s) can access it
        */
        QPushButton* signUpButton();
        /**
         * Returns the Sign Up widget's username QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* usernameLineEdit();
        /**
         * Returns the Sign Up widget's password QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* passwordLineEdit();
        /**
         * Returns the Sign Up widget's verify password QLineEdit
         * Used so test project(s) can access it
        */
        QLineEdit* verifyPasswordLineEdit();

    private:
        Ui::SignUpWidget *ui;

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
         * Checks the user given informations
         * and proceeds with the sign up procedure
         * if this is a new user
        */
        void slot_signUp();

    signals:
        /**
         * Signal emitted when the user wants to go to the LoginWidget
        */
        void sig_backToLogin();
        /**
         * Signal emitted when the sign up procedure finishes with success
         * The signal's parameters hold the user related authentication information
        */
        void sig_signedUp(const QString& username, const QString& password, const QString& id);
    };
}

#endif // SIGNUPWIDGET_H
