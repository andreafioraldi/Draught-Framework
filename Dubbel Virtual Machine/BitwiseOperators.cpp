/*
 * BitwiseOperators.cpp
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


Var dubbel::Var::operator&(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return Var((Char)(GetChar() & v.GetChar()));
		else if(Type() == TypeId::Int)
			return Var(Int(GetInt() & v.GetInt()));
	}
	else if(Type() == TypeId::Char && v.Type() == TypeId::Int)
		return Var(Int(GetChar() & v.GetInt()));
	else if(Type() == TypeId::Int && v.Type() == TypeId::Char)
		return Var(Int(GetInt() & v.GetChar()));
	throw Var("BitAnd operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}

Var dubbel::Var::operator|(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return Var((Char)(GetChar() | v.GetChar()));
		else if(Type() == TypeId::Int)
			return Var(Int(GetInt() | v.GetInt()));
	}
	else if(Type() == TypeId::Char && v.Type() == TypeId::Int)
		return Var(Int(GetChar() | v.GetInt()));
	else if(Type() == TypeId::Int && v.Type() == TypeId::Char)
		return Var(Int(GetInt() | v.GetChar()));
	throw Var("BitOr operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}

Var dubbel::Var::operator^(Var v) {
	if(Type() == v.Type()) {
		if(Type() == TypeId::Char)
			return Var((Char)(GetChar() ^ v.GetChar()));
		else if(Type() == TypeId::Int)
			return Var(Int(GetInt() ^ v.GetInt()));
	}
	else if(Type() == TypeId::Char && v.Type() == TypeId::Int)
		return Var(Int(GetChar() ^ v.GetInt()));
	else if(Type() == TypeId::Int && v.Type() == TypeId::Char)
		return Var(Int(GetInt() ^ v.GetChar()));
	throw Var("BitXor operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}


Var dubbel::Var::operator~() {
	if(Type() == TypeId::Char)
		return Var((Char)(~GetChar()));
	else if(Type() == TypeId::Int)
		return Var(Int(~GetInt()));
	throw Var("BitNot operator : " + TypeStr(*this) + " is an invalid operand type");
}


Var dubbel::Var::operator<<(Var v) {
	if(Type() == TypeId::Int && v.Type() == TypeId::Int) {
		Int r;
		mpz_mul_2exp(r.get_mpz_t(), GetInt().get_mpz_t(), v.GetInt().get_ui());
		return Var(r);
	}
	else if(Type() == TypeId::Char && v.Type() == TypeId::Int) {
		return Var((Char)(GetChar() << v.GetInt().get_ui()));
	}
	else if(Type() == TypeId::Float && v.Type() == TypeId::Int) {
		Float r;
		mpf_mul_2exp(r.get_mpf_t(), GetFloat().get_mpf_t(), v.GetInt().get_ui());
		return Var(r);
	}
	throw Var("LShift operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}

Var dubbel::Var::operator>>(Var v) {
	if(Type() == TypeId::Int && v.Type() == TypeId::Int) {
		Int r;
		mpz_fdiv_q_2exp(r.get_mpz_t(), GetInt().get_mpz_t(), v.GetInt().get_ui());
		return Var(r);
	}
	else if(Type() == TypeId::Char && v.Type() == TypeId::Int) {
		return Var((Char)(GetChar() >> v.GetInt().get_ui()));
	}
	else if(Type() == TypeId::Float && v.Type() == TypeId::Int) {
		Float r;
		mpf_div_2exp(r.get_mpf_t(), GetFloat().get_mpf_t(), v.GetInt().get_ui());
		return Var(r);
	}
	throw Var("RShift operator : " + TypeStr(*this) + " and " + TypeStr(v) + " are invalid operands types");
}

