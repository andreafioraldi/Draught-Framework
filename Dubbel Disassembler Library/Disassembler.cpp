/*
 * Disassembler.cpp
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Disassembler Library.
 * 
 * Dubbel Disassembler Library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Disassembler Library is distributed in the hope that it will be useful,
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
 
#include "DubbelDisassembler.h"
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace dubbel;
using namespace std;

template<class T>
String uiToStr(T i) {
	stringstream convert;
	convert << i;
	return convert.str();
}

void adjustStr(String & str) {
	for(size_t i = 0; i < str.size(); ++i) {
		if(str[i] == '\\') {
			str[i] = '\\';
			str.insert(str.begin() + i, '\\');
			++i;
		}
		else if(str[i] == '\n') {
			str[i] = 'n';
			str.insert(str.begin() + i, '\\');
			++i;
		}
		else if(str[i] == '\t') {
			str[i] = 't';
			str.insert(str.begin() + i, '\\');
			++i;
		}
		else if(str[i] == '\b') {
			str[i] = 'b';
			str.insert(str.begin() + i, '\\');
			++i;
		}
		else if(str[i] == '\r') {
			str[i] = 'n';
			str.insert(str.begin() + i, '\\');
			++i;
		}
		else if(str[i] == '\v') {
			str[i] = 'n';
			str.insert(str.begin() + i, '\\');
			++i;
		}
		else if(!isprint(str[i])) {
			stringstream convert;
			convert << hex << (static_cast<int>(str[i]) & 0xFF);
			String ss = "x" + convert.str();
			str.insert(str.begin() + i +1, ss.begin(), ss.end());
			str[i] = '\\';
			i += ss.size();
		}
	}
}


LSize buildLSize(Char a , Char b , Char c , Char d) {
	LSize result = (LSize)((a & 0xFF) << 24);
	result |= (LSize)((b & 0xFF) << 16);
	result |= (LSize)((c & 0xFF) << 8);
	result |= (LSize)(d & 0xFF);
	return result;
}

SSize buildSSize(Char a , Char b) {
	LSize result = (SSize)((a & 0xFF) << 8);
	result |= (SSize)(b & 0xFF);
	return result;
}


Int buildInt(const String & s , LSize & used , LSize begin) {
	Int i;
	used = buildLSize(s[begin+1],s[begin+2],s[begin+3],s[begin+4]);
	mpz_import(i.get_mpz_t(), used, 1, 1, -1, 0, (char *)s.substr(begin+5 , used).c_str() );
	used += 5;
	if(s[begin])
		return -i;
	return i;
}


Float buildFloat(const String & s , LSize & used , LSize begin) {
	Float f;
	Int i;
	LSize exp = buildLSize(s[begin],s[begin+1],s[begin+2],s[begin+3]);
	LSize prec = buildLSize(s[begin+4],s[begin+5],s[begin+6],s[begin+7]);
	f.set_prec(prec);
	used = buildLSize(s[begin+9],s[begin+10],s[begin+11],s[begin+12]);
	mpz_import(i.get_mpz_t(), used, 1, 1, -1, 0, (char *)s.substr(begin+13 , used).c_str() );
	used += 13;
	f = i;
	f.get_mpf_t()->_mp_exp = exp;
	if(s[begin+8])
		return -f;
	return f;
}


Float buildFloat64(const String & s , LSize & used , LSize begin) {
	Float f;
	f.set_prec(64);
	Int i;
	LSize exp = buildLSize(s[begin],s[begin+1],s[begin+2],s[begin+3]);
	used = buildLSize(s[begin+5],s[begin+6],s[begin+7],s[begin+8]);
	mpz_import(i.get_mpz_t(), used, 1, 1, -1, 0, (char *)s.substr(begin+9 , used).c_str() );
	used += 9;
	f = i;
	f.get_mpf_t()->_mp_exp = exp;
	if(s[begin+4])
		return -f;
	return f;
}

String dubbel::Disassembler(const String & s , size_t tabs) {
	String output = "";
	map<SSize, String> constsMap;
	size_t constsC = 0;
	vector<LSize> closeBracket;
	for(LSize i = 0; i < s.size(); ++i) {
		LSize ii = i;
		String out = "";
		for(size_t ct = 0; ct < tabs; ++ct)
			out += "  ";
		if(s[i] == OPC_EXIT) {
			out += "exit\n";
		}
		else if(s[i] == OPC_STACK_CLEAR) {
			out += "stack_clear\n";
		}
		else if(s[i] == OPC_STACK_POP) {
			out += "stack_pop\n";
		}
		else if(s[i] == OPC_STACK_SWAP) {
			out += "stack_swap\n";
		}
		else if(s[i] == OPC_STACK_DUP) {
			out += "stack_dup\n";
		}
		else if(s[i] == OPC_$INT) {
			LSize used;
			String str = buildInt(s , used , i+1).get_str();
			out += "$int " + str + "\n";
			constsMap[constsC++] = str;
			i += used;
		}
		else if(s[i] == OPC_$FLOAT) {
			LSize used;
			mp_exp_t exp;
			int c = 0;
			Float f = buildFloat(s , used , i+1);
			String str = f.get_str(exp);
			i += used;
			if(sgn(f) == -1)
				c = 1;
			if(str.size() == 0) {
				out += "$float 0.0 " + uiToStr(f.get_prec()) + "\n";
				constsMap[constsC++] = str;
				continue;
			}
			if(exp < 0) {
				size_t cc = -exp;
				for(size_t j = 0;j < cc;++j) {
					str = "0" + str;
					exp++;
				}
			}
			size_t ss = str.size();
			for(size_t j = exp; j > ss; --j)
				str += "0";
			str.insert(str.begin() +exp +c, '.');
			if(str[0] == '.')
				str = "0" + str;
			else if(str[str.size()-1] == '.')
				str += "0";
			out += "$float " + str + " " + uiToStr(f.get_prec()) + "\n";
			constsMap[constsC++] = str;
		}
		else if(s[i] == OPC_$FLOAT64) {
			LSize used;
			mp_exp_t exp;
			int c = 0;
			Float f = buildFloat64(s , used , i+1);
			String str = f.get_str(exp);
			i += used;
			if(sgn(f) == -1)
				c = 1;
			if(str.size() == 0) {
				out += "$float64 0.0\n";
				constsMap[constsC++] = str;
				continue;
			}
			if(exp < 0) {
				size_t cc = -exp;
				for(size_t j = 0;j < cc;++j) {
					str = "0" + str;
					exp++;
				}
			}
			size_t ss = str.size();
			for(size_t j = exp; j > ss; --j)
				str += "0";
			str.insert(str.begin() +exp +c, '.');
			if(str[0] == '.')
				str = "0" + str;
			else if(str[str.size()-1] == '.')
				str += "0";
			out += "$float64 " + str + "\n";
			constsMap[constsC++] = str;
		}
		else if(s[i] == OPC_$STRING) {
			LSize len = buildLSize(s[i+1],s[i+2],s[i+3],s[i+4]);
			i += 5;
			String str;
			LSize j;
			for(j = 0; j < len; ++j)
				str += s[i+j];
			adjustStr(str);
			out += "$string \"" + str + "\"\n";
			i += j;
			--i;
			constsMap[constsC++] = "\"" + str + "\"";
		}
		else if(s[i] == OPC_$CODE) {
			LSize len = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			SSize consts = buildSSize(s[i+5],s[i+6]);
			SSize codes = buildSSize(s[i+7],s[i+8]);
			SSize locals = buildSSize(s[i+9],s[i+10]);
			i += 11;
			out += "$code [consts] " + uiToStr(consts) + "  [codes] " + uiToStr(codes) + "  [locals] " + uiToStr(locals) + "\n";
			out += "    \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "{\n";
			out += Disassembler(String(s, i, len-6) , tabs+1);
			out += "    \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "}\n";
			i = i + len -7;
		}
		else if(s[i] == OPC_NONE) {
			out += "none\n";
		}
		else if(s[i] == OPC_CHAR) {
			out += "char \"";
			out += s[i+1];
			out += "\"\n";
			++i;
		}
		else if(s[i] == OPC_INT) {
			LSize used;
			out += "int " + buildInt(s , used , i+1).get_str() + "\n";
			i += used;
		}
		else if(s[i] == OPC_FLOAT) {
			LSize used;
			mp_exp_t exp;
			int c = 0;
			Float f = buildFloat(s , used , i+1);
			String str = f.get_str(exp);
			i += used;
			if(sgn(f) == -1)
				c = 1;
			if(str.size() == 0) {
				out += "float 0.0 " + uiToStr(f.get_prec()) + "\n";
				constsMap[constsC++] = str;
				continue;
			}
			if(exp < 0) {
				size_t cc = -exp;
				for(size_t j = 0;j < cc;++j) {
					str = "0" + str;
					exp++;
				}
			}
			size_t ss = str.size();
			for(size_t j = exp; j > ss; --j)
				str += "0";
			str.insert(str.begin() +exp +c, '.');
			if(str[0] == '.')
				str = "0" + str;
			else if(str[str.size()-1] == '.')
				str += "0";
			out += "float " + str + " " + uiToStr(f.get_prec()) + "\n";
		}
		else if(s[i] == OPC_FLOAT64) {
			LSize used;
			mp_exp_t exp;
			int c = 0;
			Float f = buildFloat64(s , used , i+1);
			String str = f.get_str(exp);
			i += used;
			if(sgn(f) == -1)
				c = 1;
			if(str.size() == 0) {
				out += "float64 0.0\n";
				constsMap[constsC++] = str;
				continue;
			}
			if(exp < 0) {
				size_t cc = -exp;
				for(size_t j = 0;j < cc;++j) {
					str = "0" + str;
					exp++;
				}
			}
			size_t ss = str.size();
			for(size_t j = exp; j > ss; --j)
				str += "0";
			str.insert(str.begin() +exp +c, '.');
			if(str[0] == '.')
				str = "0" + str;
			else if(str[str.size()-1] == '.')
				str += "0";
			out += "float64 " + str + "\n";
		}
		else if(s[i] == OPC_TRUE) {
			out += "true\n";
		}
		else if(s[i] == OPC_FALSE) {
			out += "false\n";
		}
		else if(s[i] == OPC_STRING) {
			LSize len = buildLSize(s[i+1],s[i+2],s[i+3],s[i+4]);
			i += 5;
			String str;
			LSize j;
			for(j = 0; j < len; ++j)
				str += s[i+j];
			adjustStr(str);
			out += "string \"" + str + "\"\n";
			i += j;
			--i;
		}
		else if(s[i] == OPC_ARRAY) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "array " + uiToStr(n) + "\n";
		}
		else if (s[i] == OPC_REF_ARRAY) {
			SSize n = buildSSize(s[i + 1], s[i + 2]);
			i += 2;
			out += "ref_array " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_ARR_ALLOC) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "arr_alloc " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_OBJECT) {
			LSize len = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			SSize consts = buildSSize(s[i+5],s[i+6]);
			SSize codes = buildSSize(s[i+7],s[i+8]);
			SSize locals = buildSSize(s[i+9],s[i+10]);
			i += 11;
			out += "object [consts] " + uiToStr(consts) + "  [codes] " + uiToStr(codes) + "  [locals] " + uiToStr(locals) + "\n";
			out += "    \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "{\n";
			out += Disassembler(String(s, i, len-6) , tabs+1);
			out += "    \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "}\n";
			i = i + len -7;
		}
		else if(s[i] == OPC_OBJECT_EXT) {
			LSize len = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			SSize consts = buildSSize(s[i+5],s[i+6]);
			SSize codes = buildSSize(s[i+7],s[i+8]);
			SSize locals = buildSSize(s[i+9],s[i+10]);
			i += 11;
			out += "object_ext [consts] " + uiToStr(consts) + "  [codes] " + uiToStr(codes) + "  [locals] " + uiToStr(locals) + "\n";
			out += "    \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "{\n";
			out += Disassembler(String(s, i, len-6) , tabs+1);
			out += "    \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "}\n";
			i = i + len -7;
		}
		else if(s[i] == OPC_LOAD) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "load " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_LOAD_C) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "load_c " + uiToStr(n) + "	//" + constsMap[n] + "\n";
		}
		else if(s[i] == OPC_BUILD_OBJ) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "build_obj " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_BUILD_OBJEXT) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "build_objext " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_LOAD_NS) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "load_ns \"" + str + "\"\n";
		}
		else if(s[i] == OPC_ARGS) {
			out += "args\n";
		}
		else if(s[i] == OPC_ME) {
			out += "me\n";
		}
		else if(s[i] == OPC_ME_PARENT) {
			out += "me_parent\n";
		}
		else if(s[i] == OPC_PARENT) {
			out += "parent\n";
		}
		else if(s[i] == OPC_GLOBAL) {
			out += "global\n";
		}
		else if(s[i] == OPC_MAIN) {
			out += "main\n";
		}
		else if(s[i] == OPC_ERROR) {
			out += "error\n";
		}
		else if(s[i] == OPC_ME_MEMBER) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "me_member \"" + str + "\"\n";
		}
		else if(s[i] == OPC_PARENT_MEMBER) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "parent_member \"" + str + "\"\n";
		}
		else if(s[i] == OPC_MEMBER) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "member \"" + str + "\"\n";
		}
		else if(s[i] == OPC_SET_PUBLIC) {
			out += "set_public\n";
		}
		else if(s[i] == OPC_SET_PRIVATE) {
			out += "set_private\n";
		}
		else if(s[i] == OPC_CREATE_MEMBER) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "create_member \"" + str + "\"\n";
		}
		else if(s[i] == OPC_AT) {
			out += "at\n";
		}
		else if(s[i] == OPC_AT_N) {
			//TODO
		}
		else if(s[i] == OPC_CALL) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "call " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_CALL_0) {
			out += "call_0\n";
		}
		else if(s[i] == OPC_CALL_A) {
			out += "call_a\n";
		}
		else if(s[i] == OPC_NEW) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "new " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_NEW_0) {
			out += "new_0\n";
		}
		else if(s[i] == OPC_NEW_A) {
			out += "new_a\n";
		}
		else if(s[i] == OPC_STORE) {
			SSize n = buildSSize(s[i+1],s[i+2]);
			i += 2;
			out += "store " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_DEBUG) {
			out += "debug\n";
		}
		else if(s[i] == OPC_DELETE) {
			out += "delete\n";
		}
		else if(s[i] == OPC_EXTENDS) {
			out += "extends\n";
		}
		else if(s[i] == OPC_RETURN) {
			out += "return\n";
		}
		else if(s[i] == OPC_RETURN_NONE) {
			out += "return_none\n";
		}
		else if(s[i] == OPC_THROW) {
			out += "throw\n";
		}
		else if(s[i] == OPC_PLUS) {
			out += "plus\n";
		}
		else if(s[i] == OPC_MINUS) {
			out += "minus\n";
		}
		else if(s[i] == OPC_INCR) {
			out += "incr\n";
		}
		else if(s[i] == OPC_DECR) {
			out += "decr\n";
		}
		else if(s[i] == OPC_ADD) {
			out += "add\n";
		}
		else if(s[i] == OPC_SUB) {
			out += "sub\n";
		}
		else if(s[i] == OPC_MUL) {
			out += "mul\n";
		}
		else if(s[i] == OPC_DIV) {
			out += "div\n";
		}
		else if(s[i] == OPC_MOD) {
			out += "mod\n";
		}
		else if(s[i] == OPC_IS_EQ) {
			out += "is_eq\n";
		}
		else if(s[i] == OPC_ISN_EQ) {
			out += "isn_eq\n";
		}
		else if(s[i] == OPC_IS_LOW) {
			out += "is_low\n";
		}
		else if(s[i] == OPC_IS_LOW_EQ) {
			out += "is_low_eq\n";
		}
		else if(s[i] == OPC_IS_GRT) {
			out += "is_grt\n";
		}
		else if(s[i] == OPC_IS_GRT_EQ) {
			out += "is_grt_eq\n";
		}
		else if(s[i] == OPC_LIKE) {
			out += "like\n";
		}
		else if(s[i] == OPC_BIT_AND) {
			out += "bit_and\n";
		}
		else if(s[i] == OPC_BIT_OR) {
			out += "bit_or\n";
		}
		else if(s[i] == OPC_BIT_XOR) {
			out += "bit_xor\n";
		}
		else if(s[i] == OPC_BIT_NOT) {
			out += "bit_not\n";
		}
		else if(s[i] == OPC_L_SHIFT) {
			out += "l_shift\n";
		}
		else if(s[i] == OPC_R_SHIFT) {
			out += "r_shift\n";
		}
		else if(s[i] == OPC_NOT) {
			out += "not\n";
		}
		else if(s[i] == OPC_ASSIGN) {
			out += "assign\n";
		}
		else if(s[i] == OPC_REF_ASSIGN) {
			out += "ref_assign\n";
		}
		else if(s[i] == OPC_ADD_ASSIGN) {
			out += "add_assign\n";
		}
		else if(s[i] == OPC_SUB_ASSIGN) {
			out += "sub_assign\n";
		}
		else if(s[i] == OPC_MUL_ASSIGN) {
			out += "mul_assign\n";
		}
		else if(s[i] == OPC_DIV_ASSIGN) {
			out += "div_assign\n";
		}
		else if(s[i] == OPC_MOD_ASSIGN) {
			out += "mod_assign\n";
		}
		else if(s[i] == OPC_BIT_AND_ASSIGN) {
			out += "bit_and_assign\n";
		}
		else if(s[i] == OPC_BIT_OR_ASSIGN) {
			out += "bit_or_assign\n";
		}
		else if(s[i] == OPC_BIT_XOR_ASSIGN) {
			out += "bit_xor_assign\n";
		}
		else if(s[i] == OPC_L_SHIFT_ASSIGN) {
			out += "l_shift_assign\n";
		}
		else if(s[i] == OPC_R_SHIFT_ASSIGN) {
			out += "r_shift_assign\n";
		}
		else if(s[i] == OPC_L_BIND) {
			out += "l_bind\n";
		}
		else if(s[i] == OPC_R_BIND) {
			out += "r_bind\n";
		}
		else if(s[i] == OPC_LOAD_LIB) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "load_lib \"" + str + "\"\n";
		}
		else if(s[i] == OPC_ADD_LIB) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "add_lib \"" + str + "\"\n";
		}
		else if(s[i] == OPC_LOAD_LIB_S) {
			out += "add_lib_s\n";
		}
		else if(s[i] == OPC_ADD_LIB) {
			out += "add_lib_s\n";
		}
		else if(s[i] == OPC_JUMP) {
			LSize n = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			i += 4;
			out += "jump " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_JUMP_IF) {
			LSize n = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			i += 4;
			out += "jump_if " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_JUMP_IFNOT) {
			LSize n = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			i += 4;
			out += "jump_ifnot " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_JUMP_BACK) {
			LSize n = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			i += 4;
			out += "jump_back " + uiToStr(n) + "\n";
		}
		else if(s[i] == OPC_TRY) {
			LSize len = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			i += 4;
			out += "try\n";
			out += "   \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "{\n";
			closeBracket.push_back(i+len);
			++tabs;
		}
		else if(s[i] == OPC_CATCH) {
			LSize len = buildLSize(s[i+1], s[i+2], s[i+3], s[i+4]);
			i += 4;
			out += "catch\n";
			out += "   \t";
			for (size_t ct = 0; ct < tabs; ++ct)
				out += "  ";
			out += "{\n";
			closeBracket.push_back(i+len);
			++tabs;
		}
		else if(s[i] == OPC_TOBOOL) {
			out += "tobool\n";
		}
		else if(s[i] == OPC_TYPEID) {
			out += "typeid\n";
		}
		else if(s[i] == OPC_TYPESTR) {
			out += "typestr\n";
		}
		else if(s[i] == OPC_ADDROF) {
			out += "addrof\n";
		}
		else if(s[i] == OPC_IDOF) {
			out += "idof\n";
		}
		else if(s[i] == OPC_EXTERNAL) {
			out += "external\n";
		}
		else if(s[i] == OPC_SET_RDONLY) {
			out += "set_rdonly\n";
		}
		else if(s[i] == OPC_MOVE) {
			out += "move\n";
		}
		else if(s[i] == OPC_COPY) {
			out += "copy\n";
		}
		else if(s[i] == OPC_SWAP) {
			out += "swap\n";
		}
		else if(s[i] == OPC_FOREACH) {
			SSize n1 = buildSSize(s[i+1],s[i+2]);
			LSize n2 = buildLSize(s[i+3],s[i+4],s[i+5],s[i+6]);
			i += 6;
			out += "foreach " + uiToStr(n1) + " " + uiToStr(n2) + "\n";
		}
		else if(s[i] == OPC_SET_DBG_INFO) {
			String str = "";
			for(++i; s[i] != 0x03; ++i)
				str += s[i];
			adjustStr(str);
			out += "set_dbg_info \"" + str + "\"\n";
		}
		else {
			;
		}
		output += "[" + uiToStr(i -ii +1) + "]\t" + out;
		if (find(closeBracket.begin(), closeBracket.end(), i) != closeBracket.end()) {
			--tabs;
			output += "   \t";
			for(size_t ct = 0; ct < tabs; ++ct)
				output += "  ";
			output += "}\n";
		}
	}
	if(find(closeBracket.begin(), closeBracket.end(), s.size()) != closeBracket.end()) {
		--tabs;
		output += "   \t";
		for(size_t ct = 0; ct < tabs; ++ct)
			output += "  ";
		output += "}\n";
	}
	return output;
}


String dubbel::FileDisassembler(const String & s) {
	String out = "";
	out += "//bytecode version: " + uiToStr((unsigned)s[0]) + "\n";
	SSize consts = buildSSize(s[1],s[2]);
	SSize codes = buildSSize(s[3],s[4]);
	SSize locals = buildSSize(s[5],s[6]);
	out += "@head [consts] " + uiToStr(consts) + "  [codes] " + uiToStr(codes) + "  [locals] " + uiToStr(locals) + "\n";
	out += Disassembler(String(s, 7, s.size() -7));
	return out;
}



