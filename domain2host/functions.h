#pragma once

using namespace std;

void addCustomHostToDomain( char **, const string & );
void bookmarksToHostFile( ofstream &, string, const string & );
string cleanStringsFromUselessContent( string );
bool checkForDoubleDomain( const string &, vector<string> & );