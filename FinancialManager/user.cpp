#include "user.h"

User::User(const QString &username, const QString &password, const QString &id) :
    m_username(username), m_password(password), m_id(id)
{

}

User* User::Instance()
{
//    if(!m_instance)
//    {
//        m_instance = this;
//    }

//    return *m_instance;
    return nullptr;
}
