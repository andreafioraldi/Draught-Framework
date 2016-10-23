/*
 * Object.cpp
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
 * GNU Lesser General Public License for more detai\\ls.
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

Char dubbel::Var::Code::At(size_t pos) {
	return static_cast<Char>(bin[pos]);
}

void dubbel::Var::Code::ClearPtr() {
	for(vector<Var>::iterator it = consts.begin(); it != consts.end(); ++it)
			it->Clear();
	consts.clear();
	for(size_t i = 0; i < codes.size(); ++i) {
		codes[i]->ClearPtr();
		delete codes[i];
	}
	codes.clear();
}

bool dubbel::Var::Object::IsByteCode() {
	return flags == ObjFlag::ByteCode;
}

bool dubbel::Var::Object::IsNative() {
	return flags == ObjFlag::Native;
}

bool dubbel::Var::Object::IsInvocable() {
	return flags != ObjFlag::NotInvocable;
}


Object dubbel::Var::Object::Copy() {
	Object o;
	o.flags = flags;
	o.extra = extra;
	o.content = content;
	for(map<String , Var>::reverse_iterator it = members.rbegin(); it != members.rend(); ++it)
		o.members[it->first].Assign(it->second);
	for(map<String , Bool>::reverse_iterator it = modifiers.rbegin(); it != modifiers.rend(); ++it)
		o.modifiers[it->first] = it->second;
	return o;
}

void dubbel::Var::Object::Clear() {
	for(map<String , Var>::reverse_iterator it = members.rbegin(); it != members.rend();++it)
		it->second.Clear();
	members.clear();
	modifiers.clear();
	flags = ObjFlag::NotInvocable;
	content = nullptr;
}

dubbel::Var::Object::Object() {
	flags = ObjFlag::NotInvocable;
	content = nullptr;
	parent = nullptr;
	global = &mainObj;
}

dubbel::Var::Object::Object(Var * gbl) {
	flags = ObjFlag::NotInvocable;
	content = nullptr;
	parent = nullptr;
	global = gbl;
}

dubbel::Var::Object::Object(Native func) {
	flags = ObjFlag::Native;
	content = (void*)func;
	parent = nullptr;
	global = &mainObj;
}

dubbel::Var::Object::Object(Native func, Var * gbl) {
	flags = ObjFlag::Native;
	content = (void*)func;
	parent = nullptr;
	global = gbl;
}

dubbel::Var::Object::Object(Code * code) {
	flags = ObjFlag::ByteCode;
	content = (void*)code;
	parent = nullptr;
	global = &mainObj;
}

dubbel::Var::Object::Object(Code * code, Var * gbl) {
	flags = ObjFlag::ByteCode;
	content = (void*)code;
	parent = nullptr;
	global = gbl;
}

dubbel::Var::Object::~Object() {
	ClearParent();
}

void dubbel::Var::Object::SetParent(Var v) {
	ClearParent();
	parent = new Var(v.Reference());
}

void dubbel::Var::Object::ClearParent() {
	if (parent != nullptr) {
		parent->Clear();
		delete parent;
	}
}

