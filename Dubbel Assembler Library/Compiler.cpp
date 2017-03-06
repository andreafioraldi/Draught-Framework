/*
 * Compiler.cpp
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

using namespace std;
using namespace dubbel;

void dubbel::Assembler::Compile(const String & code) {
	vector<Line> lines = ScanLines(code);
	Compile(lines);
}

void dubbel::Assembler::Compile(const vector<Line> & lines) {
	if(lines.size() == 0)
		return;
	if(lines[0].words[0] == "@HEAD") {
		if(lines[0].words.size() != 4)
			throw AssemblerErr("<0> : the @HEAD declaration need 3 arguments");
		
		fileHead = "";
		fileHead += (char)BYTECODE_VER; //bytecode version
		fileHead += ToBytes(StringToSSize(lines[0].words[1])); //constN
		fileHead += ToBytes(StringToSSize(lines[0].words[2])); //codesN
		fileHead += ToBytes(StringToSSize(lines[0].words[3])); //localsN
		
		Translate(vector<Line>(lines.begin() +1, lines.end()));
	}
	else Translate(lines);
	SolveLabels();
}


#define hasErr(s)\
	throw AssemblerErr("<" + size_tToStr(lines[i].index) + "> : " + String(s))\
		
#define nullArgsSize()\
	do {\
		if(lines[i].words.size() != 1)\
			hasErr("instruction " + lines[i].words[0] + " does not need arguments");\
	} while(0)
		
#define checkArgsSize(n)\
	do {\
		if(lines[i].words.size() != n +1)\
			hasErr("instruction " + lines[i].words[0] + " needs " #n " arguments");\
	} while(0)

void dubbel::Assembler::Translate(const vector<Line> & lines) {
	bool inConstPool = true;
	
	for(size_t i = 0; i < lines.size(); ++i) {
		if(inConstPool && lines[i].type != LineType::Const)
			inConstPool = false;

		if(lines[i].type == LineType::Label) {
			labels[lines[i].words[0]] = list.Size();
		}
		else if(lines[i].words[0] == "EXIT") {
			nullArgsSize();
			list.Push(Instr(OPC_EXIT));
		}
		else if(lines[i].words[0] == "STACK_CLEAR") {
			nullArgsSize();
			list.Push(Instr(OPC_STACK_CLEAR));
		}
		else if(lines[i].words[0] == "STACK_POP") {
			nullArgsSize();
			list.Push(Instr(OPC_STACK_POP));
		}
		else if(lines[i].words[0] == "STACK_SWAP") {
			nullArgsSize();
			list.Push(Instr(OPC_STACK_SWAP));
		}
		else if(lines[i].words[0] == "STACK_DUP") {
			nullArgsSize();
			list.Push(Instr(OPC_STACK_DUP));
		}
		else if(lines[i].words[0] == "$INT") {
			if(!inConstPool)
				hasErr("instruction $INT can be placed only at the beginning of a block of code");
			
			checkArgsSize(1);
			list.Push(Instr(OPC_$INT, Int(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "$FLOAT") {
			if(!inConstPool)
				hasErr("instruction $FLOAT can be placed only at the beginning of a block of code");
			
			checkArgsSize(2);
			Instr in(OPC_$FLOAT, Float(lines[i].words[1] , StringToLSize(lines[i].words[2])));
			list.Push(in);
		}
		else if(lines[i].words[0] == "$FLOAT64") {
			if(!inConstPool)
				hasErr("instruction $FLOAT64 can be placed only at the beginning of a block of code");
			
			checkArgsSize(1);
			list.Push(Instr(OPC_$FLOAT64, Float(lines[i].words[1] , 64)));
		}
		else if(lines[i].words[0] == "$STRING") {
			if(!inConstPool)
				hasErr("instruction $STRING can be placed only at the beginning of a block of code");
			
			checkArgsSize(1);
			list.Push(Instr(OPC_$STRING, (LSize)(lines[i].words[1].size()), lines[i].words[1]));
		}
		else if(lines[i].words[0] == "$CODE") {
			if(!inConstPool) {
				hasErr("instruction $CODE can be placed only at the beginning of a block of code");
			}
			checkArgsSize(3);
			vector<String> args = lines[i].words;
			if(i > lines.size() -3 || lines[i+1].words[0] != "{")
				hasErr("instruction $CODE needs a code block after");
			i += 2;
			size_t opened = 1;
			size_t j;
			for(j = i; j < lines.size(); ++j) {
				if(lines[j].words[0] == "{")
					++opened;
				else if(lines[j].words[0] == "}")
					--opened;
				if(opened == 0)
					break;
			}
			Assembler as;
			as.Compile(vector<Line>(lines.begin() +i, lines.begin() +j));
			i = j;
			list.Push(Instr(OPC_$CODE, (LSize)(as.list.Size() +6), StringToSSize(args[1]), StringToSSize(args[2]), StringToSSize(args[3])));
			list.Join(as.list);
		}
		else if(lines[i].words[0] == "NONE") {
			nullArgsSize();
			list.Push(Instr(OPC_NONE));
		}
		else if(lines[i].words[0] == "CHAR") {
			checkArgsSize(1);
			list.Push(Instr(OPC_CHAR, (Char)lines[i].words[1][0]));
		}
		else if(lines[i].words[0] == "INT") {
			checkArgsSize(1);
			list.Push(Instr(OPC_INT, Int(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "FLOAT") {
			checkArgsSize(2);
			list.Push(Instr(OPC_FLOAT, Float(lines[i].words[1] , StringToLSize(lines[i].words[2]))));
		}
		else if(lines[i].words[0] == "FLOAT64") {
			checkArgsSize(1);
			list.Push(Instr(OPC_FLOAT64, Float(lines[i].words[1] , 64)));
		}
		else if(lines[i].words[0] == "TRUE") {
			nullArgsSize();
			list.Push(Instr(OPC_TRUE));
		}
		else if(lines[i].words[0] == "FALSE") {
			nullArgsSize();
			list.Push(Instr(OPC_FALSE));
		}
		else if(lines[i].words[0] == "STRING") {
			checkArgsSize(1);
			list.Push(Instr(OPC_STRING, (LSize)(lines[i].words[1].size()), lines[i].words[1]));
		}
		else if(lines[i].words[0] == "ARRAY") {
			checkArgsSize(1);
			list.Push(Instr(OPC_ARRAY, StringToSSize(lines[i].words[1])));
		}
		else if (lines[i].words[0] == "REF_ARRAY") {
			checkArgsSize(1);
			list.Push(Instr(OPC_REF_ARRAY, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "ARR_ALLOC") {
			nullArgsSize();
			list.Push(Instr(OPC_ARR_ALLOC));
		}
		else if(lines[i].words[0] == "OBJECT") {
			checkArgsSize(3);
			vector<String> args = lines[i].words;
			if(i > lines.size() -3 || lines[i+1].words[0] != "{")
				hasErr("instruction OBJECT needs a code block after");
			i += 2;
			size_t opened = 1;
			size_t j;
			for(j = i; j < lines.size(); ++j) {
				if(lines[j].words[0] == "{")
					++opened;
				else if(lines[j].words[0] == "}")
					--opened;
				if(opened == 0)
					break;
			}
			Assembler as;
			as.Compile(vector<Line>(lines.begin() +i, lines.begin() +j));
			i = j;
			list.Push(Instr(OPC_OBJECT, (LSize)(as.list.Size() +6), StringToSSize(args[1]), StringToSSize(args[2]), StringToSSize(args[3])));
			list.Join(as.list);
		}
		else if(lines[i].words[0] == "OBJECT_EXT") {
			checkArgsSize(3);
			vector<String> args = lines[i].words;
			if(i > lines.size() -3 || lines[i+1].words[0] != "{")
				hasErr("instruction OBJECT_EXT needs a code block after");
			i += 2;
			size_t opened = 1;
			size_t j;
			for(j = i; j < lines.size(); ++j) {
				if(lines[j].words[0] == "{")
					++opened;
				else if(lines[j].words[0] == "}")
					--opened;
				if(opened == 0)
					break;
			}
			Assembler as;
			as.Compile(vector<Line>(lines.begin() +i, lines.begin() +j));
			i = j;
			list.Push(Instr(OPC_OBJECT_EXT, (LSize)(as.list.Size() +3), StringToSSize(args[1]), StringToSSize(args[2]), StringToSSize(args[3])));
			list.Join(as.list);
		}
		else if(lines[i].words[0] == "LOAD") {
			checkArgsSize(1);
			list.Push(Instr(OPC_LOAD, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "LOAD_C") {
			checkArgsSize(1);
			list.Push(Instr(OPC_LOAD_C, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "BUILD_OBJ") {
			checkArgsSize(1);
			list.Push(Instr(OPC_BUILD_OBJ, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "BUILD_OBJEXT") {
			checkArgsSize(1);
			list.Push(Instr(OPC_BUILD_OBJEXT, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "LOAD_NS") {
			checkArgsSize(1);
			list.Push(Instr(OPC_LOAD_NS , lines[i].words[1] + "\x03"));
		}
		else if(lines[i].words[0] == "ARGS") {
			nullArgsSize();
			list.Push(Instr(OPC_ARGS));
		}
		else if(lines[i].words[0] == "ME") {
			nullArgsSize();
			list.Push(Instr(OPC_ME));
		}
		else if(lines[i].words[0] == "ME_PARENT") {
			nullArgsSize();
			list.Push(Instr(OPC_ME_PARENT));
		}
		else if(lines[i].words[0] == "PARENT") {
			nullArgsSize();
			list.Push(Instr(OPC_PARENT));
		}
		else if(lines[i].words[0] == "GLOBAL") {
			nullArgsSize();
			list.Push(Instr(OPC_GLOBAL));
		}
		else if(lines[i].words[0] == "MAIN") {
			nullArgsSize();
			list.Push(Instr(OPC_MAIN));
		}
		else if(lines[i].words[0] == "ERROR") {
			nullArgsSize();
			list.Push(Instr(OPC_ERROR));
		}
		else if(lines[i].words[0] == "ME_MEMBER") {
			checkArgsSize(1);
			list.Push(Instr(OPC_ME_MEMBER , lines[i].words[1] + "\x03"));
		}
		else if(lines[i].words[0] == "MEMBER") {
			checkArgsSize(1);
			list.Push(Instr(OPC_MEMBER, lines[i].words[1] + "\x03"));
		}
		else if(lines[i].words[0] == "SET_PUBLIC") {
			nullArgsSize();
			list.Push(Instr(OPC_SET_PUBLIC));
		}
		else if(lines[i].words[0] == "SET_PRIVATE") {
			nullArgsSize();
			list.Push(Instr(OPC_SET_PRIVATE));
		}
		else if(lines[i].words[0] == "CREATE_MEMBER") {
			checkArgsSize(1);
			list.Push(Instr(OPC_CREATE_MEMBER, lines[i].words[1] + "\x03"));
		}
		else if(lines[i].words[0] == "AT") {
			nullArgsSize();
			list.Push(Instr(OPC_AT));
		}
		else if(lines[i].words[0] == "AT_N") {
			checkArgsSize(1);
			list.Push(Instr(OPC_AT_N, StringToLSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "CALL") {
			checkArgsSize(1);
			list.Push(Instr(OPC_CALL, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "CALL_0") {
			nullArgsSize();
			list.Push(Instr(OPC_CALL_0));
		}
		else if(lines[i].words[0] == "CALL_A") {
			nullArgsSize();
			list.Push(Instr(OPC_CALL_A));
		}
		else if(lines[i].words[0] == "NEW") {
			checkArgsSize(1);
			list.Push(Instr(OPC_NEW, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "NEW_0") {
			nullArgsSize();
			list.Push(Instr(OPC_NEW_0));
		}
		else if(lines[i].words[0] == "NEW_A") {
			nullArgsSize();
			list.Push(Instr(OPC_NEW_A));
		}
		else if(lines[i].words[0] == "STORE") {
			checkArgsSize(1);
			list.Push(Instr(OPC_STORE, StringToSSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "DEBUG") {
			nullArgsSize();
			list.Push(Instr(OPC_DEBUG));
		}
		else if(lines[i].words[0] == "DELETE") {
			nullArgsSize();
			list.Push(Instr(OPC_DELETE));
		}
		else if(lines[i].words[0] == "EXTENDS") {
			nullArgsSize();
			list.Push(Instr(OPC_EXTENDS));
		}
		else if(lines[i].words[0] == "RETURN") {
			nullArgsSize();
			list.Push(Instr(OPC_RETURN));
		}
		else if(lines[i].words[0] == "RETURN_NONE") {
			nullArgsSize();
			list.Push(Instr(OPC_RETURN_NONE));
		}
		else if(lines[i].words[0] == "THROW") {
			nullArgsSize();
			list.Push(Instr(OPC_THROW));
		}
		else if(lines[i].words[0] == "PLUS") {
			nullArgsSize();
			list.Push(Instr(OPC_PLUS));
		}
		else if(lines[i].words[0] == "MINUS") {
			nullArgsSize();
			list.Push(Instr(OPC_MINUS));
		}
		else if(lines[i].words[0] == "INCR") {
			nullArgsSize();
			list.Push(Instr(OPC_INCR));
		}
		else if(lines[i].words[0] == "DECR") {
			nullArgsSize();
			list.Push(Instr(OPC_DECR));
		}
		else if(lines[i].words[0] == "ADD") {
			nullArgsSize();
			list.Push(Instr(OPC_ADD));
		}
		else if(lines[i].words[0] == "SUB") {
			nullArgsSize();
			list.Push(Instr(OPC_SUB));
		}
		else if(lines[i].words[0] == "MUL") {
			nullArgsSize();
			list.Push(Instr(OPC_MUL));
		}
		else if(lines[i].words[0] == "DIV") {
			nullArgsSize();
			list.Push(Instr(OPC_DIV));
		}
		else if(lines[i].words[0] == "MOD") {
			nullArgsSize();
			list.Push(Instr(OPC_MOD));
		}
		else if(lines[i].words[0] == "IS_EQ") {
			nullArgsSize();
			list.Push(Instr(OPC_IS_EQ));
		}
		else if(lines[i].words[0] == "ISN_EQ") {
			nullArgsSize();
			list.Push(Instr(OPC_ISN_EQ));
		}
		else if(lines[i].words[0] == "IS_LOW") {
			nullArgsSize();
			list.Push(Instr(OPC_IS_LOW));
		}
		else if(lines[i].words[0] == "IS_LOW_EQ") {
			nullArgsSize();
			list.Push(Instr(OPC_IS_LOW_EQ));
		}
		else if(lines[i].words[0] == "IS_GRT") {
			nullArgsSize();
			list.Push(Instr(OPC_IS_GRT));
		}
		else if(lines[i].words[0] == "IS_GRT_EQ") {
			nullArgsSize();
			list.Push(Instr(OPC_IS_GRT_EQ));
		}
		else if(lines[i].words[0] == "LIKE") {
			nullArgsSize();
			list.Push(Instr(OPC_LIKE));
		}
		else if(lines[i].words[0] == "BIT_AND") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_AND));
		}
		else if(lines[i].words[0] == "BIT_OR") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_OR));
		}
		else if(lines[i].words[0] == "BIT_XOR") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_XOR));
		}
		else if(lines[i].words[0] == "BIT_NOT") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_NOT));
		}
		else if(lines[i].words[0] == "L_SHIFT") {
			nullArgsSize();
			list.Push(Instr(OPC_L_SHIFT));
		}
		else if(lines[i].words[0] == "R_SHIFT") {
			nullArgsSize();
			list.Push(Instr(OPC_R_SHIFT));
		}
		else if(lines[i].words[0] == "NOT") {
			nullArgsSize();
			list.Push(Instr(OPC_NOT));
		}
		else if(lines[i].words[0] == "ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_ASSIGN));
		}
		else if(lines[i].words[0] == "REF_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_REF_ASSIGN));
		}
		else if(lines[i].words[0] == "ADD_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_ADD_ASSIGN));
		}
		else if(lines[i].words[0] == "SUB_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_SUB_ASSIGN));
		}
		else if(lines[i].words[0] == "MUL_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_MUL_ASSIGN));
		}
		else if(lines[i].words[0] == "DIV_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_DIV_ASSIGN));
		}
		else if(lines[i].words[0] == "MOD_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_MOD_ASSIGN));
		}
		else if(lines[i].words[0] == "BIT_AND_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_AND_ASSIGN));
		}
		else if(lines[i].words[0] == "BIT_OR_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_OR_ASSIGN));
		}
		else if(lines[i].words[0] == "BIT_XOR_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_BIT_XOR_ASSIGN));
		}
		else if(lines[i].words[0] == "L_SHIFT_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_L_SHIFT_ASSIGN));
		}
		else if(lines[i].words[0] == "R_SHIFT_ASSIGN") {
			nullArgsSize();
			list.Push(Instr(OPC_R_SHIFT_ASSIGN));
		}
		else if(lines[i].words[0] == "L_BIND") {
			nullArgsSize();
			list.Push(Instr(OPC_L_BIND));
		}
		else if(lines[i].words[0] == "R_BIND") {
			nullArgsSize();
			list.Push(Instr(OPC_R_BIND));
		}
		else if(lines[i].words[0] == "LOAD_LIB") {
			checkArgsSize(1);
			list.Push(Instr(OPC_LOAD_LIB , lines[i].words[1] + "\x03"));
		}
		else if(lines[i].words[0] == "ADD_LIB") {
			checkArgsSize(1);
			list.Push(Instr(OPC_ADD_LIB , lines[i].words[1] + "\x03"));
		}
		else if(lines[i].words[0] == "LOAD_LIB_S") {
			nullArgsSize();
			list.Push(Instr(OPC_LOAD_LIB_S));
		}
		else if(lines[i].words[0] == "ADD_LIB_S") {
			nullArgsSize();
			list.Push(Instr(OPC_ADD_LIB_S));
		}
		else if(lines[i].words[0] == "JUMP") {
			checkArgsSize(1);
			if(lines[i].words[1][0] == ':')
				list.Push(Instr(NO_OP, string("JUMP"), lines[i].words[1]));
			else list.Push(Instr(OPC_JUMP, StringToLSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "JUMP_IF") {
			checkArgsSize(1);
			if(lines[i].words[1][0] == ':')
				list.Push(Instr(NO_OP, string("JUMP_IF"), lines[i].words[1]));
			else list.Push(Instr(OPC_JUMP_IF, StringToLSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "JUMP_IFNOT") {
			checkArgsSize(1);
			if(lines[i].words[1][0] == ':')
				list.Push(Instr(NO_OP, string("JUMP_IFNOT"), lines[i].words[1]));
			else list.Push(Instr(OPC_JUMP_IFNOT, StringToLSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "JUMP_BACK") {
			checkArgsSize(1);
			if(lines[i].words[1][0] == ':')
				list.Push(Instr(NO_OP, string("JUMP_BACK"), lines[i].words[1]));
			else list.Push(Instr(OPC_JUMP_BACK, StringToLSize(lines[i].words[1])));
		}
		else if(lines[i].words[0] == "TRY") {
			nullArgsSize();
			if(i > lines.size() -1 || lines[i+1].words[0] != "{")
				hasErr("instruction TRY needs a code block after");
			i += 2;
			size_t opened = 1;
			size_t j;
			for(j = i; j < lines.size(); ++j) {
				if(lines[j].words[0] == "{")
					++opened;
				else if(lines[j].words[0] == "}")
					--opened;
				if(opened == 0)
					break;
			}
			list.Push(Instr(OPC_TRY, (LSize)0));
			size_t oldS = list.Size();
			size_t pos = list.Len() -1;
			Translate(vector<Line>(lines.begin() +i, lines.begin() +j));
			i = j;
			list[pos] = Instr(OPC_TRY, (LSize)(list.Size() - oldS));
		}
		else if(lines[i].words[0] == "CATCH") {
			nullArgsSize();
			if(i > lines.size() -1 || lines[i+1].words[0] != "{")
				hasErr("instruction CATCH needs a code block after");
			i += 2;
			size_t opened = 1;
			size_t j;
			for(j = i; j < lines.size(); ++j) {
				if(lines[j].words[0] == "{")
					++opened;
				else if(lines[j].words[0] == "}")
					--opened;
				if(opened == 0)
					break;
			}
			list.Push(Instr(OPC_CATCH, (LSize)0));
			size_t oldS = list.Size();
			size_t pos = list.Len() -1;
			Translate(vector<Line>(lines.begin() +i, lines.begin() +j));
			i = j;
			list[pos] = Instr(OPC_CATCH, (LSize)(list.Size() - oldS));
		}
		else if(lines[i].words[0] == "TOBOOL") {
			nullArgsSize();
			list.Push(Instr(OPC_TOBOOL));
		}
		else if(lines[i].words[0] == "TYPEID") {
			nullArgsSize();
			list.Push(Instr(OPC_TYPEID));
		}
		else if(lines[i].words[0] == "TYPESTR") {
			nullArgsSize();
			list.Push(Instr(OPC_TYPESTR));
		}
		else if(lines[i].words[0] == "ADDROF") {
			nullArgsSize();
			list.Push(Instr(OPC_ADDROF));
		}
		else if(lines[i].words[0] == "IDOF") {
			nullArgsSize();
			list.Push(Instr(OPC_IDOF));
		}
		else if(lines[i].words[0] == "EXTERNAL") {
			nullArgsSize();
			list.Push(Instr(OPC_EXTERNAL));
		}
		else if(lines[i].words[0] == "SET_RDONLY") {
			nullArgsSize();
			list.Push(Instr(OPC_SET_RDONLY));
		}
		else if(lines[i].words[0] == "MOVE") {
			nullArgsSize();
			list.Push(Instr(OPC_MOVE));
		}
		else if(lines[i].words[0] == "COPY") {
			nullArgsSize();
			list.Push(Instr(OPC_COPY));
		}
		else if(lines[i].words[0] == "SWAP") {
			nullArgsSize();
			list.Push(Instr(OPC_SWAP));
		}
		else if(lines[i].words[0] == "FOREACH") {
			checkArgsSize(2);
			if(lines[i].words[2][0] == ':')
				list.Push(Instr(NO_OP, string("FOREACH"), lines[i].words[2], StringToSSize(lines[i].words[1])));
			else list.Push(Instr(OPC_FOREACH, StringToSSize(lines[i].words[1]), StringToSSize(lines[i].words[2])));
		}
		else if(lines[i].words[0] == "SET_DBG_INFO") {
			checkArgsSize(1);
			list.Push(Instr(OPC_SET_DBG_INFO , lines[i].words[1] + "\x03"));
		}
		else {
			hasErr("invalid instruction '" + lines[i].words[0] + "'");
		}
	}
}

bool dubbel::Assembler::LabelExist(const String & name) {
	return labels.find(name) != labels.end();
}

void dubbel::Assembler::SolveLabels() {
	size_t bytesC = 0;
	for(size_t i = 0; i < list.Len(); ++i) {
		if(list[i].opcode == NO_OP && list[i].args.size() > 1) {
			if(list[i].args[0] == "JUMP") {
				if(!LabelExist(list[i].args[1]))
					throw AssemblerErr("labels checking fail : label " + list[i].args[1] + " not found");
				if(labels[list[i].args[1]] < bytesC +3)
					throw AssemblerErr("labels checking fail : JUMP cannot jump to the prevoius defined label " + list[i].args[1]);
				
				bytesC += 5; //5 is the size of the JUMP instruction
				list[i] = Instr(OPC_JUMP, (LSize)(labels[list[i].args[1]] - bytesC));
			}
			else if(list[i].args[0] == "JUMP_IF") {
				if(!LabelExist(list[i].args[1]))
					throw AssemblerErr("labels checking fail : label " + list[i].args[1] + " not found");
				if(labels[list[i].args[1]] < bytesC +3)
					throw AssemblerErr("labels checking fail : JUMP_IF cannot jump to the prevoius defined label " + list[i].args[1]);
				
				bytesC += 5; //5 is the size of the JUMP_IF instruction
				list[i] = Instr(OPC_JUMP_IF, (LSize)(labels[list[i].args[1]] - bytesC));
			}
			else if(list[i].args[0] == "JUMP_IFNOT") {
				if(!LabelExist(list[i].args[1]))
					throw AssemblerErr("labels checking fail : label " + list[i].args[1] + " not found");
				if(labels[list[i].args[1]] < bytesC +3)
					throw AssemblerErr("labels checking fail : JUMP_IFNOT cannot jump to the prevoius defined label " + list[i].args[1]);
				
				bytesC += 5; //5 is the size of the JUMP_IFNOT instruction
				list[i] = Instr(OPC_JUMP_IFNOT, (LSize)(labels[list[i].args[1]] - bytesC));
			}
			else if(list[i].args[0] == "JUMP_BACK") {
				if(!LabelExist(list[i].args[1]))
					throw AssemblerErr("labels checking fail : label " + list[i].args[1] + " not found");
				if(labels[list[i].args[1]] > bytesC)
					throw AssemblerErr("labels checking fail : JUMP_BACK cannot jump to the forward defined label " + list[i].args[1]);
				
				list[i] = Instr(OPC_JUMP_BACK, (LSize)(bytesC - labels[list[i].args[1]]));
				bytesC += 5; //5 is the size of the JUMP_BACK instruction
			}
			else if(list[i].args[0] == "FOREACH") {
				if(!LabelExist(list[i].args[1]))
					throw AssemblerErr("labels checking fail : label " + list[i].args[1] + " not found");
				if(labels[list[i].args[1]] < bytesC +5)
					throw AssemblerErr("labels checking fail : FOREACH cannot jump to the prevoius defined label " + list[i].args[1]);
	
				bytesC += 7; //7 is the size of the FOREACH instruction
				list[i] = Instr(OPC_FOREACH, list[i].args[2], (LSize)(labels[list[i].args[1]] - bytesC));
			}
		}
		else bytesC += list[i].Size();
	}
}

void dubbel::Assembler::AddBlock(const InstrList & l) {
	list.Join(l);
}

String dubbel::Assembler::GetBytecode() {
	return fileHead + list.GenerateBytecode();
}


