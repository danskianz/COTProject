#ifndef SIMPLIFIEDDES_H_
#define SIMPLIFIEDDES_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <iterator>
#include <time.h>
#include <math.h>
using namespace std;

//-- Function/Class Declarations
string EncryptDES(string, string);
string LeftMessage(string);
string RightMessage(string);
string FeistelSystem(string, string&, string&);
void RightExpansion(string&);
int RightExpansionBeta(string&, string&);
void KeyPermutation1(string&);
void LeftShift(string&);
void KeyPermutation2(string&);
string toBit(char);
string XOR(string, string);

//-- Function/Class Implementations
string EncryptDES(string message, string key) {
    // 0. Declare output (local) variable(s)
    string output;
    string leftM;
    string rightM;
    string tempM;
    
    // Perform initial permutation on key to make it into 56-bit
    KeyPermutation1(key);
    
    
    // 0.1 Perform Initial Permutation??? (Note: This actually does not help)
    //... Skip for right now
    
    
    // Perform 16 round encryption
    cout << "Begin 16 round loop!" << endl;
    for (int i = 0; i < 16; i++) {
        cout << "Round " << i << endl;
        
        // 1. Split message string into left and right 32 bit strings
        cout << "\tSplit message (left & right)" << endl;
        
        // 1.1 Call a left message function into 32-bit string
        leftM = LeftMessage(message);
        cout << "\t   leftM =  " << leftM << endl;
        
        // 1.2 Call a right message function into 32-bit string
        rightM = RightMessage(message);
        cout << "\t   rightM = " << rightM << endl;
        
        // 2. Perform Feistel System function on rightM, and key
        cout << "\n\tBegin Feistel System" << endl;
        string feistelM = FeistelSystem(rightM, key);
        
        
        // 3. XOR Feistel System string 32 bit output with the current leftM 32 bit input (This now becomes the new left side)
        cout << "\n\tXOR Feistel System with leftM" << endl;
        string tempM = XOR(leftM, feistelM);
        cout << "\t   xor = " << tempM << endl;
        
        // 4. Turn old rightM into new leftM
        leftM = rightM;
        rightM = tempM;
        
        cin.ignore();
    }

    // 5. Perform Final Permutation??? (Note: This actually does not help)
    
    // Return ciphertext string
    return output;
}

string LeftMessage(string message) 
{
    //cout <<"The size of the message string is " << message.size() << " 'bits'?" << endl;
    string output;
    
    // This loop iterates through the message and stores only first half (leftM) into output
    for (int index = 0 ; index < (message.size() / 2); index++)
    {
        output += message[index];
    }
    
//    cout << output << endl;
    return output;
}

string RightMessage(string message) 
{
    string output;
    
    // This loop iterates through the message and stores only second half (rightM) into output
    for (int index = (message.size() / 2) ; index < message.size(); index++)
    {
        output += message[index];
    }
    
//    cout << output << endl;
    return output;
}


string FeistelSystem(string rightMessage, string& key, string& saltPile) {
    // 0. Declare Feistel temporary (local) variable(s)
    string output;
    
    // 1. Expand rightMessage from 32 bits to 48 bits (E-Box Substitution)
    cout << "\t1. Perform right expansion" << endl;
    //RightExpansion(rightMessage);
    RightExpansionBeta(rightMessage);
    cout << "\t     rightM: " << rightMessage << endl;
    
    // 2. Mix/Shift key schedule
    // 2.1 Split new 56-bit key into C & D each 28-bit
    cout << "\t2. Perform key mixing schedule" << endl;
    cout << "\t     key = " << key << endl;
    
    string c = LeftMessage(key);
    cout << "\t     c =   " << c << endl;
    
    string d = RightMessage(key);
    cout << "\t     d =   " << d << endl;
    
    // 2.2 LeftShift (once or twice)
    cout << "\t     Perform left shift on both 'c' and 'd'" << endl;
    LeftShift(c);
    LeftShift(d);
    
    // 2.3 Then Permute once again with either 1 or 2 shift (depending on ith iteration)
    string key2 = c + d;
    KeyPermutation2(key2);
    // 2.1 XOR 48-bit rightMessage with new 48-bit key
    output = XOR(rightMessage, key2);
    
    // 3. Call new MagicFunction
    
    // 4. Return new string output
    return output;
}

