#include "encryption.h"

QString Encryption::encode_decode(QString temp_str)
{
    char key = 'f';
    std::string copy_str = temp_str.toStdString(), converted_str = temp_str.toStdString();
    for (int i = 0; i < temp_str.size(); i++){
        converted_str[i] = copy_str[i] ^ key;
    }
    return QString::fromStdString((converted_str));
}
