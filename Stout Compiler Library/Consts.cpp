/*
* Consts.cpp
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

string sizeToS(size_t i);

Node * ConstPlus(Node * a, string file, size_t l) {
	if(a->type == NodeType::String)
		throw CompilerErr(file,l,"constant folding error, invalid unary '+' applied to a string constant");
	else if(a->type == NodeType::None)
		throw CompilerErr(file,l,"constant folding error, invalid unary '+' applied to 'none' constant");
	else if(a->type == NodeType::True || a->type == NodeType::False)
		throw CompilerErr(file,l,"constant folding error, invalid unary '+' applied to a bool constant");
	return a;
}

Node * ConstMinus(Node * a, string file, size_t l) {
	if(a->type == NodeType::String)
		throw CompilerErr(file,l,"constant folding error, invalid unary '-' applied to a string constant");
	else if(a->type == NodeType::None)
		throw CompilerErr(file,l,"constant folding error, invalid unary '-' applied to 'none' constant");
	else if(a->type == NodeType::True || a->type == NodeType::False)
		throw CompilerErr(file,l,"constant folding error, invalid unary '-' applied to a bool constant");
	else if(a->type == NodeType::Char) {
		String s = { (char)-ParseChar(((CharNode *)a)->text) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else if(a->type == NodeType::Int) {
		if(((IntNode *)a)->text[0] == '-')
			((IntNode *)a)->text.erase(((IntNode *)a)->text.begin());
		else ((IntNode *)a)->text = "-" + ((IntNode *)a)->text;
	}
	else if(a->type == NodeType::Float) {
		if(((FloatNode *)a)->text[0] == '-')
			((FloatNode *)a)->text.erase(((FloatNode *)a)->text.begin());
		else ((FloatNode *)a)->text = "-" + ((FloatNode *)a)->text;
	}
	else if(a->type == NodeType::Float64) {
		if(((Float64Node *)a)->text[0] == '-')
			((FloatNode *)a)->text.erase(((Float64Node *)a)->text.begin());
		else ((Float64Node *)a)->text = "-" + ((Float64Node *)a)->text;
	}
	return a;
}

Node * ConstBitNot(Node * a, string file, size_t l) {
	if(a->type == NodeType::String)
		throw CompilerErr(file,l,"constant folding error, invalid unary '~' applied to a string constant");
	else if(a->type == NodeType::None)
		throw CompilerErr(file,l,"constant folding error, invalid unary '~' applied to 'none' constant");
	else if(a->type == NodeType::True || a->type == NodeType::False)
		throw CompilerErr(file,l,"constant folding error, invalid unary '~' applied to a bool constant");
	else if(a->type == NodeType::Float || a->type == NodeType::Float64)
		throw CompilerErr(file,l,"constant folding error, invalid unary '~' applied to a float constant");
	else if(a->type == NodeType::Char) {
		String s = { (char)~ParseChar(((CharNode *)a)->text) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else if(a->type == NodeType::Int)
		((IntNode *)a)->text = Int(~Int(((IntNode *)a)->text)).get_str();
	return a;
}

Node * ConstNot(Node * a, string file, size_t l) {
	if(a->type == NodeType::String)
		throw CompilerErr(file,l,"constant folding error, invalid unary '!' applied to a string constant");
	else if(a->type == NodeType::None)
		throw CompilerErr(file,l,"constant folding error, invalid unary '!' applied to 'none' constant");
	else if(a->type == NodeType::Float || a->type == NodeType::Float64)
		throw CompilerErr(file,l,"constant folding error, invalid unary '!' applied to a float constant");
	else if(a->type == NodeType::True) {
		a->Destroy();
		a = new FalseNode(l);
	}
	else if(a->type == NodeType::False) {
		a->Destroy();
		a = new TrueNode(l);
	}
	else if(a->type == NodeType::Char) {
		String s = { (char)!ParseChar(((CharNode *)a)->text) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else if(a->type == NodeType::Int)
		((IntNode *)a)->text = Int(!Int(((IntNode *)a)->text).get_si()).get_str();
	return a;
}

Node * ConstTypeOf(Node * a, string file, size_t l) {
	NodeType t = a->type;
	a->Destroy();
	if(t == NodeType::None)
		a = new IntNode("1", l);
	else if(t == NodeType::Char)
		a = new IntNode("2", l);
	else if(t == NodeType::Int)
		a = new IntNode("3", l);
	else if(t == NodeType::Float64 || t == NodeType::Float)
		a = new IntNode("4", l);
	else if(t == NodeType::True || t == NodeType::False)
		a = new IntNode("5", l);
	else if(t == NodeType::String)
		a = new IntNode("6", l);
	else if(t == NodeType::Array || t == NodeType::RefArray)
		a = new IntNode("7", l);
	else if(t == NodeType::Object)
		a = new IntNode("8", l);
	return a;
}


String TypeStr(NodeType t) {
	if(t == NodeType::None)
		return "none";
	else if(t == NodeType::Char)
		return "char";
	else if(t == NodeType::Int)
		return "int";
	else if(t == NodeType::Float64 || t == NodeType::Float)
		return "float";
	else if(t == NodeType::True || t == NodeType::False)
		return "bool";
	else if(t == NodeType::String)
		return "string";
	else if(t == NodeType::Array || t == NodeType::RefArray)
		return "array";
	else if(t == NodeType::Object)
		return "object";
}


Node * ConstTypeStr(Node * a, string file, size_t l) {
	NodeType t = a->type;
	a->Destroy();
	a = new StringNode("\"" + TypeStr(t) + "\"", l);
	return a;
}


Node * createFloatNode(Float f, size_t line) {
	mp_exp_t exp;
	int c = 0;
	String str = f.get_str(exp);
	if(sgn(f) == -1)
		c = 1;
	if(str.size() == 0)
		str = "0.0";
	else {
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
	}
	if(f.get_prec() == 64)
		return new Float64Node(str, line);
	else return new FloatNode(str + "p" + sizeToS(f.get_prec()), line);
}


Node * ConstMul(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) * Int(((IntNode*)b)->text)).get_str();
		}
		else if(a->type == NodeType::Float) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) * ParseFloat(((FloatNode*)b)->text), l);
		}
		else if(a->type == NodeType::Float64) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(Float(s, 64) * Float(((Float64Node*)b)->text, 64)), l);
		}
		else if(a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) * ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if(a->type == NodeType::Int) {
		if(b->type == NodeType::Float) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) * ParseFloat(((FloatNode*)b)->text), l);
		}
		else if(b->type == NodeType::Float64) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) * Float(((FloatNode*)b)->text, 64), l);
		}
		else if(b->type == NodeType::Char) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) * ParseChar(((CharNode*)b)->text)).get_str();
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c * ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c * Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Int) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = new IntNode(Int(c * Int(((IntNode*)b)->text)).get_str(), l);
		}
	}
	else if(a->type == NodeType::Float) {
		if(b->type == NodeType::Int) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) * Int(((IntNode*)b)->text), l);
		}
		else if(b->type == NodeType::Float64) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) * Float(((Float64Node*)b)->text, 64), l);
		}
		else if(b->type == NodeType::Char) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) * ParseChar(((CharNode*)b)->text), l);
		}
	}
	else if(a->type == NodeType::Float64) {
		if(b->type == NodeType::Int) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) * Int(((IntNode*)b)->text), l);
		}
		else if(b->type == NodeType::Float) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) * ParseFloat(((FloatNode*)b)->text), l);
		}
		else if(b->type == NodeType::Char) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) * ParseChar(((CharNode*)b)->text), l);
		}
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '*' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstDiv(Node * a, Node * b, string file, size_t l) {
	if (a->type == b->type) {
		if (a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) / Int(((IntNode*)b)->text)).get_str();
		}
		else if (a->type == NodeType::Float) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) / ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (a->type == NodeType::Float64) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(Float(s, 64) / Float(((Float64Node*)b)->text, 64)), l);
		}
		else if (a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) / ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if (a->type == NodeType::Int) {
		if (b->type == NodeType::Float) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) / ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) / Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Char) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) / ParseChar(((CharNode*)b)->text)).get_str();
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c / ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c / Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Int) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = new IntNode(Int(c / Int(((IntNode*)b)->text)).get_str(), l);
		}
	}
	else if (a->type == NodeType::Float) {
		if (b->type == NodeType::Int) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) / Int(((IntNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) / Float(((Float64Node*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Char) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) / ParseChar(((CharNode*)b)->text), l);
		}
	}
	else if (a->type == NodeType::Float64) {
		if (b->type == NodeType::Int) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) / Int(((IntNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) / ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Char) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) / ParseChar(((CharNode*)b)->text), l);
		}
	}
	else {
		throw CompilerErr(file, l, "constant folding error, invalid '/' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstMod(Node * a, Node * b, string file, size_t l) {
	if (a->type == b->type) {
		if (a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) % Int(((IntNode*)b)->text)).get_str();
		}
		else if (a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) % ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if (a->type == NodeType::Int && b->type == NodeType::Char) {
		((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) % ParseChar(((CharNode*)b)->text)).get_str();
	}
	else if (a->type == NodeType::Char && b->type == NodeType::Int) {
		Char c = ParseChar(((CharNode*)a)->text);
		a->Destroy();
		a = new IntNode(Int(c % Int(((IntNode*)b)->text)).get_str(), l);
	}
	else {
		throw CompilerErr(file, l, "constant folding error, invalid '/' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstAdd(Node * a, Node * b, string file, size_t l) {
	if (a->type == b->type) {
		if (a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) + Int(((IntNode*)b)->text)).get_str();
		}
		else if (a->type == NodeType::Float) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) + ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (a->type == NodeType::Float64) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(Float(s, 64) + Float(((Float64Node*)b)->text, 64)), l);
		}
		else if (a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) + ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
		else if (a->type == NodeType::String) {
			((StringNode *)a)->text += ((StringNode*)b)->text;
		}
		else if (a->type == NodeType::Array || a->type == NodeType::RefArray) {
			if (b->children[0] != nullptr) {
				if (a->children[0] == nullptr)
					a->children[0] = b->children[0];
				else {
					for (unsigned i = 0; i < b->children[0]->children.size(); ++i)
						a->children[0]->children.push_back(b->children[0]->children[i]);
				}
				delete b;
				return a;
			}
			
		}
	}
	else if (a->type == NodeType::Int) {
		if (b->type == NodeType::Float) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) + ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) + Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Char) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) + ParseChar(((CharNode*)b)->text)).get_str();
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c + ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c + Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Int) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = new IntNode(Int(c + Int(((IntNode*)b)->text)).get_str(), l);
		}
	}
	else if (a->type == NodeType::Float) {
		if (b->type == NodeType::Int) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) + Int(((IntNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) + Float(((Float64Node*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Char) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) + ParseChar(((CharNode*)b)->text), l);
		}
	}
	else if (a->type == NodeType::Float64) {
		if (b->type == NodeType::Int) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) + Int(((IntNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) + ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Char) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) + ParseChar(((CharNode*)b)->text), l);
		}
	}
	else {
		throw CompilerErr(file, l, "constant folding error, invalid '+' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}



Node * ConstSub(Node * a, Node * b, string file, size_t l) {
	if (a->type == b->type) {
		if (a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) - Int(((IntNode*)b)->text)).get_str();
		}
		else if (a->type == NodeType::Float) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) - ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (a->type == NodeType::Float64) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(Float(s, 64) - Float(((Float64Node*)b)->text, 64)), l);
		}
		else if (a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) - ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if (a->type == NodeType::Int) {
		if (b->type == NodeType::Float) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) - ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			String s = ((IntNode*)a)->text;
			a->Destroy();
			a = createFloatNode(Int(s) - Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Char) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) - ParseChar(((CharNode*)b)->text)).get_str();
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c - ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = createFloatNode(c - Float(((FloatNode*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Int) {
			Char c = ParseChar(((CharNode*)a)->text);
			a->Destroy();
			a = new IntNode(Int(c - Int(((IntNode*)b)->text)).get_str(), l);
		}
	}
	else if (a->type == NodeType::Float) {
		if (b->type == NodeType::Int) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) - Int(((IntNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float64) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) - Float(((Float64Node*)b)->text, 64), l);
		}
		else if (b->type == NodeType::Char) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) - ParseChar(((CharNode*)b)->text), l);
		}
	}
	else if (a->type == NodeType::Float64) {
		if (b->type == NodeType::Int) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) - Int(((IntNode*)b)->text), l);
		}
		else if (b->type == NodeType::Float) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) - ParseFloat(((FloatNode*)b)->text), l);
		}
		else if (b->type == NodeType::Char) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) - ParseChar(((CharNode*)b)->text), l);
		}
	}
	else {
		throw CompilerErr(file, l, "constant folding error, invalid '-' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstLShift(Node * a, Node * b, string file, size_t l) {
	if (a->type == NodeType::Int && b->type == NodeType::Int) {
		Int r;
		mpz_mul_2exp(r.get_mpz_t(), Int(((IntNode *)a)->text).get_mpz_t(), Int(((IntNode *)b)->text).get_ui());
		((IntNode *)a)->text = r.get_str();
	}
	else if (a->type == NodeType::Float && b->type == NodeType::Int) {
		String s = ((FloatNode*)a)->text;
		a->Destroy();
		Float r;
		mpf_mul_2exp(r.get_mpf_t(), ParseFloat(s).get_mpf_t(), Int(((IntNode *)b)->text).get_ui());
		a = createFloatNode(r, l);
	}
	else if (a->type == NodeType::Float64 && b->type == NodeType::Int) {
		String s = ((Float64Node*)a)->text;
		a->Destroy();
		Float r;
		mpf_mul_2exp(r.get_mpf_t(), Float(s, 64).get_mpf_t(), Int(((IntNode *)b)->text).get_ui());
		a = createFloatNode(r, l);
	}
	else if (a->type == NodeType::Char && b->type == NodeType::Int) {
		String s = { (char)(ParseChar(((CharNode*)a)->text) << Int(((IntNode*)b)->text).get_ui()) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else {
		throw CompilerErr(file, l, "constant folding error, invalid '<<' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstRShift(Node * a, Node * b, string file, size_t l) {
	if (a->type == NodeType::Int && b->type == NodeType::Int) {
		Int r;
		mpz_fdiv_q_2exp(r.get_mpz_t(), Int(((IntNode *)a)->text).get_mpz_t(), Int(((IntNode *)b)->text).get_ui());
		((IntNode *)a)->text = r.get_str();
	}
	else if (a->type == NodeType::Float && b->type == NodeType::Int) {
		String s = ((FloatNode*)a)->text;
		a->Destroy();
		Float r;
		mpf_div_2exp(r.get_mpf_t(), ParseFloat(s).get_mpf_t(), Int(((IntNode *)b)->text).get_ui());
		a = createFloatNode(r, l);
	}
	else if (a->type == NodeType::Float64 && b->type == NodeType::Int) {
		String s = ((Float64Node*)a)->text;
		a->Destroy();
		Float r;
		mpf_div_2exp(r.get_mpf_t(), Float(s, 64).get_mpf_t(), Int(((IntNode *)b)->text).get_ui());
		a = createFloatNode(r, l);
	}
	else if (a->type == NodeType::Char && b->type == NodeType::Int) {
		String s = { (char)(ParseChar(((CharNode*)a)->text) >> Int(((IntNode*)b)->text).get_ui()) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else {
		throw CompilerErr(file, l, "constant folding error, invalid '<<' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}




Node * ConstGE(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			Int A(((IntNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float64) {
			Float A(((Float64Node*)a)->text, 64);
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Char) {
			Char A = ParseChar(((CharNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Int) {
		if(b->type == NodeType::Float) {
			Int A(((IntNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Int A(((IntNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Int A(((IntNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Float64) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Int) {
			Char A = ParseChar(((CharNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float) {
		if(b->type == NodeType::Int) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Int B(((IntNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float64) {
		if(b->type == NodeType::Int) {
			Float A(((FloatNode*)a)->text, 64);
			Int B(((IntNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float) {
			Float A(((FloatNode*)a)->text, 64);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(((FloatNode*)a)->text, 64);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A >= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '>=' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}



Node * ConstLE(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			Int A(((IntNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float64) {
			Float A(((Float64Node*)a)->text, 64);
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Char) {
			Char A = ParseChar(((CharNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Int) {
		if(b->type == NodeType::Float) {
			Int A(((IntNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Int A(((IntNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Int A(((IntNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Float64) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Int) {
			Char A = ParseChar(((CharNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float) {
		if(b->type == NodeType::Int) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Int B(((IntNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float64) {
		if(b->type == NodeType::Int) {
			Float A(((FloatNode*)a)->text, 64);
			Int B(((IntNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float) {
			Float A(((FloatNode*)a)->text, 64);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(((FloatNode*)a)->text, 64);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A <= B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '<=' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}




Node * ConstGreater(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			Int A(((IntNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float64) {
			Float A(((Float64Node*)a)->text, 64);
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Char) {
			Char A = ParseChar(((CharNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Int) {
		if(b->type == NodeType::Float) {
			Int A(((IntNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Int A(((IntNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Int A(((IntNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Float64) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Int) {
			Char A = ParseChar(((CharNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float) {
		if(b->type == NodeType::Int) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Int B(((IntNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float64) {
		if(b->type == NodeType::Int) {
			Float A(((FloatNode*)a)->text, 64);
			Int B(((IntNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float) {
			Float A(((FloatNode*)a)->text, 64);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(((FloatNode*)a)->text, 64);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A > B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '>' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}



Node * ConstLower(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			Int A(((IntNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Float64) {
			Float A(((Float64Node*)a)->text, 64);
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(a->type == NodeType::Char) {
			Char A = ParseChar(((CharNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Int) {
		if(b->type == NodeType::Float) {
			Int A(((IntNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Int A(((IntNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Int A(((IntNode*)a)->text);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if (a->type == NodeType::Char) {
		if (b->type == NodeType::Float) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Float64) {
			Char A = ParseChar(((CharNode*)a)->text);
			Float B(((FloatNode*)b)->text, 64);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if (b->type == NodeType::Int) {
			Char A = ParseChar(((CharNode*)a)->text);
			Int B(((IntNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float) {
		if(b->type == NodeType::Int) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Int B(((IntNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float64) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Float B(((Float64Node*)b)->text, 64);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(ParseFloat(((FloatNode*)a)->text));
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else if(a->type == NodeType::Float64) {
		if(b->type == NodeType::Int) {
			Float A(((FloatNode*)a)->text, 64);
			Int B(((IntNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Float) {
			Float A(((FloatNode*)a)->text, 64);
			Float B(ParseFloat(((FloatNode*)b)->text));
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
		else if(b->type == NodeType::Char) {
			Float A(((FloatNode*)a)->text, 64);
			Char B = ParseChar(((CharNode*)b)->text);
			Bool b = A < B;
			a->Destroy();
			if(b) a = new TrueNode(l);
			else a = new FalseNode(l);
		}
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '<' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}




Node * ConstAnd(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) & Int(((IntNode*)b)->text)).get_str();
		}
		else if(a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) & ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if(a->type == NodeType::Int && b->type == NodeType::Char) {
		((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) & ParseChar(((CharNode*)b)->text)).get_str();
	}
	else if (a->type == NodeType::Char && b->type == NodeType::Int) {
		Char c = ParseChar(((CharNode*)a)->text);
		a->Destroy();
		a = new IntNode(Int(c & Int(((IntNode*)b)->text)).get_str(), l);
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '&' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstOr(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) | Int(((IntNode*)b)->text)).get_str();
		}
		else if(a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) | ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if(a->type == NodeType::Int && b->type == NodeType::Char) {
		((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) | ParseChar(((CharNode*)b)->text)).get_str();
	}
	else if (a->type == NodeType::Char && b->type == NodeType::Int) {
		Char c = ParseChar(((CharNode*)a)->text);
		a->Destroy();
		a = new IntNode(Int(c | Int(((IntNode*)b)->text)).get_str(), l);
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '|' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstXor(Node * a, Node * b, string file, size_t l) {
	if(a->type == b->type) {
		if(a->type == NodeType::Int) {
			((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) ^ Int(((IntNode*)b)->text)).get_str();
		}
		else if(a->type == NodeType::Char) {
			String s = { (char)(ParseChar(((CharNode*)a)->text) ^ ParseChar(((CharNode*)b)->text)) };
			((CharNode *)a)->text = "\"" + s + "\"";
		}
	}
	else if(a->type == NodeType::Int && b->type == NodeType::Char) {
		((IntNode *)a)->text = Int(Int(((IntNode*)a)->text) ^ ParseChar(((CharNode*)b)->text)).get_str();
	}
	else if (a->type == NodeType::Char && b->type == NodeType::Int) {
		Char c = ParseChar(((CharNode*)a)->text);
		a->Destroy();
		a = new IntNode(Int(c ^ Int(((IntNode*)b)->text)).get_str(), l);
	}
	else {
		throw CompilerErr(file,l,"constant folding error, invalid '^' applied to " + TypeStr(a->type) + " and " + TypeStr(b->type) + " constants");
	}
	b->Destroy();
	return a;
}


Node * ConstIncr(Node * a, string file, size_t l) {
	if(a->type == NodeType::String)
		throw CompilerErr(file,l,"constant folding error, invalid unary '++' applied to a string constant");
	else if(a->type == NodeType::None)
		throw CompilerErr(file,l,"constant folding error, invalid unary '++' applied to 'none' constant");
	else if(a->type == NodeType::True) {
		a->Destroy();
		a = new FalseNode(l);
	}
	else if(a->type == NodeType::False) {
		a->Destroy();
		a = new TrueNode(l);
	}
	else if(a->type == NodeType::Char) {
		String s = { (char)(1+ParseChar(((CharNode *)a)->text)) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else if(a->type == NodeType::Int)
		((IntNode *)a)->text = Int(1+(Int(((IntNode *)a)->text).get_si())).get_str();
	else if(a->type == NodeType::Float) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) + 1, l);
	}
	else if(a->type == NodeType::Float64) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) + 1, l);
	}
	return a;
}


Node * ConstDecr(Node * a, string file, size_t l) {
	if(a->type == NodeType::String)
		throw CompilerErr(file,l,"constant folding error, invalid unary '--' applied to a string constant");
	else if(a->type == NodeType::None)
		throw CompilerErr(file,l,"constant folding error, invalid unary '--' applied to 'none' constant");
	else if(a->type == NodeType::True) {
		a->Destroy();
		a = new FalseNode(l);
	}
	else if(a->type == NodeType::False) {
		a->Destroy();
		a = new TrueNode(l);
	}
	else if(a->type == NodeType::Char) {
		String s = { (char)(ParseChar(((CharNode *)a)->text)-1) };
		((CharNode *)a)->text = "\"" + s + "\"";
	}
	else if(a->type == NodeType::Int)
		((IntNode *)a)->text = Int((Int(((IntNode *)a)->text).get_si())-1).get_str();
	else if(a->type == NodeType::Float) {
			String s = ((FloatNode*)a)->text;
			a->Destroy();
			a = createFloatNode(ParseFloat(s) - 1, l);
	}
	else if(a->type == NodeType::Float64) {
			String s = ((Float64Node*)a)->text;
			a->Destroy();
			a = createFloatNode(Float(s, 64) - 1, l);
	}
	return a;
}







