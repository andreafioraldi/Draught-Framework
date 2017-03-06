/*
 * Var.cpp
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

TypeId dubbel::Var::Type() const {
	if(val == nullptr)
		return TypeId::None;
	return val->type;
}

Bool dubbel::Var::ReadOnly() const {
	if(val == nullptr)
		return false;
	return val->readOnly;
}

Char & dubbel::Var::GetChar() {
	return static_cast<Data<Char>*>(val->ptr)->data;
}

Int & dubbel::Var::GetInt() {
	return static_cast<Data<Int>*>(val->ptr)->data;
}

Float & dubbel::Var::GetFloat() {
	return static_cast<Data<Float>*>(val->ptr)->data;
}

Bool & dubbel::Var::GetBool() {
	return static_cast<Data<Bool>*>(val->ptr)->data;
}

String & dubbel::Var::GetString() {
	return static_cast<Data<String>*>(val->ptr)->data;
}

Array & dubbel::Var::GetArray() {
	return static_cast<Data<Array>*>(val->ptr)->data;
}

Object & dubbel::Var::GetObject() {
	return static_cast<Data<Object>*>(val->ptr)->data;
}


dubbel::Var::Var() {
	val = nullptr;
}

dubbel::Var::Var(Char t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(Int t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(Float t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(Bool t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(String t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(Array t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(Object t, Bool ronly) {
	val = nullptr;
	Set(t);
	val->readOnly = ronly;
}

dubbel::Var::Var(const char * t, Bool ronly) {
	val = nullptr;
	Set(String(t));
	val->readOnly = ronly;
}

void dubbel::Var::SetNone() {
	if(val == nullptr)
		val = new Value();
	else if(val->ptr != nullptr) {
		if(Type() == TypeId::Int)
			delete (Data<Int> *) val->ptr;
		else if(Type() == TypeId::Float)
			delete (Data<Float> *) val->ptr;
		else if(Type() == TypeId::String)
			delete (Data<String> *) val->ptr;
		else if(Type() == TypeId::Object) {
			if(GetObject().members.find("_finalize") != GetObject().members.end() && Attr("_finalize").Type() == TypeId::Object) {
				Attr("_finalize").GetObject().SetParent(*this);
				Attr("_finalize").Call(Var(Array())).Clear();
			}
			GetObject().Clear();
			delete (Data<Object> *) val->ptr;
		}
		else if(Type() == TypeId::Array) {
			for(Array::iterator it = GetArray().begin() ; it != GetArray().end(); ++it)
				it->Clear();
			GetArray().clear();
			delete (Data<Array> *) val->ptr;
		}
		else delete val->ptr;
		val->ptr = nullptr;
		val->type = TypeId::None;
	}
}

/* for future use
void dubbel::Var::ClearRef() {
	if(val == nullptr)
		return;
	if(val->ptr == nullptr)
		return;
	if(Type() == TypeId::Int)
		delete (Data<Int> *) val->ptr;
	else if(Type() == TypeId::Float)
		delete (Data<Float> *) val->ptr;
	else if(Type() == TypeId::String)
		delete (Data<String> *) val->ptr;
	else if(Type() == TypeId::Object) {
		if(GetObject().members.find("_finalize") != GetObject().members.end() && Attr("_finalize").Type() == TypeId::Object) {
			Attr("_finalize").GetObject().SetParent(*this);
			Attr("_finalize").Call(Var(Array())).Clear();
		}
		GetObject().Clear();
		delete (Data<Object> *) val->ptr;
	}
	else if(Type() == TypeId::Array) {
		for(Array::iterator it = GetArray().begin() ; it != GetArray().end(); ++it)
			it->Clear();
		GetArray().clear();
		delete (Data<Array> *) val->ptr;
	}
		else delete val->ptr;
	val->ptr = nullptr;
	val->type = TypeId::None;
}
*/

