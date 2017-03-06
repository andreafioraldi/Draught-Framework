/*
 * Cell.cpp
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

void dubbel::Var::Cell::Clear() {
	if(isConst) {
		v->Clear();
		delete v;
	}
	v = nullptr;
	isConst = false;
}

Var & dubbel::Var::Cell::Get() {
	return *v;
}

dubbel::Var::Cell::Cell(Var * p , bool iscst) {
	v = p;
	isConst = iscst;
}

dubbel::Var::Cell::Cell(Char t) {
	v = new Var(t);
	isConst = true;
}

dubbel::Var::Cell::Cell(Int t) {
	v = new Var(t);
	isConst = true;
}

dubbel::Var::Cell::Cell(Float t) {
	v = new Var(t);
	isConst = true;
}
	
dubbel::Var::Cell::Cell(Bool t) {
	v = new Var(t);
	isConst = true;
}

dubbel::Var::Cell::Cell(String t) {
	v = new Var(t);
	isConst = true;
}

dubbel::Var::Cell::Cell(Array t) {
	v = new Var(t);
	isConst = true;
}

dubbel::Var::Cell::Cell(Object t) {
	v = new Var(t);
	isConst = true;
}


