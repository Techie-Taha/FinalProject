#include "QRcode.h"
#include <iostream>
#include <cmath>
#include <cctype>
#include <fstream>
using namespace std;


string chartoBinary(char c) {
    string bits = "";
    int value = c;
    while (bits.length() < 8){
        bits = char('0' + (value%2)) + bits;
        value = value /= 2;
    }
// This is how the algorithm: value%2 helps to get remainder 0 and 1, like it divides the character's number by 2 and the loop keeps on going until it has 8 bits.
    return bits;
}

string texttoBinary(const string &text){
    string result = "";
    for (unsigned int i = 0; i < text.size(); i++){
        result += chartoBinary(text.at(i));
    }
    return result;
}

int calculatetheCheckSum(const string &text){
    int sum = 0;
    for (unsigned int i = 0; i < text.size(); i++){
        sum += int(text.at(i));
    }
    return sum;
}
// This function will use the concept of ASCII values to calculate the checksum of a text which is sum of all characters in the text. 

unsigned int calculateImgSize(unsigned int bitCount){
    unsigned int size = 1;
    while (size*size < bitCount){
        size++;
    }
    return size;
}


/***********
     
        Researched and took assistance from this website:
        GeeksForGeeks
        https://www.geeksforgeeks.org/dsa/convert-a-string-into-a-square-matrix-grid-of-characters/
        Accessed: Dec. 2025

         **********/
vector<string> binarytoImg(const string &binary){
    unsigned int length = binary.length();
    unsigned int size = calculateImgSize(length);
    vector<string> rows(size);
    int x = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (x < length){
                if (binary.at(x) == '1'){
                    rows.at(i) += '#';
                }
                else {
                    rows.at(i) += ' ';

                }
                x++;
            }
            else {
                rows.at(i) += ' ';
            }
        }
    }
    return rows;
}

// This is how the algorithm works: The function is basically converting the string into a square grid where inner loop  moves column by column and inner loop moves row by row.
// It uses # for 1, and 0 for spaces to form QR alike shape.


void printImg(const vector<string> &grid){
    for (unsigned int i = 0; i < grid.size(); i++){
        cout << grid.at(i) << endl;
    }
}

string imgtoBinary(const vector<string> &grid){
    string bits = "";
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            if (grid[i][j] == '#'){
                bits += '1';
            } 
            else {
                    bits += '0';
                }
            }
        }
            return bits;
    }

string binarytoText(const string &binary){
    string text = "";
    int value = 0;
    int count = 0;
    for (int i = 0; i < binary.length(); i++){
        value = value*2;

        if (binary.at(i) == '1'){
            value = value + 1;
        }
        count = count + 1;

        if (count == 8){
            text += char(value);
            value = 0;
            count = 0;
        }
    }
    return text;
}
// Here's how the code runs: Once the loop starts, it goes through each of the binary string character at a time, the value*2 works because this shifts the current number to the left once it multiplied by 2.
// if the current binary is = '1', one is added to the current value. At the end value and count is equal to 0 because resetting the number is important, so the next character can be calculated. 



/* -----
This code was written with the aid of ChatGPT;
when prompted 'how do I remove extra spaces and newlines from the END of a string?'
the generated text helped me write the following code:
accessed: Aug. 2025
 -------- */

 string rtrim(const string &s){
    string result = s;

    while (!result.empty() && result.back() == ' '){
        result.pop_back();
    }
    return result;
 }

 QRCode::QRCode() {
    message = "";
    binaryData = "";
    grid.clear();  // This line of code was written with the aid of ChatGPT; when prompted 'how to remove all stored QR rows so the vector is empty and ready to store new data?'the generated text helped me write the this line of code: accessed: Dec. 2025
    checksum = 0;

 }

 void QRCode::explainSignature() {
    cout << endl << "Here is the explantion of the signature:" << endl;
    cout << "This program has a unique signature, which is: [[TAHA_SIG_v11]]" << endl;
    cout << "The signature appears as the first and last line of of the saved file." << endl;
    cout << "To help the decoder to verify the message, A CHECKSUM line is also saved" << endl;
    cout << "These lines of code will not affect decoding because these lines are not part of the grid." << endl;
    cout << endl;


 }
/* -----
This code was written with the aid of ChatGPT;
when prompted 'how to write a function that loads a QR code from a file, verifies signature and reads the checksum?'
the generated text helped me write the following code:
accessed: Aug. 2025
 -------- */
 bool QRCode::loadFromFile(const string &filename){
    ifstream file(filename);
    if (!file){
        cout << "Error: could not open file." << endl;
        return false;
    }

    string signature = "[[TAHA_SIG_v11]]";
    string line;

    getline(file, line);
    line = rtrim(line);
    if (line != signature){
        cout << "Error: The QR file is invalid." << endl;
        return false;

    }

    getline(file, line);
    line = rtrim(line);
    int initialChecksum = 0;
    for (int i = 9; i < line.length(); i++){
        if (line.at(i) >= '0' && line.at(i) <= '9'){
            initialChecksum = initialChecksum * 10 + (line.at(i) - '0');
        }
    }

    vector<string> loadedGrid;

    while (getline(file, line)){
        if (rtrim(line) == signature){
            break;
        }
        loadedGrid.push_back(line);
    }

    if (loadedGrid.size() == 0){
        cout << "Error: No QR code found, try again!!" << endl;
        return false;
    }
    grid = loadedGrid;
    checksum = initialChecksum;

    cout << "QR code loaded successfully" << endl;
    return true;

 }

 void QRCode::decodeQr(){
    if (grid.size() == 0){
        cout << "No grid loaded to decode" << endl;
        return;
    }
        string bits = imgtoBinary(grid);

        string decodedMessage = binarytoText(bits);
        int decodedChecksum = calculatetheCheckSum(decodedMessage);

        cout << endl;

        cout << "Decoded message:" << endl;

        cout << decodedMessage << endl;
        cout << endl;
        cout << "Saved checksum: " << checksum << endl;
        cout << "Decoded checksum: " << decodedChecksum << endl;

        if (checksum == decodedChecksum){
            cout << "Checksum verification: PASSED" << endl;

        }
        else {
            cout << "Checksum verification: FAILED" << endl;
        }
    }
 






