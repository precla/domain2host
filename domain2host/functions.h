#pragma once

void addCustomHostToDomain( char **, std::string );
void bookmarksToHostFile( std::ofstream &, std::string, std::string );
std::string cleanStringsFromUselessContent( std::string );