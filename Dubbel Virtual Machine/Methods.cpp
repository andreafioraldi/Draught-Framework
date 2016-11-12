/*
 * Methods.cpp
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

Var dubbel::any_ToString(Var me, Var args) {
	return Var(me.GetObject().parent->ToString());
}

Var dubbel::any_ToBool(Var me, Var args) {
	return Var(me.GetObject().parent->ToBool());
}

Var dubbel::char_ToInt(Var me, Var args) {
	return Var(Int(me.GetObject().parent->GetChar()));
}

Var dubbel::char_ToFloat(Var me, Var args) {
	return Var(Float(me.GetObject().parent->GetChar(), 64));
}

Var dubbel::char_IsDigit(Var me, Var args) {
	return Var((Bool)isdigit(me.GetObject().parent->GetChar()));
}

Var dubbel::char_IsUpper(Var me, Var args) {
	return Var((Bool)isupper(me.GetObject().parent->GetChar()));
}

Var dubbel::char_IsLower(Var me, Var args) {
	return Var((Bool)islower(me.GetObject().parent->GetChar()));
}

Var dubbel::char_IsLetter(Var me, Var args) {
	return Var((Bool)isalpha(me.GetObject().parent->GetChar()));
}

Var dubbel::char_IsPrintable(Var me, Var args) {
	return Var((Bool)isprint(me.GetObject().parent->GetChar()));
}

Var dubbel::char_IsControl(Var me, Var args) {
	return Var((Bool)iscntrl(me.GetObject().parent->GetChar()));
}

Var dubbel::char_ToUpper(Var me, Var args) {
	return Var((Char)toupper(me.GetObject().parent->GetChar()));
}

Var dubbel::char_ToLower(Var me, Var args) {
	return Var((Char)tolower(me.GetObject().parent->GetChar()));
}



Var dubbel::int_ToChar(Var me, Var args) {
	return Var((Char)(me.GetObject().parent->GetInt().get_si()));
}

Var dubbel::int_ToFloat(Var me, Var args) {
	size_t prec = 64;
	if(args.GetArray().size() > 0) {
		if(args.GetArray()[0].Type() != TypeId::Int) {
			throw Var("<Int>.ToFloat : the argument 1 must be of type int");
		}
		prec = args.GetArray()[0].GetInt().get_ui();
	}
	return Var(Float(me.GetObject().parent->GetInt(), prec));
}


Var dubbel::float_ToChar(Var me, Var args) {
	return Var((Char)(me.GetObject().parent->GetFloat().get_si()));
}

Var dubbel::float_ToInt(Var me, Var args) {
	return Var(Int(me.GetObject().parent->GetFloat()));
}


Var dubbel::float_GetPrec(Var me, Var args) {
	return Var(Int(me.GetObject().parent->GetFloat().get_prec()));
}

Var dubbel::float_SetPrec(Var me, Var args) {
	if(args.GetArray().size() < 1) {
		throw Var("<Float>.SetPrec : an argument is needed");
	}
	if(args.GetArray()[0].Type() != TypeId::Int) {
		throw Var("<Float>.SetPrec : the argument 1 must be of type int");
	}
	me.GetObject().parent->GetFloat().set_prec(args.GetArray()[0].GetInt().get_ui());
	return Var();
}

Var dubbel::bool_ToInt(Var me, Var args) {
	return Var(Int(me.GetObject().parent->GetBool()));
}



Var dubbel::string_ToArray(Var me, Var args) {
	String * s = &me.GetObject().parent->GetString();
	Array arr;
	for(unsigned i = 0; i < s->size(); ++i)
		arr.push_back(Var((Char)(*s)[i]));
	return Var(arr);
}

Var dubbel::string_ToInt(Var me, Var args) {
	String * s = &me.GetObject().parent->GetString();
	Int i;
	try {
		i = *s;
	}
	catch(invalid_argument err) {
		throw Var("<String>.ToInt : the string is not a number");
	}
	return Var(i);
}

Var dubbel::string_ToFloat(Var me, Var args) {
	String * s = &me.GetObject().parent->GetString();
	Float f;
	size_t prec = 64;
	if(args.GetArray().size() > 0) {
		if(args.GetArray()[0].Type() != TypeId::Int) {
			throw Var("<String>.ToFloat : the argument 1 must be of type int");
		}
		prec = args.GetArray()[0].GetInt().get_ui();
	}
	try {
		f = Float(*s, prec);
	}
	catch(invalid_argument err) {
		throw Var("<String>.ToFloat : the string is not a number");
	}
	return Var(f);
}

Var dubbel::string_Length(Var me, Var args) {
	return Var(Int(me.GetObject().parent->GetString().size()));
}

Var dubbel::string_Push(Var me, Var args) {
	if(args.GetArray().size() == 1) {
		me.GetObject().parent->GetString() += args.GetArray()[0].ToString();
	}
	else if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<String>.Push : the argument 2 must be of type int");
		}
		size_t pos = args.GetArray()[1].GetInt().get_ui();
		if(pos > me.GetObject().parent->GetString().size()) {
			throw Var("<String>.Push : index out of range");
		}
		me.GetObject().parent->GetString().insert(pos , args.GetArray()[0].ToString());
	}
	return Var();
}

Var dubbel::string_Pop(Var me, Var args) {
	if(me.GetObject().parent->GetString().size() == 0) {
		throw Var("<String>.pop : the string is empty");
	}
	if(args.GetArray().size() == 0) {
		me.GetObject().parent->GetString().pop_back();
	}
	else if(args.GetArray().size() == 1) {
		if(args.GetArray()[0].Type() != TypeId::Int) {
			throw Var("<String>.Pop : the argument 1 must be of type int");
		}
		size_t pos = args.GetArray()[0].GetInt().get_ui();
		if(pos >= me.GetObject().parent->GetString().size()) {
			throw Var("<String>.Pop : index out of range");
		}
		me.GetObject().parent->GetString().erase(me.GetObject().parent->GetString().begin() + pos);
	}
	else if(args.GetArray().size() > 1) {
		if(args.GetArray()[0].Type() != TypeId::Int) {
			throw Var("<String>.Pop : the argument 1 must be of type int");
		}
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<String>.Pop : the argument 2 must be of type int");
		}
		size_t b = args.GetArray()[0].GetInt().get_ui();
		size_t e = args.GetArray()[1].GetInt().get_ui();
		if(b > e) {
			throw Var("<String>.Pop : the argument 1 must be lower than the argument 2");
		}
		if(e > me.GetObject().parent->GetString().size()) {
			throw Var("<String>.Pop : index out of range");
		}
		me.GetObject().parent->GetString().erase(me.GetObject().parent->GetString().begin() + b, me.GetObject().parent->GetString().begin() + e);
	}
	return Var();
}

Var dubbel::string_Find(Var me, Var args) {
	if(args.GetArray().size() < 1) {
		throw Var("<String>.Find : an argument is needed");
	}
	size_t r, pos = 0;
	if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<String>.Find : the argument 2 must be of type int");
		}
		pos = args.GetArray()[1].GetInt().get_ui();
		if(pos >= me.GetObject().parent->GetString().size()) {
			throw Var("<String>.Find : index out of range");
		}
	}
	if(args.GetArray()[0].Type() == TypeId::Char) {
		r = me.GetObject().parent->GetString().find(args.GetArray()[0].GetChar(), pos);
	}
	else if(args.GetArray()[0].Type() == TypeId::String) {
		r = me.GetObject().parent->GetString().find(args.GetArray()[0].GetString(), pos);
	}
	else throw Var("<String>.Find : the argument 1 must be of type char or string");
	if(r == string::npos)
		return Var(Int(-1));
	return Var(Int(r));
}

Var dubbel::string_RFind(Var me, Var args) {
	if(args.GetArray().size() < 1) {
		throw Var("<String>.RFind : an argument is needed");
	}
	size_t r, pos = string::npos;
	if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<String>.RFind : the argument 2 must be of type int");
		}
		pos = args.GetArray()[1].GetInt().get_ui();
		if(pos >= me.GetObject().parent->GetString().size()) {
			throw Var("<String>.RFind : index out of range");
		}
	}
	if(args.GetArray()[0].Type() == TypeId::Char) {
		r = me.GetObject().parent->GetString().rfind(args.GetArray()[0].GetChar(), pos);
	}
	else if(args.GetArray()[0].Type() == TypeId::String) {
		r = me.GetObject().parent->GetString().rfind(args.GetArray()[0].GetString(), pos);
	}
	else throw Var("<String>.RFind : the argument 1 must be of type char or string");
	if (r == string::npos)
		return Var(Int(-1));
	return Var(Int(r));
}

Var dubbel::string_First(Var me, Var args) {
	if(me.GetObject().parent->GetString().size() == 0) {
		throw Var("<String>.First : empty string");
	}
	return Var((Char)(me.GetObject().parent->GetString().front()));
}

Var dubbel::string_Last(Var me, Var args) {
	if(me.GetObject().parent->GetString().size() == 0) {
		throw Var("<String>.Last : empty string");
	}
	return Var((Char)(me.GetObject().parent->GetString().back()));
}

Var dubbel::string_SubStr(Var me, Var args) {
	if(args.GetArray().size() < 1) {
		throw Var("<String>.SubStr : an argument is needed");
	}
	size_t begin, end = string::npos;
	if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<String>.SubStr : the argument 2 must be of type int");
		}
		end = args.GetArray()[1].GetInt().get_ui();
		if(end > me.GetObject().parent->GetString().size()) {
			throw Var("<String>.SubStr : index out of range");
		}
	}
	if(args.GetArray()[0].Type() != TypeId::Int) {
		throw Var("<String>.SubStr : the argument 1 must be of type int");
	}
	begin = args.GetArray()[0].GetInt().get_ui();
	if(begin > end) {
		throw Var("<String>.SubStr : index out of range");
	}
	return Var(String(me.GetObject().parent->GetString().substr(begin, end - begin)));
}

Var dubbel::string_Replace(Var me, Var args) {
	if(args.GetArray().size() == 1) {
		throw Var("<String>.Replace : 2 arguments are needed");
	}
	String str;
	if(args.GetArray().size() == 2) {
		if(args.GetArray()[0].Type() != TypeId::String) {
			throw Var("<String>.Change : the argument 1 must be of type string");
		}
		if(args.GetArray()[1].Type() != TypeId::String) {
			throw Var("<String>.Change : the argument 2 must be of type string");
		}
		String * search = &args.GetArray()[0].GetString();
		String * replace = &args.GetArray()[1].GetString();
		str = me.GetObject().parent->GetString();
		for(size_t pos = 0; ; pos += replace->size()) {
			pos = str.find(*search, pos);
			if(pos == string::npos)
				break;
			str.erase(pos, search->size());
			str.insert(pos, *replace);
		}
	}
	else if(args.GetArray().size() == 3) {
		if(args.GetArray()[0].Type() != TypeId::String) {
			throw Var("<String>.Change : the argument 1 must be of type string");
		}
		if(args.GetArray()[1].Type() != TypeId::String) {
			throw Var("<String>.Change : the argument 2 must be of type string");
		}
		if(args.GetArray()[2].Type() != TypeId::Int) {
			throw Var("<String>.Change : the argument 3 must be of type int");
		}
		Int * count = &args.GetArray()[2].GetInt();
		String * search = &args.GetArray()[0].GetString();
		String * replace = &args.GetArray()[1].GetString();
		str = me.GetObject().parent->GetString();
		for(size_t pos = 0; *count > 0; pos += replace->size()) {
			pos = str.find(*search, pos);
			if(pos == string::npos)
				break;
			str.erase(pos, search->size());
			str.insert(pos, *replace);
			--(*count);
		}
	}
	return Var(str);
}

Var dubbel::string_Trim(Var me, Var args) {
	String str = me.GetObject().parent->GetString();
	str.erase(0, str.find_first_not_of(" \t\n"));
	str.erase(str.find_last_not_of(" \t\n") +1);
	return Var(str);
}

Var dubbel::string_LTrim(Var me, Var args) {
	String str = me.GetObject().parent->GetString();
	str.erase(0, str.find_first_not_of(" \t\n"));
	return Var(str);
}

Var dubbel::string_RTrim(Var me, Var args) {
	String str = me.GetObject().parent->GetString();
	str.erase(str.find_last_not_of(" \t\n") +1);
	return Var();
}

Var dubbel::string_Split(Var me, Var args) {
	if (args.GetArray().size() < 1) {
		throw Var("<String>.Split : an argument is needed");
	}
	if (args.GetArray()[0].Type() != TypeId::String) {
		throw Var("<String>.Split : the argument 1 must be of type string");
	}
	bool ws = true;
	if (args.GetArray().size() > 1) {
		if (args.GetArray()[1].Type() != TypeId::Bool) {
			throw Var("<String>.Split : the argument 2 must be of type bool");
		}
		ws = args.GetArray()[1].GetBool();
	}
	String * str = &me.GetObject().parent->GetString();
	String * del = &args.GetArray()[0].GetString();
	Array arr;
	String token;
	size_t start = 0;
	size_t end = str->find(*del);
	while (end != std::string::npos)
	{
		token = str->substr(start, end - start);
		if (token != "" || ws)
			arr.push_back(Var(token));
		start = end + del->length();
		end = str->find(*del, start);
	}
	token = str->substr(start, end - start);
	if (token != "" || ws)
		arr.push_back(Var(token));
	return Var(arr);
}

Var dubbel::string_Change(Var me, Var args) {
	if(args.GetArray().size() == 1) {
		throw Var("<String>.Change : 2 arguments are needed");
	}
	else if(args.GetArray().size() > 1) {
		if(args.GetArray()[0].Type() != TypeId::Char) {
			throw Var("<String>.Change : the argument 1 must be of type char");
		}
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<String>.Change : the argument 2 must be of type int");
		}
		if(args.GetArray()[1].GetInt().get_ui() >= me.GetObject().parent->GetString().size()) {
			throw Var("<String>.Change : index out of range");
		}
		me.GetObject().parent->GetString()[args.GetArray()[1].GetInt().get_ui()] = args.GetArray()[0].GetChar();
	}
	return me.GetObject().parent->Reference();
}

Var dubbel::string_Clear(Var me, Var args) {
	me.GetObject().parent->GetString().clear();
	return Var();
}

Var dubbel::array_Length(Var me, Var args) {
	return Var(Int(me.GetObject().parent->GetArray().size()));
}

Var dubbel::array_Push(Var me, Var args) {
	if(args.GetArray().size() == 1)
		me.GetObject().parent->GetArray().push_back(args.GetArray()[0].Copy());
	else if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int)
			throw Var("<Array>.Push : the argument 2 must be of type int");
		size_t pos = args.GetArray()[1].GetInt().get_ui();
		if(pos > me.GetObject().parent->GetArray().size())
			throw Var("<Array>.Push : index out of range");
		me.GetObject().parent->GetArray().insert(me.GetObject().parent->GetArray().begin() + pos , args.GetArray()[0].Copy());
	}
	return Var();
}

Var dubbel::array_PushRef(Var me, Var args) {
	if (args.GetArray().size() == 1)
		me.GetObject().parent->GetArray().push_back(args.GetArray()[0]);
	else if (args.GetArray().size() > 1) {
		if (args.GetArray()[1].Type() != TypeId::Int)
			throw Var("<Array>.PushRef : the argument 2 must be of type int");
		size_t pos = args.GetArray()[1].GetInt().get_ui();
		if (pos > me.GetObject().parent->GetArray().size())
			throw Var("<Array>.PushRef : index out of range");
		me.GetObject().parent->GetArray().insert(me.GetObject().parent->GetArray().begin() + pos, args.GetArray()[0]);
	}
	return Var();
}

Var dubbel::array_Pop(Var me, Var args) {
	if(me.GetObject().parent->GetArray().size() == 0)
		throw Var("<Array>.Pop : the array is empty");
	if(args.GetArray().size() == 0)
		me.GetObject().parent->GetArray().pop_back();
	else if(args.GetArray().size() == 1) {
		if(args.GetArray()[0].Type() != TypeId::Int)
			throw Var("<Array>.Pop : the argument 1 must be of type int");
		size_t pos = args.GetArray()[0].GetInt().get_ui();
		if(pos >= me.GetObject().parent->GetArray().size())
			throw Var("<Array>.Pop : index out of range");
		me.GetObject().parent->GetArray().erase(me.GetObject().parent->GetArray().begin() + pos);
	}
	else if(args.GetArray().size() > 1) {
		if(args.GetArray()[0].Type() != TypeId::Int)
			throw Var("<Array>.Pop : the argument 1 must be of type int");
		if(args.GetArray()[1].Type() != TypeId::Int)
			throw Var("<Array>.Pop : the argument 2 must be of type int");
		size_t b = args.GetArray()[0].GetInt().get_ui();
		size_t e = args.GetArray()[1].GetInt().get_ui();
		if(b > e)
			throw Var("<Array>.Pop : the argument 1 must be lower than the argument 2");
		if(e > me.GetObject().parent->GetArray().size())
			throw Var("<Array>.Pop : index out of range");
		me.GetObject().parent->GetArray().erase(me.GetObject().parent->GetArray().begin() + b, me.GetObject().parent->GetArray().begin() + e);
	}
	return Var();
}

Int ArrayFind(Array & a, Var e, size_t pos) {
	for (; pos < a.size(); ++pos)
		if (a[pos] == e) break;
	if(pos == a.size())
		return -1;
	return Int(pos);
}

Int ArrayRFind(Array & a, Var e, long pos) {
	for (; pos >= 0; --pos)
		if (a[pos] == e) break;
	if (pos == a.size())
		return -1;
	return Int(pos);
}

Var dubbel::array_Find(Var me, Var args) {
	if(args.GetArray().size() < 1) {
		throw Var("<Array>.Find : an argument is needed");
	}
	size_t pos = 0;
	if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<Array>.Find : the argument 2 must be of type int");
		}
		pos = args.GetArray()[1].GetInt().get_ui();
		if(pos >= me.GetObject().parent->GetArray().size()) {
			throw Var("<Array>.Find : index out of range");
		}
	}
	return Var(ArrayFind(me.GetObject().parent->GetArray(), args.GetArray()[0], pos));
}

Var dubbel::array_RFind(Var me, Var args) {
	if(args.GetArray().size() < 1) {
		throw Var("<Array>.RFind : an argument is needed");
	}
	long pos = me.GetObject().parent->GetArray().size() -1;
	if(args.GetArray().size() > 1) {
		if(args.GetArray()[1].Type() != TypeId::Int) {
			throw Var("<Array>.RFind : the argument 2 must be of type int");
		}
		pos = args.GetArray()[1].GetInt().get_ui();
		if(pos >= me.GetObject().parent->GetArray().size()) {
			throw Var("<Array>.RFind : index out of range");
		}
	}
	return Var(ArrayRFind(me.GetObject().parent->GetArray(), args.GetArray()[0], pos));
}

Var dubbel::array_First(Var me, Var args) {
	if(me.GetObject().parent->GetArray().size() == 0) {
		throw Var("<Array>.First : empty array");
	}
	return me.GetObject().parent->GetArray().front();
}

Var dubbel::array_Last(Var me, Var args) {
	if(me.GetObject().parent->GetArray().size() == 0) {
		throw Var("<Array>.Last : empty array");
	}
	return me.GetObject().parent->GetArray().back();
}

Var dubbel::array_Clear(Var me, Var args) {
	for(Array::iterator it = me.GetObject().parent->GetArray().begin() ; it != me.GetObject().parent->GetArray().end(); ++it)
		it->Clear();
	me.GetObject().parent->GetArray().clear();
	return Var();
}
