/*
 * DubbelBuilder.h
 * 
 * Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
 * 
 * This file is part of Dubbel Builder.
 * 
 * Dubbel Builder is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Dubbel Builder is distributed in the hope that it will be useful,
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

#pragma once

#include <iostream>
#include <vector>

#ifdef _WIN32
#ifdef DubbelBuilder_EXPORTS
#define DUBBEL_BUILDER_API __declspec(dllexport)
#else
#define DUBBEL_BUILDER_API __declspec(dllimport)
#endif
#pragma warning(disable: 4800)
#pragma warning(disable: 4146)
#pragma warning(disable: 4244)
#include "mpirxx.h"
#else
#include <gmpxx.h>
#define DUBBEL_BUILDER_API
#endif

#ifndef DUBBEL_OPCODES
#define DUBBEL_OPCODES

/************************************
    Opcodes list (OPC_ is a prefix)
 ************************************/
#define OPC_EXIT 0 //0x0
#define OPC_STACK_CLEAR 1 //0x1
#define OPC_STACK_POP 2 //0x2
#define OPC_STACK_SWAP 3 //0x3
#define OPC_STACK_DUP 4 //0x4
#define OPC_$INT 5 //0x5
#define OPC_$FLOAT 6 //0x6
#define OPC_$FLOAT64 7 //0x7
#define OPC_$STRING 8 //0x8
#define OPC_$CODE 9 //0x9
#define OPC_NONE 10 //0xa
#define OPC_CHAR 11 //0xb
#define OPC_INT 12 //0xc
#define OPC_FLOAT 13 //0xd
#define OPC_FLOAT64 14 //0xe
#define OPC_TRUE 15 //0xf
#define OPC_FALSE 16 //0x10
#define OPC_STRING 17 //0x11
#define OPC_ARRAY 18 //0x12
#define OPC_REF_ARRAY 19 //0x13
#define OPC_ARR_ALLOC 20 //0x14
#define OPC_OBJECT 21 //0x15
#define OPC_OBJECT_EXT 22 //0x16
#define OPC_LOAD 23 //0x17
#define OPC_LOAD_C 24 //0x18
#define OPC_BUILD_OBJ 25 //0x19
#define OPC_BUILD_OBJEXT 26 //0x1a
#define OPC_LOAD_NS 27 //0x1b
#define OPC_ARGS 28 //0x1c
#define OPC_ME 29 //0x1d
#define OPC_ME_PARENT 30 //0x1e
#define OPC_PARENT 31 //0x1f
#define OPC_GLOBAL 32 //0x20
#define OPC_MAIN 33 //0x21
#define OPC_ERROR 34 //0x22
#define OPC_ME_MEMBER 35 //0x23
#define OPC_PARENT_MEMBER 36 //0x24
#define OPC_MEMBER 37 //0x25
#define OPC_SET_PUBLIC 38 //0x26
#define OPC_SET_PRIVATE 39 //0x27
#define OPC_CREATE_MEMBER 40 //0x28
#define OPC_AT 41 //0x29
#define OPC_AT_N 42 //0x2a
#define OPC_CALL 43 //0x2b
#define OPC_CALL_0 44 //0x2c
#define OPC_CALL_A 45 //0x2d
#define OPC_NEW 46 //0x2e
#define OPC_NEW_0 47 //0x2f
#define OPC_NEW_A 48 //0x30
#define OPC_STORE 49 //0x31
#define OPC_DEBUG 50 //0x32
#define OPC_DELETE 51 //0x33
#define OPC_EXTENDS 52 //0x34
#define OPC_RETURN 53 //0x35
#define OPC_RETURN_NONE 54 //0x36
#define OPC_THROW 55 //0x37
#define OPC_PLUS 56 //0x38
#define OPC_MINUS 57 //0x39
#define OPC_INCR 58 //0x3a
#define OPC_DECR 59 //0x3b
#define OPC_ADD 60 //0x3c
#define OPC_SUB 61 //0x3d
#define OPC_MUL 62 //0x3e
#define OPC_DIV 63 //0x3f
#define OPC_MOD 64 //0x40
#define OPC_IS_EQ 65 //0x41
#define OPC_ISN_EQ 66 //0x42
#define OPC_IS_LOW 67 //0x43
#define OPC_IS_LOW_EQ 68 //0x44
#define OPC_IS_GRT 69 //0x45
#define OPC_IS_GRT_EQ 70 //0x46
#define OPC_LIKE 71 //0x47
#define OPC_BIT_AND 72 //0x48
#define OPC_BIT_OR 73 //0x49
#define OPC_BIT_XOR 74 //0x4a
#define OPC_BIT_NOT 75 //0x4b
#define OPC_L_SHIFT 76 //0x4c
#define OPC_R_SHIFT 77 //0x4d
#define OPC_NOT 78 //0x4e
#define OPC_ASSIGN 79 //0x4f
#define OPC_REF_ASSIGN 80 //0x50
#define OPC_ADD_ASSIGN 81 //0x51
#define OPC_SUB_ASSIGN 82 //0x52
#define OPC_MUL_ASSIGN 83 //0x53
#define OPC_DIV_ASSIGN 84 //0x54
#define OPC_MOD_ASSIGN 85 //0x55
#define OPC_BIT_AND_ASSIGN 86 //0x56
#define OPC_BIT_OR_ASSIGN 87 //0x57
#define OPC_BIT_XOR_ASSIGN 88 //0x58
#define OPC_L_SHIFT_ASSIGN 89 //0x59
#define OPC_R_SHIFT_ASSIGN 90 //0x5a
#define OPC_L_BIND 91 //0x5b
#define OPC_R_BIND 92 //0x5c
#define OPC_LOAD_LIB 93 //0x5d
#define OPC_ADD_LIB 94 //0x5e
#define OPC_LOAD_LIB_S 95 //0x5f
#define OPC_ADD_LIB_S 96 //0x60
#define OPC_JUMP 97 //0x61
#define OPC_JUMP_IF 98 //0x62
#define OPC_JUMP_IFNOT 99 //0x63
#define OPC_JUMP_BACK 100 //0x64
#define OPC_TRY 101 //0x65
#define OPC_CATCH 102 //0x66
#define OPC_TOBOOL 103 //0x67
#define OPC_TYPEID 104 //0x68
#define OPC_TYPESTR 105 //0x69
#define OPC_ADDROF 106 //0x6a
#define OPC_IDOF 107 //0x6b
#define OPC_EXTERNAL 108 //0x6c
#define OPC_SET_RDONLY 109 //0x6d
#define OPC_MOVE 110 //0x6e
#define OPC_COPY 111 //0x6f
#define OPC_SWAP 112 //0x70
#define OPC_FOREACH 113 //0x71
#define OPC_SET_DBG_INFO 114 //0x72