//string Expand(string& right) {
void RightExpansion(string& right) 
{
    string output;
    
    output.push_back(right[31]);
    output.push_back(right[0]);
    output.push_back(right[1]);
    output.push_back(right[2]);
    output.push_back(right[3]);
    output.push_back(right[4]);
    output.push_back(right[3]);
    output.push_back(right[4]);
    output.push_back(right[5]);
    output.push_back(right[6]);
    output.push_back(right[7]);
    output.push_back(right[8]);
    output.push_back(right[7]);
    output.push_back(right[8]);
    output.push_back(right[9]);
    output.push_back(right[10]);
    output.push_back(right[11]);
    output.push_back(right[12]);
    output.push_back(right[11]);
    output.push_back(right[12]);
    output.push_back(right[13]);
    output.push_back(right[14]);
    output.push_back(right[15]);
    output.push_back(right[16]);
    output.push_back(right[15]);
    output.push_back(right[16]);
    output.push_back(right[17]);
    output.push_back(right[18]);
    output.push_back(right[19]);
    output.push_back(right[20]);
    output.push_back(right[19]);
    output.push_back(right[20]);
    output.push_back(right[21]);
    output.push_back(right[22]);
    output.push_back(right[23]);
    output.push_back(right[24]);
    output.push_back(right[23]);
    output.push_back(right[24]);
    output.push_back(right[25]);
    output.push_back(right[26]);
    output.push_back(right[27]);
    output.push_back(right[28]);
    output.push_back(right[27]);
    output.push_back(right[28]);
    output.push_back(right[29]);
    output.push_back(right[30]);
    output.push_back(right[31]);
    output.push_back(right[0]);
    
    right = output;
//    cout << "32-bit output --> 48-bit output: " << endl << output << endl;
//    cout << "output size: " << output.size() << endl;
//    return output;
}

int RightExpansionBeta(string& right, string& sP)
{
    
    char salt1 = (rand() % 93) + 33;
    char salt2 = (rand() % 93) + 33;
    cout<<"r before append: "<<right<<endl;
    sP.push_back(salt1);
    sP.push_back(salt2);
    string s1 = toBit(salt1);
    string s2 = toBit(salt2);
    

    right += s1;
    right += s2;

    cout<<"r after append: "<< right<<endl;
    


    
}

// KeyPermutation turns 64-bit key input into 56-bit permuted output
// Should only occur (be called) once throughout the entire DES process
void KeyPermutation1(string& key) 
{
    string output;
    
    output.push_back(key[56]);
    output.push_back(key[48]);
    output.push_back(key[40]);
    output.push_back(key[32]);
    output.push_back(key[24]);
    output.push_back(key[16]);
    output.push_back(key[8]);
    output.push_back(key[0]);
    output.push_back(key[57]);
    output.push_back(key[49]);
    output.push_back(key[41]);
    output.push_back(key[33]);
    output.push_back(key[25]);
    output.push_back(key[17]);

    output.push_back(key[9]);
    output.push_back(key[1]);
    output.push_back(key[58]);
    output.push_back(key[50]);
    output.push_back(key[42]);
    output.push_back(key[34]);
    output.push_back(key[26]);
    output.push_back(key[18]);
    output.push_back(key[10]);
    output.push_back(key[2]);
    output.push_back(key[59]);
    output.push_back(key[51]);
    output.push_back(key[43]);
    output.push_back(key[35]);

    output.push_back(key[62]);
    output.push_back(key[54]);
    output.push_back(key[46]);
    output.push_back(key[38]);
    output.push_back(key[30]);
    output.push_back(key[22]);
    output.push_back(key[14]);
    output.push_back(key[6]);
    output.push_back(key[61]);
    output.push_back(key[53]);
    output.push_back(key[45]);
    output.push_back(key[37]);
    output.push_back(key[29]);
    output.push_back(key[21]);

    output.push_back(key[13]);
    output.push_back(key[5]);
    output.push_back(key[60]);
    output.push_back(key[52]);
    output.push_back(key[44]);
    output.push_back(key[36]);
    output.push_back(key[28]);
    output.push_back(key[20]);
    output.push_back(key[12]);
    output.push_back(key[4]);
    output.push_back(key[27]);
    output.push_back(key[19]);
    output.push_back(key[11]);
    output.push_back(key[3]);
    
//    cout << "Permuted Key: " << output << endl;
//    cout << "output.size(): " << output.size() << endl;
    key = output;
}

