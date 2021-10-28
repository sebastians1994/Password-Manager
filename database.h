#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include "card.h"
#include "password.h"
#include "encryption.h"

class Database
{
public:
    Database();

private:
    QList<Card> card;
    QList<Password> business;
    QList<Password> education;
    QList<Password> email;
    QList<Password> entertainment;
    QList<Password> finance;
    QList<Password> games;
    QList<Password> news;
    QList<Password> productivity;
    QList<Password> shopping;
    QList<Password> social;

    Encryption encrypt;

    void initializeP();// once program starts initialize passwords into memeory
    void initializeC(); // once program starts initialize cards into memeory

    QList<Password> reducePassList(QList<Password> pList); //removes empty Password Obj in list
    QList<Card> reduceCardList(QList<Card> cList); //removes empty Card Obj in list
    QString passListToString(QList<Password> list);
public:
    ~Database();
    QList<Password> getPasswordList(int)const; //returns Password List based on index passed;
    QList<Card> getCardList()const{return card;} //returns Card List
    void setPasswordList(QList<Password> pList); //from dashboard if there are any changes made, pass the new list to this function.
    void setCardList(QList<Card> cList); ///from dashboard if there are any changes made, pass the new list to this function.
    void writeToFileC()const; //write all Card objects to file
    void writeToFileP(); //write all Password objects to file
    void addToPassList(Password p); //add a new password to the list;
    void addCardToList(Card c){this->card.append(c);} //add a card to the list;
};

#endif // DATABASE_H
