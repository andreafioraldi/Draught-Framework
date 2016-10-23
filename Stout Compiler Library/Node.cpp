/*
* Node.cpp
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

#include "StoutCompiler.h"

TrueNode::TrueNode(size_t l) {
	type = NodeType::True;
	line = l;
}

FalseNode::FalseNode(size_t l) {
	type = NodeType::False;
	line = l;
}

NoneNode::NoneNode(size_t l) {
	type = NodeType::None;
	line = l;
}

IdNode::IdNode(String txt, size_t l) {
	type = NodeType::Id;
	text = txt;
	line = l;
}

IntNode::IntNode(String txt, size_t l) {
	type = NodeType::Int;
	text = txt;
	line = l;
}

FloatNode::FloatNode(String txt, size_t l) {
	type = NodeType::Float;
	text = txt;
	line = l;
}

Float64Node::Float64Node(String txt, size_t l) {
	type = NodeType::Float64;
	text = txt;
	line = l;
}

CharNode::CharNode(String txt, size_t l) {
	type = NodeType::Char;
	text = txt;
	line = l;
}

StringNode::StringNode(String txt, size_t l) {
	type = NodeType::String;
	text = txt;
	line = l;
}

GlobalNode::GlobalNode(size_t l) {
	type = NodeType::Global;
	line = l;
}

MainNode::MainNode(size_t l) {
	type = NodeType::Main;
	line = l;
}

ArgsNode::ArgsNode(size_t l) {
	type = NodeType::Args;
	line = l;
}

MeNode::MeNode(size_t l) {
	type = NodeType::Me;
	line = l;
}

ParentNode::ParentNode(size_t l) {
	type = NodeType::Parent;
	line = l;
}

ErrorNode::ErrorNode(size_t l) {
	type = NodeType::Error;
	line = l;
}

ExternalNode::ExternalNode(Node * a, Node * b, size_t l) {
	type = NodeType::External;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

SwapNode::SwapNode(Node * a, Node * b, size_t l) {
	type = NodeType::Swap;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

ObjectNode::ObjectNode(Node * a, Node * b, size_t l) {
	type = NodeType::Object;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

ArrayNode::ArrayNode(Node * a, size_t l) {
	type = NodeType::Array;
	line = l;
	children.push_back(a);
}

RefArrayNode::RefArrayNode(Node * a, size_t l) {
	type = NodeType::RefArray;
	line = l;
	children.push_back(a);
}


AtNode::AtNode(Node * a, Node * b, size_t l) {
	type = NodeType::At;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

CallNode::CallNode(Node * a, Node * b, size_t l) {
	type = NodeType::Call;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

CallArrNode::CallArrNode(Node * a, Node * b, size_t l) {
	type = NodeType::CallArr;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

AttrNode::AttrNode(String txt, Node * a, size_t l) {
	type = NodeType::Attr;
	text = txt;
	line = l;
	children.push_back(a);
}

NewNode::NewNode(Node * a, Node * b, size_t l) {
	type = NodeType::New;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

NewArrNode::NewArrNode(Node * a, Node * b, size_t l) {
	type = NodeType::NewArr;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

ExprListNode::ExprListNode(Node * a, size_t l) {
	type = NodeType::ExprList;
	line = l;
	children.push_back(a);
}

ReadOnlyNode::ReadOnlyNode(Node * a, size_t l) {
	type = NodeType::ReadOnly;
	line = l;
	children.push_back(a);
}

PlusNode::PlusNode(Node * a, size_t l) {
	type = NodeType::Plus;
	line = l;
	children.push_back(a);
}

MinusNode::MinusNode(Node * a, size_t l) {
	type = NodeType::Minus;
	line = l;
	children.push_back(a);
}

BitNotNode::BitNotNode(Node * a, size_t l) {
	type = NodeType::BitNot;
	line = l;
	children.push_back(a);
}

NotNode::NotNode(Node * a, size_t l) {
	type = NodeType::Not;
	line = l;
	children.push_back(a);
}

AddrOfNode::AddrOfNode(Node * a, size_t l) {
	type = NodeType::AddrOf;
	line = l;
	children.push_back(a);
}

IdOfNode::IdOfNode(Node * a, size_t l) {
	type = NodeType::IdOf;
	line = l;
	children.push_back(a);
}

ParentOfNode::ParentOfNode(Node * a, size_t l) {
	type = NodeType::ParentOf;
	line = l;
	children.push_back(a);
}

TypeOfNode::TypeOfNode(Node * a, size_t l) {
	type = NodeType::TypeOf;
	line = l;
	children.push_back(a);
}

TypeStrNode::TypeStrNode(Node * a, size_t l) {
	type = NodeType::TypeStr;
	line = l;
	children.push_back(a);
}

MoveNode::MoveNode(Node * a, size_t l) {
	type = NodeType::Move;
	line = l;
	children.push_back(a);
}

CopyNode::CopyNode(Node * a, size_t l) {
	type = NodeType::Copy;
	line = l;
	children.push_back(a);
}

AllocNode::AllocNode(Node * a, size_t l) {
	type = NodeType::Alloc;
	line = l;
	children.push_back(a);
}

MulNode::MulNode(Node * a, Node * b, size_t l) {
	type = NodeType::Mul;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

DivNode::DivNode(Node * a, Node * b, size_t l) {
	type = NodeType::Div;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

ModNode::ModNode(Node * a, Node * b, size_t l) {
	type = NodeType::Mod;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

AddNode::AddNode(Node * a, Node * b, size_t l) {
	type = NodeType::Add;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

SubNode::SubNode(Node * a, Node * b, size_t l) {
	type = NodeType::Sub;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LShiftNode::LShiftNode(Node * a, Node * b, size_t l) {
	type = NodeType::LShift;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

RShiftNode::RShiftNode(Node * a, Node * b, size_t l) {
	type = NodeType::RShift;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LowerNode::LowerNode(Node * a, Node * b, size_t l) {
	type = NodeType::Lower;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

GreaterNode::GreaterNode(Node * a, Node * b, size_t l) {
	type = NodeType::Greater;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LENode::LENode(Node * a, Node * b, size_t l) {
	type = NodeType::LE;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

GENode::GENode(Node * a, Node * b, size_t l) {
	type = NodeType::GE;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

EQNode::EQNode(Node * a, Node * b, size_t l) {
	type = NodeType::EQ;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

NENode::NENode(Node * a, Node * b, size_t l) {
	type = NodeType::NE;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LikeNode::LikeNode(Node * a, Node * b, size_t l) {
	type = NodeType::Like;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

AndNode::AndNode(Node * a, Node * b, size_t l) {
	type = NodeType::And;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

XorNode::XorNode(Node * a, Node * b, size_t l) {
	type = NodeType::Xor;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

OrNode::OrNode(Node * a, Node * b, size_t l) {
	type = NodeType::Or;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LogicAndNode::LogicAndNode(Node * a, size_t l) {
	type = NodeType::LogicAnd;
	line = l;
	children.push_back(a);
}

LogicOrNode::LogicOrNode(Node * a, size_t l) {
	type = NodeType::LogicOr;
	line = l;
	children.push_back(a);
}

LogicNode::LogicNode(Node * a, size_t l) {
	type = NodeType::Logic;
	line = l;
	children.push_back(a);
}

AssignNode::AssignNode(Node * a, Node * b, size_t l) {
	type = NodeType::Assign;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

RBindNode::RBindNode(Node * a, Node * b, size_t l) {
	type = NodeType::RBind;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LBindNode::LBindNode(Node * a, Node * b, size_t l) {
	type = NodeType::LBind;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

RefAsNode::RefAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::RefAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

MulAsNode::MulAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::MulAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

DivAsNode::DivAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::DivAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

ModAsNode::ModAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::ModAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

AddAsNode::AddAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::AddAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

SubAsNode::SubAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::SubAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LShiftAsNode::LShiftAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::LShiftAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

RShiftAsNode::RShiftAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::RShiftAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

AndAsNode::AndAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::AndAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

XorAsNode::XorAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::XorAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

OrAsNode::OrAsNode(Node * a, Node * b, size_t l) {
	type = NodeType::OrAs;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LabelNode::LabelNode(String txt, Node * a, size_t l) {
	type = NodeType::Label;
	text = txt;
	line = l;
	children.push_back(a);
}

IfNode::IfNode(Node * a, Node * b, size_t l) {
	type = NodeType::If;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

IfElseNode::IfElseNode(Node * a, Node * b, Node *c, size_t l) {
	type = NodeType::IfElse;
	line = l;
	children.push_back(a);
	children.push_back(b);
	children.push_back(c);
}

CondNode::CondNode(Node * a, Node * b, Node *c, size_t l) {
	type = NodeType::CondNode;
	line = l;
	children.push_back(a);
	children.push_back(b);
	children.push_back(c);
}

WhileNode::WhileNode(Node * a, Node * b, size_t l) {
	type = NodeType::While;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

ForNode::ForNode(Node * a, Node * b, Node *c, Node *d, size_t l) {
	type = NodeType::For;
	line = l;
	children.push_back(a);
	children.push_back(b);
	children.push_back(c);
	children.push_back(d);
}

TryNode::TryNode(Node * a, size_t l) {
	type = NodeType::Try;
	line = l;
	children.push_back(a);
}

TryCatchNode::TryCatchNode(Node * a, Node * b, size_t l) {
	type = NodeType::TryCatch;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

DebugNode::DebugNode(Node * a, size_t l) {
	type = NodeType::Debug;
	line = l;
	children.push_back(a);
}

AttachNode::AttachNode(String txt, size_t l) {
	type = NodeType::Attach;
	text = txt;
	line = l;
}

UseNode::UseNode(String txt, Node * a, size_t l) {
	type = NodeType::Use;
	text = txt;
	line = l;
	children.push_back(a);
}

ExtendsNode::ExtendsNode(Node * a, size_t l) {
	type = NodeType::Extends;
	line = l;
	children.push_back(a);
}

ThrowNode::ThrowNode(Node * a, size_t l) {
	type = NodeType::Throw;
	line = l;
	children.push_back(a);
}

DeleteNode::DeleteNode(Node * a, size_t l) {
	type = NodeType::Delete;
	line = l;
	children.push_back(a);
}

LibraryNode::LibraryNode(String txt, Node * a, size_t l) {
	type = NodeType::Library;
	text = txt;
	line = l;
	children.push_back(a);
}

GotoNode::GotoNode(String txt, size_t l) {
	type = NodeType::Goto;
	text = txt;
	line = l;
}

ContinueNode::ContinueNode(size_t l) {
	type = NodeType::Continue;
	line = l;
}

BreakNode::BreakNode(size_t l) {
	type = NodeType::Break;
	line = l;
}

ReturnNode::ReturnNode(Node * a, size_t l) {
	type = NodeType::Return;
	line = l;
	children.push_back(a);
}

ExitNode::ExitNode(Node * a, size_t l) {
	type = NodeType::Exit;
	line = l;
	children.push_back(a);
}

ExprStmtNode::ExprStmtNode(Node * a, size_t l) {
	type = NodeType::ExprStmt;
	line = l;
	children.push_back(a);
}

StmtListNode::StmtListNode(Node * a, size_t l) {
	type = NodeType::StmtList;
	line = l;
	children.push_back(a);
}

ForEachNode::ForEachNode(String txt, Node * a, Node * b, size_t l) {
	type = NodeType::ForEach;
	text = txt;
	line = l;
	children.push_back(a);
	children.push_back(b);
}

LIncrNode::LIncrNode(Node * a, size_t l) {
	type = NodeType::LIncr;
	line = l;
	children.push_back(a);
}

LDecrNode::LDecrNode(Node * a, size_t l) {
	type = NodeType::LDecr;
	line = l;
	children.push_back(a);
}

RIncrNode::RIncrNode(Node * a, size_t l) {
	type = NodeType::RIncr;
	line = l;
	children.push_back(a);
}

RDecrNode::RDecrNode(Node * a, size_t l) {
	type = NodeType::RDecr;
	line = l;
	children.push_back(a);
}

String sizeToS(size_t i);

void Node::Destroy() {
	for(size_t i = 0; i < children.size(); ++i) {
		if(children[i] != nullptr) {
			children[i]->Destroy();
			delete children[i];
		}
	} 
}

String NodeTypeStr[] = {
	"True",
	"False",
	"None",
	"Id",
	"Int",
	"Float",
	"Float64",
	"Char",
	"String",
	"Global",
	"Main",
	"Args",
	"Me",
	"Parent",
	"Error",
	"External",
	"Swap",
	"Object",
	"Array",
	"At",
	"Call",
	"CallArr",
	"Attr",
	"New",
	"NewArr",
	"ExprList",
	"Plus",
	"Minus",
	"BitNot",
	"Not",
	"AddrOf",
	"TypeOf",
	"ParentOf",
	"TypeStr",
	"Move",
	"Copy",
	"Alloc",
	"Mul",
	"Div",
	"Mod",
	"Add",
	"Sub",
	"LShift",
	"RShift",
	"Lower",
	"Greater",
	"LE",
	"GE",
	"EQ",
	"NE",
	"Like",
	"And",
	"Xor",
	"Or",
	"LogicAnd",
	"LogicOr",
	"Logic",
	"Assign",
	"RBind",
	"LBind",
	"RefAs",
	"MulAs",
	"DivAs",
	"ModAs",
	"AddAs",
	"SubAs",
	"LShiftAs",
	"RShiftAs",
	"AndAs",
	"XorAs",
	"OrAs",
	"Label",
	"If",
	"IfElse",
	"While",
	"For",
	"Try",
	"TryCatch",
	"Debug",
	"Attach",
	"Use",
	"Extends",
	"Throw",
	"Delete",
	"Library",
	"Goto",
	"Continue",
	"Break",
	"Return",
	"Exit",
	"ExprStmt",
	"StmtList",
	"ForEach",
	"LIncr",
	"LDecr",
	"RIncr",
	"RDecr"
};


void Node::print(int level) {
	for(int i = 0; i < level; i++)
		cerr << "\t";
	cerr << NodeTypeStr[(int)type];
	if(type == NodeType::Id)
		cerr << " : " << ((IdNode*)this)->text;
	else if(type == NodeType::Int)
		cerr << " : " << ((IntNode*)this)->text;
	else if(type == NodeType::Float)
		cerr << " : " << ((FloatNode*)this)->text;
	else if(type == NodeType::Float64)
		cerr << " : " << ((Float64Node*)this)->text;
	else if(type == NodeType::Char)
		cerr << " : " << ((CharNode*)this)->text;
	else if(type == NodeType::String)
		cerr << " : " << ((StringNode*)this)->text;
	else if(type == NodeType::Attr)
		cerr << " : " << ((AttrNode*)this)->text;
	else if(type == NodeType::Label)
		cerr << " : " << ((LabelNode*)this)->text;
	else if(type == NodeType::Attach)
		cerr << " : " << ((AttachNode*)this)->text;
	else if(type == NodeType::Use)
		cerr << " : " << ((UseNode*)this)->text;
	else if(type == NodeType::Library)
		cerr << " : " << ((LibraryNode*)this)->text;
	else if(type == NodeType::Goto)
		cerr << " : " << ((GotoNode*)this)->text;
	level++;
	cerr << endl;
	for (int i = 0; i < children.size(); i++)
		if(children[i] != nullptr) 
			children[i]->print(level);
		else {
			for(int j = 0; j < level; j++)
				cerr << "\t";
			cerr << "Null\n";
		}
}


void GotoNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(NO_OP, String("GOTO"), text, compiler->fileName, sizeToS(line));
}

void LibraryNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(compiler->FindNamespaces(text) == -1)
		compiler->namespaces.push_back(text);
	if(children[0] == nullptr) {
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_ADD_LIB, text + "\x03");
	}
	else {
		children[0]->ToByteCode(compiler, scope);
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_ADD_LIB_S, text + "\x03");
	}
}

void UseNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(compiler->FindNamespaces(text) == -1)
		compiler->namespaces.push_back(text);
	if(children[0] == nullptr) {
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_LOAD_LIB, text + "\x03");
	}
	else {
		children[0]->ToByteCode(compiler, scope);
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_LOAD_LIB_S, text + "\x03");
	}
}

void AttachNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(scope->FindMembers(text) == -1)
		scope->members.push_back(text);
	scope->builder.Append(OPC_CREATE_MEMBER, text + "\x03");
}

void IdNode::ToByteCode(Compiler * compiler, Scope * scope) {
	int f;
	if(compiler->FindNamespaces(text) >= 0)
		scope->builder.Append(OPC_LOAD_NS, text + "\x03");
	else if(scope->FindMembers(text) >= 0) 
		scope->builder.Append(OPC_ME_MEMBER, text + "\x03");
	else if((f = scope->FindLocals(text)) >= 0)
		scope->builder.Append(OPC_LOAD, (SSize)f);
	else {
		scope->locals.push_back(text);
		scope->builder.Append(OPC_LOAD, (SSize)(scope->locals.size() -1));
	}
}

void IntNode::ToByteCode(Compiler * compiler, Scope * scope) {
	int f = scope->FindConsts(text);
	if(f >= 0) {
		scope->builder.Append(OPC_LOAD_C, (SSize)f);
	}
	else {
		scope->consts.push_back(text);
		scope->builder.AddConst(OPC_$INT, Int(text));
		scope->builder.Append(OPC_LOAD_C, (SSize)(scope->consts.size() - 1));
	}
}

void FloatNode::ToByteCode(Compiler * compiler, Scope * scope) {
	int f = scope->FindConsts(text);
	if(f >= 0) {
		scope->builder.Append(OPC_LOAD_C, (SSize)f);
	}
	else {
		scope->consts.push_back(text);
		scope->builder.AddConst(OPC_$FLOAT, ParseFloat(text));
		scope->builder.Append(OPC_LOAD_C, (SSize)(scope->consts.size() -1));
	}
}

void Float64Node::ToByteCode(Compiler * compiler, Scope * scope) {
	int f = scope->FindConsts(text);
	if(f >= 0) {
		scope->builder.Append(OPC_LOAD_C, (SSize)f);
	}
	else {
		scope->consts.push_back(text);
		scope->builder.AddConst(OPC_$FLOAT64, Float(text, 64));
		scope->builder.Append(OPC_LOAD_C, (SSize)(scope->consts.size() -1));
	}
}

void CharNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_CHAR, ParseChar(text));
}

void StringNode::ToByteCode(Compiler * compiler, Scope * scope) {
	int f = scope->FindConsts(text);
	if(f >= 0) {
		scope->builder.Append(OPC_LOAD_C, (SSize)f);
	}
	else {
		scope->consts.push_back(text);
		String s = ParseString(text);
		scope->builder.AddConst(OPC_$STRING, (LSize)s.size(), s);
		scope->builder.Append(OPC_LOAD_C, (SSize)(scope->consts.size() -1));
	}
}

void LabelNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(text == "public")
		scope->builder.Append(OPC_SET_PUBLIC);
	else if(text == "private")
		scope->builder.Append(OPC_SET_PRIVATE);
	else
		scope->labels[text] = scope->builder.body.Size();
	children[0]->ToByteCode(compiler, scope);
}

void AttrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	Char opc = OPC_MEMBER;
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_ME) {
		scope->builder.body.Pop();
		opc = OPC_ME_MEMBER;
	}
	else if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_ME_PARENT) {
		scope->builder.body.Pop();
		opc = OPC_PARENT_MEMBER;
	}
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(opc, text + "\x03");
}

void NoneNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_NONE);
}

void TrueNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_TRUE);
}

void FalseNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_FALSE);
}

void GlobalNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_GLOBAL);
}

void MainNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_MAIN);
}

void ArgsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_ARGS);
}

void MeNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_ME);
}

void ParentNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_ME_PARENT);
}

void ErrorNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_ERROR);
}

void BreakNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(!scope->inLoop)
		throw CompilerErr(compiler->fileName, line, "semantic error, 'break' outside a loop");
	scope->builder.Append(NO_OP, String("BREAK"));
}

void ContinueNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(!scope->inLoop)
		throw CompilerErr(compiler->fileName, line, "semantic error, 'continue' outside a loop");
	scope->builder.Append(NO_OP, String("CONTINUE"));
}

void LogicNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_TOBOOL);
}

void ArrayNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0] == nullptr)
		scope->builder.Append(OPC_ARRAY, (SSize)0);
	else {
		SSize len = children[0]->children.size();
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_ARRAY, len);
	}
}

void RefArrayNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0] == nullptr)
		scope->builder.Append(OPC_REF_ARRAY, (SSize)0);
	else {
		SSize len = children[0]->children.size();
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_REF_ARRAY, len);
	}
}

void ExitNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0] == nullptr)
		scope->builder.Append(OPC_NONE);
	else children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_EXIT);
}

void ReturnNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0] == nullptr)
		scope->builder.Append(OPC_RETURN_NONE);
	else {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_RETURN);
	}
}

void ExtendsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_EXTENDS);
}

void ThrowNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_THROW);
}

void DeleteNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_DELETE);
}

void ExprStmtNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0] != nullptr) {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_STACK_POP);
	}
}

void DebugNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(compiler->debug) {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_DEBUG);
		scope->builder.Append(OPC_STACK_POP);
	}
}

void AllocNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_ARR_ALLOC);
}

void AddrOfNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_ADDROF);
}

void IdOfNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_IDOF);
}

void ParentOfNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_PARENT);
}

void TypeOfNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_TYPEID);
}

void TypeStrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_TYPESTR);
}

void MoveNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_MOVE);
}

void CopyNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_COPY);
}

void ReadOnlyNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_SET_RDONLY);
}

void NotNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_NOT);
}

void BitNotNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_BIT_NOT);
}

void MinusNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_MINUS);
}

void PlusNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
}

void TryNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_TRY, (LSize)0);
	size_t size = scope->builder.body.Size();
	size_t pos = scope->builder.body.Len() -1;
	children[0]->ToByteCode(compiler, scope);
	scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
}

void ObjectNode::ToByteCode(Compiler * compiler, Scope * scope) {
	Scope ns;
	children[1]->ToByteCode(compiler, &ns);
	ns.SolveLabels();
	if(ns.builder.body.Len() > 0 && ns.builder.body[ns.builder.body.Len() -1].opcode == OPC_STACK_POP)
		ns.builder.body.Pop(ns.builder.body.Len() -1);
	scope->builder.constPool.Join(ns.builder.BuildCode(OPC_$CODE));
	if(children[0] == nullptr)
		scope->builder.Append(OPC_BUILD_OBJ, scope->codes++);
	else {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_BUILD_OBJEXT, scope->codes++);
	}
}

void ExprListNode::ToByteCode(Compiler * compiler, Scope * scope) {
	for(size_t i = 0; i < children.size(); ++i)
		children[i]->ToByteCode(compiler, scope);
}

void StmtListNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0] != nullptr)
		for(size_t i = 0; i < children.size(); ++i)
			children[i]->ToByteCode(compiler, scope);
}

void IfNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0]->type == NodeType::False ||
	 (children[0]->type == NodeType::Int && Int(((IntNode*)children[0])->text) == 0) ||
	 children[0]->type == NodeType::None ||
	 (children[0]->type == NodeType::Float64 && Float(((Float64Node*)children[0])->text, 64) == 0.0) ||
	 (children[0]->type == NodeType::Float && ParseFloat(((FloatNode*)children[0])->text) == 0.0) ||
	 (children[0]->type == NodeType::Char && ParseChar(((CharNode*)children[0])->text) == 0))
		return;
	if(children[0]->type == NodeType::True || children[0]->type == NodeType::Int || children[0]->type == NodeType::Float64 ||
	 children[0]->type == NodeType::Float || children[0]->type == NodeType::Char)
		children[1]->ToByteCode(compiler, scope);
	else {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP_IFNOT, (LSize)0);
		size_t size = scope->builder.body.Size();
		size_t pos = scope->builder.body.Len() -1;
		children[1]->ToByteCode(compiler, scope);
		scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
	}
}

void TryCatchNode::ToByteCode(Compiler * compiler, Scope * scope) {
	scope->builder.Append(OPC_TRY, (LSize)0);
	size_t size = scope->builder.body.Size();
	size_t pos = scope->builder.body.Len() -1;
	children[0]->ToByteCode(compiler, scope);
	scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
	scope->builder.Append(OPC_CATCH, (LSize)0);
	size = scope->builder.body.Size();
	pos = scope->builder.body.Len() -1;
	children[1]->ToByteCode(compiler, scope);
	scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
}


void WhileNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0]->type == NodeType::False ||
	 (children[0]->type == NodeType::Int && Int(((IntNode*)children[0])->text) == 0) ||
	 children[0]->type == NodeType::None ||
	 (children[0]->type == NodeType::Float64 && Float(((Float64Node*)children[0])->text, 64) == 0.0) ||
	 (children[0]->type == NodeType::Float && ParseFloat(((FloatNode*)children[0])->text) == 0.0) ||
	 (children[0]->type == NodeType::Char && ParseChar(((CharNode*)children[0])->text) == 0))
		return;
	size_t pre_size = scope->builder.body.Size();
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_JUMP_IFNOT, (LSize)0);
	bool oldb = scope->inLoop;
	scope->inLoop = true;
	size_t size = scope->builder.body.Size();
	size_t pos = scope->builder.body.Len() -1;
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_JUMP_BACK, (LSize)(scope->builder.body.Size() - pre_size));
	size_t end_size = scope->builder.body.Size();
	for(size_t i = pos+1; i < scope->builder.body.Len(); ++i) {
		if(scope->builder.body[i].opcode == NO_OP) {
			if(scope->builder.body[i].args[0] == "BREAK")
				scope->builder.body[i] = Instr(OPC_JUMP, (LSize)(end_size - scope->builder.body.Size(i) -5));
			else if(scope->builder.body[i].args[0] == "CONTINUE")
				scope->builder.body[i] = Instr(OPC_JUMP_BACK, (LSize)(scope->builder.body.Size(i) - pre_size));
		}
	}
	scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
	scope->inLoop = oldb;
}

void ExternalNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_EXTERNAL);
}

void SwapNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_SWAP);
}

void ModNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_MOD);
}

void DivNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_DIV);
}

void MulNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_MUL);
}

void AddNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_ADD);
}

void SubNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_SUB);
}

void RShiftNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_R_SHIFT);
}

void LShiftNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_L_SHIFT);
}

void GENode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_IS_GRT_EQ);
}

void LENode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_IS_LOW_EQ);
}

void GreaterNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_IS_GRT);
}

void LowerNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_IS_LOW);
}

void NENode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_ISN_EQ);
}

void EQNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_IS_EQ);
}

void LikeNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_LIKE);
}


void AndNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_BIT_AND);
}

void XorNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_BIT_XOR);
}

void OrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_BIT_OR);
}

void LogicAndNode::ToByteCode(Compiler * compiler, Scope * scope) {
	vector<size_t> sizes;
	vector<size_t> instrs;
	for(size_t i = 0; i < children.size(); ++i) {
		children[i]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP_IFNOT, (LSize)0);
		sizes.push_back(scope->builder.body.Size());
		instrs.push_back(scope->builder.body.Len() - 1);
	}
	size_t s = scope->builder.body.Size();
	for(size_t i = 0; i < instrs.size(); ++i)
		scope->builder.body[instrs[i]].args[0] = ToBytes((LSize)(s - sizes[i]));
}

void LogicOrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	vector<size_t> sizes;
	vector<size_t> instrs;
	for(size_t i = 0; i < children.size(); ++i) {
		children[i]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP_IF, (LSize)0);
		sizes.push_back(scope->builder.body.Size());
		instrs.push_back(scope->builder.body.Len() -1);
	}
	size_t s = scope->builder.body.Size();
	for (size_t i = 0; i < instrs.size(); ++i)
		scope->builder.body[instrs[i]].args[0] = ToBytes((LSize)(s - sizes[i]));
}

void RefAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '@=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_REF_ASSIGN);
}

void OrAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '|=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_BIT_OR_ASSIGN);
}

void AndAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '&=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_BIT_AND_ASSIGN);
}

void XorAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '^=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_BIT_XOR_ASSIGN);
}

void RShiftAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '>>=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_R_SHIFT_ASSIGN);
}

void LShiftAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '<<=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_L_SHIFT_ASSIGN);
}

void SubAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '-=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_SUB_ASSIGN);
}

void AddAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '+=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_ADD_ASSIGN);
}

void ModAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '%=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_MOD_ASSIGN);
}

void MulAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '*=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_MUL_ASSIGN);
}

void DivAsNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '/=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_DIV_ASSIGN);
}

void AssignNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '=' from a constant has not mean");
	children[1]->ToByteCode(compiler, scope);
	/*if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		scope->builder.Append(OPC_L_BIND);
	else*/
		scope->builder.Append(OPC_ASSIGN);
}

void CallNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(children[1] == nullptr) {
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_CALL_0);
	}
	else {
		children[1]->ToByteCode(compiler, scope);
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_CALL, (SSize)children[1]->children.size());
	}
}

void CallArrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_CALL_A);
}

void NewNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(children[1] == nullptr) {
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_NEW_0);
	}
	else {
		children[1]->ToByteCode(compiler, scope);
		if(compiler->debug)
			scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
		scope->builder.Append(OPC_NEW, (SSize)children[1]->children.size());
	}
}

void NewArrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_NEW_A);
}

void AtNode::ToByteCode(Compiler * compiler, Scope * scope) {
	//if (children[0]->type == NodeType::Array || children[0]->type == NodeType::Add)
	//	throw CompilerErr(compiler->fileName, line, "semantic error, invalid access to an element of a temporary array");
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_AT);
}

void RBindNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	children[1]->ToByteCode(compiler, scope);
	/*if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '->' to a constant has not mean");*/
	scope->builder.Append(OPC_R_BIND);
}

void LBindNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	/*if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_LOAD_C)
		throw CompilerErr(compiler->fileName, line, "semantic error, '<-' from a constant has not mean");*/
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_L_BIND);
}

void IfElseNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if(children[0]->type == NodeType::False ||
	 (children[0]->type == NodeType::Int && Int(((IntNode*)children[0])->text) == 0) ||
	 children[0]->type == NodeType::None ||
	 (children[0]->type == NodeType::Float64 && Float(((Float64Node*)children[0])->text, 64) == 0.0) ||
	 (children[0]->type == NodeType::Float && ParseFloat(((FloatNode*)children[0])->text) == 0.0) ||
	 (children[0]->type == NodeType::Char && ParseChar(((CharNode*)children[0])->text) == 0))
		children[2]->ToByteCode(compiler, scope);
	else if(children[0]->type == NodeType::True || children[0]->type == NodeType::Int || children[0]->type == NodeType::Float64 ||
	 children[0]->type == NodeType::Float || children[0]->type == NodeType::Char)
		children[1]->ToByteCode(compiler, scope);
	else {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP_IFNOT, (LSize)0);
		size_t size = scope->builder.body.Size();
		size_t pos = scope->builder.body.Len() -1;
		children[1]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP, (LSize)0);
		scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
		size = scope->builder.body.Size();
		pos = scope->builder.body.Len() -1;
		children[2]->ToByteCode(compiler, scope);
		scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
	}
}

