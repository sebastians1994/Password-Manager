#include "password.h"

Password::Password(){
    folder = 0;
    name = username = pass = website = QString();  //default constructor called for QString which set to NULL
}

Password::Password( unsigned short folder, QString name, QString username, QString pass, QString website){
    this->folder = folder;
    this->name = name;
    this->username = username;
    this->pass = pass;
    this->website = website;
}

Password::Password(const Password &p){
    this->folder = p.folder;
    this->name = p.name;
    this->username = p.username;
    this->pass = p.pass;
    this->website = p.website;
}

bool Password::isEmpty(){
    if(name.isEmpty() && username.isEmpty() && pass.isEmpty() && website.isEmpty()){
        return true;
    }
    return false;
}
