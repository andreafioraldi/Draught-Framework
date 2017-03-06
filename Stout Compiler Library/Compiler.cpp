/*
* Compiler.cpp
*
* Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
*
* This file is part of Stout Compiler Library.
*
* Stout Compiler Library is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* Stout Compiler Library is distributed in the hope that it will be useful,
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

#include "Parser.h"
#include <algorithm>
#include <sstream>

string sizeToS(size_t i) {
	stringstream convert;
	convert << i;
	return convert.str();
}

Float ParseFloat(String s) {
	String num , prec;
	bool np = true;
	for(size_t i = 0; i < s.size(); ++i) {
		if(s[i] == 'p')
			np = false;
		else if(np)
			num += s[i];
		else prec += s[i];
	}
	return Float(num, Int(prec).get_ui());
}

Char ParseChar(String s) {
	s.erase(s.begin());
	s.erase(s.end() -1);
	if(s.size() > 1) {
		if(s[0] == '\\' && s[1] == '\\');
		else if(s[0] == '\\' && s[1] == '\"') s[0] = '\"';
		else if(s[0] == '\\' && s[1] == '\'') s[0] = '\'';
		else if(s[0] == '\\' && s[1] == 'n') s[0] = '\n';
		else if(s[0] == '\\' && s[1] == 't') s[0] = '\t';
		else if(s[0] == '\\' && s[1] == 'b') s[0] = '\b';
		else if(s[0] == '\\' && s[1] == 'r') s[0] = '\r';
		else if(s[0] == '\\' && s[1] == 'v') s[0] = '\v';
		else if(s[0] == '\\' && s[1] == 'd') s[0] = (Char)Int(s.substr(2, s.size() -2)).get_ui();
		else if(s[0] == '\\' && s[1] == 'x') s[0] = (Char)Int("0" + s.substr(1, s.size() -1)).get_ui();
		else if(s[0] == '\\' && s[1] >= '0' && s[1] <= '9') s[0] = (Char)Int("0" + s.substr(1, s.size() -1)).get_ui();
	}
	return s[0];
}

String inStr(String & s, size_t pos, size_t len) {
	String out = "";
	for (size_t i = 0; pos < s.size() && i < len; ++i) {
		out += s[pos];
		s.erase(s.begin() + pos);
	}
	return out;
}

String ParseString(String s) {
	s.erase(s.begin());
	s.erase(s.end() - 1);
	if (s.size() == 0)
		return "";
	for (size_t i = 0; i < s.size() - 1; ++i) {
		if (s[i] == '\\' && s[i+1] == '\\');
		else if (s[i] == '\\' && s[i+1] == '\"') s[i] = '\"';
		else if (s[i] == '\\' && s[i+1] == '\'') s[i] = '\'';
		else if (s[i] == '\\' && s[i+1] == 'n') s[i] = '\n';
		else if (s[i] == '\\' && s[i+1] == 't') s[i] = '\t';
		else if (s[i] == '\\' && s[i+1] == 'b') s[i] = '\b';
		else if (s[i] == '\\' && s[i+1] == 'r') s[i] = '\r';
		else if (s[i] == '\\' && s[i+1] == 'v') s[i] = '\v';
		else if (s[i] == '\\' && s[i+1] == 'd') s[i] = (Char)Int(inStr(s, i+2, 3)).get_ui();
		else if (s[i] == '\\' && s[i+1] == 'x') s[i] = (Char)Int("0x" + inStr(s, i+2, 2)).get_ui();
		else if (s[i] == '\\' && s[i+1] >= '0' && s[i+1] <= '9') {
			s[i] = (Char)Int("0" + inStr(s, i + 1, 2)).get_ui();
			continue;
		}
		else continue;
		s.erase(s.begin() + i+1);
	}
	return s;
}


CompilerErr::CompilerErr(String file, size_t l, String e) {
	err = "Error: " + file + ": " + sizeToS(l) + ": " + e;
}

CompilerErr::CompilerErr(String file, String l, String e) {
	err = "Error: " + file + ": " + l + ": " + e;
}

void Scope::SolveLabels() {
	for (size_t i = 0; i < builder.body.Len(); ++i) {
		if (builder.body[i].opcode == NO_OP && builder.body[i].args.size() > 0 && builder.body[i].args[0] == "GOTO") {
			if(labels.find(builder.body[i].args[1]) == labels.end())
				throw CompilerErr(builder.body[i].args[2], builder.body[i].args[3], "label check error, '" + builder.body[i].args[1] + "' is not present in this scope");
			size_t spos = builder.body.Size(i);
			if (spos > labels[builder.body[i].args[1]])
				builder.body[i] = Instr(OPC_JUMP_BACK, (LSize)(spos - labels[builder.body[i].args[1]]));
			else builder.body[i] = Instr(OPC_JUMP, (LSize)(labels[builder.body[i].args[1]] - spos -3));
		}

	}
}

int Scope::FindMembers(string s) {
	vector<string>::iterator it = find(members.begin(), members.end(), s);
	if(it == members.end())
		return -1;
	return (int)(it - members.begin());
}

int Scope::FindLocals(string s) {
	vector<string>::iterator it = find(locals.begin(), locals.end(), s);
	if(it == locals.end())
		return -1;
	return (int)(it - locals.begin());
}

int Scope::FindConsts(string s) {
	vector<string>::iterator it = find(consts.begin(), consts.end(), s);
	if(it == consts.end())
		return -1;
	return (int)(it - consts.begin());
}

Compiler::Compiler() {
	init();
}

Compiler::Compiler(string i , string file) {
	fileName = file;
	input = i;
	init();
}

Compiler::~Compiler() {
	free();
	if(tree != nullptr) {
		tree->Destroy();
		delete tree;
	}
}

int Compiler::FindNamespaces(string s) {
	vector<string>::iterator it = find(namespaces.begin(), namespaces.end(), s);
	if(it == namespaces.end())
		return -1;
	return (int)(it - namespaces.begin());
}

int Compiler::NextChar() {
	if(pos == input.size())
		return -1;
	return input[pos++];
}

void Compiler::Reset() {
	pos = 0;
}

void Compiler::SetInput(string i) {
	pos = 0;
	input = i;
}

void Compiler::Parse() {
	yyparse(this);
}

String Compiler::Compile() {
	Scope s;
	return Compile(&s);
}

String Compiler::Compile(Scope * scope) {
	if(tree == nullptr)
		Parse();
	tree->ToByteCode(this, scope);
	scope->SolveLabels();
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_STACK_POP)
		scope->builder.body.Pop(scope->builder.body.Len() -1);
	return scope->builder.BuildFile();
}







	
	
