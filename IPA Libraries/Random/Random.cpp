#include "Dubbel.h"

using namespace std;
using namespace dubbel;

NativeDef(State) {
	if (args.GetArray().size() == 0)
		throw Var("Random.State : an argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Random.State : the argument 1 must be of type int");
	gmp_randclass * R = new gmp_randclass(gmp_randinit_default);
	R->seed(args.GetArray()[0].GetInt());
	me.GetObject().extra = (void*)R;
	return Var();
}

NativeDef(State_NextBits) {
	if (args.GetArray().size() == 0)
		throw Var("Random.State.NextBits : an argument is needed");
	gmp_randclass * R = (gmp_randclass*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Random.State.NextBits : cannot run after a _finalize call");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Random.State.NextBits : the argument 1 must be of type int");
	return Var(Int(R->get_z_bits(args.GetArray()[0].GetInt())));
}

NativeDef(State_NextRange) {
	if (args.GetArray().size() == 0)
		throw Var("Random.State.NextRange : an argument is needed");
	gmp_randclass * R = (gmp_randclass*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Random.State.NextRange : cannot run after a _finalize call");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Random.State.NextRange : the argument 1 must be of type int");
	return Var(Int(R->get_z_range(args.GetArray()[0].GetInt())));
}

NativeDef(State_NextFloat) {
	if (args.GetArray().size() == 0)
		throw Var("Random.State.NextFloat : an argument is needed");
	gmp_randclass * R = (gmp_randclass*)me.GetObject().parent->GetObject().extra;
	if (R == nullptr)
		throw Var("Random.State.NextFloat : cannot run after a _finalize call");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Random.State.NextFloat : the argument 1 must be of type int");
	return Var(Float(R->get_f(args.GetArray()[0].GetInt().get_ui())));
}

NativeDef(State__copy) {
	me.GetObject().parent->GetObject().extra = nullptr;
	return Var();
}

NativeDef(State__finalize) {
	gmp_randclass * R = (gmp_randclass*)me.GetObject().parent->GetObject().extra;
	if (R != nullptr) {
		delete R;
		me.GetObject().parent->GetObject().extra = nullptr;
	}
	return Var();
}

LibInit {
	me.Attr("State") = Object(&State, &me);
	me.Attr("State").Attr("NextBits") = Object(&State_NextBits, &me);
	me.Attr("State").Attr("NextRange") = Object(&State_NextRange, &me);
	me.Attr("State").Attr("NextFloat") = Object(&State_NextFloat, &me);
	me.Attr("State").Attr("_copy") = Object(&State__copy, &me);
	me.Attr("State").Attr("_finalize") = Object(&State__finalize, &me);
}
