#include <iostream>
#include "QRCode.h"

using namespace std;
int main () {

    QRCode qr; // So we going to start with an object which is qr, and this hold encode, decode, save to txt file and display on the terminal.

    
    cout << "1. Encode message" << endl;
    cout << "2. Decode QR code from file" << endl;
    cout << "Choose: " << endl;


    int choice = 0;
    cin >> choice;
    cin.ignore(); // This code was written with the aid of ChatGPT; when prompted 'how to fix input buffering?'the generated text helped me write the this line of code: accessed: Dec. 2025
    if (choice == 1){

        qr.encodeFromUserInput();  // This funsction will ask the user for input, which will be converted into binary
        qr.displayQrOnTerminal(); // This one just prints the QR grid inside the terminal using #.
        qr.explainSignature(); // To verify QR code when decoding.
        cout << "Would you like to save the QR code to a file? (y/n): " << endl;

        char c;
        cin >> c;
        cin.ignore();
        if (c == 'y' || c == 'Y'){
            cout << "Enter filename to save (for example myqr.txt): " << endl;
            string fileName;
            getline(cin, fileName);
            if (fileName.size() == 0){  // This will only execute if the user didn't type anything
                fileName = "qr_output.txt";
            }
            qr.saveToFile(fileName);
        }
    }
    else if (choice == 2){
        cout << "Enter filename to load (for example qr_output.txt): " << endl;
        string fileName;
        getline(cin, fileName);
        /* -----
        This code was written with the aid of ChatGPT; when prompted
        'how to decode plain text from saved QR grid?'the generated text helped me write the this following lines of code: accessed: Dec. 2025
        -----*/
        /***********
     
        Knowledge was also adapted from:
        College Wallah
        https://youtu.be/e7sAf4SbS_g?si=c9qa6YKqGddEeDkJ
        Accessed: Dec. 2025

         **********/
        if (fileName.size() == 0){
            fileName = "qr_output.txt";
        }
        bool yes = qr.loadFromFile(fileName);
        if(yes){
            qr.decodeQr();
        }
    }
    else{
        cout << "Invalid choice." << endl;
    }


    return 0;
}
