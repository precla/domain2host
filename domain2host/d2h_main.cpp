#include <iostream>
#include <fstream>
#include <string>

#define LOCALHOST "127.0.0.1 "

using namespace std;

int main( int argc, char *argv[] ) {

	string inputFileName, ouputFileName;

	if (argc > 3) {
		cout << "Too much arguments!\n";
		return 0;
	} else if (argc == 3) {
		ouputFileName = argv[2];
		inputFileName = argv[1];
	} else if (argc == 2) {
		inputFileName = argv[1];
		cout << "Insert name of file to save into: ";
		cin >> ouputFileName;
	} else if (argc <= 1) {
		cout << "Insert name of file to read from: ";
		cin >> inputFileName;
		cout << "Insert name of file to save into: ";
		cin >> ouputFileName;
	}

	ifstream inputFile;
	inputFile.open( inputFileName, ios::in );

	if ( !inputFile.is_open() ) {
		perror( "error opening file\n" );
	} else {
		ofstream outputFile;
		outputFile.open( ouputFileName, ios::out );
		if ( !outputFile.is_open() ) {
			perror( "error creating file\n" );
		} else {
			string domainName;
			while (getline( inputFile, domainName )) {
				outputFile << LOCALHOST << domainName << '\n';
			}
			outputFile.close();
		}
		inputFile.close();
	}

	return 0;
}