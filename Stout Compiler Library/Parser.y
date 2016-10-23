/*
* Parser.y
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

%output  "Parser.cpp"
%pure-parser
%locations
%defines "Parser.h"
%error-verbose
%parse-param { Compiler * compiler }
%lex-param { void * lexer }

%code requires {

#include "StoutCompiler.h"

}

%{

#include "Parser.h"
#include <sstream>

int yylex(YYSTYPE * lvalp, YYLTYPE * llocp, void * lexer);

void yyerror(YYLTYPE * locp, Compiler * compiler, const char * err) {
	throw CompilerErr(compiler->fileName, locp->first_line, err);
}

#define lexer compiler->lexer

bool isConst(Node * node) {
	if(node->type == NodeType::True ||
	node->type == NodeType::False ||
	node->type == NodeType::None ||
	node->type == NodeType::Char ||
	node->type == NodeType::Int ||
	node->type == NodeType::Float ||
	node->type == NodeType::Float64 ||
	node->type == NodeType::String)
		return true;
	if(node->type == NodeType::Array || node->type == NodeType::RefArray) {
		/*if(node->children[0] == nullptr)
			return true;
		for(size_t i = 0; i < node->children.size(); ++i)
			if(!isConst(node->children[i]))
				return false;*/
		return true;
	}
	return false;
}

%}

%union {
   string * text;
   Node * node;
}

%token	TK_TRUE "'true'"
%token	TK_FALSE "'false'"
%token	TK_NONE "'none'"
%token	TK_GLOBAL "'global'"
%token	TK_MAIN "'main'"
%token	TK_ARGS "'args'"
%token	TK_ME "'me'"
%token	TK_PARENT "'parent'"
%token	TK_ERROR "'error'"
%token	TK_NEW "'new'"
%token	TK_ALLOC "'alloc'"
%token	TK_IF "'if'"
%token	TK_ELSE "'else'"
%token	TK_WHILE "'while'"
%token	TK_FOR "'for'"
%token	TK_TRY "'try'"
%token	TK_CATCH "'catch'"
%token	TK_BREAK "'break'"
%token	TK_CONTINUE "'continue'"
%token	TK_GOTO "'goto'"
%token	TK_RETURN "'return'"
%token	TK_ATTACH "'attach'"
%token	TK_EXIT "'exit'"
%token	TK_DEBUG "'debug'"
%token	TK_OBJECT "'object'"
%token	TK_EXTENDS "'extends'"
%token	TK_DELETE "'delete'"
%token	TK_LIBRARY "'library'"
%token	TK_USE "'use'"
%token	TK_LIKE "'like'"
%token	TK_MOVE "'move'"
%token	TK_COPY "'copy'"
%token	TK_SWAP "'swap'"
%token	TK_READONLY "'readonly'"
%token	TK_EXTERNAL "'external'"
%token	TK_ADDRESSOF "'addressof'"
%token	TK_IDOF "'idof'"
%token	<text> TK_ID "identifier"
%token	<text> TK_INT "int"
%token	<text> TK_FLOAT "float"
%token	<text> TK_FLOAT64 "float64"
%token	<text> TK_CHAR "char"
%token	<text> TK_STRING "string"
%token	TK_RSHIFT_AS "'>>='"
%token	TK_LSHIFT_AS "'<<='"
%token	TK_REF_AS "'@='"
%token	TK_ADD_AS "'+='"
%token	TK_SUB_AS "'-='"
%token	TK_MUL_AS "'*='"
%token	TK_DIV_AS "'/='"
%token	TK_MOD_AS "'%='"
%token	TK_AND_AS "'&='"
%token	TK_XOR_AS "'^='"
%token	TK_OR_AS "'|='"
%token	TK_RSHIFT "'>>'"
%token	TK_LSHIFT "'<<'"
%token	TK_RBIND "'->'"
%token	TK_LBIND "'<-'"
%token	TK_AND "'&&'"
%token	TK_OR "'||'"
%token	TK_LE "'<='"
%token	TK_GE "'>='"
%token	TK_EQ "'=='"
%token	TK_NE "'!='"
%token	TK_INCR "'++'"
%token	TK_DECR "'--'"
%token	TK_TYPEOF "'typeof'"
%token	TK_TYPESTR "'typestr'"
%token	TK_PARENTOF "'parentof'"
%token	TK_THROW "'throw'"
%token	TK_NOT_RECOGNIZED "invalid character"

