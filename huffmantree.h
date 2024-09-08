#include <iostream>
#include <string>
#include <map>
#include <queue>

using namespace std;

#ifndef NODE
#define NODE

struct Node
{
    string character;
    int weight;
    Node* one; //right child
    Node* zero; //left child
};

#endif

#ifndef NODECOMPARE
#define NODECOMPARE

//Function to have nodes ordered according to their weights when in a priority queue
struct NodeCompare
{
    bool operator()( const Node* first_node, const Node* second_node) const
    {
        return first_node->weight > second_node->weight;
    }
};

#endif

#ifndef HUFFMAN_HUFFMANTREE_H
#define HUFFMAN_HUFFMANTREE_H

class HuffmanTree
{
private:
    Node* root;

    /**
     * This method creates a map with each unique character in the given string
     *      as a key, and stores the number of occurrences of each character, then
     *      returns that map.
     *
     * @param input_string the string we're creating a map for.
     * @return the map storing the unique characters and their frequency or weight.
     */
    map<string,int> BuildCharFrequencyTable(string input_string);

    /**
     * This method goes down the tree that is passed in, recursively calling itself
     *      and storing 0s and 1s depending on the path it goes down, until it
     *      reaches a leaf. It then adds the string of 0s and 1s into a map with the
     *      character at the leaf as the key of the map element.
     *
     * @param current_node the current node for which we're storing the bit.
     * @param prefix the string we're storing the 0s and 1s in.
     * @param codes the map we're storing the characters and their codes in.
     * @return the map the characters and their codes are stored in.
     */
    map<string,string> HuffmanGetCodes(Node *current_node, string prefix, map<string,string> &codes);

    /**
     * This method builds a Huffman tree for the string that is passed in. It calls the
     *      BuildCharFrequencyTable method and uses the map returned to create nodes, it
     *      then stores those nodes in a priority queue before building a tree with the nodes.
     *
     * @param text the string we're building a Huffman tree for.
     * @return the root of the created tree.
     */
    Node* HuffmanBuildTree(string text);

    /**
    * This method deletes all the nodes in the tree by repeatedly calling itself,
    *       it deletes the root of the tree at the very end.
    *
    * @param tree the root of the tree/subtree that we are currently going down.
    */
    void deleteAll(const Node* tree);

public:

    HuffmanTree(); //Default constructor
    ~HuffmanTree(); //Destructor

    /**
     * This method encodes the string passed in by calling helper methods to
     *      build the Huffman tree and get the bit codes for each character
     *      before concatenating the codes for the characters appropriately.
     *
     * @param text the string we're encoding.
     * @return the encoded string.
     * @see HuffmanBuildTree the helper function used to build the Huffman tree.
     * @see HuffmanGetCodes the helper function used to acquire the bit codes for
     *      the characters.
     */
    string encode(string text);

    /**
     * This method decodes the string passed in by going down the root of the
     *      tree, moving to the zero or one child depending on the current bit,
     *      it then moves to the next bit in the string, repeating the process
     *      until it reaches a leaf node. It then stores the node's character
     *      before setting the current node as the root again to begin decoding
     *      the next character.
     *
     * @param encoded_text the string of 0s and 1s which we're decoding
     * @return the decoded string
     */
    string decode(string encoded_text);

};

#endif //HUFFMAN_HUFFMANTREE_H