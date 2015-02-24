/*
* (C) 2015 precla
*
* This file is part of domain2host.
*
* domain2host is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* domain2host is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
*/

#include <iostream>
#include <fstream>
#include <string>

#define LOCALHOST "127.0.0.1"

using namespace std;

void addCustomHostToDomain( char **, string );

int main( int argc, char *argv[] ) {

	if (argc < 4) {
		cout << "Not enough parameters" << endl;
	} else if (argc >= 4) {
		string customHostAddress;
		if ( argv[1] == "0" ) {
			customHostAddress = LOCALHOST;
		} else {
			customHostAddress = argv[1];
		}
		addCustomHostToDomain( argv, customHostAddress );
	}

	return 0;
}

void addCustomHostToDomain( char **argList, string _customHostAddress ) {
	
	ofstream outputFile;
	outputFile.open( argList[2], ios::out );
	if ( !outputFile.is_open() ) {
		perror( "error opening file\n" );
	} else {
		unsigned int n = 3;
		do {
			ifstream inputFile;
			inputFile.open( argList[n], ios::in );

			if ( !inputFile.is_open() ) {
				perror( "error opening input file!\n" );
			} else {
				string domainName;
				while ( getline( inputFile, domainName ) ) {
					//TODO: add regex to read only domains or ip addresses
					outputFile << _customHostAddress << " " << domainName << '\n';
				}
				inputFile.close();
			}
		} while ( argList[++n] != NULL );
		outputFile << "## This host file has been created with domain2host";
		outputFile.close();
	}
}