#include <iostream>
#include <string>

#define LOCALHOST "127.0.0.1 "

int main( int argc, char *argv[] ) {

	char fileName[50];
	scanf_s( "%s", fileName, 50 );

	FILE *fileToOpen;
	fileToOpen = fopen( fileName, "r" );
	if (fileToOpen == NULL) {
		perror( "error opening file\n" );
	} else {
		char *buffer;
		FILE *newFile;
		newFile = fopen( "edited.txt", "w+" );
		if (newFile == NULL) {
			perror( "error creating file\n" );
		} else {
			while (!feof( fileToOpen )) {
				if (fgets( buffer, 100, fileToOpen ) == NULL) {
					break;
				}
				fputs( LOCALHOST, newFile );
				fputs( buffer, newFile );
			}
			fclose( newFile );
		}
		fclose( fileToOpen );
	}

	return 0;
}