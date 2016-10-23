/*
 * ExecCode.cpp
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

void dubbel::StackPop(vector<Cell> & stack, size_t pos) {
	stack[pos].Clear();
	stack.erase(stack.begin() + pos);
}

String toHexStr(Char c) {
	stringstream buf;
	buf << hex << ((unsigned int)c & 0xFF);
	return buf.str();
}

struct forArr {
	Var v;
	size_t pos = 0;
};

int dubbel::ExecCode(Code * code , Var * me , Var & args , Var & returned , Array & locals , vector<Cell> & stack) {
	SSize trycount = 0;
	vector<LSize> tryBegin;
	vector<LSize> tryEnd;
	map<SSize, forArr> forMap;
	Var error;
	String dbgCache = "";
	Bool isPrivate = false;
	
	for(LSize i = 0; i < code->bin.size(); ++i) {
		//cerr << "EXEC  [pos] " << std::dec << i << "\t[val]  dec:" << ((unsigned int)code->At(i) & 0xFF) << "\thex:" << std::hex << ((unsigned int)code->At(i) & 0xFF) << std::dec << endl;
		try {
			if(code->At(i) == OPC_EXIT) {
				if(stack[0].Get().Type() == TypeId::Int)
					Exit(stack[0].Get().GetInt().get_si());
				Exit(0);
			}
			else if(code->At(i) == OPC_STACK_CLEAR) {
				while(stack.size() > 0)
					StackPop(stack);
			}
			else if(code->At(i) == OPC_STACK_POP) {
				StackPop(stack);
			}
			else if(code->At(i) == OPC_STACK_SWAP) {
				Cell b = stack[0];
				Cell a = stack[1];
				stack[0] = a;
				stack[1] = b;
			}
			else if(code->At(i) == OPC_STACK_DUP) {
				stack.insert(stack.begin() , stack[0]);
			}
			else if(code->At(i) == OPC_NONE) {
				stack.insert(stack.begin() , Cell(new Var(),true));
			}
			else if(code->At(i) == OPC_CHAR) {
				stack.insert(stack.begin() ,Cell((Char)code->At(i+1)));
				i++;
			}
			else if(code->At(i) == OPC_INT) {
				LSize used;
				stack.insert(stack.begin() , Cell(BuildInt(code->bin, used, i+1)));
				i += used;
			}
			else if(code->At(i) == OPC_FLOAT) {
				LSize used;
				stack.insert(stack.begin() , Cell(BuildFloat(code->bin, used, i+1)));
				i += used;
			}
			else if(code->At(i) == OPC_FLOAT64) {
				LSize used;
				stack.insert(stack.begin() , Cell(BuildFloat64(code->bin, used, i+1)));
				i += used;
			}
			else if(code->At(i) == OPC_TRUE) {
				stack.insert(stack.begin() , Cell(true));
			}
			else if(code->At(i) == OPC_FALSE) {
				stack.insert(stack.begin() , Cell(false));
			}
			else if(code->At(i) == OPC_STRING) {
				LSize len = BuildLSize(code->At(i+1),code->At(i+2),code->At(i+3),code->At(i+4));
				i += 5;
				String str;
				str.resize(len);
				LSize j;
				for(j = 0; j < len; ++j)
					str[j] = code->At(i+j);
				stack.insert(stack.begin() , Cell(str));
				i += j;
				--i;
			}
			else if(code->At(i) == OPC_ARRAY) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				Array arr;
				for(size_t j = 0; j < n; ++j) {
					arr.insert(arr.begin(), stack[0].Get().Copy());
					StackPop(stack);
				}
				stack.insert(stack.begin() , Cell(arr));
			}
			else if (code->At(i) == OPC_REF_ARRAY) {
				SSize n = BuildSSize(code->At(i + 1), code->At(i + 2));
				i += 2;
				Array arr;
				for (size_t j = 0; j < n; ++j) {
					arr.insert(arr.begin(), stack[0].Get().Reference());
					StackPop(stack);
				}
				stack.insert(stack.begin(), Cell(arr));
			}
			else if(code->At(i) == OPC_ARR_ALLOC) {
				if(stack[0].Get().Type() != TypeId::Int) {
					throw Var("The arr_alloc instruction works only with an int on stack's top");
				}
				Array arr(stack[0].Get().GetInt().get_ui());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(arr));
			}
			else if(code->At(i) == OPC_OBJECT) {
				LSize len = BuildLSize(code->At(i+1),code->At(i+2),code->At(i+3),code->At(i+4));
				i += 4;
				Var * r = new Var(Object(BuildCode(code->bin , i+1 , len), me->GetObject().global));
				stack.insert(stack.begin() , Cell(r, true));
				i += len;
			}
			else if(code->At(i) == OPC_OBJECT_EXT) {
				LSize len = BuildLSize(code->At(i + 1), code->At(i + 2), code->At(i + 3), code->At(i + 4));
				i += 4;
				Var * r = new Var(Object(BuildCode(code->bin , i+1 , len), me->GetObject().global));
				r->Extends(stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r, true));
				i += len;
			}
			else if(code->At(i) == OPC_LOAD) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				stack.insert(stack.begin() , Cell(&locals[n], false));
			}
			else if(code->At(i) == OPC_LOAD_C) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				stack.insert(stack.begin() , Cell(new Var(code->consts[n].Reference()), true));
			}
			else if(code->At(i) == OPC_BUILD_OBJ) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				Var * r = new Var(Object(code->codes[n],  me->GetObject().global));
				stack.insert(stack.begin() , Cell(r, true));
			}
			else if(code->At(i) == OPC_BUILD_OBJEXT) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				Var * r = new Var(Object(code->codes[n], me->GetObject().global));
				r->Extends(stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r, true));
			}
			else if(code->At(i) == OPC_LOAD_NS) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				stack.insert(stack.begin() , Cell(&namespaces[s]));
			}
			else if(code->At(i) == OPC_ARGS) {
				stack.insert(stack.begin() , Cell(&args));
			}
			else if(code->At(i) == OPC_ME) {
				stack.insert(stack.begin() , Cell(me));
			}
			else if(code->At(i) == OPC_ME_PARENT) {
				Var * p = me->GetObject().parent;
				if(p == nullptr)
					stack.insert(stack.begin() , Cell(new Var(),true));
				else stack.insert(stack.begin() , Cell(p));
			}
			else if(code->At(i) == OPC_PARENT) {
				if(stack[0].Get().Type() != TypeId::Object)
					throw Var("You can get only the parent of an object");
				Var * p = stack[0].Get().GetObject().parent;
				StackPop(stack);
				if(p == nullptr)
					stack.insert(stack.begin() , Cell(new Var(),true));
				else stack.insert(stack.begin() , Cell(p));
			}
			else if(code->At(i) == OPC_GLOBAL) {
				stack.insert(stack.begin() , Cell(me->GetObject().global));
			}
			else if(code->At(i) == OPC_MAIN) {
				stack.insert(stack.begin() , Cell(&mainObj));
			}
			else if(code->At(i) == OPC_ERROR) {
				stack.insert(stack.begin() , Cell(&error));
			}
			else if(code->At(i) == OPC_ME_MEMBER) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				if(me->GetObject().members[s].Type() == TypeId::Object)
					me->GetObject().members[s].GetObject().SetParent(*me);
				stack.insert(stack.begin() , Cell(&me->GetObject().members[s]));
			}
			else if(code->At(i) == OPC_PARENT_MEMBER) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				Var * p = me->GetObject().parent;
				if(p == nullptr)
					throw Var("the object does not have a parent");
				if(p->GetObject().members[s].Type() == TypeId::Object)
					p->GetObject().members[s].GetObject().SetParent(*p);
				stack.insert(stack.begin() , Cell(&p->GetObject().members[s]));
			}
			else if(code->At(i) == OPC_MEMBER) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				if(stack[0].Get().Type() == TypeId::Object) {
					if(stack[0].Get().GetObject().members.find(s) == stack[0].Get().GetObject().members.end())
						throw Var("\'" + s + "\' is not a member of the object");
					if(stack[0].Get().GetObject().modifiers[s] == true)
						throw Var("\'" + s + "\' is private");
					if(stack[0].Get().GetObject().members[s].Type() == TypeId::Object)
						stack[0].Get().GetObject().members[s].GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(&stack[0].Get().GetObject().members[s]));
					StackPop(stack, 1);
				}
				else if(stack[0].Get().Type() == TypeId::Int) {
					Var * r;
					if(s == "ToString")
						r = new Var(Object(&any_ToString));
					else if(s == "ToBool")
						r = new Var(Object(&any_ToBool));
					else if(s == "ToFloat")
						r = new Var(Object(&int_ToFloat));
					else if(s == "ToChar")
						r = new Var(Object(&int_ToChar));
					else throw Var("\'" + s + "\' is not a member of the int type");
					r->GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(r, true));
					StackPop(stack, 1);
				}
				else if(stack[0].Get().Type() == TypeId::Float) {
					Var * r;
					if(s == "ToString")
						r = new Var(Object(&any_ToString));
					else if(s == "ToBool")
						r = new Var(Object(&any_ToBool));
					else if(s == "ToInt")
						r = new Var(Object(&float_ToInt));
					else if(s == "ToChar")
						r = new Var(Object(&float_ToChar));
					else if (s == "GetPrec")
						r = new Var(Object(&float_GetPrec));
					else if (s == "SetPrec")
						r = new Var(Object(&float_SetPrec));
					else throw Var("\'" + s + "\' is not a member of the float type");
					r->GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(r, true));
					StackPop(stack, 1);
				}
				else if(stack[0].Get().Type() == TypeId::Char) {
					Var * r;
					if(s == "ToString")
						r = new Var(Object(&any_ToString));
					else if(s == "ToBool")
						r = new Var(Object(&any_ToBool));
					else if(s == "ToInt")
						r = new Var(Object(&char_ToInt));
					else if(s == "ToFloat")
						r = new Var(Object(&char_ToFloat));
					else if(s == "IsDigit")
						r = new Var(Object(&char_IsDigit));
					else if(s == "IsUpper")
						r = new Var(Object(&char_IsUpper));
					else if(s == "IsLower")
						r = new Var(Object(&char_IsLower));
					else if(s == "IsLetter")
						r = new Var(Object(&char_IsLetter));
					else if(s == "IsPrintable")
						r = new Var(Object(&char_IsPrintable));
					else if(s == "IsControl")
						r = new Var(Object(&char_IsControl));
					else if(s == "ToUpper")
						r = new Var(Object(&char_ToUpper));
					else if(s == "ToLower")
						r = new Var(Object(&char_ToLower));
					else throw Var("\'" + s + "\' is not a member of the char type");
					r->GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(r, true));
					StackPop(stack, 1);
				}
				else if(stack[0].Get().Type() == TypeId::Bool) {
					Var * r;
					if(s == "ToString")
						r = new Var(Object(&any_ToString));
					else if(s == "ToInt")
						r = new Var(Object(&bool_ToInt));
					else throw Var("\'" + s + "\' is not a member of the bool type");
					r->GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(r, true));
					StackPop(stack, 1);
				}
				else if(stack[0].Get().Type() == TypeId::String) {
					Var * r;
					if(s == "ToString")
						r = new Var(Object(&any_ToString));
					else if(s == "ToInt")
						r = new Var(Object(&string_ToInt));
					else if(s == "ToFloat")
						r = new Var(Object(&string_ToFloat));
					else if(s == "ToArray")
						r = new Var(Object(&string_ToArray));
					else if(s == "Length")
						r = new Var(Object(&string_Length));
					else if(s == "Push")
						r = new Var(Object(&string_Push));
					else if(s == "Pop")
						r = new Var(Object(&string_Pop));
					else if(s == "Find")
						r = new Var(Object(&string_Find));
					else if(s == "RFind")
						r = new Var(Object(&string_RFind));
					else if(s == "First")
						r = new Var(Object(&string_First));
					else if(s == "Last")
						r = new Var(Object(&string_Last));
					else if(s == "SubStr")
						r = new Var(Object(&string_SubStr));
					else if(s == "Replace")
						r = new Var(Object(&string_Replace));
					else if(s == "Trim")
						r = new Var(Object(&string_Trim));
					else if(s == "LTrim")
						r = new Var(Object(&string_LTrim));
					else if(s == "RTrim")
						r = new Var(Object(&string_RTrim));
					else if(s == "Split")
						r = new Var(Object(&string_Split));
					else if(s == "Change")
						r = new Var(Object(&string_Change));
					else if(s == "Clear")
						r = new Var(Object(&string_Clear));
					else throw Var("\'" + s + "\' is not a member of the string type");
					r->GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(r, true));
					StackPop(stack, 1);
				}
				else if(stack[0].Get().Type() == TypeId::Array) {
					Var * r;
					if(s == "ToString")
						r = new Var(Object(&any_ToString));
					else if(s == "Length")
						r = new Var(Object(&array_Length));
					else if(s == "Push")
						r = new Var(Object(&array_Push));
					else if (s == "PushRef")
						r = new Var(Object(&array_PushRef));
					else if(s == "Pop")
						r = new Var(Object(&array_Pop));
					else if(s == "Find")
						r = new Var(Object(&array_Find));
					else if(s == "RFind")
						r = new Var(Object(&array_RFind));
					else if(s == "First")
						r = new Var(Object(&array_First));
					else if(s == "Last")
						r = new Var(Object(&array_Last));
					else if(s == "Clear")
						r = new Var(Object(&array_Clear));
					else throw Var("\'" + s + "\' is not a member of the array type");
					r->GetObject().SetParent(stack[0].Get());
					stack.insert(stack.begin() , Cell(r, true));
					StackPop(stack, 1);
				}
			}
			else if(code->At(i) == OPC_SET_PUBLIC) {
				isPrivate = false;
			}
			else if(code->At(i) == OPC_SET_PRIVATE) {
				isPrivate = true;
			}
			else if(code->At(i) == OPC_CREATE_MEMBER) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				Var * r = me->CreateMember(s, isPrivate);
				if(r->Type() == TypeId::Object)
					r->GetObject().SetParent(*me);
				stack.insert(stack.begin() , Cell(r));
			}
			else if(code->At(i) == OPC_AT) {
				Cell r;
				if(stack[1].Get().Type() == TypeId::Array) {
					if(stack[0].Get().Type() != TypeId::Int)
						throw Var("At operator : the second operand is not an integer");
					size_t pos = stack[0].Get().GetInt().get_ui();
					if(pos >= stack[1].Get().GetArray().size())
						throw Var("At operator : index out of range");
					r = Cell(new Var(stack[1].Get().GetArray()[pos].Reference()), true);
				}
				else if (stack[1].Get().Type() == TypeId::String) {
					if (stack[0].Get().Type() != TypeId::Int)
						throw Var("At operator : the second operand is not an integer");
					size_t pos = stack[0].Get().GetInt().get_ui();
					if (pos >= stack[1].Get().GetString().size())
						throw Var("At operator : index out of range");
					r = Cell(new Var((Char)stack[1].Get().GetString()[pos]));
					r.Get().val->readOnly = true;
				}
				else throw Var("At operator : the first operand must be an array or a string");
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , r);
			}
			else if(code->At(i) == OPC_AT_N) {
				/*LSize n = BuildLSize(code->At(i+1),code->At(i+2),code->At(i+3),code->At(i+4));
				i += 4;
				if(stack[0].Get().Type() != TypeId::Array)
					throw Var("At_n operator : the operand is not an array");
				Var * r = &stack[1].Get().GetArray()[n];
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r));*/
			}
			else if(code->At(i) == OPC_CALL) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				Array arr;
				for(size_t j = 0; j < n; ++j) {
					arr.insert(arr.begin(), stack[0].Get().Reference());
					StackPop(stack);
				}
				Var * r = new Var(stack[0].Get().Call(Var(arr)));
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_CALL_0) {
				Var * r = new Var(stack[0].Get().Call(Var(Array())));
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_CALL_A) {
				if(stack[0].Get().Type() != TypeId::Array)
					throw Var("Call_a instruction : the operand is not an array");
				Var * r = new Var(stack[1].Get().Call(stack[0].Get().Reference()));
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_NEW) {
				SSize n = BuildSSize(code->At(i+1),code->At(i+2));
				i += 2;
				Array arr;
				for(size_t j = 0; j < n; ++j) {
					arr.insert(arr.begin(), stack[0].Get().Reference());
					StackPop(stack);
				}
				Var * r = new Var(stack[0].Get().New(Var(arr)));
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_NEW_0) {
				Var * r = new Var(stack[0].Get().New(Var(Array())));
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_NEW_A) {
				Var * r = new Var(stack[1].Get().New(stack[0].Get().Reference()));
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_STORE) {
				//TODO
				;
			}
			else if(code->At(i) == OPC_DEBUG) {
				cerr << "Debug : " + stack[0].Get().ToString() + "\n";
			}
			else if(code->At(i) == OPC_DELETE) {
				stack[0].Get().Clear();
				StackPop(stack);
			}
			else if(code->At(i) == OPC_EXTENDS) {
				me->Extends(stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_RETURN) {
				returned = stack[0].Get().Reference();
				return 1;
			}
			else if(code->At(i) == OPC_RETURN_NONE) {
				returned = Var();
				return 1;
			}
			else if(code->At(i) == OPC_THROW) {
				throw stack[0].Get().Reference();
			}
			else if(code->At(i) == OPC_PLUS) {
				//TODO , now solved at compile-time
				;
			}
			else if(code->At(i) == OPC_MINUS) {
				Var * r = new Var(-stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_INCR) {
				Var * v = stack[0].v;
				if(v->Type() == TypeId::Char)
					++v->GetChar();
				else if(v->Type() == TypeId::Int)
					++v->GetInt();
				else if(v->Type() == TypeId::Float)
					++v->GetFloat();
				else if(v->Type() == TypeId::Bool)
					v->GetBool() = !v->GetBool();
				else throw Var("The incr instruction works only with a numerical type on stack's top");
			}
			else if(code->At(i) == OPC_DECR) {
				Var * v = stack[0].v;
				if(v->Type() == TypeId::Char)
					--v->GetChar();
				else if(v->Type() == TypeId::Int)
					-v->GetInt();
				else if(v->Type() == TypeId::Float)
					--v->GetFloat();
				else if(v->Type() == TypeId::Bool)
					v->GetBool() = !v->GetBool();
				else throw Var("The decr instruction works only with a numerical type on stack's top");
			}
			else if(code->At(i) == OPC_ADD) {
				Var * r = new Var(stack[1].Get() + stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_SUB) {
				Var * r = new Var(stack[1].Get() - stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_MUL) {
				Var * r = new Var(stack[1].Get() * stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_DIV) {
				Var * r = new Var(stack[1].Get() / stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_MOD) {
				Var * r = new Var(stack[1].Get() % stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_IS_EQ) {
				Var * r = new Var(stack[1].Get() == stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_ISN_EQ) {
				Var * r = new Var(stack[1].Get() != stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_IS_LOW) {
				Var * r = new Var(stack[1].Get() < stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_IS_LOW_EQ) {
				Var * r = new Var(stack[1].Get() <= stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_IS_GRT) {
				Var * r = new Var(stack[1].Get() > stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_IS_GRT_EQ) {
				Var * r = new Var(stack[1].Get() >= stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_LIKE) {
				Var * r = new Var(stack[1].Get().Like(stack[0].Get()));
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_BIT_AND) {
				Var * r = new Var(stack[1].Get() & stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_BIT_OR) {
				Var * r = new Var(stack[1].Get() | stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_BIT_XOR) {
				Var * r = new Var(stack[1].Get() ^ stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_BIT_NOT) {
				Var * r = new Var(~stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_L_SHIFT) {
				Var * r = new Var(stack[1].Get() << stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_R_SHIFT) {
				Var * r = new Var(stack[1].Get() >> stack[0].Get());
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_NOT) {
				Var * r = new Var(!stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if (code->At(i) == OPC_ASSIGN) {
				stack[1].Get().Assign(stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_REF_ASSIGN) {
				stack[1].Get().RefAssign(stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_ADD_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() + stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_SUB_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() - stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_MUL_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() * stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_DIV_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() / stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_MOD_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() % stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_BIT_AND_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() & stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_BIT_OR_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() | stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_BIT_XOR_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() ^ stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_L_SHIFT_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() << stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_R_SHIFT_ASSIGN) {
				stack[1].Get().Assign(stack[1].Get() >> stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_L_BIND) {
				stack[1].Get().Bind(stack[0].Get());
				StackPop(stack);
			}
			else if(code->At(i) == OPC_R_BIND) {
				stack[0].Get().Bind(stack[1].Get());
				StackPop(stack, 1);
			}
			else if(code->At(i) == OPC_LOAD_LIB) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				LoadLib(s);
			}
			else if(code->At(i) == OPC_ADD_LIB) {
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				if(namespaces.find(s) == namespaces.end())
					LoadLib(s);
			}
			else if(code->At(i) == OPC_LOAD_LIB_S) {
				if(stack[0].Get().Type() != TypeId::String) {
					throw Var("The load_lib_s instruction works only with a string on stack's top");
				}
				string s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				LoadLib(stack[0].Get().GetString(), s);
			}
			else if(code->At(i) == OPC_ADD_LIB_S) {
				if(stack[0].Get().Type() != TypeId::String) {
					throw Var("The add_lib_s instruction works only with a string on stack's top");
				}
				String s = "";
				for(++i; code->At(i) != 0x03; ++i)
					s += code->At(i);
				if(namespaces.find(s) == namespaces.end())
					LoadLib(stack[0].Get().GetString(), s);
			}
			else if(code->At(i) == OPC_JUMP) {
				LSize n = BuildLSize(code->At(i+1), code->At(i+2), code->At(i+3), code->At(i+4));
				i += n + 4;
			}
			else if(code->At(i) == OPC_JUMP_IF) {
				LSize n = BuildLSize(code->At(i+1), code->At(i+2), code->At(i+3), code->At(i+4));
				i += 4;
				if(stack[0].Get().Type() == TypeId::Bool) {
					if(stack[0].Get().GetBool())
						i += n;
				}
				else if(stack[0].Get().Type() == TypeId::Int) {
					if(stack[0].Get().GetInt().get_si())
						i += n;
				}
				else if(stack[0].Get().Type() == TypeId::Float) {
					if(stack[0].Get().GetFloat().get_si())
						i += n;
				}
				else if(stack[0].Get().Type() == TypeId::Char) {
					if(stack[0].Get().GetChar())
						i += n;
				}
			}
			else if(code->At(i) == OPC_JUMP_IFNOT) {
				LSize n = BuildLSize(code->At(i+1), code->At(i+2), code->At(i+3), code->At(i+4));
				i += 4;
				if(stack[0].Get().Type() == TypeId::Bool) {
					if(!stack[0].Get().GetBool())
						i += n;
				}
				else if(stack[0].Get().Type() == TypeId::None) {
					i += n;
				}
				else if(stack[0].Get().Type() == TypeId::Int) {
					if(!stack[0].Get().GetInt().get_si())
						i += n;
				}
				else if(stack[0].Get().Type() == TypeId::Float) {
					if(!stack[0].Get().GetFloat().get_si())
						i += n;
				}
				else if(stack[0].Get().Type() == TypeId::Char) {
					if(!stack[0].Get().GetChar())
						i += n;
				}
			}
			else if(code->At(i) == OPC_JUMP_BACK) {
				LSize n = BuildLSize(code->At(i+1), code->At(i+2), code->At(i+3), code->At(i+4));
				i -= n +1;
			}
			else if(code->At(i) == OPC_TRY) {
				LSize n = BuildLSize(code->At(i+1), code->At(i+2), code->At(i+3), code->At(i+4));
				i += 4;
				tryBegin.push_back(i);
				tryEnd.push_back(n + i);
			}
			else if(code->At(i) == OPC_CATCH) {
				LSize n = BuildLSize(code->At(i+1), code->At(i+2), code->At(i+3), code->At(i+4));
				i += n + 4;
			}
			else if(code->At(i) == OPC_TOBOOL) {
				stack.insert(stack.begin() , Cell(new Var(stack[0].Get().ToBool()) , true));
				StackPop(stack, 1);
			}
			else if(code->At(i) == OPC_TYPEID) {
				Char t = (Char)stack[0].Get().Type();
				StackPop(stack);
				stack.insert(stack.begin() , Cell(new Var(t) , true));
			}
			else if(code->At(i) == OPC_TYPESTR) {
				String t = TypeStr(stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(new Var(t) , true));
			}
			else if(code->At(i) == OPC_ADDROF) {
				Int t = AddressOf(stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(new Var(t) , true));
			}
			else if(code->At(i) == OPC_IDOF) {
				Int t = IdOf(stack[0].Get());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(new Var(t) , true));
			}
			else if(code->At(i) == OPC_EXTERNAL) {
				if(stack[0].Get().Type() != TypeId::String || stack[1].Get().Type() != TypeId::String)
					throw Var("The external instruction works only with two strings at the stack's top");
				Var * r = new Var(Object(External(stack[1].Get().GetString(), stack[0].Get().GetString())));
				StackPop(stack);
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_SET_RDONLY) {
				if(stack[0].Get().val == nullptr)
					stack[0].Get().val = new Var::Value();
				stack[0].Get().val->readOnly = true;
			}
			else if(code->At(i) == OPC_MOVE) {
				Var * r = new Var(Move(stack[0].Get()));
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_COPY) {
				Var * r = new Var(stack[0].Get().Copy());
				StackPop(stack);
				stack.insert(stack.begin() , Cell(r , true));
			}
			else if(code->At(i) == OPC_SWAP) {
				Swap(stack[1].Get(), stack[0].Get());
			}
			else if(code->At(i) == OPC_FOREACH) {
				//TOFIX the program may crash sometimes due to an ignote issue
				SSize n1 = BuildSSize(code->At(i+1),code->At(i+2));
				LSize n2 = BuildLSize(code->At(i+3),code->At(i+4),code->At(i+5),code->At(i+6));
				i += 6;
				forArr * a = &forMap[n1];
				if(!a->pos) {
					if(stack[0].Get().Type() != TypeId::Array)
						throw Var("The foreach instruction works only with an array at the stack's top");
					a->v = stack[0].Get().Reference();
					StackPop(stack);
				}
				if(a->pos >= a->v.GetArray().size()) {
					i += n2;
					a->v.Clear();
					forMap.erase(n1);
				}
				else {
					//cerr<<"S "<<a->v.GetArray().size() <<"  "<< a->pos << endl;
					locals[n1].Bind(a->v.GetArray()[a->pos]);
					++a->pos;
				}
			}
			else if(code->At(i) == OPC_SET_DBG_INFO) {
				dbgCache = "";
				for(++i; code->At(i) != 0x03; ++i)
					dbgCache += code->At(i);
			}
			else if(code->At(i) == NO_OP) {
				continue;
			}
			else {
				throw Var("Invalid opcode 0x" + toHexStr(code->At(i)));
			}
		}
		catch(Var err) {
			while(tryEnd.size() > 0 && (i > tryEnd[tryEnd.size() -1] || i < tryBegin[tryBegin.size() -1])) {
				tryBegin.erase(tryBegin.end() -1);
				tryEnd.erase(tryEnd.end() -1);
			}
			if(tryEnd.size() > 0) {
				i = tryEnd[tryEnd.size() -1] +1;
				error.Clear();
				error = err;
				if(code->At(i) == OPC_CATCH)
					i += 4;
				else --i;
				debugInfo = "";
			}
			else {
				debugInfo = dbgCache + debugInfo;
				throw err;
			}
		}
	}
	return 0;
}

