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
string DecryptDES(string, string);
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
string OR(string, string);
string AND(string, string);

//-- Function/Class Implementations
string EncryptDES(string message, string key) {
    // 0. Declare output (local) variable(s)
    string output;
    string leftM;
    string rightM;
    string tempM;
    string saltPile;
    
    srand(time(NULL));
    
    // Perform initial permutation on key to make it into 56-bit
    KeyPermutation1(key);
    
    
    // 0.1 Perform Initial Permutation??? (Note: This actually does not help)
    //... Skip for right now
    
    
    // Perform 16 round encryption
    cout << "Begin 16 round encryption loop!" << endl;
    for (int i = 0; i < 16; i++) {
        cout << "*********************************** Round " << i << " ***********************************" << endl;
        
        // 1. Split message string into left and right 32 bit strings
        cout << "\tSplit message (left & right)" << endl;
        
        // 1.1 Call a left message function into 32-bit string
        leftM = LeftMessage(message);
        cout << "\t  leftM =  " << leftM << endl;
        
        // 1.2 Call a right message function into 32-bit string
        rightM = RightMessage(message);
        cout << "\t  rightM = " << rightM << endl;
        
        // 2. Perform Feistel System function on rightM, and key
        cout << "\n\tBegin Feistel System" << endl;
        string feistelM = FeistelSystem(rightM, key, saltPile);
       // cout<<feistelM.length()<<endl; 
        
        // 3. XOR Feistel System string 32 bit output with the current leftM 32 bit input (This now becomes the new left side)
        cout << "\n\tXOR Feistel System with leftM" << endl;
        string tempM = XOR(leftM, feistelM);
        cout << "\t   leftM =    " << leftM << endl;
        cout << "\t   feistelM = " << feistelM << endl;
        cout << "\t   xor =      " << tempM << endl;
        
        // 4. Turn old rightM into new leftM
        leftM = rightM;
        rightM = tempM;
        
        // 5. Merge new left & right together
        cout << "old message: " << message << endl;
        message = leftM + rightM;
        cout << "new message: " << message << endl;
        
        cin.ignore();
    }
    
    cout << "*******************************************************************************" << endl;
    // 5. Perform Final Permutation??? (Note: This actually does not help)
    
    // Return ciphertext string
    return output;
}

