#include "CaesarCipher.h"
#include <cctype>

using namespace std;

CaesarCipher::CaesarCipher() {
    key = 'a';
    shift = key;
}

CaesarCipher::~CaesarCipher() {

}



void CaesarCipher::setKey(char k) {
    key = k;
    shift = key - 'a';
    cout << shift << endl;
}

char CaesarCipher::getKey() {
    return key;
}

string CaesarCipher::encrypt(string plainText) {

    string result = "";

    for (int i = 0; i < plainText.length(); i++) {

        char currentCharacter = plainText[i];

        // check if alphabetical value
        if (isalpha(currentCharacter)) {
            char base = islower(currentCharacter) ? 'a' : 'A';
            result += (currentCharacter - base + shift) % 26 + base;
        } else {
            result += currentCharacter;
        }

    }

    return result;
}

string CaesarCipher::decrypt(string plainText) {

    string result = "";

    for (int i = 0; i < plainText.length(); i++) {

        char currentCharacter = plainText[i];

        // check if alphabetical value
        if (isalpha(currentCharacter)) {
            char base = islower(currentCharacter) ? 'a' : 'A';
            result += (currentCharacter - base - shift + 26) % 26 + base;
        } else {
            result += currentCharacter;
        }

    }

    return result;
}