void CondNode::ToByteCode(Compiler * compiler, Scope * scope) {
	if (children[0]->type == NodeType::False ||
		(children[0]->type == NodeType::Int && Int(((IntNode*)children[0])->text) == 0) ||
		children[0]->type == NodeType::None ||
		(children[0]->type == NodeType::Float64 && Float(((Float64Node*)children[0])->text, 64) == 0.0) ||
		(children[0]->type == NodeType::Float && ParseFloat(((FloatNode*)children[0])->text) == 0.0) ||
		(children[0]->type == NodeType::Char && ParseChar(((CharNode*)children[0])->text) == 0))
		children[2]->ToByteCode(compiler, scope);
	else if (children[0]->type == NodeType::True || children[0]->type == NodeType::Int || children[0]->type == NodeType::Float64 ||
		children[0]->type == NodeType::Float || children[0]->type == NodeType::Char)
		children[1]->ToByteCode(compiler, scope);
	else {
		children[0]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP_IFNOT, (LSize)0);
		size_t size = scope->builder.body.Size();
		size_t pos = scope->builder.body.Len() - 1;
		children[1]->ToByteCode(compiler, scope);
		scope->builder.Append(OPC_JUMP, (LSize)0);
		scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
		size = scope->builder.body.Size();
		pos = scope->builder.body.Len() - 1;
		children[2]->ToByteCode(compiler, scope);
		scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
	}
}

void ForNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(children[1]->type == NodeType::False ||
	 (children[1]->type == NodeType::Int && Int(((IntNode*)children[1])->text) == 0) ||
	 children[1]->type == NodeType::None ||
	 (children[1]->type == NodeType::Float64 && Float(((Float64Node*)children[1])->text, 64) == 0.0) ||
	 (children[1]->type == NodeType::Float && ParseFloat(((FloatNode*)children[1])->text) == 0.0) ||
	 (children[1]->type == NodeType::Char && ParseChar(((CharNode*)children[1])->text) == 0))
		return;
	size_t pre_size = scope->builder.body.Size();
	children[1]->ToByteCode(compiler, scope);
	if(scope->builder.body.Len() > 0 && scope->builder.body[scope->builder.body.Len() -1].opcode == OPC_STACK_POP)
		scope->builder.body.Pop(scope->builder.body.Len() -1);
	scope->builder.Append(OPC_JUMP_IFNOT, (LSize)0);
	bool oldb = scope->inLoop;
	scope->inLoop = true;
	size_t size = scope->builder.body.Size();
	size_t pos = scope->builder.body.Len() -1;
	children[3]->ToByteCode(compiler, scope);
	size_t inc_size = scope->builder.body.Size();
	if(children[2] != nullptr)
		children[2]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_JUMP_BACK, (LSize)(scope->builder.body.Size() - pre_size));
	size_t end_size = scope->builder.body.Size();
	for(size_t i = pos+1; i < scope->builder.body.Len(); ++i) {
		if(scope->builder.body[i].opcode == NO_OP) {
			if(scope->builder.body[i].args[0] == "BREAK")
				scope->builder.body[i] = Instr(OPC_JUMP, (LSize)(end_size - scope->builder.body.Size(i) -5));
			else if(scope->builder.body[i].args[0] == "CONTINUE")
				scope->builder.body[i] = Instr(OPC_JUMP, (LSize)(inc_size - scope->builder.body.Size(i) -5));
		}
	}
	scope->builder.body[pos].args[0] = ToBytes((LSize)(scope->builder.body.Size() - size));
	scope->inLoop = oldb;
}


void ForEachNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	size_t pre_size = scope->builder.body.Size();
	int f;
	if(compiler->FindNamespaces(text) >= 0 || scope->FindMembers(text) >= 0) 
		throw CompilerErr(compiler->fileName, line, "semantic error, the for iterator must be a local variable");
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	if((f = scope->FindLocals(text)) >= 0)
		scope->builder.Append(OPC_FOREACH, (SSize)f, (LSize)0);
	else {
		scope->locals.push_back(text);
		scope->builder.Append(OPC_FOREACH, (SSize)(scope->locals.size() -1), (LSize)0);
	}
	bool oldb = scope->inLoop;
	scope->inLoop = true;
	size_t size = scope->builder.body.Size();
	size_t pos = scope->builder.body.Len() -1;
	children[1]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_JUMP_BACK, (LSize)(scope->builder.body.Size() - pre_size));
	size_t end_size = scope->builder.body.Size();
	for(size_t i = pos+1; i < scope->builder.body.Len(); ++i) {
		if(scope->builder.body[i].opcode == NO_OP) {
			if(scope->builder.body[i].args[0] == "BREAK")
				scope->builder.body[i] = Instr(OPC_JUMP, (LSize)(end_size - scope->builder.body.Size(i) -5));
			else if(scope->builder.body[i].args[0] == "CONTINUE")
				scope->builder.body[i] = Instr(OPC_JUMP_BACK, (LSize)(scope->builder.body.Size(i) - pre_size));
		}
	}
	scope->builder.body[pos].args[1] = ToBytes((LSize)(scope->builder.body.Size() - size));
	scope->inLoop = oldb;
}

void LIncrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_INCR);
}

void LDecrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_DECR);
}

void RIncrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_STACK_DUP);
	scope->builder.Append(OPC_COPY);
	scope->builder.Append(OPC_STACK_SWAP);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_INCR);
	scope->builder.Append(OPC_STACK_POP);
}

void RDecrNode::ToByteCode(Compiler * compiler, Scope * scope) {
	children[0]->ToByteCode(compiler, scope);
	scope->builder.Append(OPC_STACK_DUP);
	scope->builder.Append(OPC_COPY);
	scope->builder.Append(OPC_STACK_SWAP);
	if(compiler->debug)
		scope->builder.Append(OPC_SET_DBG_INFO, compiler->fileName + ": " + sizeToS(line) + ": \x03");
	scope->builder.Append(OPC_DECR);
	scope->builder.Append(OPC_STACK_POP);
}