%type <node>  stmt_list compound_stmt expr_stmt stmt
%type <node>  expr assign_expr cond_expr logic_or_expr logic_and_expr
%type <node>  or_expr xor_expr and_expr equal_expr comparison_expr
%type <node>  shift_expr add_expr mul_expr unary_expr new_expr
%type <node>  expr_list postfix_expr primary_expr start



%start start

%%


start
	: stmt_list	{ compiler->tree = $1; }
	;

stmt_list
	: stmt	{ $$ = new StmtListNode($1, @1.first_line); }
	| stmt_list stmt	{ $1->children.push_back($2); $$ = $1; }
	;

compound_stmt
	: '{' stmt_list '}'	{ $$ = $2; }
	| '{' '}'	{ $$ = new StmtListNode(nullptr, @1.first_line); }
	;
      
expr_stmt
	: ';'	{ $$ = new ExprStmtNode(nullptr, @1.first_line); }
	| expr ';' { $$ = new ExprStmtNode($1, @1.first_line); }
	;

stmt
	: TK_ID ':' stmt	{ $$ = new LabelNode(*$1, $3, @1.first_line); }
	| TK_IF '(' expr ')' stmt	{ $$ = new IfNode($3, $5, @1.first_line); }
	| TK_IF '(' expr ')' stmt TK_ELSE stmt	{ $$ = new IfElseNode($3, $5, $7, @1.first_line); }
	| TK_WHILE '(' expr ')' stmt	{ $$ = new WhileNode($3, $5, @1.first_line); }
	| TK_FOR '(' expr_stmt expr_stmt ')' stmt	{ $$ = new ForNode($3, $4, nullptr, $6, @1.first_line); }
	| TK_FOR '(' expr_stmt expr_stmt expr ')' stmt	{ $$ = new ForNode($3, $4, $5, $7, @1.first_line); }
	| TK_FOR '(' TK_ID ':' expr ')' stmt	{ $$ = new ForEachNode(*$3, $5, $7, @1.first_line); }
	| TK_TRY stmt	{ $$ = new TryNode($2, @1.first_line); }
	| TK_TRY stmt TK_CATCH stmt	{ $$ = new TryCatchNode($2, $4, @1.first_line); }
	| TK_DEBUG expr ';'	{ $$ = new DebugNode($2, @1.first_line); }
	| TK_USE TK_ID ';'	{ $$ = new UseNode(*$2, nullptr, @1.first_line); }
	| TK_USE TK_ID expr ';'	{ $$ = new UseNode(*$2, $3, @1.first_line); }
	| TK_EXTENDS expr ';'	{ $$ = new ExtendsNode($2, @1.first_line); }
	| TK_THROW expr ';'	{ $$ = new ThrowNode($2, @1.first_line); }
	| TK_DELETE expr ';'	{ $$ = new DeleteNode($2, @1.first_line); }
	| TK_LIBRARY TK_ID ';'	{ $$ = new LibraryNode(*$2, nullptr, @1.first_line); }
	| TK_LIBRARY TK_ID expr ';'	{ $$ = new LibraryNode(*$2, $3, @1.first_line); }
	| TK_GOTO TK_ID ';'	{ $$ = new GotoNode(*$2, @1.first_line); }
	| TK_CONTINUE ';'	{ $$ = new ContinueNode(@1.first_line); }
	| TK_BREAK ';'	{ $$ = new BreakNode(@1.first_line); }
	| TK_RETURN ';'	{ $$ = new ReturnNode(nullptr, @1.first_line); }
	| TK_RETURN expr ';'	{ $$ = new ReturnNode($2, @1.first_line); }
	| TK_EXIT ';'		{ $$ = new ExitNode(nullptr, @1.first_line); }
	| TK_EXIT expr ';'	{ $$ = new ExitNode($2, @1.first_line); }
	| compound_stmt	{ $$ = $1; }
	| expr_stmt	{ $$ = $1; }
	;

expr
	: assign_expr	{ $$ = $1; }
	| TK_READONLY expr	{ $$ = new ReadOnlyNode($2, @1.first_line); }
	;

