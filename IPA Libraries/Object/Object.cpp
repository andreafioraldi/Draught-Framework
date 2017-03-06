#include "Dubbel.h"

using namespace std;
using namespace dubbel;

NativeDef(Attr) {
	if(args.GetArray().size() < 2)
		throw Var("Object.Attr : 2 arguments are needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.Attr : the argument 1 must be of type object");
	if(args.GetArray()[1].Type() != TypeId::String)
		throw Var("Object.Attr : the argument 2 must be of type string");
	if(args.GetArray()[0].Attr(args.GetArray()[1].GetString()).Type() == TypeId::Object)
		args.GetArray()[0].Attr(args.GetArray()[1].GetString()).GetObject().SetParent(args.GetArray()[0]);
	return args.GetArray()[0].Attr(args.GetArray()[1].GetString()).Reference();
}

NativeDef(Exist) {
	if(args.GetArray().size() < 2)
		throw Var("Object.Exist : 2 arguments are needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.Exist : the argument 1 must be of type object");
	if(args.GetArray()[1].Type() != TypeId::String)
		throw Var("Object.Exist : the argument 2 must be of type string");
	Bool r = args.GetArray()[0].GetObject().members.find(args.GetArray()[1].GetString()) != args.GetArray()[0].GetObject().members.end();
	return Var(r);
}

NativeDef(Remove) {
	if(args.GetArray().size() < 2)
		throw Var("Object.Remove : 2 arguments are needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.Remove : the argument 1 must be of type object");
	if(args.GetArray()[1].Type() != TypeId::String)
		throw Var("Object.Remove : the argument 2 must be of type string");
	map<String, Var>::iterator it = args.GetArray()[0].GetObject().members.find(args.GetArray()[1].GetString());
	if(it == args.GetArray()[0].GetObject().members.end())
		throw Var("Object.Remove : \'" + args.GetArray()[1].GetString() + "\' is not a member of the object");
	it->second.Clear();
	args.GetArray()[0].GetObject().members.erase(it);
	return Var();
}

NativeDef(CleanByteCode) {
	if(args.GetArray().size() < 1)
		throw Var("Object.FromByteCode : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::String)
		throw Var("Object.FromByteCode : the argument 1 must be of type string");
	String s = args.GetArray()[0].GetString();
	if(s.size() > 21 && s.substr(0, 22) == "#!/usr/bin/env dubbel\n")
		s.erase(0, 22);
	s.erase(s.begin());
	return Var(s);
}

NativeDef(FromByteCode) {
	if(args.GetArray().size() < 1)
		throw Var("Object.FromByteCode : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::String)
		throw Var("Object.FromByteCode : the argument 1 must be of type string");
	Code * c = BuildCode(args.GetArray()[0].GetString(), 0, args.GetArray()[0].GetString().size());
	return Var(Object(c));
}

NativeDef(ListNames) {
	if(args.GetArray().size() < 1)
		throw Var("Object.ListNames : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.ListNames : the argument 1 must be of type object");
	Array arr;
	for(map<String , Var>::iterator it = args.GetArray()[0].GetObject().members.begin(); it != args.GetArray()[0].GetObject().members.end(); ++it) {
		arr.push_back(Var(it->first));
	}
	return Var(arr);
}

NativeDef(ListConsts) {
	if(args.GetArray().size() < 1)
		throw Var("Object.ListConsts : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.ListConsts : the argument 1 must be of type object");
	if(args.GetArray()[0].GetObject().IsByteCode()) {
		return Var(static_cast<Code*>(args.GetArray()[0].GetObject().content)->consts).Reference();
	}
	throw Var("Object.ListConsts : the object type is not bytecode");
}

NativeDef(IsInvocable) {
	if(args.GetArray().size() < 1)
		throw Var("Object.IsInvocable : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.IsInvocable : the argument 1 must be of type object");
	return Var(args.GetArray()[0].GetObject().IsInvocable());	
}

NativeDef(IsByteCode) {
	if(args.GetArray().size() < 1)
		throw Var("Object.IsByteCode : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.IsByteCode : the argument 1 must be of type object");
	return Var(args.GetArray()[0].GetObject().IsByteCode());	
}

NativeDef(IsNative) {
	if(args.GetArray().size() < 1)
		throw Var("Object.IsNative : an argument is needed");
	if(args.GetArray()[0].Type() != TypeId::Object)
		throw Var("Object.IsNative : the argument 1 must be of type object");
	return Var(args.GetArray()[0].GetObject().IsNative());	
}

LibInit {
	me.Attr("NotInvocable") = Object();
	me.Attr("Attr") = Object(&Attr, &me);
	me.Attr("Exist") = Object(&Exist, &me);
	me.Attr("Remove") = Object(&Remove, &me);
	me.Attr("CleanByteCode") = Object(&CleanByteCode, &me);
	me.Attr("FromByteCode") = Object(&FromByteCode, &me);
	me.Attr("ListNames") = Object(&ListNames, &me);
	me.Attr("ListConsts") = Object(&ListConsts, &me);
	me.Attr("IsInvocable") = Object(&IsInvocable, &me);
	me.Attr("IsByteCode") = Object(&IsByteCode, &me);
	me.Attr("IsNative") = Object(&IsNative, &me);
}
