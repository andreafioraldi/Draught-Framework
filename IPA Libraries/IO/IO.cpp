#include "Dubbel.h"
#include <cstdio>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
using namespace dubbel;

NativeDef(Print) {
	Array * a = &args.GetArray();
	for (size_t i = 0; i < a->size(); ++i)
		cout << a->at(i).ToString();
	return Var();
}

NativeDef(Printl) {
	Array * a = &args.GetArray();
	for (size_t i = 0; i < a->size(); ++i)
		cout << a->at(i).ToString();
	cout << endl;
	return Var();
}

NativeDef(PrintErr) {
	Array * a = &args.GetArray();
	for (size_t i = 0; i < a->size(); ++i)
		cerr << a->at(i).ToString();
	return Var();
}

NativeDef(Read) {
	size_t l = 2;
	if (args.GetArray().size() > 0) {
		if (args.GetArray()[0].Type() != TypeId::Int)
			throw Var("IO.Read : the argument 1 must be of type int");
		l = args.GetArray()[0].GetInt().get_ui() + 1;
	}
	char * s;
	cin.get(s, l);
	return Var(String(s));
}

NativeDef(Readl) {
	String str;
	if (args.GetArray().size() > 0) {
		if (args.GetArray()[0].Type() != TypeId::Char)
			throw Var("IO.Readl : the argument 1 must be of type char");
		getline(cin, str, (char)args.GetArray()[0].GetChar());
	}
	else getline(cin, str);
	return Var(str);
}

NativeDef(ReadChar) {
	Char ch = cin.get();
	return Var(ch);
}


NativeDef(File) {
	if(args.GetArray().size() == 0)
		return Var();
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("IO.File : the argument 1 must be of type string");
	String flags;
	if(args.GetArray().size() > 1) {
		if (args.GetArray()[1].Type() != TypeId::String)
			throw Var("IO.File : the argument 2 must be of type string");
		flags = args.GetArray()[1].GetString();
		if (flags != "r" && flags != "rb" && flags != "w" && flags != "wb" && flags != "a" && flags != "ab" && flags != "r+" && flags != "w+" && flags != "a+")
			throw Var("IO.File : invalid file flags");
	}
	else flags = "r";
	FILE * f = fopen(args.GetArray()[0].GetString().c_str(), flags.c_str());
	if(!f)
		throw Var("IO.File : invalid file '" + args.GetArray()[0].GetString() + "'");
	me.GetObject().extra = (void*)f;
	return Var();
}

NativeDef(File_Open) {
	if(args.GetArray().size() == 0)
		throw Var("IO.File.Open : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("IO.File.Open : the argument 1 must be of type string");
	String flags;
	if (args.GetArray().size() > 1) {
		if (args.GetArray()[1].Type() != TypeId::String)
			throw Var("IO.File.Open : the argument 2 must be of type string");
		flags = args.GetArray()[1].GetString();
		if(flags != "r" && flags != "rb" && flags != "w" && flags != "wb" && flags != "a" && flags != "ab" && flags != "r+" && flags != "w+" && flags != "a+")
			throw Var("IO.File.Open : invalid file flags");
	}
	else flags = "r";
	FILE * f = fopen(args.GetArray()[0].GetString().c_str(), flags.c_str());
	if (!f)
		throw Var("IO.File.Open : invalid file '" + args.GetArray()[0].GetString() + "'");
	me.GetObject().parent->GetObject().extra = (void*)f;
	return Var();
}

NativeDef(File_Close) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f != nullptr) {
		fclose(f);
		me.GetObject().parent->GetObject().extra = nullptr;
	}
	return Var();
}

NativeDef(File_Flush) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.Flush : the file is closed");
	fflush(f);
	return Var();
}

NativeDef(File_Write) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if(f == nullptr) 
		throw Var("IO.File.Write : the file is closed");
	Array * a = &args.GetArray();
	for (size_t i = 0; i < a->size(); ++i) {
		String s = a->at(i).ToString();
		for (size_t j = 0; j < s.size(); ++j)
			fputc(s[j], f);
	}
	return Var();
}

NativeDef(File_Read) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.Read : the file is closed");
	size_t ssize = 1;
	if (args.GetArray().size() > 0) {
		if (args.GetArray()[0].Type() != TypeId::Int)
			throw Var("IO.File.Read : the argument 1 must be of type int");
		ssize = args.GetArray()[0].GetInt().get_ui();
	}
	String s = "";
	for (; ssize > 0; --ssize) {
		int r = fgetc(f);
		if (r == EOF)
			break;
		s += (char)r;
	}
	return Var(s);
}

NativeDef(File_Readl) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.Readl : the file is closed");
	char delim = '\n';
	if (args.GetArray().size() > 0) {
		if (args.GetArray()[0].Type() != TypeId::Char)
			throw Var("IO.File.Readl : the argument 1 must be of type char");
		delim = (char)args.GetArray()[0].GetChar();
	}
	String s = "";
	while(1) {
		int r = fgetc(f);
		if (r == EOF || r == delim)
			break;
		s += (char)r;
	}
	return Var(s);
}

