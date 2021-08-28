#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(const QString& username, const QString& password, const QString& id);

    User* Instance();

private:
    //static User* m_instance;

    QString m_username;
    QString m_password;
    QString m_id;
};

#endif // USER_H
