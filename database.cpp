#include "database.h"

Database::Database()
{
    initializeC();
    initializeP();
}

Database::~Database(){
   card.empty();
   business.empty();
   education.empty();
   email.empty();
   entertainment.empty();
   finance.empty();
   games.empty();
   news.empty();
   productivity.empty();
   shopping.empty();
   social.empty();
}

QList<Password> Database::getPasswordList(int folder)const{
    switch(folder){
    case(0):
        return business;
        break;
    case(1):
        return education;
        break;
    case(2):
        return email;
        break;
    case(3):
        return entertainment;
        break;
    case(4):
        return finance;
        break;
    case(5):
        return games;
        break;
    case(6):
        return news;
        break;
    case(7):
        return productivity;
        break;
    case(8):
        return shopping;
        break;
    case(9):
        return social;
        break;
    }
}

void Database::addToPassList(Password p){
    switch(p.getFolder()){
    case(0):
        business.append(p);
        break;
    case(1):
        education.append(p);
        break;
    case(2):
        email.append(p);
        break;
    case(3):
        entertainment.append(p);
        break;
    case(4):
        finance.append(p);
        break;
    case(5):
        games.append(p);
        break;
    case(6):
        news.append(p);
        break;
    case(7):
        productivity.append(p);
        break;
    case(8):
        shopping.append(p);
        break;
    case(9):
        social.append(p);
        break;
    }
}

void Database::setCardList(QList<Card> cList){
    cList = reduceCardList(cList);
    this->card = cList;
}

void Database::setPasswordList(QList<Password> p){
    if(!p.isEmpty()){
        int folder = p[0].getFolder();
         p = reducePassList(p);
        switch(folder){
        case(0):
            business = p;
            break;
        case(1):
            education= p;
            break;
        case(2):
            email= p;
            break;
        case(3):
            entertainment = p;
            break;
        case(4):
            finance = p;
            break;
        case(5):
            games = p;
            break;
        case(6):
            news = p;
            break;
        case(7):
            productivity = p;
            break;
        case(8):
            shopping = p;
            break;
        case(9):
            social = p;
            break;
        }
    }
}

QList<Password> Database::reducePassList(QList<Password> pList){
    for(int i = 0; i < pList.size(); i+=1){
        if(pList[i].isEmpty()) {
            pList.removeAt(i);
            i--;
        }
    }
    return pList;
}

QList<Card> Database::reduceCardList(QList<Card> cList){
    for(int i = 0; i < cList.size(); i+=1){
        if(cList[i].isEmpty()) {
            cList.removeAt(i);
            i--;
        }
    }
    return cList;
}

void Database::initializeP(){
    QFile file("files/password123");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }
    QTextStream in(&file);
    QString fileEncrypt = in.readAll();
    if(fileEncrypt == QString()) return;
    fileEncrypt = encrypt.encode_decode(fileEncrypt);
    QStringList wordList = fileEncrypt.split('\n');
    for(int i = 0; i < wordList.size(); i++){
        QStringList subList = wordList[i].split('\t');
        Password temp(subList[0].toInt(), subList[1], subList[2], subList[3], subList[4]);
        addToPassList(temp);
    }
}

void Database::initializeC(){
    QFile file("files/cards.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }
    QTextStream in(&file);

    QStringList wordlist;
    while(!in.atEnd()){
        QString line = in.readLine();
        wordlist = line.split('\t');

        QDate tempDate(wordlist[5].toInt(), wordlist[4].toInt(), 1);
        Card temp(wordlist[0], wordlist[1], wordlist[2], wordlist[3], tempDate, wordlist[6]);
        card.append(temp);
    }
    file.close();
}

void Database::writeToFileP(){
    QFile file("files/password123");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QString passString = QString();
    passString += passListToString(business);
    passString += passListToString(education);
    passString += passListToString(email);
    passString += passListToString(entertainment);
    passString += passListToString(finance);
    passString += passListToString(games);
    passString += passListToString(news);
    passString += passListToString(productivity);
    passString += passListToString(shopping);
    passString += passListToString(social);
    passString.remove(passString.size()-1,passString.size()); //remove \n line character from last data entry
    passString = encrypt.encode_decode(passString);
    QTextStream stream(&file);
    stream << passString;
    file.close();
}

QString Database::passListToString(QList<Password> list){
    QString listString = QString();
    QString temp;
    if(list.isEmpty()) return QString();
    for(auto i:list){
        listString += (QString::number(i.getFolder()) + '\t' + i.getName() + '\t' + i.getUsername() + '\t' + i.getPassword() + '\t' + i.getWesbite() + '\n');
    }
    return listString;
}

void Database::writeToFileC()const{
    QFile file("files/cards.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        return;
    }
    QTextStream stream(&file);
    for(auto i : card){
        stream << i.getCardType() << '\t' << i.getName() <<  '\t' << i.getNameOnCard() << '\t' << i.getCardNum() << '\t' << i.getexpirationMonth() <<'\t' << i.getexpirationYear()<< '\t' << i.getCVV() << '\n';
    }
}
