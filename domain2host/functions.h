#pragma once

using namespace std;

void addCustomHostToDomain( char **, const string & );
void bookmarksToHostFile( ofstream &, const string & );
string cleanStringsFromUselessContent( string );
bool checkForDoubleDomain( const string &, vector<string> & );