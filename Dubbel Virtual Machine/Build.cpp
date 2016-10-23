/*
 * Build.cpp
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

LSize dubbel::BuildLSize(Char a , Char b , Char c , Char d) {
	LSize result = (LSize)((a & 0xFF) << 24);
	result |= (LSize)((b & 0xFF) << 16);
	result |= (LSize)((c & 0xFF) << 8);
	result |= (LSize)(d & 0xFF);
	return result;
}


SSize dubbel::BuildSSize(Char a , Char b) {
	LSize result = (SSize)((a & 0xFF) << 8);
	result |= (SSize)(b & 0xFF);
	return result;
}


Int dubbel::BuildInt(const String & s , LSize & used , LSize begin) {
	Int i;
	used = BuildLSize(s[begin+1],s[begin+2],s[begin+3],s[begin+4]);
	mpz_import(i.get_mpz_t(), used, 1, 1, -1, 0, (char*)s.substr(begin+5 , used).c_str() );
	used += 5;
	if(s[begin])
		return -i;
	return i;
}


Float dubbel::BuildFloat(const String & s , LSize & used , LSize begin) {
	Float f;
	Int i;
	LSize exp = BuildLSize(s[begin],s[begin+1],s[begin+2],s[begin+3]);
	LSize prec = BuildLSize(s[begin+4],s[begin+5],s[begin+6],s[begin+7]);
	f.set_prec(prec);
	used = BuildLSize(s[begin+9],s[begin+10],s[begin+11],s[begin+12]);
	mpz_import(i.get_mpz_t(), used, 1, 1, -1, 0, (char *)s.substr(begin+13 , used).c_str() );
	used += 13;
	f = i;
	f.get_mpf_t()->_mp_exp = exp;
	if(s[begin+8])
		return -f;
	return f;
}


Float dubbel::BuildFloat64(const String & s , LSize & used , LSize begin) {
	Float f;
	f.set_prec(64);
	Int i;
	LSize exp = BuildLSize(s[begin],s[begin+1],s[begin+2],s[begin+3]);
	used = BuildLSize(s[begin+5],s[begin+6],s[begin+7],s[begin+8]);
	mpz_import(i.get_mpz_t(), used, 1, 1, -1, 0, (char *)s.substr(begin+9 , used).c_str() );
	used += 9;
	f = i;
	f.get_mpf_t()->_mp_exp = exp;
	if(s[begin+4])
		return -f;
	return f;
}



Code * dubbel::BuildCode(const String & s , LSize begin , LSize end) {
	Code * c = new Code();
	SSize constSize = BuildSSize(s[begin] , s[begin+1]);
	SSize codesSize = BuildSSize(s[begin+2] , s[begin+3]);
	c->localsSize = BuildSSize(s[begin+4] , s[begin+5]);
	begin += 6;
	c->consts.reserve(constSize);
	c->codes.reserve(codesSize);
	
	LSize i;
	for(i = begin; i < end; ++i) {
		//cerr << "BUILD [pos] " << std::dec << i << "\t[val]  dec:" << ((unsigned int)s.at(i) & 0xFF) << "\thex:" << std::hex << ((unsigned int)s.at(i) & 0xFF) << std::dec << endl;
		if(s[i] == OPC_$INT) {
			LSize used;
			c->consts.push_back(Var(BuildInt(s , used , i+1), true));
			i += used;
		}
		else if(s[i] == OPC_$FLOAT) {
			LSize used;
			c->consts.push_back(Var(BuildFloat(s , used , i+1), true));
			i += used;
		}
		else if(s[i] == OPC_$FLOAT64) {
			LSize used;
			c->consts.push_back(Var(BuildFloat64(s , used , i+1), true));
			i += used;
		}
		else if(s[i] == OPC_$STRING) {
			LSize len = BuildLSize(s[i+1],s[i+2],s[i+3],s[i+4]);
			i += 5;
			String str;
			str.resize(len);
			LSize j;
			for(j = 0; j < len; ++j)
				str[j] = s[i+j];
			c->consts.push_back(Var(str, true));
			i += j;
			--i;
		}
		else if(s[i] == OPC_$CODE) {
			LSize len = BuildLSize(s[i+1],s[i+2],s[i+3],s[i+4]);
			i += 5;
			c->codes.push_back(BuildCode(s , i , i+len));
			i = i + len -1;
		}
		else break;
	}
	c->bin = s.substr(i, end - i);
	return c;
}


