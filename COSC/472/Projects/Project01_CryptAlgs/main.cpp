#include <cstdlib>
#include <iostream>

#include "CaesarCipher.h"

using namespace std;

void printMenu();

int main() {

    CaesarCipher CC;
    char key = ' ';

    string plainText = "hello...";

    cout << "First is CaesarCipher, please enter the key: ";
    cin >> key;

    CC.setKey(key);

    key = CC.getKey();

    cout << "The key for the shift is: " << key << endl << endl;

    printMenu();

    string encrypted;
    encrypted = CC.encrypt(plainText);

    string decrypted;
    decrypted = CC.decrypt(encrypted);

    cout << encrypted << endl;

    cout << decrypted << endl;

    return 0;
}

void printMenu() {

    cout << "Please enter one of the options listed:" << endl;
    cout << "e - to encypt" << endl;
    cout << "d - to decrypt" << endl;
    cout << "q - to quit" << endl;

};
