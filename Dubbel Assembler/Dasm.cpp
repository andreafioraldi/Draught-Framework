/*
 * Dasm.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Assembler.
 * 
 * Dubbel Assembler is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Assembler is distributed in the hope that it will be useful,
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

#include "DubbelAssembler.h"
#include <string>
#include <fstream>

using namespace std;
using namespace dubbel;

#ifndef _WIN32
#include <sys/stat.h>
#endif

void Help() {
	cout << "Usage: dasm [options] <filename>\n";
	cout << "Options:\n";
	cout << "   -help               Show this information\n";
	cout << "   -stdin              Use stdin as input file\n";
	cout << "   -stdout             Place the output in stdout\n";
	cout << "   -o <filename>       Place the output in <filename>\n\n";
}

int main(int argc , char ** argv) {
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
		if(fin.size() >= 5 && fin.substr(fin.size() -5, 5) == ".dasm") {
			fout = fin.substr(0, fin.size() -5) + ".dubbel";
		}
		else fout = fin + ".dubbel";
	}
	ifstream * fr;
	if(noInFile)
		fr = (ifstream*)&cin;
	else fr = new ifstream(fin.c_str(), ifstream::in);
	String str;
	if (!fr->good()) {
		cerr << "Invalid input file\n";
		return 1;
	}
	String read = "";
	while (fr->good())
	{
		getline(*fr, str);
		if (str.size() > 0 && str[str.size()-1] == '\r' )
			str.erase(str.end()-1);
		read += str + "\n";
	}
	if(!noInFile) {
		fr->close();
		delete fr;
	}
	Assembler as;
	try {
		as.Compile(read);
	}
	catch(AssemblerErr e) {
		cerr << e.err << endl;
		return 1;
	}
	ofstream * fw;
	if(noOutFile)
		fw = (ofstream*)&cout;
	else fw = new ofstream(fout.c_str(), ofstream::binary | ofstream::out);
	*fw << "#!/usr/bin/env dubbel\n";
	*fw << as.GetBytecode();
	if(!noOutFile) {
		fw->close();
		delete fw;
		#ifndef _WIN32
		chmod(fout.c_str(),S_IRWXU);
		#endif
	}
	return 0;
}


