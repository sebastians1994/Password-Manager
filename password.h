#ifndef PASSWORD_H
#define PASSWORD_H

#include <QString>

class Password
{
private:
    int folder;
    QString name, username, pass, website;
public:
    Password();
    Password(unsigned short, QString, QString, QString, QString);
    Password(const Password &p);
    void setName(QString name){this->name = name;}
    void setUsername(QString username) { this->username = username; }
    void setPassword(QString pass) { this->pass = pass; }
    void setWebsite(QString website) {this->website = website;}
    void setFolder(int folder) {this->folder = folder; }

    QString getUsername() const{ return username; }
    QString getPassword() const{ return pass; }
    QString getWesbite()const{return website;}
    qint8 getFolder() const{ return folder; }
    QString getName() const{return name;}
    bool isEmpty();
};

#endif // PASSWORD_H
