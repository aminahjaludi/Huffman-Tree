#include "huffmantree.h"

int main()
{
    HuffmanTree tree;
    string text = "go go go gophers";

    string encoded = tree.encode(text);
    string decoded = tree.decode(encoded);

    cout << "The original text is: \"" << text << "\"." << endl;
    cout << "The encoded text is:  \"" << encoded << "\"." << endl;
    cout << "The decoded text is:  \"" << decoded << "\"." << endl;
    return 0;
}