void dubbel::Var::Clear() {
	if(val == nullptr)
		return;
	if(val->pointers == 0) {
		if(Type() == TypeId::Int)
			delete (Data<Int> *) val->ptr;
		else if(Type() == TypeId::Float)
			delete (Data<Float> *) val->ptr;
		else if(Type() == TypeId::String)
			delete (Data<String> *) val->ptr;
		else if(Type() == TypeId::Object) {
			if(GetObject().members.find("_finalize") != GetObject().members.end() && Attr("_finalize").Type() == TypeId::Object) {
				Attr("_finalize").GetObject().SetParent(*this);
				Attr("_finalize").Call(Var(Array())).Clear();
			}
			GetObject().Clear();
			delete (Data<Object> *) val->ptr;
		}
		else if(Type() == TypeId::Array) {
			for(Array::iterator it = GetArray().begin() ; it != GetArray().end(); ++it)
				it->Clear();
			GetArray().clear();
			delete (Data<Array> *) val->ptr;
		}
		else delete val->ptr;
		delete val;
		val = nullptr;
	}
	else {
		val->pointers--;
		val = nullptr;
	}
}


void dubbel::Var::Set(Char t) {
	SetNone();
	val->ptr = new Data<Char>(t);
	val->type = TypeId::Char;
}

void dubbel::Var::Set(Int t) {
	SetNone();
	val->ptr = new Data<Int>(t);
	val->type = TypeId::Int;
}

void dubbel::Var::Set(Float t) {
	SetNone();
	val->ptr = new Data<Float>(t);
	val->type = TypeId::Float;
}

void dubbel::Var::Set(Bool t) {
	SetNone();
	val->ptr = new Data<Bool>(t);
	val->type = TypeId::Bool;
}

void dubbel::Var::Set(String t) {
	SetNone();
	val->ptr = new Data<String>(t);
	val->type = TypeId::String;
}

void dubbel::Var::Set(Array t) {
	SetNone();
	val->ptr = new Data<Array>(t);
	val->type = TypeId::Array;
}

void dubbel::Var::Set(Object t) {
	SetNone();
	val->ptr = new Data<Object>(t);
	val->type = TypeId::Object;
}

Var & dubbel::Var::Assign(Var v) {
	Clear();
	if(v.Type() == TypeId::Char)
		Set(v.GetChar());
	else if(v.Type() == TypeId::Int)
		Set(v.GetInt());
	else if(v.Type() == TypeId::Float)
		Set(v.GetFloat());
	else if(v.Type() == TypeId::Bool)
		Set(v.GetBool());
	else if(v.Type() == TypeId::String)
		Set(v.GetString());
	else if(v.Type() == TypeId::Array) {
		Array a;
		size_t s = v.GetArray().size();
		a.reserve(s);
		for(size_t i = 0; i < s; ++i)
			a.push_back(v.GetArray().at(i).Copy());
		Set(a);
	}
	else if (v.Type() == TypeId::Object) {
		Set(v.GetObject().Copy());
		if (GetObject().members.find("_copy") != GetObject().members.end() && Attr("_copy").Type() == TypeId::Object) {
			Attr("_copy").GetObject().SetParent(*this);
			Attr("_copy").Call(Var(Array())).Clear();
		}
	}
	else if (v.Type() == TypeId::None)
		SetNone();
	return *this;
}

Var & dubbel::Var::Assign(Char t) {
	Clear();
	Set(t);
	return *this;
}

Var & dubbel::Var::Assign(Int t) {
	Clear();
	Set(t);
	return *this;
}

Var & dubbel::Var::Assign(Float t) {
	Clear();
	Set(t);
	return *this;
}

Var & dubbel::Var::Assign(Bool t) {
	Clear();
	Set(t);
	return *this;
}

Var & dubbel::Var::Assign(String t) {
	Clear();
	Set(t);
	return *this;
}

Var & dubbel::Var::Assign(Array t) {
	Clear();
	Set(t);
	return *this;
}

Var & dubbel::Var::Assign(Object t) {
	Clear();
	Set(t);
	return *this;
}