void LeftShift(string& key) 
{
    string output = key;
    string tempChar;
    
//    cout << "Key: " << output << endl;
//    cout << "key.size(): " << output.size() << endl;
    tempChar = output.front();
    output.erase(0,1);
    output = output + tempChar;
//    cout << "Key: " << output << endl;
//    cout << "key.size(): " << output.size() << endl;
    
    key = output;
}

void KeyPermutation2(string& key)
{
    static int round = 0;
    
    string output;
    
    output.push_back(key[13]);
    output.push_back(key[16]);
    output.push_back(key[10]);
    output.push_back(key[23]);
    output.push_back(key[0]);
    output.push_back(key[4]);
    output.push_back(key[2]);
    output.push_back(key[27]);
    output.push_back(key[14]);
    output.push_back(key[5]);
    output.push_back(key[20]);
    output.push_back(key[9]);
    
    output.push_back(key[22]);
    output.push_back(key[18]);
    output.push_back(key[11]);
    output.push_back(key[3]);
    output.push_back(key[25]);
    output.push_back(key[7]);
    output.push_back(key[15]);
    output.push_back(key[6]);
    output.push_back(key[26]);
    output.push_back(key[19]);
    output.push_back(key[12]);
    output.push_back(key[1]);
    
    output.push_back(key[40]);
    output.push_back(key[51]);
    output.push_back(key[30]);
    output.push_back(key[36]);
    output.push_back(key[46]);
    output.push_back(key[54]);
    output.push_back(key[29]);
    output.push_back(key[39]);
    output.push_back(key[50]);
    output.push_back(key[44]);
    output.push_back(key[32]);
    output.push_back(key[47]);
    
    output.push_back(key[43]);
    output.push_back(key[48]);
    output.push_back(key[38]);
    output.push_back(key[55]);
    output.push_back(key[33]);
    output.push_back(key[52]);
    output.push_back(key[45]);
    output.push_back(key[41]);
    output.push_back(key[49]);
    output.push_back(key[35]);
    output.push_back(key[28]);
    output.push_back(key[31]);

    //    cout << "Permuted Key: " << output << endl;
    //    cout << "output.size(): " << output.size() << endl;
    key = output;
}

string XOR(string right, string key) 
{
    string output;
    
    cout << "right:      " << right << endl;
    cout << "key:        " << key << endl;
    
    for (int i = 0; i < 48; i++) {
        if ((right[i] == key[i]) || (right[i] == '0' && key[i] == '0')) {
            output = output + "0";
        }
        else {
            output = output + "1";
        }
//        output = output + [(right[i] ^ key[i]);
    }
    
    cout << "xor output: " << output << endl;
    
    return output;
}

string toBit(char target) // for 8 bits only.
{
    string bitStream;
    int x =  target;
    for(int i = 7; i !=-1 ; --i)
    {
        if(pow(2, i) <= x)
        {
            bitStream.push_back(1+48);
            x-= pow(2, i);
        }
        else
            bitStream.push_back(0+48);

    }
    return bitStream;

}

#endif
