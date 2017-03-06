/*
 * Conversion.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Assembler Library.
 * 
 * Dubbel Assembler Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Assembler Library is distributed in the hope that it will be useful,
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
 
#include "DubbelAssembler.h"
#include <sstream>

using namespace std;
using namespace dubbel;

string dubbel::size_tToStr(size_t i) {
	stringstream convert;
	convert << i;
	return convert.str();
}

SSize dubbel::StringToSSize(const String & s) {
	stringstream buffer(s);
	SSize value;
	buffer >> value;
	return value;
}

SSize dubbel::HexToSSize(const String & s) {
	stringstream buffer(s);
	SSize value;
	buffer >> hex >> value;
	return value;
}

SSize dubbel::OctToSSize(const String & s) {
	stringstream buffer(s);
	SSize value;
	buffer >> oct >> value;
	return value;
}

LSize dubbel::StringToLSize(const String & s) {
	stringstream buffer(s);
	LSize value;
	buffer >> dec >> value;
	return value;
}


