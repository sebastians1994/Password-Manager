#ifndef RNG_H
#define RNG_H

#include <QWidget>
#include <QRandomGenerator>

class RNG
{
public:
    QString passwordGen(int pass_length,bool upper,bool lower, bool nums, bool special);
};

#endif // RNG_H
