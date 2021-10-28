#include "user.h"

User::User()
{
    getCredentials();
}

User::User(QString loginUser, QString loginPassword){
    this->loginUser = loginUser;
    this->loginPassword =loginPassword;
    getCredentials();
}

User::User(const User &u){
    this->username = u.username;
    this->password = u.password;
}

void User::getCredentials(){
    QFile file("files/credentials.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }
    QTextStream in(&file);
    QString line = in.readLine();
    file.close();
    QStringList wordlist = line.split('\t');
    this->username = wordlist[0]; this->password = wordlist[1];
}

bool User::changeUsername(QString prevUsername, QString newUsername){
    if(prevUsername == username){
        username = newUsername;
        saveData();
        return true;
    }else{
        return false;
    }
}

bool User::changePassword(QString prevPassword, QString newPassword){
    if(prevPassword == password){
        password = newPassword;
        saveData();
        return true;
    }else{
        return false;
    }
}

bool User::validCredentials()const{
    if(username == loginUser && password == loginPassword)
        return true;
    else
        return false;
}

void User::saveData(){
    QFile file("files/credentials.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream stream(&file);
    stream << username << '\t' << password;
    file.close();
}
