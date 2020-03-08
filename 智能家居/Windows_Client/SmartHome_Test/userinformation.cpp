#include "userinformation.h"

UserInformation::UserInformation(const QString &name,
                                 const QString &password,
                                 const QString &email,
                                 const QString &telphone)
{
    this->name = name;
    this->password = password;
    this->email = email;
    this->telphone = telphone;
}

QString UserInformation::getName() const
{
    return name;
}

void UserInformation::setName(const QString &value)
{
    name = value;
}

QString UserInformation::getPassword() const
{
    return password;
}

void UserInformation::setPassword(const QString &value)
{
    password = value;
}

QString UserInformation::getEmail() const
{
    return email;
}

void UserInformation::setEmail(const QString &value)
{
    email = value;
}

QString UserInformation::getTelphone() const
{
    return telphone;
}

void UserInformation::setTelphone(const QString &value)
{
    telphone = value;
}
