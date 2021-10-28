#include "rng.h"

QString RNG::passwordGen(int pass_length,bool upper,bool lower, bool nums, bool special){
    /*Called from dashboard, adds appropriate strings to the character banks based on the booleans received
    and then randomly picks an index from the char bank and puts it into password until reaches length,
    sends result back.*/
  QString password;
  QString charBank;
  if(nums){
      charBank.append("0123456789");
  }
  if(special){
      charBank.append("!@#$%^&");
  }
  if(upper){
      charBank.append("ABCDEFGHIJKLMNOPQRSTUVXYZ");
  }
  if(lower){
      charBank.append("abcdefghijklmnopqrstuvxyz");
  }

  for(int i = 0; i<pass_length;++i){
      quint64 rand = QRandomGenerator::global()->generate64();
      int index = rand*time(NULL) % charBank.length();
             QChar nextChar = charBank.at(index);
             password.append(nextChar);
  }
  return password;
}
