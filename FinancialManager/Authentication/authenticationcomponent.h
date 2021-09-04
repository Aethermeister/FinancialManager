#ifndef AUTHENTICATION_AUTHENTICATIONCOMPONENT_H
#define AUTHENTICATION_AUTHENTICATIONCOMPONENT_H

#include <QLabel>
#include <QLineEdit>

namespace Authentication
{
    /**
     * Base class for the LoginWidget and SignUpWidget classes
    */
    class AuthenticationComponent
    {
    public:
        AuthenticationComponent() = default;

    protected:
        /**
         * Stores the information QLabel in the base class
         * This QLabel is present in both derived classes
        */
        void setInformationLabel(QLabel* information_lbl);

        /**
         * Checks whether a user with the same parameter given name already exists
         * Return true if the given username already exists
        */
        bool checkForExistingUsername(const QString& username) const;
        /**
         * Checks whether a user with the given username and password exists
         * Return true if the user exist and the given password matches the user
         * Also return the user id via the parameter given QString pointer
        */
        bool checkForExistingUsername(const QString& username, const QString& password, QString *id) const;

    private:
        QLabel* m_information_lbl;
    };

} // namespace Authentication

#endif // AUTHENTICATION_AUTHENTICATIONCOMPONENT_H
