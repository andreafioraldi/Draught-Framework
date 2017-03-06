/*
* Stout.cpp
*
* Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
*
* This file is part of Stout Loader.
*
* Stout Loader is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* Stout Loader is distributed in the hope that it will be useful,
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
#include "Dubbel.h"
#include <cstdlib>
#include <fstream>
#include <cstdint>

#ifdef __APPLE__
#include "TargetConditionals.h"
#endif

using namespace std;
using namespace dubbel;

void Help() {
	cout << "Usage: stout [options] <filename>\n";
	cout << "Options:\n";
	cout << "   -help               Show this information\n";
	cout << "   -dx                 Execute a Dubbel bytecode file\n";
	cout << "   -sx                 Compile in memory and execute a Stout source file\n";
	cout << "   -ax                 Execute a Dubbel executable archive\n";
	cout << "   -shell              Start the Stout shell\n";
	cout << "   -x                  Execute a file catching type from extension\n";
	cout << "\n   Without options -x is used implicitly\n";
	cout << "   Without options and filename -shell is used implicitly\n\n";
}

void stoutShell(int argc, char ** argv) {
	cout << "StoutShell [v1.0alpha";
#if UINTPTR_MAX == 0xffffffff
	cout << " 32 bit";
#elif UINTPTR_MAX == 0xffffffffffffffff
	cout << " 64 bit";
#endif
	cout << "]";
#if defined _WIN32
	cout << " on Windows";
#elif defined __ANDROID__
	cout << " on Android";
#elif defined __linux__
	#ifdef __GNUC__
		cout << " on GNU/Linux";
	#else
		cout << " on Linux";
	#endif
#elif defined __APPLE__
	#if TARGET_OS_IPHONE
        	cout << " on iOS";
	#elif TARGET_OS_MAC
        		cout << " on Mac OS";
	#else
		cout << " on Darwin";
	#endif
#elif defined __sun__
	cout << " on Solaris";
#elif defined BSD
	#ifdef __FreeBSD__
		cout << " on FreeBSD";
	#else
		cout << " on BSD";
	#endif
	cout << " on FreeBSD";
#elif defined __unix__
	#ifdef __GNUC__
		cout << " on GNU";
	#else
		cout << " on Unix";
	#endif
#endif
	cout << "\n(c) 2016 Andrea Fioraldi\n\n";
	cmdArgs = argv;
	cmdArgsLen = argc;
	vector<string> names;
	Scope scope;
	Var args = Array{ Var(String(argv[0])) };
	mainObj = Object();
	Array locals;
	vector<Cell> stack;
	Code code;
	String cmd;
	
	while(true) {
		cout << "stout> ";
		getline(cin, cmd);
		if (cmd.size() == 0)
			continue;
		while(isspace(cmd[cmd.size() -1]))
			cmd.erase(cmd.end() - 1);
		if(cmd.size() == 0)
			continue;
		if(cmd[cmd.size() -1] == '{') {
			string last = " ";
			while(last.size() > 0) {
				getline(cin, last);
				cmd += last + "\n";
			}
		}
		if(cmd[cmd.size() -1] != ';')
			cmd += ";";
		Compiler comp(cmd, "<shell>");
		comp.debug = true;
		comp.namespaces = names;
		try {
			comp.Compile(&scope);
		}
		catch(CompilerErr e) {
			cerr << e.err << endl;
			scope.consts.clear();
			scope.labels.clear();
			names = comp.namespaces;
			scope.builder.body.Clear();
			scope.builder.constPool.Clear();
			continue;
		}
		scope.consts.clear();
		scope.labels.clear();
		names = comp.namespaces;
		String built = scope.builder.BuildFile();
		built.erase(built.begin());
		scope.builder.body.Clear();
		scope.builder.constPool.Clear();
		try {
			Code * c = BuildCode(built, 0, built.size());
			code.bin = c->bin;
			code.consts = c->consts;
			code.codes.insert(code.codes.end(), c->codes.begin(), c->codes.end());
			code.localsSize += c->localsSize;
			while(locals.size() < code.localsSize)
				locals.push_back(Var());
			Var returned;
			ExecCode(&code, &mainObj, args, returned, locals, stack);
			returned.Clear();
		}
		catch(Var err) {
			cerr << "VM Error : An exception has occurred\n";
			cerr << debugInfo << err.ToString() << endl;
			debugInfo = "";
		}
	}
}


int execStout(int argc, char ** argv) {
	String line;
	ifstream fr;
	fr.open(argv[1], ifstream::in);
	String lines;
	while (getline(fr,line,'\n')) {
		if (line.size() > 0 && line[line.size()-1] == '\r' ) {
			line.erase(line.end()-1);
		}
		lines += line + "\n";
	}
	Compiler c(lines);
	c.debug = true;
	c.fileName = argv[1];
	Scope scope;
	try {
		c.Compile(&scope);
	}
	catch(CompilerErr e) {
		cerr << e.err << endl;
		return 1;
	}
	String built = scope.builder.BuildFile();
	built.erase(built.begin());
	return RunMain(built, argc, argv);
}

int execDubbel(int argc, char ** argv) {
	ifstream fs(argv[1], ifstream::in | ifstream::binary);
	String str;
	if(!fs.good()) {
		cerr<< "Invalid file\n";
		return 1;
	}
	getline(fs, str);
	String read = "";
	if(str != "#!/usr/bin/env dubbel")
		read += str + "\n";
	while(fs.good())
	{
		getline(fs, str);
		read += str + "\n";
	}
	read.erase(read.end() -1);
	read.erase(read.begin());
	
	return RunMain(read, argc, argv);
}

int execArchive(int argc, char ** argv) {
	ifstream fs(argv[1], ifstream::in | ifstream::binary);
	String str;
	if (!fs.good()) {
		cerr << "Invalid file\n";
		return EXIT_FAILURE;
	}
	getline(fs, str);
	String read = "";
	if (str != "#!/usr/bin/env dubar")
		read += str + "\n";
	while (fs.good())
	{
		getline(fs, str);
		read += str + "\n";
	}
	read.erase(read.end() - 1);
	Archive arc(read);
	return RunMain(arc, argc, argv);
}


int main(int argc, char ** argv) {
	if(argc < 2)
		stoutShell(argc, argv);
	else {
		String n = argv[1];
		if(n == "-help") {
			Help();
			return EXIT_SUCCESS;
		}
		else if(n == "-shell")
			stoutShell(argc, argv);
		if(argc > 2) {
			if(n == "-dx")
				return execDubbel(argc-1, argv+1);
			else if(n == "-sx")
				return execStout(argc-1, argv+1);
			else if(n == "-ax")
				return execArchive(argc-1, argv+1);
			else if(n == "-x") {
				String f = argv[2];
				if(f.size() > 6 && f.substr(f.size()-6,6) == ".stout")
					return execStout(argc-1, argv+1);
				else if(f.size() > 7 && f.substr(f.size()-7,7) == ".dubbel")
					return execDubbel(argc-1, argv+1);
				else if(f.size() > 4 && f.substr(f.size()-4,4) == ".dea")
					return execArchive(argc-1, argv+1);
				cerr << "Invalid file extension\n";
				return EXIT_FAILURE;
			}
		}
		if(n.size() > 6 && n.substr(n.size()-6,6) == ".stout")
			return execStout(argc, argv);
		else if(n.size() > 7 && n.substr(n.size()-7,7) == ".dubbel")
			return execDubbel(argc, argv);
		else if(n.size() > 4 && n.substr(n.size()-4,4) == ".dea")
			return execArchive(argc, argv);
		cerr << "Invalid file extension\n";
		return EXIT_FAILURE;
	
	}
}



