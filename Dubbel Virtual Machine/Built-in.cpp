/*
 * Built-in.cpp
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
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;
using namespace dubbel;

#ifdef _WIN32
#include <windows.h>
#define DIR_SEP "\\"
#define MYDIR
#else
#include <dlfcn.h>
#define DIR_SEP "/"
#define MYDIR "./" + 
#endif

inline bool FileExist(const String & path) {
	if (FILE *file = fopen(path.c_str(), "r")) {
		fclose(file);
		return true;
	} else return false; 
}

void dubbel::LoadByteCodeLib(String path, String name) {
	ifstream fs(path.c_str(), ifstream::in | ifstream::binary);
	String str;
	if(!fs.good()) {
		throw Var("LoadByteCodeLib : Failed to load '" + path + "'");
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
	if(read[0] != BYTECODE_VER)
		throw Var("LoadByteCodeLib : Failed to load '" + path + "' , invalid bytecode version");
	read.erase(read.begin());
	Code * code = BuildCode(read , 0 , read.size());
	namespaces[name] = Object(code);
	namespaces[name].GetObject().global = &namespaces[name];
	namespaces[name].Call(Var(Array())).Clear();
}

void dubbel::LoadNativeLib(String path, String name) {
#ifdef _WIN32
	HMODULE handle;
	handle = LoadLibraryA(path.c_str());
	if (handle == NULL) {
		stringstream ss;
		ss << GetLastError();
		throw Var("LoadNativeLib loading : Windows system error code " + ss.str());
	}
	GetLastError();
	FARPROC f;
	f =  GetProcAddress(handle, "__li");
	if (f == NULL) {
		stringstream ss;
		ss << GetLastError();
		throw Var("LoadNativeLib initializing : Windows system error code " + ss.str());
	}
	GetLastError();
#else
	void * handle;
	handle = dlopen (path.c_str(), RTLD_LAZY);
	if (!handle) {
		throw Var("LoadNativeLib loading : " + String(dlerror()));
	}
	dlerror();
	char * error;
	void * f;
	f = dlsym(handle, "__li");
	if ((error = (char *)dlerror()) != NULL) {
		throw Var("LoadNativeLib initializing : " + String(dlerror()));
	}
#endif
	namespaces[name] = Object();
	namespaces[name].GetObject().global = &namespaces[name];
	((void (*)(Var))f)(namespaces[name]);
}

void dubbel::LoadLib(String lib) {
	LoadLib(lib, lib);
}

void dubbel::LoadLib(String lib, String name) {
	if(FileExist(lib + ".dubbel")) {
		LoadByteCodeLib(MYDIR lib + ".dubbel", name);
		return;
	}
	else if(FileExist(lib + ".dubsl")) {
		LoadNativeLib(MYDIR lib + ".dubsl", name);
		return;
	}
	char * cpath = getenv("DUBBEL_LIBPATH");
	if(cpath) {
		String path(cpath);
		if(FileExist(path + DIR_SEP + lib + ".dubbel")) {
			LoadByteCodeLib(path + DIR_SEP + lib + ".dubbel", name);
			return;
		}
		else if(FileExist(path + DIR_SEP + lib + ".dubsl")) {
			LoadNativeLib(path + DIR_SEP + lib + ".dubsl", name);
			return;
		}
	}
	throw Var("LoadLib : library '" + lib + "' not found");
}


void dubbel::Exit(int status) {
	Bool bc = mainObj.GetObject().IsByteCode();
	Code * code;
	if(bc) code = static_cast<Code*>(mainObj.GetObject().content);
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
	if(bc) {
		code->ClearPtr();
		delete code;
	}
	if(status == 0)
		exit(EXIT_SUCCESS);
	else exit(EXIT_FAILURE);
}

#ifdef _WIN32
Native dubbel::External(String lib , String name) {
	HMODULE handle;
	handle = LoadLibraryA(lib.c_str());
	if (handle == NULL) {
		stringstream ss;
		ss << GetLastError();
		throw Var("LoadExternal Error : Windows system error code " + ss.str());
	}
	GetLastError();
	FARPROC f;
	f =  GetProcAddress(handle, name.c_str());
	if (f == NULL) {
		stringstream ss;
		ss << GetLastError();
		throw Var("LoadExternal Error : Windows system error code " + ss.str());
	}
	GetLastError();
	return (Native)f;
}
#else
Native dubbel::External(String lib , String name) {
	void *handle;
	handle = dlopen (lib.c_str(), RTLD_LAZY);
	if (!handle) {
		throw Var("LoadExternal Error : " + String(dlerror()));
	}
	dlerror();
	char * error;
	Native f;
	f = (Native)dlsym(handle , name.c_str());
	if ((error = (char *)dlerror()) != NULL) {
		throw Var("LoadExternal Error : " + String(dlerror()));
	}
	return f;
}
#endif

Char dubbel::TypeOf(Var v) {
	return (Char)v.Type();
}

Int dubbel::IdOf(Var v) {
	if(v.Type() == TypeId::Object)
		return Int((unsigned long)v.GetObject().content) * 10 + (int)v.GetObject().flags;
	else return (int)v.Type();
}

Int dubbel::AddressOf(Var v) {
	return (unsigned long)v.val;
}

String dubbel::TypeStr(Var v) {
	if(v.Type() == TypeId::None)
		return "none";
	else if(v.Type() == TypeId::Char)
		return "char";
	else if(v.Type() == TypeId::Int)
		return "int";
	else if(v.Type() == TypeId::Float)
		return "float";
	else if(v.Type() == TypeId::Bool)
		return "bool";
	else if(v.Type() == TypeId::String)
		return "string";
	else if(v.Type() == TypeId::Array)
		return "array";
	else if(v.Type() == TypeId::Object)
		return "object";
}

Var dubbel::Move(Var v) {
	Var n;
	if(v.val == nullptr)
		return n;
	n.val = new Var::Value();
	n.val->ptr = v.val->ptr;
	n.val->type = v.Type();
	v.val->ptr = nullptr;
	v.val->type = TypeId::None;
	return n;
}

void dubbel::Swap(Var a , Var b) {
	if(a.val == nullptr)
		a.val = new Var::Value();
	if(b.val == nullptr)
		b.val = new Var::Value();
	Var::Container * p = a.val->ptr;
	TypeId t = a.Type();
	a.val->ptr = b.val->ptr;
	a.val->type = b.Type();
	b.val->ptr = p;
	b.val->type = t;
}

