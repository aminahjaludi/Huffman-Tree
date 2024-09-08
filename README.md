## Overview

Huffman Tree Encoding is a lossless data compression algorithm used to reduce the size of data files by assigning shorter codes to more frequent symbols and longer codes to less frequent symbols. This repository provides an implementation of Huffman Encoding and Decoding in C++, demonstrating the creation of a Huffman Tree and the encoding/decoding processes.<br>
<br>
<br>
## How It Works

1. **Frequency Analysis**: Determine the frequency of each symbol in the data.
2. **Build the Tree**: Construct a Huffman Tree where more frequent symbols have shorter codes.
3. **Generate Codes**: Assign binary codes based on the tree’s structure.
4. **Encode Data**: Replace symbols with their binary codes.
5. **Decode Data**: Use the tree to convert binary codes back to symbols.
