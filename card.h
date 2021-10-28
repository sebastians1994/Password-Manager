#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QDate>

class Card
{
private:
    QString cType, name, nameOnCard, cardNumber, cvv;
    QDate  expirationDate;

public:
    Card();
    Card( QString cType, QString name, QString nameOnCard, QString cardNumber, QDate expirationDate, QString cvv);
    Card(const Card &p);
    void setName(QString name) { this->name = name; }
    void setCardName(QString nameOnCard) {this->nameOnCard = nameOnCard; }
    void setCardType(QString cardtype){this->cType = cardtype;}
    void setCardNum(QString cardNumber) { this->cardNumber = cardNumber; }
    void setExpirationDate(QDate expirationDate) { this->expirationDate = expirationDate; }
    void setCvvNum(QString cvv) { this->cvv = cvv; }
    QString getName()const {return this->name;}
    QString getCardType()const {return cType;}
    QString getNameOnCard()const{return this->nameOnCard;}
    QString getCardNum() const { return cardNumber; }
    QDate getexpirationDate() const{ return this->expirationDate; }
    int getexpirationMonth()const{return this->expirationDate.month();}
    int getexpirationYear()const{return this->expirationDate.year();}
    QString getCVV() const { return this->cvv; }
    bool isEmpty();
};

#endif // CARD_H