#define NO_OP 125 //0x7d

#define BYTECODE_VER 0

#endif

namespace dubbel {
	
	typedef unsigned char Char;
	typedef mpz_class Int;
	typedef mpf_class Float;
	typedef bool Bool;
	typedef std::string String;

	typedef uint_least16_t SSize;
	typedef uint_least32_t LSize;

	/**
	 * Serialize in binary a 16 bit number (SSize)
	 * @param t the number to convert
	 * @return return the binary representation of the number
	 */
	DUBBEL_BUILDER_API String ToBytes(SSize t);

	/**
	 * Serialize in binary a 32 bit number (LSize)
	 * @param t the number to convert
	 * @return return the binary representation of the number
	 */
	DUBBEL_BUILDER_API String ToBytes(LSize t);

	/**
	 * Serialize in binary a character
	 * @param t the character to convert
	 * @return return the binary representation of the character
	 */
	DUBBEL_BUILDER_API String ToBytes(Char t);

	/**
	 * Serialize in binary an integer
	 * @param t the integer to convert
	 * @return return the binary representation of the integer
	 */
	DUBBEL_BUILDER_API String ToBytes(Int t);

	/**
	 * Serialize in binary a float
	 * Note: the precision is relevant
	 * @param t the float to convert
	 * @return return the binary representation of the float
	 */
	DUBBEL_BUILDER_API String ToBytes(Float t);

	/**
	 * Serialize in binary a float without specifying the precision
	 * Note: the float precison is 64-bit by default in the Dubble VM
	 * @param t the float to convert
	 * @return return the binary representation of the float
	 */
	DUBBEL_BUILDER_API String F64ToBytes(Float t);

	/**
	 * Serialize in binary a boolean
	 * @param t the boolean to convert
	 * @return return the binary representation of the boolean
	 */
	DUBBEL_BUILDER_API String ToBytes(Bool t);

	/**
	 * Serialize in binary a string
	 * @param t the boolean to convert
	 * @return return the binary representation of the string
	 */
	DUBBEL_BUILDER_API String ToBytes(String t);

	
	/**
	 * This struct represents an instruction
	 */
	struct DUBBEL_BUILDER_API Instr {
		Char opcode; /**< the opcode , th first byte of the instruction */
		std::vector<String> args; /**< the arguments in binary */
		
		/**
		 * Constructor of Instr
		 * @param opc the opcode
		 * @param pack... the list of the instruction's arguments
		 */
		template<class... Ts>
		Instr(Char opc , Ts... pack) : args{(ToBytes(pack))...} {
			opcode = opc;
		}
		
