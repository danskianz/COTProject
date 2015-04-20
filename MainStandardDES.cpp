/* MainSimplifiedDES.c
author: Christian A. Rodriguez
Main file of the class library for the class SimplifiedDES
*/

#include <iostream>
#include <string>
#include <iterator>
#include "StandardDES.h"

int main() {
    string message;
    string key;
    string ciphertext;
    
    message = "1111111100000000111111110000000000000000111111110000000011111111";
    cout << "Testing Standard DES" << endl;
    cout << "Enter a 64-bit message string: " << endl << message << endl;
    //cin >> message;
    
    //key = "00000000000000000000000000000000000000000000000000000000";
    //key = "0111111101111111011111110111111101111111011111110111111101111111";
    //key = "0000000000000000000000000000000000000000000000000000000001100011";
    key = "0110001101100011011000110110001101100011011000110110001101100011";

    cout << "Enter a 64-bit key string: " << endl << key << endl;
    //cin >> key;
    
    cout << endl;
    
    ciphertext = EncryptDES(message, key);
    cout << ciphertext << endl;
}
