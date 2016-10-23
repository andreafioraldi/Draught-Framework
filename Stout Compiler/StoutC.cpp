/*
* StoutC.cpp
*
* Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
*
* This file is part of Stout Compiler.
*
* Stout Compiler is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* Stout Compiler is distributed in the hope that it will be useful,
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

#include "StoutCompiler.h"
#include <fstream>
#include <cstdlib>

#ifdef _WIN32
#define DIR_SEP "\\"
#else
#define DIR_SEP "/"
#endif

using namespace std;
using namespace dubbel;

#ifndef _WIN32
#include <sys/stat.h>
#endif

String basename(String path) {
	return path.substr(path.find_last_of(DIR_SEP) + 1);
}

void Help() {
	cout << "Usage: stoutc [options] <filename>...\n";
	cout << "Options:\n";
	cout << "   -help               Show this information\n";
	cout << "   -stdin              Use stdin as input file (not usable with -a)\n";
	cout << "   -stdout             Place the output in stdout\n";
	cout << "   -debug              Include debug symbols in the output\n";
	cout << "   -not-optimize       Disable compiler optimization (not recommended)\n";
	cout << "   -o <filename>       Place the output in <filename>\n";
	cout << "   -a, -archive        Compile and build a 'dea' archive\n";
	cout << "   -main               When building an archive specify the main object filename,\n                          otherwise the main is the first file passed\n";
	cout << "\n   With multiple files -a is used implicitly\n\n";
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		Help();
		return EXIT_FAILURE;
	}
	String fin = "";
	vector<String> files;
	String fout = "";
	String mainFile = "";
	Bool noOutFile = false, noInFile = false;
	Bool debug = false, optimize = true;
	Bool archiver = false;
	for (size_t i = 1; i < argc; ++i) {
		if(String(argv[i]) == "-help") {
			Help();
			return EXIT_SUCCESS;
		}
		else if (String(argv[i]) == "-stdout")
			noOutFile = true;
		else if (String(argv[i]) == "-stdin")
			noInFile = true;
		else if (String(argv[i]) == "-o") {
			if (i == argc - 1) {
				cerr << "A filename must follow the -o argument.\n";
				return EXIT_FAILURE;
			}
			fout = argv[++i];
		}
		else if (String(argv[i]) == "-debug")
			debug = true;
		else if (String(argv[i]) == "-main") {
			if (i == argc - 1) {
				cerr << "A filename must follow the -main argument.\n";
				return EXIT_FAILURE;
			}
			mainFile = argv[++i];
		}
		else if (String(argv[i]) == "-a" || String(argv[i]) == "-archive")
			archiver = true;
		else if (String(argv[i]) == "-not-optimize")
			optimize = false;
		else if (fin.size() == 0)
			fin = argv[i];
		else {
			files.push_back(argv[i]);
			archiver = true;
		}
	}
	if(archiver && noInFile) {
		cerr << "-stdin option cannot be used when building an archive.\n";
		return EXIT_FAILURE;
	}
	if (fin.size() == 0 && !noInFile) {
		cerr << "No input file.\n";
		return EXIT_FAILURE;
	}
	if(mainFile == "") {
		if (noInFile) {
			cerr << "No main file.\n";
			return EXIT_FAILURE;
		}
		mainFile = fin;
		if (fin.size() >= 6 && fin.substr(fin.size() - 6, 6) == ".stout") {
			mainFile = fin.substr(0, fin.size() - 6);
		}
	}
	String ext;
	if(archiver) ext = ".dea";
	else ext = ".dubbel";
	if (fout.size() == 0 && !noOutFile) {
		if(mainFile != "")
			fout = mainFile + ext;
		else if (noInFile) {
			cerr << "No output file.\n";
			return EXIT_FAILURE;
		}
		else if (fin.size() >= 6 && fin.substr(fin.size() - 6, 6) == ".stout") {
			fout = fin.substr(0, fin.size() - 6) + ext;
		}
		else fout = fin + ext;
	}
	if(archiver) {
		files.insert(files.begin(), fin);
		String mainName = mainFile;
		vector<String> fileNames;
		vector<String> fileContents;
		Bool mainFound = false;
		for(size_t i = 0; i < files.size(); ++i) {
			ifstream fs(files[i], ifstream::in);
			String str;
			if (!fs.good()) {
				cerr << "Invalid file " << files[i] << endl;
				return 1;
			}
			String read = "";
			while (fs.good())
			{
				getline(fs, str);
				read += str + "\n";
			}
			read.erase(read.end() - 1);
			fs.close();
			Compiler c(read, files[i]);
			c.debug = debug;
			c.optimize = optimize;
			Scope scope;
			try {
				c.Compile(&scope);
			}
			catch (CompilerErr e) {
				cerr << e.err << endl;
				return 1;
			}
			String bin = scope.builder.BuildFile();
			bin.erase(bin.begin());
			String name = basename((char*)files[i].c_str());
			if(name.size() >= 6 && name.substr(name.size() -6, 6) == ".stout")
				name = name.substr(0, name.size() -6);
			if(name == mainFile)
				mainFound = true;
			fileNames.push_back(name);
			fileContents.push_back(bin);
		}
		if(!mainFound) {
			cerr << "Wrong main file.\n";
			return EXIT_FAILURE;
		}
		ofstream * fw;
		if (noOutFile)
			fw = (ofstream*)&cout;
		else fw = new ofstream(fout.c_str(), ofstream::out | ofstream::binary);
		fw->write("#!/usr/bin/env dubar\n", 21);
		String bin = ToBytes((LSize)mainName.size());
		bin += mainName;
		for(size_t i = 0; i < fileContents.size(); ++i) {
			bin += ToBytes((LSize)fileNames[i].size());
			bin += fileNames[i];
			bin += ToBytes((LSize)fileContents[i].size());
			bin += fileContents[i];
		}
		fw->write(bin.c_str(), bin.size());
		if (!noOutFile) {
			fw->close();
			delete fw;
			#ifndef _WIN32
			chmod(fout.c_str(),S_IRWXU);
			#endif
		}
	}
	else {
		ifstream * fr;
		if (noInFile)
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
			read += str + "\n";
		}
		if (!noInFile) {
			fr->close();
			delete fr;
		}
		read.erase(read.end() - 1);
		if (noInFile)
			fin = "<stdin>";
		Compiler c(read, fin);
		c.debug = debug;
		c.optimize = optimize;
		Scope scope;
		try {
			c.Compile(&scope);
		}
		catch (CompilerErr e) {
			cerr << e.err << endl;
			return 1;
		}
		ofstream * fw;
		if (noOutFile)
			fw = (ofstream*)&cout;
		else fw = new ofstream(fout.c_str(), ofstream::out | ofstream::binary);
		String bin = scope.builder.BuildFile();
		fw->write("#!/usr/bin/env dubbel\n", 22);
		fw->write(bin.c_str(), bin.size());
		if (!noOutFile) {
			fw->close();
			delete fw;
			#ifndef _WIN32
			chmod(fout.c_str(),S_IRWXU);
			#endif
		}
	}
	return 0;
}

