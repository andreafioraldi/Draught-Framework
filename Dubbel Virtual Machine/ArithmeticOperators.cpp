/*
 * ArithmeticOperators.cpp
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


Var dubbel::Var::operator+(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return Var((Char)(GetChar() + v.GetChar()));
		else if(Type() == TypeId::Int)
			return Var(Int(GetInt() + v.GetInt()));
		else if(Type() == TypeId::Float)
			return Var(Float(GetFloat() + v.GetFloat()));
		else if(Type() == TypeId::Array) {
			Array a;
			for(Array::iterator it = GetArray().begin(); it != GetArray().end(); ++it)
				a.push_back(it->Copy());
			for(Array::iterator it = v.GetArray().begin(); it != v.GetArray().end(); ++it)
				a.push_back(it->Copy());
			return Var(a);
		}
		else if(Type() == TypeId::String)
			return Var(GetString() + v.GetString());
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return Var(Int(GetChar() + v.GetInt()));
		else if(v.Type() == TypeId::Float)
			return Var(Float(GetChar() + v.GetFloat()));
		else if(v.Type() == TypeId::String)
			return Var(String{(char)GetChar()} + v.GetString());
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return Var(Int(GetInt() + v.GetChar()));
		else if(v.Type() == TypeId::Float)
			return Var(Float(GetInt() + v.GetFloat()));
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return Var(Float(GetFloat() + v.GetChar()));
		else if(v.Type() == TypeId::Int)
			return Var(Float(GetFloat() + v.GetInt()));
	}
	else if(Type() == TypeId::String) {
		if(v.Type() == TypeId::Char)
			return Var(GetString() + String{(char)v.GetChar()});
	}
	throw Var("Add operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Var dubbel::Var::operator-(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return Var((Char)(GetChar() - v.GetChar()));
		else if(Type() == TypeId::Int)
			return Var(Int(GetInt() - v.GetInt()));
		else if(Type() == TypeId::Float)
			return Var(Float(GetFloat() - v.GetFloat()));	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return Var(Int(GetChar() - v.GetInt()));
		else if(v.Type() == TypeId::Float)
			return Var(Float(GetChar() - v.GetFloat()));
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return Var(Int(GetInt() - v.GetChar()));
		else if(v.Type() == TypeId::Float)
			return Var(Float(GetInt() - v.GetFloat()));
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return Var(Float(GetFloat() - v.GetChar()));
		else if(v.Type() == TypeId::Int)
			return Var(Float(GetFloat() - v.GetInt()));
	}
	throw Var("Sub operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}

Var dubbel::Var::operator*(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return Var((Char)(GetChar() * v.GetChar()));
		else if(Type() == TypeId::Int)
			return Var(Int(GetInt() * v.GetInt()));
		else if(Type() == TypeId::Float)
			return Var(Float(GetFloat() * v.GetFloat()));	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int)
			return Var(Int(GetChar() * v.GetInt()));
		else if(v.Type() == TypeId::Float)
			return Var(Float(GetChar() * v.GetFloat()));
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char)
			return Var(Int(GetInt() * v.GetChar()));
		else if(v.Type() == TypeId::Float)
			return Var(Float(GetInt() * v.GetFloat()));
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char)
			return Var(Float(GetFloat() * v.GetChar()));
		else if(v.Type() == TypeId::Int)
			return Var(Float(GetFloat() * v.GetInt()));
	}
	throw Var("Mul operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Var dubbel::Var::operator/(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char) {
			if(v.GetChar() == 0)
				throw Var("Div operator : division by 0");
			return Var((Char)(GetChar() / v.GetChar()));
		}
		else if(Type() == TypeId::Int) {
			if(v.GetInt() == 0)
				throw Var("Div operator : division by 0");
			return Var(Int(GetInt() / v.GetInt()));
		}
		else if(Type() == TypeId::Float) {
			if(v.GetFloat() == 0)
				throw Var("Div operator : division by 0");
			return Var(Float(GetFloat() / v.GetFloat()));
		}	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int) {
			if(v.GetInt() == 0)
				throw Var("Div operator : division by 0");
			return Var(Int(GetChar() / v.GetInt()));
		}
		else if(v.Type() == TypeId::Float) {
			if(v.GetFloat() == 0)
				throw Var("Div operator : division by 0");
			return Var(Float(GetChar() / v.GetFloat()));
		}
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char) {
			if(v.GetChar() == 0)
				throw Var("Div operator : division by 0");
			return Var(Int(GetInt() / v.GetChar()));
		}
		else if(v.Type() == TypeId::Float) {
			if(v.GetChar() == 0)
				throw Var("Div operator : division by 0");
			return Var(Float(GetInt() / v.GetFloat()));
		}
	}
	else if(Type() == TypeId::Float) {
		if(v.Type() == TypeId::Char) {
			if(v.GetChar() == 0)
				throw Var("Div operator : division by 0");
			return Var(Float(GetFloat() / v.GetChar()));
		}
		else if(v.Type() == TypeId::Int) {
			if(v.GetChar() == 0)
				throw Var("Div operator : division by 0");
			return Var(Float(GetFloat() / v.GetInt()));
		}
	}
	throw Var("Div operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Var dubbel::Var::operator%(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char) {
			if(v.GetChar() == 0)
				throw Var("Mod operator : division by 0");
			return Var((Char)(GetChar() % v.GetChar()));
		}
		else if(Type() == TypeId::Int) {
			if(v.GetInt() == 0)
				throw Var("Mod operator : division by 0");
			return Var(Int(GetInt() % v.GetInt()));
		}	
	}
	else if(Type() == TypeId::Char) {
		if(v.Type() == TypeId::Int) {
			if(v.GetInt() == 0)
				throw Var("Mod operator : division by 0");
			return Var(Int(GetChar() % v.GetInt()));
		}
	}
	else if(Type() == TypeId::Int) {
		if(v.Type() == TypeId::Char) {
			if(v.GetChar() == 0)
				throw Var("Mod operator : division by 0");
			return Var(Int(GetInt() % v.GetChar()));
		}
	}
	throw Var("Mod operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Var dubbel::Var::operator+() {
	//TODO
	return this->Copy();
}


Var dubbel::Var::operator-() {
	if(Type() == TypeId::Char)
		return Var((Char)(-GetChar()));
	else if(Type() == TypeId::Int)
		return Var(Int(-GetInt()));
	else if(Type() == TypeId::Float)
		return Var(Float(-GetFloat()));
	throw Var("Minus operator : " + TypeStr(*this) + " is an invalid operand type");
}



