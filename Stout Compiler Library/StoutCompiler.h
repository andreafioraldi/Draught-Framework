/*
* StoutCompiler.h
*
* Copyright 2016 Andrea Fioraldi <andreafioraldi@gmail.com>
*
* This file is part of Stout Compiler Library.
*
* Stout Compiler Library is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 3 of the License, or
* (at your option) any later version.
*
* Stout Compiler Library is distributed in the hope that it will be useful,
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

#include "DubbelBuilder.h"
#include <map>

#ifdef _WIN32
#ifdef StoutCompiler_EXPORTS
#define STOUT_API __declspec(dllexport)
#else
#define STOUT_API __declspec(dllimport)
#endif
#else
#define STOUT_API
#endif

using namespace std;
using namespace dubbel;

struct STOUT_API CompilerErr {
	String err;
	CompilerErr(String file, size_t l, String e);
	CompilerErr(String file, String l, String e);
};

struct Node;

struct STOUT_API Scope {
	vector<String> members;
	vector<String> locals;
	vector<String> consts;
	map<String, LSize> labels;
	SSize codes = 0;
	int FindMembers(String s);
	int FindLocals(String s);
	int FindConsts(String s);
	Builder builder;
	Bool inLoop = false;

	void SolveLabels();
};

STOUT_API Float ParseFloat(String s);
STOUT_API Char ParseChar(String s);
STOUT_API String ParseString(String s);

struct STOUT_API Compiler {
	Node * tree = nullptr;
	String fileName = "<none>";
	vector<String> namespaces;

	Compiler();
	Compiler(String i , String file = "<none>");
	~Compiler();

	int FindNamespaces(String s);
	int NextChar();
	void Reset();
	void SetInput(String i);
	void Parse();
	String Compile();
	String Compile(Scope * s);

	void * lexer;
	Bool debug = false;
	Bool optimize = true;

	private:
	String input = "";
	size_t pos = 0;

	void init();
	void free();
};


STOUT_API Node * ConstPlus(Node * a, String file, size_t l);
STOUT_API Node * ConstMinus(Node * a, String file, size_t l);
STOUT_API Node * ConstBitNot(Node * a, String file, size_t l);
STOUT_API Node * ConstNot(Node * a, String file, size_t l);
STOUT_API Node * ConstIncr(Node * a, String file, size_t l);
STOUT_API Node * ConstDecr(Node * a, String file, size_t l);
STOUT_API Node * ConstTypeOf(Node * a, String file, size_t l);
STOUT_API Node * ConstTypeStr(Node * a, String file, size_t l);

STOUT_API Node * ConstMul(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstDiv(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstMod(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstAdd(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstSub(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstLShift(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstRShift(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstGE(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstLE(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstGreater(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstLower(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstAnd(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstOr(Node * a, Node * b, String file, size_t l);
STOUT_API Node * ConstXor(Node * a, Node * b, String file, size_t l);

enum class NodeType : char {
	True,
	False,
	None,
	Id,
	Int,
	Float,
	Float64,
	Char,
	String,
	Global,
	Main,
	Args,
	Me,
	Parent,
	Error,
	External,
	Swap,
	Object,
	Array,
	RefArray,
	At,
	Call,
	CallArr,
	Attr,
	New,
	NewArr,
	ExprList,
	ReadOnly,
	Plus,
	Minus,
	BitNot,
	Not,
	AddrOf,
	IdOf,
	TypeOf,
	ParentOf,
	TypeStr,
	Move,
	Copy,
	Alloc,
	Mul,
	Div,
	Mod,
	Add,
	Sub,
	LShift,
	RShift,
	Lower,
	Greater,
	LE,
	GE,
	EQ,
	NE,
	Like,
	And,
	Xor,
	Or,
	LogicAnd,
	LogicOr,
	Logic,
	Assign,
	RBind,
	LBind,
	RefAs,
	MulAs,
	DivAs,
	ModAs,
	AddAs,
	SubAs,
	LShiftAs,
	RShiftAs,
	AndAs,
	XorAs,
	OrAs,
	Label,
	If,
	IfElse,
	CondNode,
	While,
	For,
	Try,
	TryCatch,
	Debug,
	Attach,
	Use,
	Extends,
	Throw,
	Delete,
	Library,
	Goto,
	Continue,
	Break,
	Return,
	Exit,
	ExprStmt,
	StmtList,
	ForEach,
	LIncr,
	LDecr,
	RIncr,
	RDecr
};

struct STOUT_API Node {
	NodeType type;
	size_t line;
	vector<Node *> children;

	void print(int level);
	Node() {}

	void Destroy();
	virtual void ToByteCode(Compiler * compiler, Scope * scope) {}
};


struct STOUT_API TrueNode : Node {
	TrueNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API FalseNode : Node {
	FalseNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API NoneNode : Node {
	NoneNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API IdNode : Node {
	String text;
	IdNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API IntNode : Node {
	String text;
	IntNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API FloatNode : Node {
	String text;
	FloatNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API Float64Node : Node {
	String text;
	Float64Node(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API CharNode : Node {
	String text;
	CharNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API StringNode : Node {
	String text;
	StringNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API GlobalNode : Node {
	GlobalNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API MainNode : Node {
	MainNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ArgsNode : Node {
	ArgsNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API MeNode : Node {
	MeNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ParentNode : Node {
	ParentNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ErrorNode : Node {
	ErrorNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ExternalNode : Node {
	ExternalNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API SwapNode : Node {
	SwapNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ObjectNode : Node {
	ObjectNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ArrayNode : Node {
	ArrayNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RefArrayNode : Node {
	RefArrayNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AtNode : Node {
	AtNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API CallNode : Node {
	CallNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API CallArrNode : Node {
	CallArrNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AttrNode : Node {
	String text;
	AttrNode(String txt, Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API NewNode : Node {
	NewNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API NewArrNode : Node {
	NewArrNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ExprListNode : Node {
	ExprListNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ReadOnlyNode : Node {
	ReadOnlyNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API PlusNode : Node {
	PlusNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API MinusNode : Node {
	MinusNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API BitNotNode : Node {
	BitNotNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API NotNode : Node {
	NotNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AddrOfNode : Node {
	AddrOfNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API IdOfNode : Node {
	IdOfNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ParentOfNode : Node {
	ParentOfNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API TypeOfNode : Node {
	TypeOfNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API TypeStrNode : Node {
	TypeStrNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API MoveNode : Node {
	MoveNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API CopyNode : Node {
	CopyNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AllocNode : Node {
	AllocNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API MulNode : Node {
	MulNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API DivNode : Node {
	DivNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ModNode : Node {
	ModNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AddNode : Node {
	AddNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API SubNode : Node {
	SubNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LShiftNode : Node {
	LShiftNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RShiftNode : Node {
	RShiftNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LowerNode : Node {
	LowerNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API GreaterNode : Node {
	GreaterNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LENode : Node {
	LENode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API GENode : Node {
	GENode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API EQNode : Node {
	EQNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API NENode : Node {
	NENode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LikeNode : Node {
	LikeNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AndNode : Node {
	AndNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API XorNode : Node {
	XorNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API OrNode : Node {
	OrNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LogicAndNode : Node {
	LogicAndNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LogicOrNode : Node {
	LogicOrNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LogicNode : Node {
	LogicNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AssignNode : Node {
	AssignNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RBindNode : Node {
	RBindNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LBindNode : Node {
	LBindNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RefAsNode : Node {
	RefAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API MulAsNode : Node {
	MulAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API DivAsNode : Node {
	DivAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ModAsNode : Node {
	ModAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AddAsNode : Node {
	AddAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API SubAsNode : Node {
	SubAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LShiftAsNode : Node {
	LShiftAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RShiftAsNode : Node {
	RShiftAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AndAsNode : Node {
	AndAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API XorAsNode : Node {
	XorAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API OrAsNode : Node {
	OrAsNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LabelNode : Node {
	String text;
	LabelNode(String txt, Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API IfNode : Node {
	IfNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API IfElseNode : Node {
	IfElseNode(Node * a, Node * b, Node *c, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API CondNode : Node {
	CondNode(Node * a, Node * b, Node *c, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API WhileNode : Node {
	WhileNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ForNode : Node {
	ForNode(Node * a, Node * b, Node *c, Node *d, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API TryNode : Node {
	TryNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API TryCatchNode : Node {
	TryCatchNode(Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API DebugNode : Node {
	DebugNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API AttachNode : Node {
	String text;
	AttachNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API UseNode : Node {
	String text;
	UseNode(String txt, Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ExtendsNode : Node {
	ExtendsNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ThrowNode : Node {
	ThrowNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API DeleteNode : Node {
	DeleteNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LibraryNode : Node {
	String text;
	LibraryNode(String txt, Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API GotoNode : Node {
	String text;
	GotoNode(String txt, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ContinueNode : Node {
	ContinueNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API BreakNode : Node {
	BreakNode(size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ReturnNode : Node {
	ReturnNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ExitNode : Node {
	ExitNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ExprStmtNode : Node {
	ExprStmtNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API StmtListNode : Node {
	StmtListNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API ForEachNode : Node {
	String text;
	ForEachNode(String txt, Node * a, Node * b, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LIncrNode : Node {
	LIncrNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API LDecrNode : Node {
	LDecrNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RIncrNode : Node {
	RIncrNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};

struct STOUT_API RDecrNode : Node {
	RDecrNode(Node * a, size_t l);
	void ToByteCode(Compiler * compiler, Scope * scope);
};
