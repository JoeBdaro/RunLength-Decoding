# RunLength-Decoding
C++ Implementation of the Runlength Decoding compression algorithm 

This is the decoding algorithm for the (with zero and no wrap-around) and the (no zero and wrap-around) methods of run length encoding.
Given a properly named encoded file, the algorithm will decode said File with the right decoding method based on the name. For example, given an encoded file called image1_EncodeMethod1.txt the algorithm will decode the file with method 1 and create a decoded file called image1_EncodeMethod1_Decoded.txt

<b>How to run</b>

This code runs from the command line and requires the following arguments from command line upon running

argv[1]: any of the files with the format image1_EncodeMethod1.txt
