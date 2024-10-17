#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <iostream>
#include <string>

class CaesarCipher {
private:
    char key;
    int shift;
public:
    CaesarCipher();
    ~CaesarCipher();

    void setKey(char);
    char getKey();

    std::string encrypt(std::string);
    std::string decrypt(std::string);
};


#endif // CAESARCIPHER_H