assign_expr
	: cond_expr	{ $$ = $1; }
	| unary_expr '=' expr 	{ $$ = new AssignNode($1, $3, @2.first_line); }
	| unary_expr TK_RBIND expr 	{ $$ = new RBindNode($1, $3, @2.first_line); }
	| unary_expr TK_LBIND expr 	{ $$ = new LBindNode($1, $3, @2.first_line); }
	| unary_expr TK_REF_AS expr 	{ $$ = new RefAsNode($1, $3, @2.first_line); }
	| unary_expr TK_MUL_AS expr 	{ $$ = new MulAsNode($1, $3, @2.first_line); }
	| unary_expr TK_DIV_AS expr 	{ $$ = new DivAsNode($1, $3, @2.first_line); }
	| unary_expr TK_MOD_AS expr 	{ $$ = new ModAsNode($1, $3, @2.first_line); }
	| unary_expr TK_ADD_AS expr 	{ $$ = new AddAsNode($1, $3, @2.first_line); }
	| unary_expr TK_SUB_AS expr 	{ $$ = new SubAsNode($1, $3, @2.first_line); }
	| unary_expr TK_LSHIFT_AS expr 	{ $$ = new LShiftAsNode($1, $3, @2.first_line); }
	| unary_expr TK_RSHIFT_AS expr 	{ $$ = new RShiftAsNode($1, $3, @2.first_line); }
	| unary_expr TK_AND_AS expr 	{ $$ = new AndAsNode($1, $3, @2.first_line); }
	| unary_expr TK_XOR_AS expr 	{ $$ = new XorAsNode($1, $3, @2.first_line); }
	| unary_expr TK_OR_AS expr 	{ $$ = new OrAsNode($1, $3, @2.first_line); }
	;

cond_expr
	: logic_or_expr {
		if($1->children.size() == 1) {
			Node * n = $1;
			$1 = n->children[0];
			delete n;
			if($1->type == NodeType::LogicAnd)
				$$ = new LogicNode($1, $1->line);
			else $$ = $1;
		}	
		else $$ = new LogicNode($1, $1->line);
	}
	| logic_or_expr '?' expr ':' cond_expr {
		Node * tmp;
		if($1->children.size() == 1) {
			Node * n = $1;
			$1 = n->children[0];
			delete n;
			if($1->type == NodeType::LogicAnd)
				tmp = new LogicNode($1, $1->line);
			else tmp = $1;
		}	
		else tmp = new LogicNode($1, $1->line);
		$$ = new CondNode(tmp, $3, $5, @2.first_line);
	}
	;

logic_or_expr
	: logic_and_expr { 
		if($1->children.size() == 1) {
			Node * n = $1;
			$1 = n->children[0];
			delete n;
		}	
		$$ = new LogicOrNode($1, @1.first_line);
	}
	| logic_or_expr TK_OR logic_and_expr {
		if($3->children.size() == 1) {
			Node * n = $3;
			$3 = n->children[0];
			delete n;
		}
		$1->children.push_back($3); 
		$$ = $1;
	}
	;
	
logic_and_expr
	: or_expr {
		if($1->type == NodeType::Logic) {
			Node * n = $1;
			$1 = n->children[0];
			delete n;
		}
		$$ = new LogicAndNode($1, @1.first_line);
	}
	| logic_and_expr TK_AND or_expr {
		if($3->type == NodeType::Logic) {
			Node * n = $3;
			$3 = n->children[0];
			delete n;
		}
		$1->children.push_back($3);
		$$ = $1;
	}
	;

or_expr
	: xor_expr	{ $$ = $1; }
	| or_expr '|' xor_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstOr($1, $3, compiler->fileName, @2.first_line);
		else $$ = new OrNode($1, $3, @2.first_line);
	}
	;

xor_expr
	: and_expr	{ $$ = $1; }
	| xor_expr '^' and_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstXor($1, $3, compiler->fileName, @2.first_line);
		else $$ = new XorNode($1, $3, @2.first_line);
	}
	;

and_expr
	: equal_expr	{ $$ = $1; }
	| and_expr '&' equal_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstAnd($1, $3, compiler->fileName, @2.first_line);
		else $$ = new AndNode($1, $3, @2.first_line);
	}
	;

equal_expr
	: comparison_expr	{ $$ = $1; }
	| equal_expr TK_EQ comparison_expr 	{ $$ = new EQNode($1, $3, @2.first_line); }
	| equal_expr TK_NE comparison_expr 	{ $$ = new NENode($1, $3, @2.first_line); }
	| equal_expr TK_LIKE comparison_expr 	{ $$ = new LikeNode($1, $3, @2.first_line); }
	;

comparison_expr
	: shift_expr	{ $$ = $1; }
	| comparison_expr '<' shift_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstLower($1, $3, compiler->fileName, @2.first_line);
		else $$ = new LowerNode($1, $3, @2.first_line);
	}
	| comparison_expr '>' shift_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstGreater($1, $3, compiler->fileName, @2.first_line);
		else $$ = new GreaterNode($1, $3, @2.first_line);
	}
	| comparison_expr TK_LE shift_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstLE($1, $3, compiler->fileName, @2.first_line);
		else $$ = new LENode($1, $3, @2.first_line);
	}
	| comparison_expr TK_GE shift_expr 	{
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstGE($1, $3, compiler->fileName, @2.first_line);
		else $$ = new GENode($1, $3, @2.first_line);
	}
	;