Var & Var::RefAssign(Var v) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	TypeId vtype = v.Type();
	if (vtype == TypeId::Object) {
		Set(v.GetObject().Copy());
		if (GetObject().members.find("_copy") != GetObject().members.end() && Attr("_copy").Type() == TypeId::Object) {
			Attr("_copy").GetObject().SetParent(*this);
			Attr("_copy").Call(Var(Array())).Clear();
		}
	}
	else if(vtype == TypeId::Array) {
		Array a;
		size_t s = v.GetArray().size();
		a.reserve(s);
		for(size_t i = 0; i < s; ++i)
			a.push_back(GetArray().at(i).Copy());
		Set(a);
	}
	else if(Type() == vtype) {
		if(vtype == TypeId::Char)
			GetChar() = v.GetChar();
		else if(vtype == TypeId::Int)
			GetInt() = v.GetInt();
		else if(vtype == TypeId::Float)
			GetInt() = v.GetInt();
		else if(vtype == TypeId::Bool)
			GetBool() = v.GetBool();
		else if(vtype == TypeId::String)
			GetString() = v.GetString();
	}
	else if(vtype == TypeId::Char)
		Set(v.GetChar());
	else if(vtype == TypeId::Int)
		Set(v.GetInt());
	else if(vtype == TypeId::Float)
		Set(v.GetFloat());
	else if(vtype == TypeId::Bool)
		Set(v.GetBool());
	else if(vtype == TypeId::String)
		Set(v.GetString());
	else if (vtype == TypeId::None)
		SetNone();
	return *this;
}

Var & dubbel::Var::RefAssign(Char t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & dubbel::Var::RefAssign(Int t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & dubbel::Var::RefAssign(Float t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & dubbel::Var::RefAssign(Bool t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & dubbel::Var::RefAssign(String t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & dubbel::Var::RefAssign(Array t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & dubbel::Var::RefAssign(Object t) {
	if(ReadOnly())
		throw Var("RefAssign operator : readonly variable");
	Set(t);
}

Var & Var::Bind(Var & v) {
	Clear();
	if(v.val == nullptr)
		v.val = new Value();
	v.val->pointers++;
	val = v.val;
	return *this;
}

Var dubbel::Var::Copy() {
	Var v;
	v.Assign(*this);
	return v;
}

Var dubbel::Var::Reference() {
	Var v;
	v.Bind(*this);
	return v;
}

Bool dubbel::Var::ToBool() {
	if(Type() == TypeId::Char)
		return (Bool)GetChar();
	if(Type() == TypeId::Int)
		return (Bool)GetInt().get_si();
	else if(Type() == TypeId::Float)
		return (Bool)GetFloat().get_si();
	else if(Type() == TypeId::Bool)
		return GetBool();
	else if(Type() == TypeId::None)
		return false;
	return true;
}

String dubbel::Var::ToString() {
	if(Type() == TypeId::Char) {
		String s;
		s += GetChar();
		return s;
	}
	if(Type() == TypeId::Int) {
		return GetInt().get_str();
	}
	else if(Type() == TypeId::Float) {
		mp_exp_t exp;
		int c = 0;
		String s = GetFloat().get_str(exp);
		if(sgn(GetFloat()) == -1)
			c = 1;
		if(s.size() == 0)
			return "0.0";
		if(exp < 0) {
			size_t cc = -exp;
			for(size_t j = 0;j < cc;++j) {
				s = "0" + s;
				exp++;
			}
		}
		size_t ss = s.size();
		for(size_t j = exp; j > ss; --j)
			s += "0";
		s.insert(s.begin() +exp +c,'.');
		if(s[0] == '.')
			s = "0" + s;
		else if(s[s.size()-1] == '.')
			s += "0";
		return s;
	}
	else if(Type() == TypeId::Bool) {
		if(GetBool())
			return "true";
		else return "false";
	}
	else if(Type() == TypeId::String) {
		return GetString();
	}
	else if(Type() == TypeId::Array) {
		String s = "[";
		for(size_t i = 0;i < GetArray().size(); ++i) {
			s += " ";
			s += GetArray().at(i).ToString();
			if(i < GetArray().size() -1)
				s += " ,";
		}
		s += " ]";
		return s;
	}
	else if(Type() == TypeId::Object) {
		if(GetObject().members.find("ToString") == GetObject().members.end() || Attr("ToString").Type() != TypeId::Object)
			return "(not printable object)";
		Attr("ToString").GetObject().SetParent(*this);
		Var r = Attr("ToString").Call(Var(Array()));
		String rs = r.ToString();
		r.Clear();
		return rs;
	}
	else if(Type() == TypeId::None)
		return "none";
}


Var & dubbel::Var::operator=(Char t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::operator=(Int t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::operator=(Float t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::operator=(Bool t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::operator=(String t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::operator=(Array t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::operator=(Object t) {
	Assign(t);
	return *this;
}

Var & dubbel::Var::Attr(const String & name) {
	return GetObject().members[name];
}

Var & dubbel::Var::At(LSize pos) {
	return GetArray().at(pos);
}