		/**
		 * Constructor of Instr with a float as argument
		 * @param opc the opcode
		 * @param t the instruction's argument , a float
		 */
		Instr(Char opc , Float t);
		
		/**
		 * Empty constructor of Instr
		 */
		Instr() {}
		
		/**
		 * Get the number of bytes of the instruction
		 * @return return a size_t 
		 */
		size_t Size();
	};

	/**
	 * A list of instructions with useful methods
	 */
	struct DUBBEL_BUILDER_API InstrList {
		std::vector<Instr> v; /**< the vector that contains the instructions */
		
		/**
		 * Constructor of InstrList
		 * @param pack... the list of instructions to store
		 */
		template<class... Ts>
		InstrList(Ts... pack) : v{pack...} {}
		
		/**
		 * Empty constructor of InstrList
		 */
		InstrList() {}
		
		/**
		 * Add an instruction at the end of the list
		 * @param i the instruction to add
		 */
		void Push(const Instr &i);
		
		/**
		 * Add an instruction at a specified position in the list
		 * @param i the instruction to add
		 * @param pos the position where add the instruction
		 */
		void Push(const Instr &i , size_t pos);
		
		/**
		 * Concatenate an another InstrList at the end of the list
		 * @param l the InstrList to join
		 */
		void Join(const InstrList &l);
		
		/**
		 * Extract and return the last instruction of the list
		 * @return the extracted instruction
		 */
		Instr Pop();
		
		/**
		 * Extract and return the instruction in a specified position in the list
		 * @param pos the position where extract the instruction
		 * @return the extracted instruction
		 */
		Instr Pop(size_t pos);
		
		/**
		* Delete the entire content
		*/
		void Clear();

		/**
		 * Get the number of bytes of the entire list
		 * @return return a size_t 
		 */
		size_t Size();
		
		/**
		 * Get the number of bytes of the list up to a specified position
		 * @param pos position where stop the bytes counting
		 * @return return a size_t 
		 */
		size_t Size(size_t pos);
		
		/**
		 * Get the number of instructions in the list
		 * @return return a size_t 
		 */
		size_t Len();
		
		/**
		 * Access to an instruction in the list
		 * @param pos the position of the targeted instruction
		 * @return return the targeted instruction
		 */
		Instr & operator[](size_t pos);
		
		/**
		 * Convert all instructions in the list in a binary string
		 * @return return a string containing the bytecode
		 */
		String GenerateBytecode();
	};


	/**
	 * A struct that build usable bytecode for the Dubble VM
	 */
	struct DUBBEL_BUILDER_API Builder {
		SSize codesSize = 0; /**< the number of codes declaration in the constant pool */
		SSize constSize = 0; /**< the number of constants declaration in the constant pool */
		SSize localsSize = 0; /**< the number of locals variables used in the body */
		
		InstrList constPool; /**< declaration of constants an codes , executed at loading */
		InstrList body; /**< instructions executed when the object is called */
		
		/**
		 * Add an InstrList that contains a code or a object declaration to the constant pool
		 * @param l the InstrList to add
		 * @return the numbers of codes in the constant pool now
		 */
		SSize AddCode(const InstrList &l);
		
		/**
		 * Add an instruction that contains a constant declaration to the constant pool
		 * @param opc the opcode of the instruction
		 * @param t the argument of the instruction
		 * @return the numbers of constants in the constant pool now
		 */
		template<class... Ts>
		SSize AddConst(Char opc , Ts... pack) {
			++constSize;
			constPool.Push(Instr(opc , pack...));
			return constSize;
		}
		
		/**
		 * Add an instruction to the body
		 * @param opc the opcode of the instruction
		 * @param pack... the list of the instruction's arguments
		 */
		template<class... Ts>
		void Append(Char opc , Ts... pack) {
			body.Push(Instr(opc , pack...));
		}
		
		/**
		 * Add an instruction with an argument to the body
		 * @param opc the opcode of the instruction
		 * @param p the argument of the instruction , a 16 bit number (SSize)
		 */
		void Append(Char opc , SSize p);
		
		/**
		 * Add an instruction without arguments to the body
		 * @param opc the opcode of the instruction
		 */
		void Append(Char opc);
		
		/**
		 * Generate an InstrList that contains the code or object declaration of this instance
		 * @param opc the opcode that describe the declaration
		 * @return the InstrList with the declaration
		 */
		InstrList BuildCode(Char opc);
		
		/**
		 * Generate a binary string that contains the bytecode of this instance as main object
		 * @return the binary string that is the content of a .dubbel file
		 */
		String BuildFile();
	};

}
