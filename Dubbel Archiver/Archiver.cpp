/*
 * Archiver.cpp
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
#ifndef _WIN32
#include <sys/stat.h>
#endif

#ifdef _WIN32
#define DIR_SEP "\\"
#else
#define DIR_SEP "/"
#endif

using namespace std;
using namespace dubbel;

String basename(String path) {
	return path.substr(path.find_last_of(DIR_SEP) + 1);
}

void Help() {
	cout << "Usage: dubar [options] <filename>...\n";
	cout << "Options:\n";
	cout << "   -help               Show this information\n";
	cout << "   -b, -build          Create an archive from a list of files\n";
	cout << "   -main               When building an archive specify the main object filename,\n                          otherwise the main is the first file passed\n";
	cout << "   -stdout             Use stdout as build output file (usable only with -b)\n";
	cout << "   -o <filename>       Use <filename> as build output file (usable only with -b)\n";
	cout << "   -x, -exec           Execute the archive\n";
	cout << "   -e, -extract <dir>  Extract the archive in <dir>\n";
	cout << "   -l, -list           List the archive's content\n";
	cout << "   -stdin              Use stdin as input file (not usable with -b)\n";
	cout << "\n   Without options -x is used implicitly\n\n";
}

int build(vector<String> files, String mainFile, ofstream * fw) {
	Archive arc;
	arc.mainName = mainFile;
	String str;
	for(vector<String>::iterator it = files.begin(); it != files.end(); ++it) {
		ifstream fs(*it, ifstream::in | ifstream::binary);
		if (!fs.good()) {
			cerr << "Invalid file " << *it << endl;
			continue;
		}
		getline(fs, str);
		String read = "";
		if (str != "#!/usr/bin/env dubbel")
			read += str + "\n";
		while (fs.good())
		{
			getline(fs, str);
			read += str + "\n";
		}
		read.erase(read.end() - 1);
		read.erase(read.begin());
		String name = basename(*it);
		if(name.size() >= 7 && name.substr(name.size() -7, 7) == ".dubbel") {
			name = name.substr(0, name.size() -7);
		}
		arc.fileNames.push_back(name);
		arc.fileContents.push_back(read);
	}
	if(!fw->good()) {
		cerr << "Cannot create the archive.\n";
		return EXIT_FAILURE;
	}
	fw->write("#!/usr/bin/env dubar\n", 21);
	String bin = arc.Build();
	fw->write(bin.c_str(), bin.size());
	return EXIT_SUCCESS;
}

int exec(ifstream * fs, int argc, char ** argv) {
	String str;
	if (!fs->good()) {
		cerr << "Invalid file\n";
		return EXIT_FAILURE;
	}
	getline(*fs, str);
	String read = "";
	if (str != "#!/usr/bin/env dubar")
		read += str + "\n";
	while (fs->good())
	{
		getline(*fs, str);
		read += str + "\n";
	}
	read.erase(read.end() - 1);
	Archive arc(read);
	return RunMain(arc, argc, argv);
}

int extract(ifstream * fs, String dir) {
	String str;
	if (!fs->good()) {
		cerr << "Invalid file\n";
		return EXIT_FAILURE;
	}
	getline(*fs, str);
	String read = "";
	if (str != "#!/usr/bin/env dubar")
		read += str + "\n";
	while (fs->good())
	{
		getline(*fs, str);
		read += str + "\n";
	}
	read.erase(read.end() - 1);
	Archive arc(read);
	for(size_t i = 0; i < arc.fileNames.size(); ++i) {
		ofstream fw(dir + DIR_SEP + arc.fileNames[i], ofstream::out);
		if(!fw.good())
			cerr << "Cannot extract " << arc.fileNames[i] << " in " << dir << ".\n";
		fw.write("#!/usr/bin/env dubbel\n", 22);
		String bin = "";
		bin += (char)BYTECODE_VER;
		bin += arc.fileContents[i];
		fw.write(bin.c_str(), bin.size());
		fw.close();
		#ifndef _WIN32
		chmod((dir + DIR_SEP + arc.fileNames[i]).c_str(), S_IRWXU);
		#endif
	}
	return EXIT_SUCCESS;
}

int list(ifstream * fs) {
	String str;
	if (!fs->good()) {
		cerr << "Invalid file\n";
		return EXIT_FAILURE;
	}
	getline(*fs, str);
	String read = "";
	if (str != "#!/usr/bin/env dubar")
		read += str + "\n";
	while (fs->good())
	{
		getline(*fs, str);
		read += str + "\n";
	}
	read.erase(read.end() - 1);
	Archive arc(read);
	cout << "Main : " << arc.mainName << endl;
	for(size_t i = 0; i < arc.fileNames.size(); ++i)
		cout << i << ")  " << arc.fileNames[i] << endl;
	return EXIT_SUCCESS;
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
	if (argc < 3) {
		String arg1 = argv[1];
		ifstream * fs;
		if(arg1 == "-stdin")
			fs = (ifstream*)&cin;
		else fs = new ifstream(argv[1], ifstream::in | ifstream::binary);
		int r = exec(fs, argc, argv);
		if(arg1 != "-stdin")
			delete fs;
		return r;
	}
	if(arg == "-b" || arg == "-build") {
		vector<String> files;
		String mainFile = "";
		String fout = "";
		Bool noOutFile = false;
		for (size_t i = 2; i < argc; ++i) {
			if (String(argv[i]) == "-main") {
				if (i == argc - 1) {
					cerr << "A filename must follow the -main argument.\n";
					return EXIT_FAILURE;
				}
				mainFile = argv[++i];
			}
			else if (String(argv[i]) == "-stdout")
				noOutFile = true;
			else if (String(argv[i]) == "-o") {
			if (i == argc - 1) {
					cerr << "A filename must follow the -o argument.\n";
					return EXIT_FAILURE;
				}
				fout = argv[++i];
			}
			else files.push_back(argv[i]);
		}
		if(files.size() == 0) {
			cerr << "No input files.\n";
			return EXIT_FAILURE;
		}
		if(mainFile == "") {
			mainFile = files[0];
			if(mainFile.size() >= 7 && mainFile.substr(mainFile.size() -7, 7) == ".dubbel") {
				mainFile = mainFile.substr(0, mainFile.size() -7);
			}
		}
		if(fout.size() == 0 && !noOutFile) {
			if(mainFile.size() >= 7 && mainFile.substr(mainFile.size() -7, 7) == ".dubbel") {
				fout = mainFile.substr(0, mainFile.size() -7) + ".dea";
			}
			else fout = mainFile + ".dea";
		}
		ofstream * fw;
		if(noOutFile)
			fw = (ofstream*)&cout;
		else fw = new ofstream(fout.c_str(), ofstream::out);
		int r = build(files, mainFile, fw);
		if(!noOutFile) {
			fw->close();
			delete fw;
			#ifndef _WIN32
			chmod(fout.c_str(),S_IRWXU);
			#endif
		}
		return r;
	}
	else if(arg == "-x" || arg == "-exec") {
		String arg1 = argv[2];
		ifstream * fs;
		if(arg1 == "-stdin")
			fs = (ifstream*)&cin;
		else fs = new ifstream(argv[2], ifstream::in | ifstream::binary);
		int r = exec(fs, argc-1, argv+1);
		if(arg1 != "-stdin") {
			fs->close();
			delete fs;
		}
		return r;
	}
	else if(arg == "-l" || arg == "-list") {
		String arg1 = argv[2];
		ifstream * fs;
		if(arg1 == "-stdin")
			fs = (ifstream*)&cin;
		else fs = new ifstream(argv[2], ifstream::in | ifstream::binary);
		int r = list(fs);
		if(arg1 != "-stdin") {
			fs->close();
			delete fs;
		}
		return r;
	}
	
	if (argc < 4) {
		Help();
		return EXIT_FAILURE;
	}
	if(arg == "-e" || arg == "-extract") {
		String arg1 = argv[2];
		String arg2 = argv[3];
		ifstream * fs;
		if(arg2 == "-stdin")
			fs = (ifstream*)&cin;
		else fs = new ifstream(argv[3], ifstream::in | ifstream::binary);
		int r = extract(fs, arg1);
		if(arg1 != "-stdin") {
			fs->close();
			delete fs;
		}
		return r;
	}
	Help();
	return EXIT_FAILURE;
}