string DecryptDES(string, string)
{
    // 0. Declare output (local) variable(s)
    string output;
    string leftM;
    string rightM;
    string tempM;
    string saltPile;
    
    srand(time(NULL));
    
    // Perform initial permutation on key to make it into 56-bit
    KeyPermutation1(key);
    
    
    // 0.1 Perform Initial Permutation??? (Note: This actually does not help)
    //... Skip for right now
    
    // First thing to note is that l1d = r15e and r1d =r1d = l15e
    
    
    // Perform 15 round decryption
    cout << "Begin 15 round decryption loop!" << endl;
    for (int i = 0; i < 15; i++) {
        cout << "*********************************** Round " << i << " ***********************************" << endl;
        // 1. Split message string into left and right 32 bit strings
        cout << "\tSplit message (left & right)" << endl;
        
        // 1.1 Call a left message function into 32-bit string
        leftM = LeftMessage(message);
        cout << "\t  leftM =  " << leftM << endl;
        
}

string LeftMessage(string message) 
{
    //cout <<"The size of the message string is " << message.size() << " 'bits'?" << endl;
    string output;
    
    // This loop iterates through the message and stores only first half (leftM) into output
    for (int index = 0; index < (message.size() / 2); index++)
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
    static int round = 0;
    
    // 1. Expand rightMessage from 32 bits to 48 bits (E-Box Substitution)
    cout << "\t1. Perform right expansion" << endl;
    //RightExpansion(rightMessage);
    cout << "\t     a. Pre right expansion" << endl;
    cout << "\t        rightM: " << rightMessage << endl;
    RightExpansionBeta(rightMessage, saltPile);
    //RightExpansion(rightMessage);
    cout << "\t     b. Post right expansion" << endl;
    cout << "\t        rightM: " << rightMessage << endl;
    
    // 2. Mix/Shift key schedule
    // 2.1 Split new 56-bit key into C & D each 28-bit
    cout << "\t2. Perform key mixing schedule" << endl;
    cout << endl;
    cout << "\t     key1 = " << key << endl;
    cout << endl;
    
    string c = LeftMessage(key);

    cout << "\t     a. Pre left shift on both 'c' and 'd'" << endl;
    
    cout << "\t        c =   " << c << endl;
    
    string d = RightMessage(key);
    cout << "\t        d =   " << d << endl;
    
    // 2.2 LeftShift (once or twice)
    cout << "\t     b. Post left shift on both 'c' and 'd'" << endl;
    cout << "\t        (Note: shift once if round is 0,1,8,15 and twice otherwise)" << endl;
    if (round == 0 || round == 1 || round == 8 || round == 15) {
        LeftShift(c);
        LeftShift(d);
    }
    else {
        LeftShift(c);
        LeftShift(c);
        LeftShift(d);
        LeftShift(d);
    }
    cout << "\t        c =   " << c << endl;
    cout << "\t        d =   " << d << endl;
    
    
    // 2.3 Then Permute once again with either 1 or 2 shift (depending on ith iteration)
    cout << "\t     c. Shifted key (c + d)" << endl;
    key = c + d;
    cout << "\t        key2 = " << key << endl;
    string key2 = key;
    KeyPermutation2(key2);
    cout << "\t     d. Permuted key" << endl;
    cout << "\t        key3 = " << key2 << endl;
    
    // 2.1 XOR 48-bit rightMessage with new 48-bit key
    cout << "\t     e. XOR rightM with new 48-bit key" << endl;
    output = XOR(rightMessage, key2);
    cout << "\t        key3   = " << key2 << endl;
    cout << "\t        rightM = " << rightMessage << endl;
    cout << "\t        xor    = " << output << endl;
    
    // 3. Call new MagicFunction
    cout << "\t3. Call new mysterious Magic Function" << endl;
    cout << "\t   (Replacement for the S-Boxes)" << endl;
    
    /*
    char outp[4];
    outp[0] = output.at(0) ^ output.at(3) ^ output.at(5);
    outp[1] = output.at(0) | output.at(2) | output.at(4);
    outp[2] = output.at(1) ^ output.at(3) ^ output.at(5);
    outp[3] = output.at(1) & output.at(2) & output.at(4);
    string code(outp);
    */
    string output2 = "";
    for(int i = 0; i < 8; ++i)
    {
        output2 += XOR(XOR(output.substr(0, 1),output.substr(3, 1)), output.substr(5, 1));
    }
    for(int i = 8; i < 16; ++i)
    {
        output2 += OR(OR(output.substr(0, 1), output.substr(2, 1)), output.substr(4, 1));
    }
    for(int i = 16; i < 24; ++i)
    {
        output2 += XOR(XOR(output.substr(1, 1), output.substr(3, 1)), output.substr(5, 1));
    }
    for(int i = 24; i < 32; ++i)
    {
        output2 += AND(AND(output.substr(1, 1), output.substr(2, 1)), output.substr(4, 1));
    }

    cout << "\t     a. Result prior to Magic Function" << endl;
    cout << "\t        xor =         " << output << endl;
    cout << "\t     b. Result prior to Magic Function" << endl;
    cout << "\t        feistelM =    " << output2 << endl;

    // 4. Return new string output
    round++;
    return output2;//code;
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
}

int RightExpansionBeta(string& right, string& sP)
{
    
    char salt1 = (rand() % 93) + 33;
    char salt2 = (rand() % 93) + 33;
    //cout<<"r before append: "<<right<<endl;
    sP.push_back(salt1);
    sP.push_back(salt2);
    string s1 = toBit(salt1);
    string s2 = toBit(salt2);
    

    right += s1;
    right += s2;

    //cout<<"r after append: "<< right<<endl;
    
    return 0;
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
    
    key = output;
}

void LeftShift(string& key) 
{
    string output = key;
    string tempChar;
    
    tempChar = output.front();
    output.erase(0,1);
    output = output + tempChar;
    
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

    key = output;
}

string XOR(string string1, string string2) 
{
    string output;
    
    for (int i = 0; i < string1.length(); i++) 
    {
        if ((string1[i] == string2[i]) || (string1[i] == '0' && string2[i] == '0')) {
            output += '0';
        }
        else {
            output += "1";
        }
    }
    
    return output;
}

string OR(string string1, string string2)
{
    string output;

    for(int i = 0; i < string1.length(); ++i)
    {
        if(string1[i] == '0' && string2[i] == '0')
            output += "0";
        else
            output += "1";
    }
    return output;
}

string AND(string string1, string string2)
{
    string output;

    for(int i = 0; i < string1.length(); ++i)
    {
        if(string1[i] == '1' && string2[i] == '1')
            output += "1";
        else
            output += "0";
    }
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
