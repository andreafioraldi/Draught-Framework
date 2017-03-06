#include "Dubbel.h"
#include "DubbelAssembler.h"
#include "DubbelDisassembler.h"

using namespace std;
using namespace dubbel;

NativeDef(_Line) {
	me.Attr("Index") = Int(0);
	me.Attr("Type") = (Char)LineType::Default;
	return Var();
}

NativeDef(_ScanLines) {
	if (args.GetArray().size() == 0)
		throw Var("Asm.ScanLines : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("Asm.ScanLines : the argument 1 must be of type string");
	vector<Line> lines = ScanLines(args.GetArray()[0].GetString());
	Array arr;
	Var * gbl = me.GetObject().global;
	for(size_t i = 0; i < lines.size(); ++i) {
		Object o(&_Line, gbl);
		Array a;
		for(size_t j = 0; j < lines[i].words.size(); ++j)
			a.push_back(Var(lines[i].words[j]));
		o.members["Words"] = a;
		o.members["Index"] = Int(lines[i].index);
		o.members["Type"] = (Char)lines[i].type;
		arr.push_back(Var(o));
	}
	return Var(arr);
}

NativeDef(_Assembler) {
	Assembler * R = new Assembler();
	me.GetObject().extra = (void*)R;
	return Var();
}

NativeDef(_Assembler_Compile) {
	if (args.GetArray().size() == 0)
		throw Var("Asm.Assembler.Compile : an argument is needed");
	Assembler * R = (Assembler*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Asm.Assembler.Compile : cannot run after a _finalize call");
	if (args.GetArray()[0].Type() == TypeId::String) {
		try {
			R->Compile(args.GetArray()[0].GetString());
		}
		catch(AssemblerErr ex) {
			throw Var(ex.err);
		}
	}
	else if (args.GetArray()[0].Type() == TypeId::Array) {
		Array * arr = &args.GetArray()[0].GetArray();
		vector<Line> lines;
		for(size_t i = 0; i < arr->size(); ++i) {
			if(IdOf(arr->at(i)) != Int((unsigned long)&_Line) * 10 + 2)
				throw Var("Asm.Assembler.Compile : if the argument 1 is an array all elements must be Line instances");
			Object * o = &arr->at(i).GetObject();
			Line l;
			for(size_t j = 0; j < o->members["Words"].GetArray().size(); ++j)
				l.words.push_back(o->members["Words"].GetArray()[j].ToString());
			l.index = o->members["Index"].GetInt().get_ui();
			l.type = (LineType)o->members["Type"].GetChar();
			lines.push_back(l);
		}
		try {
			R->Compile(lines);
		}
		catch(AssemblerErr ex) {
			throw Var(ex.err);
		}
	}
	else throw Var("Asm.Assembler.Compile : the argument 1 must be of type string or array");
	return Var();
}

NativeDef(_Assembler_Translate) {
	if (args.GetArray().size() == 0)
		throw Var("Asm.Assembler.Translate : an argument is needed");
	Assembler * R = (Assembler*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Asm.Assembler.Translate : cannot run after a _finalize call");
	if (args.GetArray()[0].Type() == TypeId::Array) {
		Array * arr = &args.GetArray();
		vector<Line> lines;
		for(size_t i = 0; i < arr->size(); ++i) {
			if(IdOf(arr->at(i)) != 10 * Int((unsigned long)_Line) + 2)
				throw Var("Asm.Assembler.Translate : if the argument 1 is an array all elements must be Line instances");
			Object * o = &arr->at(i).GetObject();
			Line l;
			for(size_t j = 0; j < o->members["Words"].GetArray().size(); ++j)
				l.words.push_back(o->members["Words"].GetArray()[j].ToString());
			l.index = o->members["Index"].GetInt().get_ui();
			l.type = (LineType)o->members["Type"].GetChar();
			lines.push_back(l);
		}
		try {
			R->Translate(lines);
		}
		catch(AssemblerErr ex) {
			throw Var(ex.err);
		}
	}
	else throw Var("Asm.Assembler.Translate : the argument 1 must be of type array");
	return Var();
}

NativeDef(_Assembler_LabelExist) {
	if (args.GetArray().size() == 0)
		throw Var("Asm.Assembler.LabelExist : an argument is needed");
	Assembler * R = (Assembler*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Asm.Assembler.Translate : cannot run after a _finalize call");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("Asm.Assembler.LabelExist : the argument 1 must be of type string");
	return Var((Bool)R->LabelExist(args.GetArray()[0].GetString()));
}

NativeDef(_Assembler_SolveLabels) {
	Assembler * R = (Assembler*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Asm.Assembler.SolveLabels : cannot run after a _finalize call");
	try {
		R->SolveLabels();
	}
	catch(AssemblerErr ex) {
		throw Var(ex.err);
	}
	return Var();
}

NativeDef(_Assembler_GetBytecode) {
	Assembler * R = (Assembler*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Asm.Assembler.GetBytecode : cannot run after a _finalize call");
	return Var(R->GetBytecode());
}

NativeDef(_Disassembler) {
	if (args.GetArray().size() == 0)
		throw Var("Asm.Disassembler : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("Asm.Disassembler : the argument 1 must be of type string");
	return Var(Disassembler(args.GetArray()[0].GetString()));
}

NativeDef(_FileDisassembler) {
	if (args.GetArray().size() == 0)
		throw Var("Asm.FileDisassembler : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("Asm.FileDisassembler : the argument 1 must be of type string");
	return Var(FileDisassembler(args.GetArray()[0].GetString()));
}

LibInit {
	me.Attr("LINETYPE_DEFAULT") = (Char)LineType::Default;
	me.Attr("LINETYPE_CONST") = (Char)LineType::Const;
	me.Attr("LINETYPE_LABEL") = (Char)LineType::Label;
	me.Attr("Line") = Object(&_Line, &me);
	me.Attr("Line").Attr("Words") = Array();
	me.Attr("Line").Attr("Index") = Int(0);
	me.Attr("Line").Attr("Words") = (Char)LineType::Default;
	me.Attr("ScanLines") = Object(&_ScanLines, &me);
	me.Attr("Assembler") = Object(&_Assembler, &me);
	me.Attr("Assembler").Attr("Compile") = Object(&_Assembler_Compile, &me);
	me.Attr("Assembler").Attr("Translate") = Object(&_Assembler_Translate, &me);
	me.Attr("Assembler").Attr("LabelExist") = Object(&_Assembler_LabelExist, &me);
	me.Attr("Assembler").Attr("SolveLabels") = Object(&_Assembler_SolveLabels, &me);
	me.Attr("Assembler").Attr("GetBytecode") = Object(&_Assembler_GetBytecode, &me);
	me.Attr("Disassembler") = Object(&_Disassembler, &me);
	me.Attr("FileDisassembler") = Object(&_FileDisassembler, &me);
}