shift_expr
	: add_expr	{ $$ = $1; }
	| shift_expr TK_LSHIFT add_expr {
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstLShift($1, $3, compiler->fileName, @2.first_line);
		else $$ = new LShiftNode($1, $3, @2.first_line);
	}
	| shift_expr TK_RSHIFT add_expr {
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstRShift($1, $3, compiler->fileName, @2.first_line);
		else $$ = new RShiftNode($1, $3, @2.first_line);
	}
	;

add_expr
	: mul_expr	{ $$ = $1; }
	| add_expr '+' mul_expr {
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstAdd($1, $3, compiler->fileName, @2.first_line);
		else $$ = new AddNode($1, $3, @2.first_line);
	}
	| add_expr '-' mul_expr {
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstSub($1, $3, compiler->fileName, @2.first_line);
		else $$ = new SubNode($1, $3, @2.first_line);
	}
	;

mul_expr
	: unary_expr	{ $$ = $1; }
	| mul_expr '*' unary_expr {
		if(isConst($1) && isConst($3) && compiler->optimize)
			$$ = ConstMul($1, $3, compiler->fileName, @2.first_line);
		else $$ = new MulNode($1, $3, @2.first_line);
	}
	| mul_expr '/' unary_expr {
		if(isConst($1) && isConst($3) && compiler->optimize) {
			if($3->type == NodeType::Int && Int(((IntNode*)$3)->text) == 0 ||
				$3->type == NodeType::Float && ParseFloat(((IntNode*)$3)->text) == 0.0 ||
				$3->type == NodeType::Float64 && Float(((IntNode*)$3)->text, 64) == 0.0 ||
				$3->type == NodeType::Char && ParseChar(((IntNode*)$3)->text) == 0)
					$$ = new DivNode($1, $3, @2.first_line);
			else $$ = ConstDiv($1, $3, compiler->fileName, @2.first_line);
		}
		else $$ = new DivNode($1, $3, @2.first_line);
	}
	| mul_expr '%' unary_expr {
		if(isConst($1) && isConst($3) && compiler->optimize) {
			if($3->type == NodeType::Int && Int(((IntNode*)$3)->text) == 0 ||
				$3->type == NodeType::Float && ParseFloat(((IntNode*)$3)->text) == 0.0 ||
				$3->type == NodeType::Float64 && Float(((IntNode*)$3)->text, 64) == 0.0 ||
				$3->type == NodeType::Char && ParseChar(((IntNode*)$3)->text) == 0)
					$$ = new ModNode($1, $3, @2.first_line);
			else $$ = ConstMod($1, $3, compiler->fileName, @2.first_line);
		}
		else $$ = new ModNode($1, $3, @2.first_line);
	}
	;

unary_expr
	: new_expr	{ $$ = $1; }
	| '+' unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstPlus($2, compiler->fileName, @1.first_line);
		else $$ = new PlusNode($2, @1.first_line);
	}
	| '-' unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstMinus($2, compiler->fileName, @1.first_line);
		else $$ = new MinusNode($2, @1.first_line);
	}
	| '~' unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstBitNot($2, compiler->fileName, @1.first_line);
		else $$ = new BitNotNode($2, @1.first_line);
	}
	| '!' unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstNot($2, compiler->fileName, @1.first_line);
		else $$ = new NotNode($2, @1.first_line);
	}
	| TK_INCR unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstIncr($2, compiler->fileName, @1.first_line);
		else $$ = new LIncrNode($2, @1.first_line);
	}
	| TK_DECR unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstDecr($2, compiler->fileName, @1.first_line);
		else $$ = new LDecrNode($2, @1.first_line);
	}
	| TK_ADDRESSOF unary_expr	{ $$ = new AddrOfNode($2, @1.first_line); }
	| TK_IDOF unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = ConstTypeOf($2, compiler->fileName, @1.first_line);
		else $$ = new IdOfNode($2, @1.first_line);
	}
	| TK_TYPEOF unary_expr {
		if(($2->type == NodeType::Object || isConst($2)) && compiler->optimize)
			$$ = ConstTypeOf($2, compiler->fileName, @1.first_line);
		else $$ = new TypeOfNode($2, @1.first_line);
	}
	| TK_PARENTOF unary_expr	{ $$ = new ParentOfNode($2, @1.first_line); }
	| TK_TYPESTR unary_expr {
		if(($2->type == NodeType::Object || isConst($2)) && compiler->optimize)
			$$ = ConstTypeStr($2, compiler->fileName, @1.first_line);
		else $$ = new TypeStrNode($2, @1.first_line);
	}
	| TK_MOVE unary_expr {
		if(isConst($2) && compiler->optimize)
			$$ = $2;
		else $$ = new MoveNode($2, @1.first_line);
	}
	| TK_COPY unary_expr	{ $$ = new CopyNode($2, @1.first_line); }
	| TK_ALLOC unary_expr	{ $$ = new AllocNode($2, @1.first_line); }
	;

