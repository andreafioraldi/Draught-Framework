#include "Dubbel.h"

using namespace std;
using namespace dubbel;

NativeDef(Create) {
	if (args.GetArray().size() == 0)
		throw Var("Ptr.Create : an argument is needed");
	Var::Value * pt = args.GetArray()[0].Copy().val;
	return Var(Int((unsigned long)pt));
}

NativeDef(Free) {
	if (args.GetArray().size() == 0)
		throw Var("Ptr.Free : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Ptr.Free : the argument 1 must be of type int");
	Var::Value * pt = (Var::Value*)args.GetArray()[0].GetInt().get_ui();
	Var v;
	v.val = pt;
	v.Clear();
	return Var();
}

NativeDef(ValueOf) {
	if (args.GetArray().size() == 0)
		throw Var("Ptr.ValueOf : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Ptr.ValueOf : the argument 1 must be of type int");
	Var::Value * pt = (Var::Value*)args.GetArray()[0].GetInt().get_ui();
	Var v;
	v.val = pt;
	return v.Reference();
}

/*NativeDef(Malloc) {
	if (args.GetArray().size() == 0)
		throw Var("Ptr.Malloc : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Ptr.Malloc : the argument 1 must be of type int");
	Var::Value * pt = (Var::Value *)malloc(sizeof(Var::Value) * args.GetArray()[0].GetInt().get_ui());
	return Var(Int((unsigned long)pt));
}*/

LibInit {
	me.Attr("Create") = Object(&Create, &me);
	me.Attr("Free") = Object(&Free, &me);
	me.Attr("ValueOf") = Object(&ValueOf, &me);
	/*me.Attr("Malloc") = Object(&Malloc, &me);
	me.Attr("VALSIZE") = Int(sizeof(Var::Value));*/
}
