#include "card.h"

Card::Card(){ 
    cType = name = nameOnCard = cardNumber = cvv = QString();
    expirationDate = QDate();
};

Card::Card(QString cType,QString name, QString nameOnCard, QString cardNumber, QDate expirationDate, QString cvv){
    this->name = name;
    this->nameOnCard = nameOnCard;
    this->cardNumber = cardNumber;
    this->cType = cType;
    this->expirationDate = expirationDate;
    this->cvv = cvv;
}

Card::Card(const Card &p){
    this->cType = p.cType;
    this->name = p.name;
    this->nameOnCard = p.nameOnCard;
    this->cardNumber = p.cardNumber;
    this->expirationDate = p.expirationDate;
    this->cvv = p.cvv;
}

bool Card::isEmpty(){
    if(cType.isEmpty() && name.isEmpty () && nameOnCard.isEmpty() && cardNumber.isEmpty() && cvv.isEmpty() && expirationDate.isNull()){
        return true;
    }
    return false;
}
