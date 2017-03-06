/*
* Lexer.l
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

%option outfile="Lexer.cpp"
%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno
%option never-interactive
%option nounistd

%{

#include "Parser.h"

#define YY_EXTRA_TYPE Compiler *
#define YY_USER_ACTION yylloc->first_line = yylineno;


#define YY_INPUT(buf, result, max_size) {	\
	int c = yyextra->NextChar();	\
	if(c == -1)			\
		result = YY_NULL;	\
	else {				\
		buf[0] = c;		\
		result = 1;		\
	}				\
}

%}


%%

"none"		{ return TK_NONE; }
"true"		{ return TK_TRUE; }
"false"		{ return TK_FALSE; }
"global"	{ return TK_GLOBAL; }
"main"		{ return TK_MAIN; }
"args"		{ return TK_ARGS; }
"me"		{ return TK_ME; }
"parent"	{ return TK_PARENT; }
"error"		{ return TK_ERROR; }
"new"		{ return TK_NEW; }
"alloc"		{ return TK_ALLOC; }
"if"		{ return TK_IF; }
"else"		{ return TK_ELSE; }
"while"		{ return TK_WHILE; }
"for"		{ return TK_FOR; }
"try"		{ return TK_TRY; }
"catch"		{ return TK_CATCH; }
"break"		{ return TK_BREAK; }
"continue"	{ return TK_CONTINUE; }
"goto"		{ return TK_GOTO; }
"return"	{ return TK_RETURN; }
"attach"	{ return TK_ATTACH; }
"exit"		{ return TK_EXIT; }
"debug"		{ return TK_DEBUG; }
"object"	{ return TK_OBJECT; }
"extends"	{ return TK_EXTENDS; }
"delete"	{ return TK_DELETE; }
"library"	{ return TK_LIBRARY; }
"use"		{ return TK_USE; }
"like"		{ return TK_LIKE; }
"move"		{ return TK_MOVE; }
"copy"		{ return TK_COPY; }
"swap"		{ return TK_SWAP; }
"readonly"	{ return TK_READONLY; }
"external"	{ return TK_EXTERNAL; }
"idof"		{ return TK_IDOF; }
"addressof"	{ return TK_ADDRESSOF; }
"parentof"	{ return TK_PARENTOF; }
"typeof"	{ return TK_TYPEOF; }
"typestr"	{ return TK_TYPESTR; }
"throw"		{ return TK_THROW; }

[a-zA-Z_][a-zA-Z_0-9]* {
	yylval->text = new string(yytext);
	return TK_ID;
}

("0"|[1-9][0-9]*)|("0"[xX]([0-9]|[a-fA-F])+)|("0"[0-7]+) {
	yylval->text = new string(yytext);
	return TK_INT;
}

[0-9]*"."[0-9]+"p"[0-9]+ {
	yylval->text = new string(yytext);
	return TK_FLOAT;
}

[0-9]*"."[0-9]+ {
	yylval->text = new string(yytext);
	return TK_FLOAT64;
}

\'(\\.|[^\\'])+\' {
	yylval->text = new string(yytext);
	return TK_CHAR;
}

"#"("0"|[1-9][0-9]{0,2}) {
	yylval->text = new string(yytext);
	*yylval->text = "\'\\d" + yylval->text->substr(1, yylval->text->size()-1) + "\'";
	return TK_CHAR;
}

"#0"[xX]([0-9]|[a-fA-F]){1,2} {
	yylval->text = new string(yytext);
	*yylval->text = "\'\\" + yylval->text->substr(2, yylval->text->size()-2) + "\'";
	return TK_CHAR;
}

"#0"[0-7]{1,3} {
	yylval->text = new string(yytext);
	*yylval->text = "\'\\" + yylval->text->substr(2, yylval->text->size()-2) + "\'";
	return TK_CHAR;
}

\"(\\.|[^\\"])*\" {
	yylval->text = new string(yytext);
	return TK_STRING;
}

">>="		{ return TK_RSHIFT_AS; }
"<<="		{ return TK_LSHIFT_AS; }
"@="		{ return TK_REF_AS; }
"+="		{ return TK_ADD_AS; }
"-="		{ return TK_SUB_AS; }
"*="		{ return TK_MUL_AS; }
"/="		{ return TK_DIV_AS; }
"%="		{ return TK_MOD_AS; }
"&="		{ return TK_AND_AS; }
"^="		{ return TK_XOR_AS; }
"|="		{ return TK_OR_AS; }
">>"		{ return TK_RSHIFT; }
"<<"		{ return TK_LSHIFT; }
"->"		{ return TK_RBIND; }
"<-"		{ return TK_LBIND; }
"&&"		{ return TK_AND; }
"||"		{ return TK_OR; }
"<="		{ return TK_LE; }
">="		{ return TK_GE; }
"=="		{ return TK_EQ; }
"!="		{ return TK_NE; }
"++"		{ return TK_INCR; }
"--"		{ return TK_DECR; }
";"		{ return ';'; }
"{"		{ return '{'; }
"}"		{ return '}'; }
","		{ return ','; }
":"		{ return ':'; }
"?"		{ return '?'; }
"="		{ return '='; }
"("		{ return '('; }
")"		{ return ')'; }
"["		{ return '['; }
"]"		{ return ']'; }
"."		{ return '.'; }
"&"		{ return '&'; }
"!"		{ return '!'; }
"~"		{ return '~'; }
"-"		{ return '-'; }
"+"		{ return '+'; }
"*"		{ return '*'; }
"/"		{ return '/'; }
"%"		{ return '%'; }
"<"		{ return '<'; }
">"		{ return '>'; }
"^"		{ return '^'; }
"|"		{ return '|'; }
"@"		{ return '@'; }


"//".*"\n"	{}
[/][*][^*]*[*]+([^/*][^*]*[*]+)*[/] {}
[ \t\v\n\f\r]+	{ }
.		{ return TK_NOT_RECOGNIZED; }


%%


void Compiler::init() {
	yylex_init(&lexer);
	yyset_extra(this, lexer);
}

void Compiler::free() {
	yylex_destroy(lexer);
}




