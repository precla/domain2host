#pragma once

using namespace std;

void addCustomHostToDomain( char **, string );
void bookmarksToHostFile( ofstream &, string, string );
string cleanStringsFromUselessContent( string );
bool checkForDoubleDomain( string, vector<string> & );