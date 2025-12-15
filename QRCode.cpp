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
        for (int j = 0; i < size; j++){
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


void printImg(const vector<string> &img){
    for (unsigned int i = 0; i < img.size(); i++){
        cout << img.at(i) << endl;
    }
}

string imgtoBinary(const vector<string> &img){
    string bits = "";
    for (int i = 0; i < img.size(); i++){
        for (int j = 0; i < img[i].size();j++){
            if (img[i][j] == '#'){
                bits += '1';
            } 
            else {
                    bits += '0';
                }
            }
        }
            return bits;
    }






