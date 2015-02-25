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
#include <vector>

#include "functions.h"

#define MIN_NUMBERS_OF_ARGUMENTS 4
#define LOCALHOST "127.0.0.1"

using namespace std;

int main( int argc, char *argv[] ) {

	if ( argc < MIN_NUMBERS_OF_ARGUMENTS ) {
		cout << "Not enough parameters\n" << endl;
	} else if ( argc >= MIN_NUMBERS_OF_ARGUMENTS ) {
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