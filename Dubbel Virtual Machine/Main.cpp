/*
 * Main.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Virtual Machine.
 * 
 * Dubbel Virtual Machine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Virtual Machine is distributed in the hope that it will be useful,
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

using namespace std;
using namespace dubbel;

namespace dubbel {
	map<String , Var> namespaces;
	Var mainObj;
	String debugInfo;
	char ** cmdArgs;
	int cmdArgsLen;
}

int dubbel::RunMain(const String & s, int argc , char ** argv) {
	cmdArgs = argv;
	cmdArgsLen = argc;
	Code * code = BuildCode(s, 0, s.size());
	mainObj = Var(Object(code), &mainObj);
	Array args;
	for(int i = 1; i < argc; ++i)
		args.push_back(Var(String(argv[i])));
	Var r;
	try {
		r = mainObj.Call(Var(args));
	}
	catch (Var err) {
		cerr << "VM Error : An exception has occurred\n";
		cerr << debugInfo << err.ToString() << endl;
		err.Clear();
		mainObj.Clear();
		for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it)
			it->second.Clear();
		namespaces.clear();
		code->ClearPtr();
		delete code;
		return 1;
	}
	int status = 0;
	if(r.Type() == TypeId::Int)
		status = r.GetInt().get_si();
	r.Clear();
	mainObj.Clear();
	for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it) {
		Bool bc = it->second.GetObject().IsByteCode();
		Code * c;
		if(bc) c = static_cast<Code*>(it->second.GetObject().content);
		it->second.Clear();
		if(bc) {
			c->ClearPtr();
			delete c;
		}
	}
	namespaces.clear();
	code->ClearPtr();
	delete code;
	return status;
}

int dubbel::RunMain(const Archive & a, int argc , char ** argv) {
	cmdArgs = argv;
	cmdArgsLen = argc;
	Code * code;
	Bool mainFound = false;
	for(size_t i = 0; i < a.fileNames.size(); ++i) {
		if(a.fileNames[i] == a.mainName) {
			mainFound = true;
			code = BuildCode(a.fileContents[i], 0, a.fileContents[i].size());
			mainObj = Var(Object(code), &mainObj);
		}
		else {
			Code * c = BuildCode(a.fileContents[i] , 0 , a.fileContents[i].size());
			namespaces[a.fileNames[i]] = Object(c);
			namespaces[a.fileNames[i]].GetObject().global = &namespaces[a.fileNames[i]];
		}
	}
	for(size_t i = 0; i < a.fileNames.size(); ++i) {
		if(a.fileNames[i] != a.mainName) {
			try {
				namespaces[a.fileNames[i]].Call(Var(Array())).Clear();
			}
			catch (Var err) {
				cerr << "VM Error : An exception has occurred\n";
				cerr << debugInfo << err.ToString() << endl;
				err.Clear();
				mainObj.Clear();
				for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it)
					it->second.Clear();
				namespaces.clear();
				code->ClearPtr();
				delete code;
				return 1;
			}
		}
	}
	Array args;
	for(int i = 1; i < argc; ++i)
		args.push_back(Var(String(argv[i])));
	Var r;
	try {
		r = mainObj.Call(Var(args));
	}
	catch (Var err) {
		cerr << "VM Error : An exception has occurred\n";
		cerr << debugInfo << err.ToString() << endl;
		err.Clear();
		mainObj.Clear();
		for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it)
			it->second.Clear();
		namespaces.clear();
		code->ClearPtr();
		delete code;
		return 1;
	}
	int status = 0;
	if(r.Type() == TypeId::Int)
		status = r.GetInt().get_si();
	r.Clear();
	mainObj.Clear();
	for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it) {
		Bool bc = it->second.GetObject().IsByteCode();
		Code * c;
		if(bc) c = static_cast<Code*>(it->second.GetObject().content);
		it->second.Clear();
		if(bc) {
			c->ClearPtr();
			delete c;
		}
	}
	namespaces.clear();
	code->ClearPtr();
	delete code;
	return status;
}


int dubbel::RunMain(Native pt, int argc , char ** argv) {
	cmdArgs = argv;
	cmdArgsLen = argc;
	mainObj = Object(pt, &mainObj);
	Array args;
	for(int i = 1; i < argc; ++i)
		args.push_back(Var(String(argv[i])));
	Var r;
	try {
		r = mainObj.Call(Var(args));
	}
	catch (Var err) {
		cerr << "VM Error : An exception has occurred\n";
		cerr << debugInfo << err.ToString() << endl;
		err.Clear();
		mainObj.Clear();
		for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it)
			it->second.Clear();
		namespaces.clear();
		return 1;
	}
	int status = 0;
	if(r.Type() == TypeId::Int)
		status = r.GetInt().get_si();
	r.Clear();
	mainObj.Clear();
	for(map<String , Var>::reverse_iterator it = namespaces.rbegin(); it!= namespaces.rend(); ++it) {
		Bool bc = it->second.GetObject().IsByteCode();
		Code * c;
		if(bc) c = static_cast<Code*>(it->second.GetObject().content);
		it->second.Clear();
		if(bc) {
			c->ClearPtr();
			delete c;
		}
	}
	namespaces.clear();
	return status;
}