expr_list
	: expr	{ $$ = new ExprListNode($1, @1.first_line); }
	| expr_list ',' expr 	{ $1->children.push_back($3); $$ = $1; }
	;

new_expr
	: postfix_expr	{ $$ = $1; }
	| TK_NEW postfix_expr '(' ')' 	{ $$ = new NewNode($2, nullptr, @1.first_line); }
	| TK_NEW postfix_expr '(' expr_list ')' 	{ $$ = new NewNode($2, $4, @1.first_line); }
	| TK_NEW postfix_expr '{' expr '}' 	{ $$ = new NewArrNode($2, $4, @1.first_line); }
	;

postfix_expr
	: primary_expr	{ $$ = $1; }
	| postfix_expr '[' expr ']' 	{ $$ = new AtNode($1, $3, @2.first_line); }
	| postfix_expr '(' ')'		{ $$ = new CallNode($1, nullptr, @2.first_line); }
	| postfix_expr '{' expr '}'		{ $$ = new CallArrNode($1, $3, @2.first_line); }
	| postfix_expr '(' expr_list ')'	{ $$ = new CallNode($1, $3, @2.first_line); }
	| postfix_expr '.' TK_ID	{ $$ = new AttrNode(*$3, $1, @2.first_line); }
	| postfix_expr TK_INCR	{
		if(isConst($1) && compiler->optimize)
			$$ = ConstIncr($1, compiler->fileName, @2.first_line);
		else $$ = new RIncrNode($1, @2.first_line);
	}
	| postfix_expr TK_DECR	{
		if(isConst($1) && compiler->optimize)
			$$ = ConstDecr($1, compiler->fileName, @2.first_line);
		else $$ = new RDecrNode($1, @2.first_line);
	}
	;

primary_expr
	: TK_TRUE { $$ = new TrueNode(@1.first_line); }
	| TK_FALSE { $$ = new FalseNode(@1.first_line); }
	| TK_NONE { $$ = new NoneNode(@1.first_line); }
	| TK_ID { $$ = new IdNode(*$1, @1.first_line); }
	| TK_ATTACH TK_ID { $$ = new AttachNode(*$2, @1.first_line); }
	| TK_INT { $$ = new IntNode(*$1, @1.first_line); }
	| TK_FLOAT { $$ = new FloatNode(*$1, @1.first_line); }
	| TK_FLOAT64 { $$ = new Float64Node(*$1, @1.first_line); }
	| TK_CHAR { $$ = new CharNode(*$1, @1.first_line); }
	| TK_STRING { $$ = new StringNode(*$1, @1.first_line); }
	| TK_GLOBAL { $$ = new GlobalNode(@1.first_line); }
	| TK_MAIN { $$ = new MainNode(@1.first_line); }
	| TK_ARGS { $$ = new ArgsNode(@1.first_line); }
	| TK_ME { $$ = new MeNode(@1.first_line); }
	| TK_PARENT { $$ = new ParentNode(@1.first_line); }
	| TK_ERROR { $$ = new ErrorNode(@1.first_line); }
	| TK_EXTERNAL '(' expr ',' expr ')' { $$ = new ExternalNode($3, $5, @1.first_line); }
	| TK_SWAP '(' expr ',' expr ')' { $$ = new SwapNode($3, $5, @1.first_line); }
	| TK_OBJECT compound_stmt	{ $$ = new ObjectNode(nullptr , $2, @1.first_line); }
	| TK_OBJECT '(' expr ')' compound_stmt	{ $$ = new ObjectNode($3, $5, @1.first_line); }
	| '@' '[' expr_list ']'	{ $$ = new RefArrayNode($3, @1.first_line); } 
	| '@' '[' ']'	{ $$ = new RefArrayNode(nullptr, @1.first_line); } 
	| '[' expr_list ']'	{ $$ = new ArrayNode($2, @1.first_line); } 
	| '[' ']'	{ $$ = new ArrayNode(nullptr, @1.first_line); } 
	| '(' expr ')'	{ $$ = $2; }





%%







