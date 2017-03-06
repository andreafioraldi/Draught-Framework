/*
 * ComparisonOperators.cpp
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
#include <sstream>

using namespace std;
using namespace dubbel;


Bool dubbel::Var::Like(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() == v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() == v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() == v.GetFloat();
		else if(Type() == TypeId::String)
			return GetString() == v.GetString();
		else if(Type() == TypeId::Array) {
			Array * a = &GetArray();
			Array * b = &v.GetArray();
			if(a->size() != b->size())
				return false;
			for(size_t i = 0; i < a->size(); ++i)
				if(!(a->at(i) == b->at(i)))
					return false;
			return true;
		}
		else if(Type() == TypeId::Object) {
			if(GetObject().members.size() != v.GetObject().members.size())
				return false;
			for(map<String , Var>::iterator i1 = GetObject().members.begin(), i2 = v.GetObject().members.begin(); i1 != GetObject().members.end();++i1, ++i2) {
				if(i1->first != i2->first)
					return false;
			}
			return true;
		}
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() == v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() == v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() == v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() == v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() == v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() == v.GetInt();
	}
	return false;
	//throw Var("IsEqual operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator==(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() == v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() == v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() == v.GetFloat();
		else if(Type() == TypeId::String)
			return GetString() == v.GetString();
		else if(Type() == TypeId::Array) {
			Array * a = &GetArray();
			Array * b = &v.GetArray();
			if(a->size() != b->size())
				return false;
			for(size_t i = 0; i < a->size(); ++i)
				if(!(a->at(i) == b->at(i)))
					return false;
			return true;
		}
		else if(Type() == TypeId::Object) {
			if(GetObject().members.size() != v.GetObject().members.size())
				return false;
			for(map<String , Var>::iterator i1 = GetObject().members.begin(), i2 = v.GetObject().members.begin(); i1 != GetObject().members.end();++i1, ++i2) {
				if(i1->first != i2->first || i2->second != i2->second)
					return false;
			}
			return true;
		}
		else if(Type() == TypeId::None)
			return true;
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() == v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() == v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() == v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() == v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() == v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() == v.GetInt();
	}
	return false;
	//throw Var("IsEqual operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator!=(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() != v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() != v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() != v.GetFloat();
		else if(Type() == TypeId::String)
			return GetString() != v.GetString();
		else if(Type() == TypeId::Array) {
			Array * a = &GetArray();
			Array * b = &v.GetArray();
			if(a->size() != b->size())
				return true;
			for(size_t i = 0; i < a->size(); ++i)
				if(!(a->at(i) == b->at(i)))
					return true;
			return false;
		}
		else if(Type() == TypeId::Object) {
			if(GetObject().members.size() != v.GetObject().members.size())
				return true;
			for(map<String , Var>::iterator i1 = GetObject().members.begin(), i2 = v.GetObject().members.begin(); i1 != GetObject().members.end();++i1, ++i2) {
				if(i1->first != i2->first || i2->second != i2->second)
					return true;
			}
			return false;
		}
		else if(Type() == TypeId::None)
			return false;
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() != v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() != v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() != v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() != v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() != v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() != v.GetInt();
	}
	return true;
	//throw Var("IsNotEqual operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator<(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() < v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() < v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() < v.GetFloat();	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() < v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() < v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() < v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() < v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() < v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() < v.GetInt();
	}
	throw Var("IsLower operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator<=(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() <= v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() <= v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() <= v.GetFloat();	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() <= v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() <= v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() <= v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() <= v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() <= v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() <= v.GetInt();
	}
	throw Var("IsLowerEqual operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator>(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() > v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() > v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() > v.GetFloat();	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() > v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() > v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() > v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() > v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() > v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() > v.GetInt();
	}
	throw Var("IsGreater operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator>=(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return GetChar() >= v.GetChar();
		else if(Type() == TypeId::Int)
			return GetInt() >= v.GetInt();
		else if(Type() == TypeId::Float)
			return GetFloat() >= v.GetFloat();	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return GetChar() >= v.GetInt();
		else if(v.Type() == TypeId::Float)
			return GetChar() >= v.GetFloat();
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return GetInt() >= v.GetChar();
		else if(v.Type() == TypeId::Float)
			return GetInt() >= v.GetFloat();
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return GetFloat() >= v.GetChar();
		else if(v.Type() == TypeId::Int)
			return GetFloat() >= v.GetInt();
	}
	throw Var("IsGreaterEqual operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Bool dubbel::Var::operator!() {
	if(Type() == TypeId::Bool)
		return !GetBool();
	if(Type() == TypeId::Char)
		return (Bool)(!GetChar());
	else if(Type() == TypeId::Int)
		return (Bool)(!GetInt().get_si());
	throw Var("Not operator : " + TypeStr(*this) + " is an invalid operand type");
}

