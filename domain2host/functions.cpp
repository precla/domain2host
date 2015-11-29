#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "functions.h"

#define FIRST_INPUT_FILE_IN_ARGUMENTLIST 3
#define FIREFOX_BOOKMARK_FILE "bookmarks.html"
#define TXT_BEFORE_LINK "<DT><A HREF=\""
#define TXT_BEFORE_LINK_LENGHT 13

using namespace std;

void addCustomHostToDomain( char **argList, const string &_customHostAddress ) {

	ofstream outputFile( argList[2], ios::out | ios::app );

	if ( outputFile.is_open() ) {
		unsigned int n = FIRST_INPUT_FILE_IN_ARGUMENTLIST;
		do {
			//if next item is bookmarks.html then call the function bookmarksToHostFile()
			if ( !_strcmpi( argList[n], FIREFOX_BOOKMARK_FILE ) ) {
				bookmarksToHostFile( outputFile, _customHostAddress );
			} else {

				ifstream inputFile( argList[n], ios::in );

				if ( !inputFile.is_open() ) {
					perror( "error creating input file!\n" );
				} else {
					string domainName;
					vector<string> checkDoubles;
					while ( getline( inputFile, domainName ) ) {
						domainName = cleanStringsFromUselessContent( domainName );
						//just in case it grabs a empty line:
						if ( domainName.empty() ) {
							continue;
						} else if ( !checkForDoubleDomain( domainName, checkDoubles ) ) {
							outputFile << _customHostAddress << " " << domainName << '\n';
						}
					}
					inputFile.close();
				}
			}
		} while ( argList[++n] != NULL );
		outputFile << "\n## This host file has been created with domain2host\n";
		outputFile.close();
	} else {
		perror( "error creating output file\n" );
	}
}

void bookmarksToHostFile( ofstream &_outputFile, const string &_customHostAddress ) {

	ifstream ffBookmarkFile( FIREFOX_BOOKMARK_FILE );

	if ( ffBookmarkFile.is_open() ) {
		_outputFile << "\n## This part is from the firefox bookmarks.html file\n";
		string domainName;
		vector<string> checkDoubles;

		while ( getline( ffBookmarkFile, domainName ) ) {

			/*
			read line by line and search for:
			<DT><A HREF="
			read into string until closing "
			*/

			if ( !( domainName.find( TXT_BEFORE_LINK ) > domainName.length() ) ) {
				domainName = domainName.substr( domainName.find( TXT_BEFORE_LINK ) + TXT_BEFORE_LINK_LENGHT, domainName.length() - domainName.find( "\"" ) );
				domainName = domainName.substr( 0, domainName.find( "\"" ) );
				cleanStringsFromUselessContent( domainName );

				if ( !checkForDoubleDomain( domainName, checkDoubles ) ) {
					_outputFile << _customHostAddress << " " << domainName << '\n';
				}
			}
		}

		_outputFile << "\n## End of bookmarks.html content\n";
		ffBookmarkFile.close();
	} else {
		perror( "error reading file 'bookmarks.html'\n" );
	}
}

string cleanStringsFromUselessContent( string &domainNameToClean ) {

	if ( !( domainNameToClean.find( "ftp://" ) > domainNameToClean.length() ) ) {
		domainNameToClean = domainNameToClean.erase( 0, 6 );
	} else if ( !( domainNameToClean.find( "ftps://" ) > domainNameToClean.length() ) ) {
		domainNameToClean = domainNameToClean.erase( 0, 7 );
	} else if ( !( domainNameToClean.find( "http://" ) > domainNameToClean.length() ) ) {
		domainNameToClean = domainNameToClean.erase( 0, 7 );
	} else if ( !( domainNameToClean.find( "https://" ) > domainNameToClean.length() ) ) {
		domainNameToClean = domainNameToClean.erase( 0, 8 );
	}

	if ( !( domainNameToClean.find( "www." ) > domainNameToClean.length() ) ) {
		domainNameToClean = domainNameToClean.erase( 0, 4 );
	}

	//remove / after TLD
	if ( !( domainNameToClean.find_last_of( "/" ) > domainNameToClean.length() ) ) {
		size_t found = domainNameToClean.find_first_of( "/" );
		domainNameToClean = domainNameToClean.substr( 0, found );
	}
	//remove whitespace after TLD
	if ( !( domainNameToClean.find_last_of( " " ) > domainNameToClean.length() ) ) {
		size_t found = domainNameToClean.find_first_of( " " );
		domainNameToClean = domainNameToClean.substr( 0, found );
	}
	//remove custom port
	if ( !( domainNameToClean.find_last_of( ":" ) > domainNameToClean.length() ) ) {
		size_t found = domainNameToClean.find_first_of( ":" );
		domainNameToClean = domainNameToClean.substr( 0, found );
	}

	return domainNameToClean;
}

bool checkForDoubleDomain( const string &domainNameToCheckDouble, vector<string> &checkDoubles ) {
	//check for duplicate before saving it to new file:

	bool foundDouble = false;

	for ( const auto &currString : checkDoubles ) {
		if ( currString == domainNameToCheckDouble ) {
			foundDouble = true;
			break;
		}
	}
	//push_back only if the domainNameToCheckDouble is not already in vector checkDoubles
	if ( !foundDouble ) {
		checkDoubles.push_back( domainNameToCheckDouble );
	}
	
	return foundDouble;
}