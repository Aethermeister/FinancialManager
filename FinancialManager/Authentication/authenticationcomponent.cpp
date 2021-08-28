#include "authenticationcomponent.h"
#include "Core/defines.h"

#include <QStyle>

namespace Authentication
{
    void AuthenticationComponent::setInformationLabel(QLabel *information_lbl)
    {
        m_information_lbl = information_lbl;
    }

    void AuthenticationComponent::setLineEditErrorState(QLineEdit *lineEdit, bool error)
    {
        lineEdit->setProperty("error", error);

        //Update the style of the QLineEdit
        //so the dynamic property dependent changes are applied
        lineEdit->style()->unpolish(lineEdit);
        lineEdit->style()->polish(lineEdit);
    }

    void AuthenticationComponent::showErrorInformation(const QString &message)
    {
        m_information_lbl->setText(message);
        m_information_lbl->setVisible(true);
    }

    bool AuthenticationComponent::checkForExistingUsername(const QString &username) const
    {
        //Get the content of the users JSON file and check the already stored usernames
        const auto existingUsersDocument = readJSONFile(USERSFILE);
        const auto existingUsersObject = existingUsersDocument.object();

        return existingUsersObject.keys().contains(username);
    }

    bool AuthenticationComponent::checkForExistingUsername(const QString &username, const QString &password) const
    {
        //Get the content of the users JSON file
        //and check whether the parameter given username exists
        const auto existingUsersDocument = readJSONFile(USERSFILE);
        const auto existingUsersObject = existingUsersDocument.object();

        //If there is a user with the given username
        //than check whether the given and stored passwords are a match
        const auto userObject = existingUsersObject.value(username).toObject();
        if(!userObject.isEmpty())
        {
            const auto userPassword = userObject.value("password").toString();
            if(userPassword == password)
            {
                return true;
            }
        }

        return false;
    }

} // namespace Authentication
