//CS 323_34 Joseph Bdaro Project 6.2 Run length Decoding

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class runLength {
public:
	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int whichMethod;
	string nameEncodeFile;
	string nameDecodeFile;

	//constructor
	runLength(int numRows, int numCols, int minVal, int maxVal, int whichMethod, string nameEncodeFile, string nameDecodeFile) {
		this->numRows = numRows;
		this->numCols = numCols;
		this->minVal = minVal;
		this->maxVal = maxVal;
		this->whichMethod = whichMethod;
		this->nameEncodeFile = nameEncodeFile;
		this->nameDecodeFile = nameDecodeFile;
	}

	int startRow;
	int startCol;
	int color;
	int length;

	void decodeMethod1(ifstream& encodeFile, ofstream& decodeFile){
		int rowCount = 0;
		int colCount = 0;
		while (rowCount < numRows) {
			encodeFile >> startRow;
			encodeFile >> startCol;
			encodeFile >> color;
			encodeFile >> length;
			for (int i = 0; i < length; i++) {
				decodeFile << color << " ";
				colCount ++;
			}
			if (colCount >= numCols) {
				decodeFile << endl;
				colCount = 0;
				rowCount++;
			}
		}
	}

	//decode method 4
	void decodeMethod4(ifstream& encodeFile, ofstream& decodeFile) {
		int rowCount = 0;
		int colCount = 0;
		//runs through the file until empty
		while (rowCount < numRows && encodeFile >> startRow) {
			encodeFile >> startCol;
			encodeFile >> color;
			encodeFile >> length;

			//if either the row count or column count is behind the start row or column of a run then 0's must be padded
			while (rowCount != startRow || colCount != startCol) {
				//if the row count is less than start row then we must pad the entire remainder of row with 0's until we reach that row
				if (rowCount != startRow) {
					while (colCount < numCols) {
						decodeFile << "0 ";
						colCount++;
					}
					decodeFile << endl;
					rowCount++;
					colCount = 0;
				}
				//if the row count and start row are equal but the start col and col count are not equal then we must pad the col until we get to the start col
				else if (rowCount == startRow && colCount != startCol) {
					while (colCount < startCol) {
						decodeFile << "0 ";
						colCount++;
					
					}
				}
			}
			//once our rowcount and col count are equal to row start and col start of the run we can now output this info to the outfile
			for (int i = 0; i < length; i++) {
				decodeFile << color << " ";
				colCount++;
				if (colCount >= numCols) {
					decodeFile << endl;
					colCount = 0;
					rowCount++;
				}
			}
			

		}
		//if the file ends with row(s) of zeros then add the rows as there's no instructions for 0's at the end of the file
		while (rowCount < numRows) {
			while (colCount < numCols) {
				decodeFile << "0 ";
				colCount++;
			}
			colCount = 0;
			rowCount++;
			decodeFile << endl;
		}
	}
};

//Method used for extract the file name of argv1 without the extenstion
string nameOutFile(string nameDecodeFile) {
	string result;
	for (int i = 0; nameDecodeFile[i] != '.'; i++) {
		result += nameDecodeFile[i];
	}
	return result;
}

int main(int argc, char* argv[])
{
	ifstream encodeFile;
	encodeFile.open(argv[1]);
	ofstream decodeFile;

	int numRows;
	int numCols;
	int minVal;
	int maxVal;
	int whichMethod;
	string nameDecodeFile;

	encodeFile >> numRows;
	encodeFile >> numCols;
	encodeFile >> minVal;
	encodeFile >> maxVal;
	encodeFile >> whichMethod;
	
	//used to create the file name pertaining to encoded file
	nameDecodeFile = argv[1];
	nameDecodeFile = nameOutFile(nameDecodeFile) + "_Decoded" + ".txt";
	decodeFile.open(nameDecodeFile);

	//creates the decode objext and inserts the image header in the decode file
	runLength* newImage = new runLength(numRows, numCols, minVal, maxVal, whichMethod, argv[1], nameDecodeFile);
	decodeFile << newImage->numRows << " " << newImage->numCols << " " << newImage->minVal << " " << newImage->maxVal << endl;
	
	//switch statements
	switch (newImage->whichMethod) {
	case 1: {
		newImage->decodeMethod1(encodeFile, decodeFile);
		encodeFile.close();
		decodeFile.close();
	}
	case 4: {
		newImage->decodeMethod4(encodeFile, decodeFile);
		encodeFile.close();
		decodeFile.close();
	}

	}



}

