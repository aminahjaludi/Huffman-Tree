#include "huffmantree.h"

//Constructor
HuffmanTree::HuffmanTree()
{
    root = nullptr;
}

//Destructor
HuffmanTree::~HuffmanTree()
{
    //Call helper function to delete the nodes
    deleteAll(root);
    root = nullptr;
}

//Method encode the string
string HuffmanTree::encode(string text)
{
    //Create the string to store the result
    string result = "";

    //Build the tree and store the root
    root = HuffmanBuildTree(text);

    //Create a map for the character codes
    map<string,string> codes;
    HuffmanGetCodes(root, "", codes);

    //Concatenate the codes
    for(int i = 0; i < text.length(); i++)
    {
        result = result + codes[text.substr(i,1)];
    }

    return result;
}

//Method to decode the string
string HuffmanTree::decode(string encoded_text)
{
    //Set current node to the root
    Node* current_node = root;

    //Create a string to store the result
    string result = "";

    for (int i = 0; i < encoded_text.length(); i++)
    {
        //String to keep track of current bit
        string bit = encoded_text.substr(i,1);

        //Go to the zero or one child based on the current bit value
        if (bit == "0")
        {
            current_node = current_node->zero;
        }
        else if (bit == "1")
        {
            current_node =  current_node->one;
        }

        //If we reach a leaf node, store its character value
        if (current_node->zero == nullptr and current_node->one == nullptr)
        {
            //Concatenate the character to the result string
            result = result + current_node->character;

            //Set current node back to the root
            current_node = root;
        }
    }
    return result;
}

//Private helper method to create the map with the characters and their weights/frequency
map<string, int> HuffmanTree::BuildCharFrequencyTable(string input_string)
{
    //Create the map
    map<string,int> table;

    for (int i = 0; i < input_string.length(); i++)
    {
        //Create a string to keep track of current character
        string currentCharacter = input_string.substr(i,1);

        //Check if the map already has a key with the current character
        if (table.find(currentCharacter) != table.end())
        {
            //Increment the character weight
            table[currentCharacter] = table[currentCharacter] + 1;
        }
        else
        {
            //Add the character with weight = 1
            table[currentCharacter] = 1;
        }
    }
    return table;

}

//Private helper method to get the bit code of the characters
map<string,string> HuffmanTree::HuffmanGetCodes(Node *current_node, string prefix, map<string,string> &codes)
{
    //If the current node is a leaf (an actual character)
    if (current_node->character != "")
    {
        //Store the prefix string as it's bit code in the map
        codes[current_node->character] = prefix;
    }

        //If the current node is an internal node
    else
    {
        //keep moving down the tree, adding 0 or 1 to the prefix depending on the side
        HuffmanGetCodes(current_node->zero, prefix + "0", codes);
        HuffmanGetCodes(current_node->one, prefix + "1", codes);
    }
    return codes;
}

//Private helper method to actually build the Huffman tree
Node* HuffmanTree::HuffmanBuildTree(string text)
{
    //Create the map of the characters and their frequency/weight
    map<string, int> table = BuildCharFrequencyTable(text);

    //Create the priority queue to store the nodes
    priority_queue<Node*, vector<Node*>, NodeCompare> nodes;

    for(auto i = table.cbegin(); i != table.cend(); i++)
    {
        //Create a node for each unique character
        Node* newNode = new Node;
        newNode->character = i->first;
        newNode->weight = i->second;
        newNode->zero = nullptr;
        newNode->one = nullptr;

        //Push the new node to the priority queue
        nodes.push(newNode);
    }

    //Begin building the tree
    while (nodes.size() > 1)
    {
        //Begin by popping the nodes with the smallest weights
        Node* left = nodes.top();
        nodes.pop();

        Node* right = nodes.top();
        nodes.pop();

        //Make a parent for the two nodes
        Node* parent = new Node;
        parent->weight = right->weight + left->weight;
        parent->zero = left;
        parent->one = right;
        parent->character = "";

        //Push the parent back into the priority queue
        nodes.push(parent);
    }

    //Return the top of priority queue, which is the root of the created tree
    return nodes.top();
}

//Private helper method to delete the allocated memory
void HuffmanTree::deleteAll(const Node* tree)
{
    //If current node is nullptr, we're done deleting
    if(tree == nullptr)
    {
        return;
    }

    deleteAll(tree->zero);
    deleteAll(tree->one);
    delete tree;
}