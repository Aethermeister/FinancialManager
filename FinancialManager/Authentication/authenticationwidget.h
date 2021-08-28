#ifndef AUTHENTICATIONWIDGET_H
#define AUTHENTICATIONWIDGET_H

#include <QWidget>

namespace Ui {
class AuthenticationWidget;
}

namespace Authentication
{
    /**
     * This is the main authentication ui class
     * It contains the additional authentication releated ui classes
    */
    class AuthenticationWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit AuthenticationWidget(QWidget *parent = nullptr);
        ~AuthenticationWidget();

    private:
        Ui::AuthenticationWidget *ui;

        /**
         * Shows the LoginWidget ui in the content area
        */
        void showLoginWidget();
        /**
         * Shows the SignUpWidget ui in the content area
        */
        void showSignUpWidget();

    signals:
        /**
         * Signal Emitted when a successful authentication has been made
         * Successful authentication: login and sign up
        */
        void sig_authenticated();
    };
}

#endif // AUTHENTICATIONWIDGET_H
