/*
 * DDis.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Disassembler.
 * 
 * Dubbel Disassembler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Disassembler is distributed in the hope that it will be useful,
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
 
#include "DubbelDisassembler.h"
#include <fstream>
#include <cstdlib>

using namespace std;
using namespace dubbel;

void Help() {
	cout << "Usage: ddis [options] <filename>\n";
	cout << "Options:\n";
	cout << "   -help               Show this information\n";
	cout << "   -stdin              Use stdin as input file\n";
	cout << "   -stdout             Place the output in stdout\n";
	cout << "   -o <filename>       Place the output in <filename>\n\n";
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		Help();
		return EXIT_FAILURE;
	}
	String fin = "";
	String fout = "";
	Bool noOutFile = false , noInFile = false;
	for(size_t i = 1; i < argc; ++i) {
		if(String(argv[i]) == "-help") {
			Help();
			return EXIT_SUCCESS;
		}
		else if(String(argv[i]) == "-stdout")
			noOutFile = true;
		else if(String(argv[i]) == "-stdin")
			noInFile = true;
		else if(String(argv[i]) == "-o") {
			if(i == argc -1) {
				cerr << "A filename must follow the -o argument.\n";
				return EXIT_FAILURE;
			}
			fout = argv[++i];
		}
		else if(fin.size() == 0)
			fin = argv[i];
		else {
			cerr << "Invalid argument '" << argv[i] << "'\n";
			return EXIT_FAILURE;
		}
	}
	if(fin.size() == 0 && !noInFile) {
		cerr << "No input file.\n";
		return EXIT_FAILURE;
	}
	if(fout.size() == 0 && !noOutFile) {
		if(noInFile) {
			cerr << "No output file.\n";
			return EXIT_FAILURE;
		}
		if(fin.size() >= 7 && fin.substr(fin.size() -7, 7) == ".dubbel") {
			fout = fin.substr(0, fin.size() -7) + ".dasm";
		}
		else fout = fin + ".dasm";
	}
	ifstream * fr;
	if(noInFile)
		fr = (ifstream*)&cin;
	else fr = new ifstream(fin.c_str(), ifstream::in | ifstream::binary);
	String str;
	if (!fr->good()) {
		cerr << "Invalid input file";
		return 1;
	}
	getline(*fr, str);
	String read = "";
	if (str != "#!/usr/bin/env dubbel")
		read += str + "\n";
	while (fr->good())
	{
		getline(*fr, str);
		read += str + "\n";
	}
	if(!noInFile) {
		fr->close();
		delete fr;
	}
	read.erase(read.end() - 1);
	ofstream * fw;
	if(noOutFile)
		fw = (ofstream*)&cout;
	else fw = new ofstream(fout.c_str(), ofstream::out);
	*fw << FileDisassembler(read);
	if(!noOutFile) {
		fw->close();
		delete fw;
	}
	return 0;
}

