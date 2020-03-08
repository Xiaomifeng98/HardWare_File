#ifndef USERINFORMATION_H
#define USERINFORMATION_H
#include <QString>

class UserInformation
{
public:
    UserInformation(const QString &name = "", const QString &password = "", const QString &email = "", const QString &telphone = "");

    QString getName() const;
    void setName(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getTelphone() const;
    void setTelphone(const QString &value);

private:
    QString name;
    QString password;
    QString email;
    QString telphone;
};

#endif // USERINFORMATION_H
