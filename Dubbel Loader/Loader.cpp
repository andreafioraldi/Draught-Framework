/*
 * Loader.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Loader.
 * 
 * Dubbel Loader is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Loader is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#include "Dubbel.h"
#include <fstream>

using namespace std;
using namespace dubbel;

void Help() {
	cout << "Usage: dubbel parameter\n";
	cout << "Parameters:\n";
	cout << "   -help               Show this information\n";
	cout << "   -stdin              Use stdin as input file\n";
	cout << "   <filename>          Use read <filename> as input\n\n";
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		Help();
		return EXIT_FAILURE;
	}
	String arg(argv[1]);
	ifstream * fs;
	if(arg == "-help") {
		Help();
		return EXIT_SUCCESS;
	}
	else if(arg == "-stdin")
		fs = (ifstream*)&cin;
	else fs = new ifstream(argv[1], ifstream::in | ifstream::binary);
	String str;
	if (!fs->good()) {
		cerr << "Invalid file\n";
		return 1;
	}
	getline(*fs, str);
	String read = "";
	if (str != "#!/usr/bin/env dubbel")
		read += str + "\n";
	while (fs->good())
	{
		getline(*fs, str);
		read += str + "\n";
	}
	read.erase(read.end() - 1);
	read.erase(read.begin());
	if(arg != "-stdin")
		delete fs;
	
	return RunMain(read, argc, argv);
}


