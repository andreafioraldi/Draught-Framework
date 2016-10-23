/*
 * Builder.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Builder.
 * 
 * Dubbel Builder is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Builder is distributed in the hope that it will be useful,
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
 
 #include "DubbelBuilder.h"

using namespace std;
using namespace dubbel;

String dubbel::ToBytes(SSize t) {
	String b = "";
	b += (t >> 8) & 0xFF;
	b += t & 0xFF;
	return b;
}

String dubbel::ToBytes(LSize t) {
	String b = "";
	b += (t >> 24) & 0xFF;
	b += (t >> 16) & 0xFF;
	b += (t >> 8) & 0xFF;
	b += t & 0xFF;
	return b;
}

String dubbel::ToBytes(Char t) {
	String b = "";
	b += t;
	return b;
}

String dubbel::ToBytes(Int t) {
	String b = "";
	b += t < 0; //add the sign of the integer
	size_t c;
	void * raw = mpz_export(NULL, &c, 1, 1, -1, 0, t.get_mpz_t());
	b += ToBytes(static_cast<LSize>(c)); //add the size of the exported integer
	b += String((char *)raw, c);
#ifndef WIN32 //solve a strange memory error on windows
	free(raw);
#endif
	return b;
}
	
String dubbel::ToBytes(Float t) {
	String b = "";
	mpz_t i;
	size_t size;
	b += ToBytes(static_cast<LSize>(t.get_mpf_t()->_mp_exp)); //add the exponent of the float
	b += ToBytes(static_cast<LSize>(t.get_prec())); //add the precision of the integer
	size = t.get_mpf_t()->_mp_size;
	//create an integer with the content of the float
	i->_mp_alloc = size; 
	i->_mp_size = size; 
	i->_mp_d = t.get_mpf_t()->_mp_d;
	b += t < 0; //add the sign of the float
	size_t c;
	void * raw = mpz_export(NULL, &c, 1, 1, -1, 0, i);
	b += ToBytes(static_cast<LSize>(c)); //add the size of the exported integer
	b += String((char *)raw, c);
#ifndef WIN32 //solve a strange memory error on windows
	free(raw);
#endif
	return b;
}	

String dubbel::F64ToBytes(Float t) {
	String b = "";
	mpz_t i;
	size_t size;
	b += ToBytes(static_cast<LSize>(t.get_mpf_t()->_mp_exp)); //add the exponent of the float
	size = t.get_mpf_t()->_mp_size;
	//create an integer with the content of the float
	i->_mp_alloc = size; 
	i->_mp_size = size; 
	i->_mp_d = t.get_mpf_t()->_mp_d;
	b += t < 0; //add the sign of the float
	size_t c;
	void * raw = mpz_export(NULL, &c, 1, 1, -1, 0, i);
	b += ToBytes(static_cast<LSize>(c)); //add the size of the exported integer
	b += String((char *)raw, c);
#ifndef WIN32 //solve a strange memory error on windows
	free(raw);
#endif
	return b;
}

String dubbel::ToBytes(Bool t) {
	String b = "";
	b += (char)t;
	return b;
}

String dubbel::ToBytes(String t) {
	return t;
}


dubbel::Instr::Instr(Char opc , Float t) {
	if(opc == OPC_FLOAT64 || opc == OPC_$FLOAT64)
		args.push_back(F64ToBytes(t));
	else args.push_back(ToBytes(t));
	opcode = opc;
}

size_t dubbel::Instr::Size() {
	if(opcode == NO_OP)
		return 5;
	size_t s = 1;
	for(vector<String>::iterator it = args.begin(); it != args.end(); ++it)
		s += it->size();
	return s;
}

void dubbel::InstrList::Push(const Instr &i) {
	v.push_back(i);
}

void dubbel::InstrList::Push(const Instr &i , size_t pos) {
	v.insert(v.begin() + pos , i);
}

void dubbel::InstrList::Join(const InstrList &l) {
	v.insert(v.end() , l.v.begin(), l.v.end());
}

Instr dubbel::InstrList::Pop() {
	Instr i = v[v.size() -1];
	v.pop_back();
	return i;
}

Instr dubbel::InstrList::Pop(size_t pos) {
	Instr i = v[pos];
	v.erase(v.begin() + pos);
	return i;
}

void dubbel::InstrList::Clear() {
	v.clear();
}

size_t dubbel::InstrList::Size() {
	size_t s = 0;
	for(vector<Instr>::iterator it = v.begin(); it != v.end(); ++it)
		s += it->Size();
	return s;
}

size_t dubbel::InstrList::Size(size_t pos) {
	size_t s = 0;
	vector<Instr>::iterator endit = v.begin() + pos;
	for(vector<Instr>::iterator it = v.begin(); it != endit; ++it)
		s += it->Size();
	return s;
}

size_t dubbel::InstrList::Len() {
	return v.size();
}

Instr & dubbel::InstrList::operator[](size_t pos) {
	return v[pos];
}
		
String dubbel::InstrList::GenerateBytecode() {
	String bc = "";
	for(vector<Instr>::iterator it = v.begin(); it != v.end(); ++it) {
		if(it->opcode == NO_OP)
			continue;
		bc += it->opcode;
		for(vector<String>::iterator j = it->args.begin(); j != it->args.end(); ++j)
			bc += *j;
	}
	return bc;
}


SSize dubbel::Builder::AddCode(const InstrList &l) {
	++codesSize;
	constPool.Join(l);
	return codesSize;
}

void dubbel::Builder::Append(Char opc , SSize p) {
	if(opc == OPC_LOAD || opc == OPC_STORE) {
		if(p >= localsSize) {
			localsSize = p +1;
		}
	}
	body.Push(Instr(opc , p));
}

void dubbel::Builder::Append(Char opc) {
	body.Push(Instr(opc));
}

InstrList dubbel::Builder::BuildCode(Char opc) { //opc ---> OPC_$CODE | OPC_OBJECT | OPC_OBJECT_EXT
	InstrList l;
	//opcode size constSize codesSize localsSize
	l.Push(Instr(opc , (LSize)(constPool.Size() + body.Size() +6) , constSize, codesSize, localsSize));
	l.Join(constPool);
	l.Join(body);
	return l;
}

String dubbel::Builder::BuildFile() {
	String bc = "";
	//add the head of the file
	bc += (char)BYTECODE_VER;
	bc += ToBytes(constSize);
	bc += ToBytes(codesSize);
	bc += ToBytes(localsSize);
	
	InstrList l;
	l.Join(constPool);
	l.Join(body);
	bc += l.GenerateBytecode();
	return bc;
}


