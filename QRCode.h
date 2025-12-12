#ifndef QR_CODE_H
#define QR_CODE_H
#include <string>
#include <vector>

using namespace std;
class QRCode {
    public:
    QRCode();
    void encodeFromUserInput();
    void saveToFile(const string &filename);
    void displayQrOnTerminal();
    void explainSignature();

    // These two will be used for decoding, like a sort of helper functions.
    bool loadFromFile(const string &filename);
    void decodeQr();
    // These are just some internal data.
    private: 
    string message;
    string binaryData;
    vector<string> grid;
    int checksum;
};
#endif
