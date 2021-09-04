#include "authenticationcomponent.h"
#include "Core/defines.h"



namespace Authentication
{
    void AuthenticationComponent::setInformationLabel(QLabel *information_lbl)
    {
        m_information_lbl = information_lbl;
    }

    bool AuthenticationComponent::checkForExistingUsername(const QString &username) const
    {
        //Get the content of the users JSON file and check the already stored usernames
        const auto existingUsersDocument = readJSONFile(USERSFILE);
        const auto existingUsersObject = existingUsersDocument.object();

        return existingUsersObject.keys().contains(username);
    }

    bool AuthenticationComponent::checkForExistingUsername(const QString &username, const QString &password, QString *id) const
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
                //Set the id pointer with the user id
                *id = userObject.value("id").toString();
                return true;
            }
        }

        return false;
    }

} // namespace Authentication
