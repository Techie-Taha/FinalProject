#include <iostream>
#include "QRCode.h"

using namespace std;
int main () {

    QRCode qr;
    cout << "1. Encode message" << endl;
    cout << "2. Decode QR code from file" << endl;
    cout << "Choose: " << endl;


    int choice = 0;
    cin >> choice;
    cin.ignore(); // This code was written with the aid of ChatGPT; when prompted 'how to fix input buffering?'the generated text helped me write the this line of code: accessed: Dec. 2025
    if (choice == 1){

        qr.encodeFromUserInput();
        qr.displayQrOnTerminal();
        qr.explainSignature();
        cout << "Would you like to save the QR code to a file? (y/n): " << endl;

        char c;
        cin >> c;
        cin.ignore();
        if (c == 'y' || c == 'Y'){
            cout << "Enter filename (myqr.txt) to save QR code : " << endl;
            string fileName;
            getline(cin, fileName);
            if (fileName.size() == 0){
                fileName = "qr_output.txt";
            }
            qr.saveToFile(fileName);
        }
    }
    else if (choice == 2){
        cout << "Enter filename to load (qr_output.txt): " << endl;
        string fileName;
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
