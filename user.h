#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class User
{
private:
    QString username, password;
    QString loginUser, loginPassword;
    void getCredentials(); //fetches the master password from file.
    void saveData();
public:
    User(); //default constructor which only gets the master password from file to compare
    User(QString,QString); //once declaring the user class and already having the username and password from the login screen
    User(const User &u);  //copy constructor if needed
    void setLoginUser(QString loginUser){this->loginUser = loginUser;} //for login class. this does not edit master Username!
    void setLoginPassword(QString loginPassword){this->loginUser = loginPassword;} //for login class. this does not edit master Password!
    bool changeUsername(QString prevUsername,QString newUsername); // for dashboard class to edit the master username
    bool changePassword(QString prevPassword, QString newPassword); // for dashboard class to edit the master password
    bool validCredentials()const;
};

#endif // USER_H
