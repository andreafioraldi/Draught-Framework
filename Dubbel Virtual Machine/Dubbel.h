/*
 * Dubbel.h
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

#pragma once

#include <iostream>
#include <vector>
#include <map>

#ifdef _WIN32
#ifdef DubbelVM_EXPORTS
#define DUBBEL_API __declspec(dllexport)
#else
#define DUBBEL_API __declspec(dllimport)
#endif
#define __NATIVE_EXPORT __declspec(dllexport)
#include "mpirxx.h"
#else
#include <gmpxx.h>
#define DUBBEL_API
#define __NATIVE_EXPORT
#endif

#define NativeDef(name) extern "C" __NATIVE_EXPORT dubbel::Var name(dubbel::Var me , dubbel::Var args)
#define LibInit extern "C" __NATIVE_EXPORT void __li (dubbel::Var me)

/* ** example of native object defnition **
NativeDef(print) {
	for(unsigned i = 0;i < args.GetArray().size();++i) {
		cout << args.GetArray().at(i).ToString();
	}
	return Var();
}
*/

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

	struct Var;

	typedef unsigned char Char;
	typedef mpz_class Int;
	typedef mpf_class Float;
	typedef bool Bool;
	typedef std::string String;
	typedef std::vector<Var> Array;
	typedef Var(*Native)(Var, Var);

	typedef uint_least16_t SSize;
	typedef uint_least32_t LSize;

	/**
	 * Enum with the Dubbel data types
	 */
	enum class TypeId : Char {
		None = 1,
		Char = 2,
		Int = 3,
		Float = 4,
		Bool = 5,
		String = 6,
		Array = 7,
		Object = 8
	};

	/**
	 * Enum with the diffent types of objects
	 */
	enum class ObjFlag : Char {
		NotInvocable,
		ByteCode,
		Native
	};

	/**
	 * This struct is the core of the VM
	 */
	struct DUBBEL_API Var {
		struct Container {}; /**< virtual superclass of Data<T> */

		/**
		 * This struct is used to store different data types like a variant
		 */
		template<class T>
		struct Data : Container {
			T data;
			Data(T t) : data(t) {}
		};

		/**
		 * This struct is the memory unit of the VM
		 * It contains data, type id, reference count and readonly flag
		 */
		struct DUBBEL_API Value {
			Container * ptr = nullptr; /**< data container */
			TypeId type = TypeId::None; /**< type id of the Value instance */
			SSize pointers = 0; /**< reference count used for the garbage collection */
			Bool readOnly = false; /**< readonly flags, inhibits RefAssign when true */
		};

		/**
		 * This struct store all information needed by a bytecode object
		 */
		struct DUBBEL_API Code {
			String bin = "";
			Array consts;
			std::vector<Code *> codes;
			SSize localsSize = 0;

			/**
			 * Get the Char at the position pos in the bin String
			 * @param pos position of the target Char
			 * @return the target Char
			 */
			Char At(size_t pos);

			/**
			 * Delete all Code * pointers in codes and its child recursively
			 * WARNING it is used by RunMain, the explicit use is discouraged
			 */
			void ClearPtr();
		};

		/**
		 * This struct is the object type, it incorporates the concepts of function, class and instance
		 */
		struct DUBBEL_API Object {
			void * content; /**< pointer to native function or Code * instance */
			ObjFlag flags;  /**< type of the Object instance */

			std::map<String, Var> members; /**< attributes of the object */
			std::map<String, Bool> modifiers; /**< modifiers , true = private, false = public, default initialized as false */
			Var * parent; /**< pointer to parent object */
			Var * global; /**< pointer to the global module */
			void * extra = nullptr; /**< useful pointer to store programmers defined info in native objects */

			bool IsByteCode(); /**< when flags == ObjFlag::ByteCode */
			bool IsNative(); /**< when flags == ObjFlag::Native */
			bool IsInvocable(); /**< when flags != ObjFlag::NotInvocable */

			/**
			 * Create a new Object with the same content and the copy of all members
			 * @return the copied Object
			 */
			Object Copy();

			/**
			 * Delete all members and set the current instance to NotInvocable
			 */
			void Clear();

			/**
			 * Create a not invocable Object
			 */
			Object();

			/**
			 * Create a not invocable Object and set the global pointer
			 * @param gbl the pointer to the global module
			 */
			Object(Var * gbl);

			/**
			 * Create a native Object with a function pointer
			 * @param func the function pointer
			 */
			Object(Native func);

			/**
			 * Create a native Object with a function pointer and set the global pointer
			 * @param func the function pointer
			 * @param gbl the pointer to the global module
			 */
			Object(Native func, Var * gbl);

			/**
			 * Create a bytecode Object with a Code pointer
			 * @param code the Code pointer
			 */
			Object(Code * code);

			/**
			 * Create a bytecode Object with a Code pointer and set the global pointer
			 * @param code the Code pointer
			 * @param gbl the pointer to the global module
			 */
			Object(Code * code, Var * gbl);

			/**
			 * Object destructor, call ClearParent
			 */
			~Object();

			/**
			 * Set the parent pointer to a reference of a variable
			 * @param v the parent variable
			 */
			void SetParent(Var v);

			/**
			 * Clear the parent pointer and delete it
			 */
			void ClearParent();
		};

		/**
		 * This struct is a stack memory cell
		 * It is used in a vector to define the stack
		 */
		struct DUBBEL_API Cell {
			Var * v = nullptr; /**< pointer to the variable contained in the stack */
			bool isConst = false; /**< specify if v is a constant */

			Var &Get(); /**< dereference v */
			void Clear(); /**< called when the cell is popped out from the stack, clear v if it is a constant */

			Cell() {}

			/**
			 * Create a Cell from a Var pointer
			 * @param p the variable to encapsulate
			 * @param iscst specify if p is a constant
			 */
			Cell(Var * p, bool iscst = false);

			/**
			 * Create a constant Cell from a Char
			 * @param t the Char
			 */
			Cell(Char t);

			/**
			 * Create a constant Cell from an Int
			 * @param t the Int
			 */
			Cell(Int t);

			/**
			 * Create a constant Cell from a Float
			 * @param t the Float
			 */
			Cell(Float t);

			/**
			 * Create a constant Cell from a Bool
			 * @param t the Bool
			 */
			Cell(Bool t);

			/**
			 * Create a constant Cell from a String
			 * @param t the String
			 */
			Cell(String t);

			/**
			 * Create a constant Cell from an Array
			 * @param t the Array
			 */
			Cell(Array t);

			/**
			 * Create a constant Cell from an Object
			 * @param t the Object
			 */
			Cell(Object t);
		};

		Value * val; /**< the Value pointer, nullptr when the Var is created */

		/**
		* Return the type id of val, None if val == nullptr
		* @ret the type id
		*/
		TypeId Type() const;

		/**
		* Return the readOnly flag of val
		* @ret the readOnly flag
		*/
		Bool ReadOnly() const;

		/**
		* Return a reference to val->ptr casted as Data<Char>
		* @ret the content of val->ptr
		*/
		Char & GetChar();

		/**
		* Return a reference to val->ptr casted as Data<Int>
		* @ret the content of val->ptr
		*/
		Int & GetInt();

		/**
		* Return a reference to val->ptr casted as Data<Float>
		* @ret the content of val->ptr
		*/
		Float & GetFloat();

		/**
		* Return a reference to val->ptr casted as Data<Bool>
		* @ret the content of val->ptr
		*/
		Bool & GetBool();

		/**
		* Return a reference to val->ptr casted as Data<Array>
		* @ret the content of val->ptr
		*/
		Array & GetArray();

		/**
		* Return a reference to val->ptr casted as Data<String>
		* @ret the content of val->ptr
		*/
		String & GetString();

		/**
		* Return a reference to val->ptr casted as Data<Object>
		* @ret the content of val->ptr
		*/
		Object & GetObject();

		/**
		* Create a None variable (this->val = nullptr)
		*/
		Var();

		/**
		* Create a Char variable and set if it is read only
		* @param t the Char
		* @param ronly if the variable id read only (default false)
		*/
		Var(Char t, Bool ronly = false);

		/**
		* Create an Int variable and set if it is read only
		* @param t the Int
		* @param ronly if the variable id read only (default false)
		*/
		Var(Int t, Bool ronly = false);

		/**
		* Create a Float variable and set if it is read only
		* @param t the Float
		* @param ronly if the variable id read only (default false)
		*/
		Var(Float t, Bool ronly = false);

		/**
		* Create a Bool variable and set if it is read only
		* @param t the Bool
		* @param ronly if the variable id read only (default false)
		*/
		Var(Bool t, Bool ronly = false);

		/**
		* Create an Array variable and set if it is read only
		* @param t the Array
		* @param ronly if the variable id read only (default false)
		*/
		Var(Array t, Bool ronly = false);

		/**
		* Create a String variable and set if it is read only
		* @param t the String
		* @param ronly if the variable id read only (default false)
		*/
		Var(String t, Bool ronly = false);

		/**
		* Create an Object variable and set if it is read only
		* @param t the Object
		* @param ronly if the variable id read only (default false)
		*/
		Var(Object t, Bool ronly = false);

		/**
		* Create a String variable from a char pointer and set if it is read only
		* @param t the char pointer
		* @param ronly if the variable id read only (default false)
		*/
		Var(const char * t, Bool ronly = false);

		/**
		* Delete the previous val content and set to None (val->ptr = nullptr)
		*/
		void SetNone();

		//void ClearRef();

		/**
		* Decrement the reference count of val and when 0 clear its content
		* If the variable is an Object the _finalize member is called
		*/
		void Clear();

		/**
		* Delete the previous val content and set it to a Char
		* @param t the Char
		*/
		void Set(Char t);

		/**
		* Delete the previous val content and set it to a Int
		* @param t the Int
		*/
		void Set(Int t);

		/**
		* Delete the previous val content and set it to a Float
		* @param t the Float
		*/
		void Set(Float t);

		/**
		* Delete the previous val content and set it to a Bool
		* @param t the Bool
		*/
		void Set(Bool t);

		/**
		* Delete the previous val content and set it to an Array
		* @param t the Array
		*/
		void Set(Array t);

		/**
		* Delete the previous val content and set it to a String
		* @param t the String
		*/
		void Set(String t);

		/**
		* Delete the previous val content and set it to an Object
		* @param t the Object
		*/
		void Set(Object t);

		/**
		* Invoke Clear() and set the val content to a copy of v.val content
		* @param v the Var to copy
		* @ret a reference to this instance
		*/
		Var & Assign(Var v); //a.Assign(b) <--> a = b.Copy()

		/**
		* Invoke Clear() and set the val content to a Char
		* @param v the Char
		* @ret a reference to this instance
		*/
		Var & Assign(Char t);

		/**
		* Invoke Clear() and set the val content to an Int
		* @param v the Int
		* @ret a reference to this instance
		*/
		Var & Assign(Int t);

		/**
		* Invoke Clear() and set the val content to a Float
		* @param v the Float
		* @ret a reference to this instance
		*/
		Var & Assign(Float t);

		/**
		* Invoke Clear() and set the val content to a Bool
		* @param v the Bool
		* @ret a reference to this instance
		*/
		Var & Assign(Bool t);

		/**
		* Invoke Clear() and set the val content to an Array
		* @param v the Array
		* @ret a reference to this instance
		*/
		Var & Assign(Array t);

		/**
		* Invoke Clear() and set the val content to a String
		* @param v the String
		* @ret a reference to this instance
		*/
		Var & Assign(String t);

		/**
		* Invoke Clear() and set the val content to an Object
		* @param v the Object
		* @ret a reference to this instance
		*/
		Var & Assign(Object t);

		/**
		* Set the val content to a copy of v.val content
		* Invalid use when ReadOnly is true
		* @param v the Var to copy
		* @ret a reference to this instance
		*/
		Var & RefAssign(Var v);

		/**
		* Set the val content to a Char
		* Invalid use when ReadOnly is true
		* @param v the Char
		* @ret a reference to this instance
		*/
		Var & RefAssign(Char t);

		/**
		* Set the val content to an Int
		* Invalid use when ReadOnly is true
		* @param v the Int
		* @ret a reference to this instance
		*/
		Var & RefAssign(Int t);

		/**
		* Set the val content to a Float
		* Invalid use when ReadOnly is true
		* @param v the Float
		* @ret a reference to this instance
		*/
		Var & RefAssign(Float t);

		/**
		* Set the val content to a Bool
		* Invalid use when ReadOnly is true
		* @param v the Bool
		* @ret a reference to this instance
		*/
		Var & RefAssign(Bool t);

		/**
		* Set the val content to a String
		* Invalid use when ReadOnly is true
		* @param v the String
		* @ret a reference to this instance
		*/
		Var & RefAssign(String t);

		/**
		* Set the val content to an Array
		* Invalid use when ReadOnly is true
		* @param v the Array
		* @ret a reference to this instance
		*/
		Var & RefAssign(Array t);

		/**
		* Set the val content to an Object
		* Invalid use when ReadOnly is true
		* @param v the Object
		* @ret a reference to this instance
		*/
		Var & RefAssign(Object t);

		/**
		* Invoke Clear() and set val to v.val
		* The reference count is incremented
		* @param v the reference Var
		* @ret a reference to this instance
		*/
		Var & Bind(Var & v);

		/**
		* Assign this instance to a new Var and return it
		* @ret the copied Var
		*/
		Var Copy();

		/**
		* Bind this instance to a new Var and return it
		* @ret the reference Var
		*/
		Var Reference();

		/**
		* Convert the content to a Bool, useful in conditionals
		* @ret the Bool
		*/
		Bool ToBool();

		/**
		* Cast the content to a String
		* @ret the Bool
		*/
		String ToString();

		Var & operator=(Char t); /**< same as Assign(Char) */
		Var & operator=(Int t); /**< same as Assign(Int) */
		Var & operator=(Float t); /**< same as Assign(Float) */
		Var & operator=(Bool t); /**< same as Assign(Bool) */
		Var & operator=(String t); /**< same as Assign(String) */
		Var & operator=(Array t); /**< same as Assign(Array) */
		Var & operator=(Object t); /**< same as Assign(Object) */

		Var operator+(Var v); /**< add operator */
		Var operator-(Var v); /**< sub operator */
		Var operator*(Var v); /**< mul operator */
		Var operator/(Var v); /**< div operator */
		Var operator%(Var v); /**< mod operator */

		Bool operator==(Var v); /**< equals operator */
		Bool operator!=(Var v); /**< not equals operator */
		Bool operator<(Var v); /**< less operator */
		Bool operator<=(Var v); /**< less equal operator */
		Bool operator>(Var v); /**< greater operator */
		Bool operator>=(Var v); /**< greater equal operator */
		
		/**
		* Return True when two Objects have the same member names
		* @param v the Object to compare with this instance
		* @ret a Bool
		*/
		Bool Like(Var v);

		Var operator&(Var v); /**< bitwise and operator */
		Var operator|(Var v); /**< bitwise or operator */
		Var operator^(Var v); /**< bitwise xor operator */
		Var operator<<(Var v); /**< left shift operator */
		Var operator>>(Var v); /**< right shift and operator */
		Var operator~(); /**< bitwise not operator */

		Bool operator!(); /**< not operator */

		Var operator-(); /**< minus operator */
		Var operator+(); /**< plus operator */

		/**
		* If the variable is an Object call it passig the arguments in an Array
		* @param args the Array of arguments
		* @ret the return Var that is returned by the Object call
		*/
		Var Call(Var args);
		
		/**
		* Copy this instance, call the copied Var and return it
		* @param args the Array of arguments
		* @ret the copied Var
		*/
		Var New(Var args);
		
		/**
		* If the variable is an Object create a member and return a pointer of the member
		* @param name the member name
		* @param isPrivate the modifier (default false)
		* @ret the pointer to the member
		*/
		Var * CreateMember(const String & name, Bool isPrivate = false);
		
		/**
		* Copy all members of v in this instance
		* @param v the source Var
		*/
		void Extends(Var v);

		//shortcuts

		/**
		* Return an Object's member by its name
		* @param name the member name
		* @ret the reference to the member
		*/
		Var & Attr(const String & name);
		
		/**
		* Return an Array element by its position
		* @param pos the position of the target element
		* @ret the reference to the element
		*/
		Var & At(LSize pos);

	};

	typedef Var::Object Object;

	typedef Var::Code Code;
	typedef Var::Cell Cell;

	/**
	 * This struct is a container for bytecode files
	 * A main module is executed and the other files are treated as libraries
	 */
	struct DUBBEL_API Archive {
		std::vector<String> fileContents; /**< bytecodes files contents */
		std::vector<String> fileNames; /**< bytecodes files names */
		String mainName; /**< name of the main module */

		Archive() {}
		
		/**
		* Create an Archive from an archive file (.dea)
		* @param content the content of the archive file
		*/
		Archive(const String & content);
		
		/**
		* Populate the Archive from an archive file (.dea)
		* @param content the content of the archive file
		*/
		void Parse(const String & content);
		
		/**
		* Generate an archive file from this instance
		* @ret the generated archive content
		*/
		String Build();
	};

	/**
	* Build an LSize integer from 4 bytes
	* @param a the first byte
	* @param b the second byte
	* @param c the third byte
	* @param d the fourth byte
	* @ret the LSize
	*/
	DUBBEL_API LSize BuildLSize(Char a, Char b, Char c, Char d);
	
	/**
	* Build an SSize integer from 2 bytes
	* @param a the first byte
	* @param b the second byte
	* @ret the SSize
	*/
	DUBBEL_API SSize BuildSSize(Char a, Char b);
	
	/**
	* Build an Int from a String specifying the begin position
	* @param s the source String
	* @param used a LSize reference that represents the length of the substring read
	* @param begin the start position
	* @ret the Int
	*/
	DUBBEL_API Int BuildInt(const String & s, LSize & used, LSize begin);
	
	/**
	* Build a Float from a String specifying the begin position
	* @param s the source String
	* @param used a LSize reference that represents the length of the substring read
	* @param begin the start position
	* @ret the Float
	*/
	DUBBEL_API Float BuildFloat(const String & s, LSize & used, LSize begin);
	
	/**
	* Build a 64 bit Float from a String specifying the begin position
	* @param s the source String
	* @param used a LSize reference that represents the length of the substring read
	* @param begin the start position
	* @ret the Float
	*/
	DUBBEL_API Float BuildFloat64(const String & s, LSize & used, LSize begin);
	
	/**
	* Build a Code pointer 
	* @param s the source String from a String specifying the begin and end positions
	* @param begin the start position
	* @param end the end position
	* @ret the Code *
	*/
	DUBBEL_API Code * BuildCode(const String & s, LSize begin, LSize end);

	extern DUBBEL_API std::map<String, Var> namespaces; /**< in this hashmap there are the libraries */
	extern DUBBEL_API Var mainObj; /**< the main module */
	extern DUBBEL_API String debugInfo; /**< contains info from SET_DBG_INFO */
	extern DUBBEL_API char ** cmdArgs; /**< argv passed to RunMain */
	extern DUBBEL_API int cmdArgsLen; /**< argc passed to RunMain */

	/**
	* Load a bytecode library (.dubbel) in the namespaces map by its path
	* @param path the library path
	* @param name the library name in the namespaces map
	*/
	DUBBEL_API void LoadByteCodeLib(String path, String name);
	
	/**
	* Load a native library (.dubsl) in the namespaces map by its path
	* @param path the library path
	* @param name the library name in the namespaces map
	*/
	DUBBEL_API void LoadNativeLib(String path, String name);
	
	/**
	* Load a library in the namespaces map by its file name (search in . and DUBBEL_LIBPATH)
	* @param lib the library file name (without extension)
	* @param name the library name in the namespaces map
	*/
	DUBBEL_API void LoadLib(String lib, String name);
	
	/**
	* Load a library in the namespaces map by its file name (search in . and DUBBEL_LIBPATH)
	* @param lib the library file name (without extension)
	*/
	DUBBEL_API void LoadLib(String lib);
	
	/**
	* Clear all members of active Objects and namespaces and call ::exit(status)
	* @param status the program return code (EXIT_SUCCESS or EXIT_FAILURE)
	*/
	DUBBEL_API void Exit(int status);
	
	/**
	* Load a single native function from a Library
	* @param lib the library name
	* @param name the function name
	* @ret the target funtion pointer
	*/
	DUBBEL_API Native External(String lib, String name);

	/**
	* Run a bytecode program
	* @param s the bytecode string
	* @param argc the main argc
	* @param argv the main argv
	* @ret the program exit code
	*/
	DUBBEL_API int RunMain(const String & s, int argc, char ** argv);
	
	/**
	* Run an archive program (add all not-main files to the namespaces map)
	* @param a the Archive instance
	* @param argc the main argc
	* @param argv the main argv
	* @ret the program exit code
	*/
	DUBBEL_API int RunMain(const Archive & a, int argc, char ** argv);
	
	/**
	* Run a native program
	* @param pt a pointer to a Native function
	* @param argc the main argc
	* @param argv the main argv
	* @ret the program exit code
	*/
	DUBBEL_API int RunMain(Native pt, int argc, char ** argv);

	/**
	* Return v.Type()
	* @param v the source Var
	* @ret the type
	*/
	DUBBEL_API Char TypeOf(Var v);
	
	/**
	* Return v.Type() if the type is not object
	* Return the Object content pointer as Int * 10 + object flag if the type is object
	* @param v the source Var
	* @ret the id
	*/
	DUBBEL_API Int IdOf(Var v);
	
	/**
	* Return v.val pointer as Int
	* @param v the source Var
	* @ret the Val pointer
	*/
	DUBBEL_API Int AddressOf(Var v);
	
	/**
	* Return the type of v as a String
	* @param v the source Var
	* @ret the type
	*/
	DUBBEL_API String TypeStr(Var v);
	
	/**
	* Move the v.val->ptr pointer to a new Var and set v.val->ptr to nullptr (None type)
	* @param v the source Var
	* @ret the new Var
	*/
	DUBBEL_API Var Move(Var v);
	
	/**
	* Swap the val->ptr pointer between two Vars
	* @param a the first Var
	* @param b the first Var
	*/
	DUBBEL_API void Swap(Var a, Var b);

	/**
	* Clear and erase an element from the stack
	* @param stack the stack, a vector of Cells
	* @param pos the target element position (default 0)
	*/
	DUBBEL_API void StackPop(std::vector<Cell> & stack, size_t pos = 0);
	
	/**
	* This is the processing function of the VM
	* @param code the Code pointer that contains the source bytecode
	* @param me a Var pointer to the Object connect with the bytecode (usually the called Object)
	* @param args the Array of arguemnts
	* @param returned a Var reference that represents the returned Var
	* @param locals the Array of local variables
	* @param stack the stack, a vector of Cells
	* @ret a integer code, 1 when the opecode RETURN is precessed, 0 when the function end without a RETURN
	*/
	DUBBEL_API int ExecCode(Code * code, Var * me, Var & args, Var & returned, Array & locals, std::vector<Cell> & stack);

	/*******************************************
	    Methods of primitives types
	    They are Native function with the
	    naming convention typename_Methodname
	 *******************************************/
	DUBBEL_API Var any_ToString(Var me, Var args);
	DUBBEL_API Var any_ToBool(Var me, Var args);
	DUBBEL_API Var char_ToInt(Var me, Var args);
	DUBBEL_API Var char_ToFloat(Var me, Var args);
	DUBBEL_API Var char_IsDigit(Var me, Var args);
	DUBBEL_API Var char_IsUpper(Var me, Var args);
	DUBBEL_API Var char_IsLower(Var me, Var args);
	DUBBEL_API Var char_IsLetter(Var me, Var args);
	DUBBEL_API Var char_IsPrintable(Var me, Var args);
	DUBBEL_API Var char_IsControl(Var me, Var args);
	DUBBEL_API Var char_ToUpper(Var me, Var args);
	DUBBEL_API Var char_ToLower(Var me, Var args);
	DUBBEL_API Var int_ToChar(Var me, Var args);
	DUBBEL_API Var int_ToFloat(Var me, Var args);
	DUBBEL_API Var float_ToChar(Var me, Var args);
	DUBBEL_API Var float_ToInt(Var me, Var args);
	DUBBEL_API Var float_GetPrec(Var me, Var args);
	DUBBEL_API Var float_SetPrec(Var me, Var args);
	DUBBEL_API Var bool_ToInt(Var me, Var args);
	DUBBEL_API Var string_ToArray(Var me, Var args);
	DUBBEL_API Var string_ToInt(Var me, Var args);
	DUBBEL_API Var string_ToFloat(Var me, Var args);
	DUBBEL_API Var string_Length(Var me, Var args);
	DUBBEL_API Var string_Push(Var me, Var args);
	DUBBEL_API Var string_Pop(Var me, Var args);
	DUBBEL_API Var string_Find(Var me, Var args);
	DUBBEL_API Var string_RFind(Var me, Var args);
	DUBBEL_API Var string_First(Var me, Var args);
	DUBBEL_API Var string_Last(Var me, Var args);
	DUBBEL_API Var string_SubStr(Var me, Var args);
	DUBBEL_API Var string_Replace(Var me, Var args);
	DUBBEL_API Var string_Trim(Var me, Var args);
	DUBBEL_API Var string_LTrim(Var me, Var args);
	DUBBEL_API Var string_RTrim(Var me, Var args);
	DUBBEL_API Var string_Split(Var me, Var args);
	DUBBEL_API Var string_Change(Var me, Var args);
	DUBBEL_API Var string_Clear(Var me, Var args);
	DUBBEL_API Var array_Length(Var me, Var args);
	DUBBEL_API Var array_Push(Var me, Var args);
	DUBBEL_API Var array_PushRef(Var me, Var args);
	DUBBEL_API Var array_Pop(Var me, Var args);
	DUBBEL_API Var array_Find(Var me, Var args);
	DUBBEL_API Var array_RFind(Var me, Var args);
	DUBBEL_API Var array_First(Var me, Var args);
	DUBBEL_API Var array_Last(Var me, Var args);
	DUBBEL_API Var array_Clear(Var me, Var args);
}
