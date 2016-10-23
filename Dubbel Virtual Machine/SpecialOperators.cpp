/*
 * SpecialOperators.cpp
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

Var dubbel::Var::New(Var args) {
	if(Type() == TypeId::Object) {
		Var v(GetObject().Copy());
		if (v.GetObject().members.find("_copy") != v.GetObject().members.end() && v.GetObject().members["_copy"].Type() == TypeId::Object) {
			v.GetObject().members["_copy"].GetObject().SetParent(v);
			v.GetObject().members["_copy"].Call(Var(Array())).Clear();
		}
		v.Call(args).Clear();
		return v;
	}
	if(args.GetArray().size() != 0)
		throw Var("New operator : not-object operands with arguments");
	return Copy();
}

Var dubbel::Var::Call(Var args) {
	if(Type() != TypeId::Object)
		throw Var("Call operator : the operand is not an object");
	if(!GetObject().IsInvocable()) {
		throw Var("Call operator : the operand is an not invocable");
	}
	if(GetObject().IsByteCode()) {
		Code * p = static_cast<Code*>(GetObject().content);
		Array locals;
		vector<Cell> stack;
		locals.reserve(p->localsSize); //TODO optimization
		for(SSize i = 0; i < p->localsSize; ++i)
			locals.push_back(Var());
		Var returned;
		try {
			ExecCode(p , this , args , returned , locals , stack);
			//throw a reference
		}
		catch(Var err) {
			while(stack.size() > 0)
				StackPop(stack);
			for(vector<Var>::reverse_iterator i = locals.rbegin(); i != locals.rend(); ++i)
				i->Clear();
			args.Clear();
			throw err;
		}
		while(stack.size() > 0)
			StackPop(stack);
		for(vector<Var>::reverse_iterator i = locals.rbegin(); i != locals.rend(); ++i)
			i->Clear();
		args.Clear();
		return returned;
	}
	else if(GetObject().IsNative()) {
		Var returned(reinterpret_cast<Native>(GetObject().content)(*this , args));
		args.Clear();
		return returned;
	}
}

Var * dubbel::Var::CreateMember(const String & name, Bool isPrivate) {
	GetObject().modifiers[name] = isPrivate;
	return &GetObject().members[name];
}

void dubbel::Var::Extends(Var v) {
	if(Type() != TypeId::Object)
		throw Var("Extends operator : the operand is not an object");
	if(v.Type() != TypeId::Object)
		throw Var("Extends operator : an object must be extended only with another object");
	for(map<String , Var>::reverse_iterator it = v.GetObject().members.rbegin(); it != v.GetObject().members.rend(); ++it) {
		GetObject().members[it->first].Assign(it->second);
		GetObject().modifiers[it->first] = v.GetObject().modifiers[it->first];
	}
}