NativeDef(File_ReadAll) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.ReadAll : the file is closed");
	String s = "";
	while (1) {
		int r = fgetc(f);
		if (r == EOF)
			break;
		s += (char)r;
	}
	return Var(s);
}

NativeDef(File_Reset) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.Reset : the file is closed");
	rewind(f);
	return Var();
}

NativeDef(File_Eof) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.Eof : the file is closed");
	return Var((Bool)feof(f));
}

NativeDef(File_GetPos) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.GetPos : the file is closed");
	return Var(Int(ftell(f)));
}

NativeDef(File_SetPos) {
	if (args.GetArray().size() == 0)
		throw Var("IO.File.SetPos : an argument is needed");
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.SetPos : the file is closed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("IO.File.SetPos : the argument 1 must be of type int");
	fseek(f, args.GetArray()[0].GetInt().get_ui(), SEEK_SET);
	return Var();
}

NativeDef(File_Size) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	if (f == nullptr)
		throw Var("IO.File.Size : the file is closed");
	long int pos = ftell(f);
	fseek(f, 0L, SEEK_END);
	long int size = ftell(f);
	fseek(f, pos, SEEK_SET);
	return Var(Int(size));
}

NativeDef(File__copy) {
	me.GetObject().parent->GetObject().extra = nullptr;
	return Var();
}

NativeDef(File_IsOpen) {
	FILE * f = (FILE*)me.GetObject().parent->GetObject().extra;
	return Var((Bool)(f != nullptr));
}

NativeDef(Rename) {
	if (args.GetArray().size() < 2)
		throw Var("IO.Rename : 2 arguments are needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("IO.Rename : the argument 1 must be of type string");
	if (args.GetArray()[1].Type() != TypeId::String)
		throw Var("IO.Rename : the argument 2 must be of type string");
	rename(args.GetArray()[0].GetString().c_str(), args.GetArray()[1].GetString().c_str());
	return Var();
}

NativeDef(Remove) {
	if (args.GetArray().size() < 1)
		throw Var("IO.Remove : one argument is needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("IO.Remove : the argument 1 must be of type string");
	remove(args.GetArray()[0].GetString().c_str());
	return Var();
}

NativeDef(ChangeDir) {
	if (args.GetArray().size() < 1)
		throw Var("IO.ChangeDir : one argument is needed");
	if (args.GetArray()[0].Type() != TypeId::String)
		throw Var("IO.ChangeDir : the argument 1 must be of type string");
	int r = chdir(args.GetArray()[0].GetString().c_str());
	if(r == -1)
		throw Var("IO.ChangeDir : invalid target path");
	return Var();
}

NativeDef(GetDir) {
#ifdef _WIN32
	char mydir[MAX_PATH];
	_getcwd(mydir, MAX_PATH);
	String s(mydir);
#elif defined _GNU_SOURCE
	char * mydir = get_current_dir_name();
	String s(mydir);
	free(mydir);
#else
	char mydir[FILENAME_MAX];
	getcwd(mydir, FILENAME_MAX);
	String s(mydir);
#endif
	return Var(s);
}

LibInit {
	me.Attr("Print") = Object(&Print, &me);
	me.Attr("Printl") = Object(&Printl, &me);
	me.Attr("PrintErr") = Object(&PrintErr, &me);
	me.Attr("Read") = Object(&Read, &me);
	me.Attr("Readl") = Object(&Readl, &me);
	me.Attr("ReadChar") = Object(&ReadChar, &me);
	me.Attr("File") = Object(&File, &me);
	me.Attr("File").Attr("Open") = Object(&File_Open, &me);
	me.Attr("File").Attr("Close") = Object(&File_Close, &me);
	me.Attr("File").Attr("_finalize") = me.Attr("File").Attr("Close").Reference();
	me.Attr("File").Attr("Flush") = Object(&File_Flush, &me);
	me.Attr("File").Attr("Write") = Object(&File_Write, &me);
	me.Attr("File").Attr("Read") = Object(&File_Read, &me);
	me.Attr("File").Attr("Readl") = Object(&File_Readl, &me);
	me.Attr("File").Attr("ReadAll") = Object(&File_ReadAll, &me);
	me.Attr("File").Attr("Reset") = Object(&File_Reset, &me);
	me.Attr("File").Attr("Eof") = Object(&File_Eof, &me);
	me.Attr("File").Attr("GetPos") = Object(&File_GetPos, &me);
	me.Attr("File").Attr("SetPos") = Object(&File_SetPos, &me);
	me.Attr("File").Attr("Size") = Object(&File_Size, &me);
	me.Attr("File").Attr("_copy") = Object(&File__copy, &me);
	me.Attr("File").Attr("IsOpen") = Object(&File_IsOpen, &me);
	me.Attr("Rename") = Object(&Rename, &me);
	me.Attr("Remove") = Object(&Remove, &me);
	me.Attr("ChangeDir") = Object(&ChangeDir, &me);
	me.Attr("GetDir") = Object(&GetDir, &me);
}



