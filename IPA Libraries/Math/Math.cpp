#include "Dubbel.h"
#include "mpfr.h"

using namespace std;
using namespace dubbel;

NativeDef(Abs) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Abs : an argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		return Var(Int(abs(args.GetArray()[0].GetInt())));
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		return Var(Float(abs(args.GetArray()[0].GetFloat())));
	}
	throw Var("Math.Abs : the argument 1 must be of type int or float");
}

NativeDef(Fact) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Fact : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init(A);
		mpfr_fac_ui(A, args.GetArray()[0].GetInt().get_ui(), MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Fact : the argument 1 must be of type int");
}

NativeDef(Ceil) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Ceil : an argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Float) {
		return Var(Float(ceil(args.GetArray()[0].GetFloat())));
	}
	throw Var("Math.Ceil : the argument 1 must be of type float");
}

NativeDef(Floor) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Floor : an argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Float) {
		return Var(Float(floor(args.GetArray()[0].GetFloat())));
	}
	throw Var("Math.Floor : the argument 1 must be of type float");
}

NativeDef(Sqrt) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Sqrt : an argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		return Var(Int(sqrt(args.GetArray()[0].GetInt())));
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		return Var(Float(sqrt(args.GetArray()[0].GetFloat())));
	}
	throw Var("Math.Sqrt : the argument 1 must be of type int or float");
}

NativeDef(Pow) {
	if (args.GetArray().size() < 2)
		throw Var("Math.Pow : 2 arguments are needed");
	TypeId tA = args.GetArray()[0].Type();
	TypeId tB = args.GetArray()[1].Type();
	if (tA == TypeId::Int) {
		if (tB == TypeId::Int) {
			mpfr_t A;
			mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init_set_z(B, args.GetArray()[1].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_pow(A, A, B, MPFR_RNDN);
			Int r;
			mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
			return Var(r);
		}
		else if (tB == TypeId::Float) {
			mpfr_t A;
			mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init2(B, args.GetArray()[1].GetFloat().get_prec());
			mpfr_set_f(B, args.GetArray()[1].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_pow(A, A, B, MPFR_RNDN);
			Float r;
			r.set_prec(args.GetArray()[1].GetFloat().get_prec());
			mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
			return Var(r);
		}
		throw Var("Math.Pow : the argument 2 must be of type int or float");
	}
	else if (tA == TypeId::Float) {
		if (tB == TypeId::Int) {
			mpfr_t A;
			mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
			mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init_set_z(B, args.GetArray()[1].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_pow(A, A, B, MPFR_RNDN);
			Float r;
			r.set_prec(args.GetArray()[0].GetFloat().get_prec());
			mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
			return Var(r);
		}
		else if (tB == TypeId::Float) {
			mpfr_t A;
			mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
			mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init2(B, args.GetArray()[1].GetFloat().get_prec());
			mpfr_set_f(B, args.GetArray()[1].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_pow(A, A, B, MPFR_RNDN);
			Float r;
			r.set_prec(args.GetArray()[0].GetFloat().get_prec());
			mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
			return Var(r);
		}
		throw Var("Math.Pow : the argument 2 must be of type int or float");
	}
	throw Var("Math.Pow : the argument 1 must be of type int or float");
}

NativeDef(Exp) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Exp : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_exp(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_exp(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Exp : the argument 1 must be of type int or float");
}

NativeDef(Exp10) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Exp10 : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_exp10(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_exp10(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Exp10 : the argument 1 must be of type int or float");
}

NativeDef(Exp2) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Exp2 : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_exp2(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_exp2(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Exp2 : the argument 1 must be of type int or float");
}

NativeDef(Log) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Log : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_log(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_log(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Log : the argument 1 must be of type int or float");
}

NativeDef(Log10) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Log10 : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_log10(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_log10(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Log10 : the argument 1 must be of type int or float");
}

NativeDef(Log2) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Log2 : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_log2(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_log2(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Log2 : the argument 1 must be of type int or float");
}

NativeDef(Acos) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Acos : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_acos(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_acos(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Acos : the argument 1 must be of type int or float");
}

NativeDef(Asin) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Asin : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_asin(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_asin(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Asin : the argument 1 must be of type int or float");
}

NativeDef(Atan) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Atan : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_atan(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_atan(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Atan : the argument 1 must be of type int or float");
}

NativeDef(Acosh) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Acosh : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_acosh(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_acosh(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Acosh : the argument 1 must be of type int or float");
}

NativeDef(Asinh) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Asinh : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_asinh(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_asinh(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Asinh : the argument 1 must be of type int or float");
}

NativeDef(Atanh) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Atanh : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_atanh(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_atanh(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Atanh : the argument 1 must be of type int or float");
}

NativeDef(Cos) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Cos : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_cos(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_cos(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Cos : the argument 1 must be of type int or float");
}

NativeDef(Sin) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Sin : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_sin(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_sin(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Sin : the argument 1 must be of type int or float");
}

NativeDef(Tan) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Tan : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_tan(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_tan(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Tan : the argument 1 must be of type int or float");
}

NativeDef(Cot) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Cot : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_cot(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_cot(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Cot : the argument 1 must be of type int or float");
}

NativeDef(Cosh) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Cosh : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_cosh(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_cosh(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Cosh : the argument 1 must be of type int or float");
}

NativeDef(Sinh) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Sinh : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_sinh(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_sinh(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Sinh : the argument 1 must be of type int or float");
}

NativeDef(Tanh) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Tanh : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_tanh(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_tanh(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Tanh : the argument 1 must be of type int or float");
}

NativeDef(Coth) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Coth : one argument is needed");
	if (args.GetArray()[0].Type() == TypeId::Int) {
		mpfr_t A;
		mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
		mpfr_coth(A, A, MPFR_RNDN);
		Int r;
		mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
		return Var(r);
	}
	else if (args.GetArray()[0].Type() == TypeId::Float) {
		mpfr_t A;
		mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
		mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
		mpfr_coth(A, A, MPFR_RNDN);
		Float r;
		mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
		return Var(r);
	}
	throw Var("Math.Coth : the argument 1 must be of type int or float");
}

NativeDef(Hypot) {
	if (args.GetArray().size() < 2)
		throw Var("Math.Hypot : 2 arguments are needed");
	TypeId tA = args.GetArray()[0].Type();
	TypeId tB = args.GetArray()[1].Type();
	if (tA == TypeId::Int) {
		if (tB == TypeId::Int) {
			mpfr_t A;
			mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init_set_z(B, args.GetArray()[1].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_hypot(A, A, B, MPFR_RNDN);
			Int r;
			mpfr_get_z(r.get_mpz_t(), A, MPFR_RNDN);
			return Var(r);
		}
		else if (tB == TypeId::Float) {
			mpfr_t A;
			mpfr_init_set_z(A, args.GetArray()[0].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init2(B, args.GetArray()[1].GetFloat().get_prec());
			mpfr_set_f(B, args.GetArray()[1].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_hypot(A, A, B, MPFR_RNDN);
			Float r;
			r.set_prec(args.GetArray()[1].GetFloat().get_prec());
			mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
			return Var(r);
		}
		throw Var("Math.Hypot : the argument 2 must be of type int or float");
	}
	else if (tA == TypeId::Float) {
		if (tB == TypeId::Int) {
			mpfr_t A;
			mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
			mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init_set_z(B, args.GetArray()[1].GetInt().get_mpz_t(), MPFR_RNDN);
			mpfr_hypot(A, A, B, MPFR_RNDN);
			Float r;
			r.set_prec(args.GetArray()[0].GetFloat().get_prec());
			mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
			return Var(r);
		}
		else if (tB == TypeId::Float) {
			mpfr_t A;
			mpfr_init2(A, args.GetArray()[0].GetFloat().get_prec());
			mpfr_set_f(A, args.GetArray()[0].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_t B;
			mpfr_init2(B, args.GetArray()[1].GetFloat().get_prec());
			mpfr_set_f(B, args.GetArray()[1].GetFloat().get_mpf_t(), MPFR_RNDN);
			mpfr_hypot(A, A, B, MPFR_RNDN);
			Float r;
			r.set_prec(args.GetArray()[0].GetFloat().get_prec());
			mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
			return Var(r);
		}
		throw Var("Math.Hypot : the argument 2 must be of type int or float");
	}
	throw Var("Math.Hypot : the argument 1 must be of type int or float");
}

NativeDef(GetPI) {
	if (args.GetArray().size() == 0)
		throw Var("Math.GetPI : one argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Math.GetPI : the argument 1 must be of type int");
	mp_prec_t p = args.GetArray()[0].GetInt().get_ui();
	mpfr_t A;
	mpfr_init2(A, p);
	mpfr_const_pi(A, MPFR_RNDN);
	Float r;
	r.set_prec(p);
	mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
	return r;
}

NativeDef(GetCatalan) {
	if (args.GetArray().size() == 0)
		throw Var("Math.GetCatalan : one argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Math.GetCatalan : the argument 1 must be of type int");
	mp_prec_t p = args.GetArray()[0].GetInt().get_ui();
	mpfr_t A;
	mpfr_init2(A, p);
	mpfr_const_catalan(A, MPFR_RNDN);
	Float r;
	r.set_prec(p);
	mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
	return r;
}

NativeDef(GetEuler) {
	if (args.GetArray().size() == 0)
		throw Var("Math.GetEuler : one argument is needed");
	if (args.GetArray()[0].Type() != TypeId::Int)
		throw Var("Math.GetEuler : the argument 1 must be of type int");
	mp_prec_t p = args.GetArray()[0].GetInt().get_ui();
	mpfr_t A;
	mpfr_init2(A, p);
	mpfr_const_euler(A, MPFR_RNDN);
	Float r;
	r.set_prec(p);
	mpfr_get_f(r.get_mpf_t(), A, MPFR_RNDN);
	return r;
}

NativeDef(Range) {
	if (args.GetArray().size() == 0)
		throw Var("Math.Range : one argument is needed");
	Int a = 0;
	Int step = 1;
	Int b;
	if (args.GetArray().size() == 1) {
		if (args.GetArray()[0].Type() != TypeId::Int)
			throw Var("Math.Range : the argument 1 must be of type int");
		b = args.GetArray()[0].GetInt();
	}
	else {
		if (args.GetArray()[0].Type() != TypeId::Int)
			throw Var("Math.Range : the argument 1 must be of type int");
		a = args.GetArray()[0].GetInt();
		if (args.GetArray()[1].Type() != TypeId::Int)
			throw Var("Math.Range : the argument 2 must be of type int");
		b = args.GetArray()[1].GetInt();
		if (args.GetArray().size() > 2) {
			if (args.GetArray()[2].Type() != TypeId::Int)
				throw Var("Math.Range : the argument 3 must be of type int");
			step = args.GetArray()[2].GetInt();
		}
	}
	Array arr;
	for(; a < b; a += step)
		arr.push_back(Var(a));
	return arr;
}

LibInit {
	me.Attr("Abs") = Object(&Abs, &me);
	me.Attr("Fact") = Object(&Fact, &me);
	me.Attr("Ceil") = Object(&Ceil, &me);
	me.Attr("Floor") = Object(&Floor, &me);
	me.Attr("Sqrt") = Object(&Sqrt, &me);
	me.Attr("Pow") = Object(&Pow, &me);
	me.Attr("Exp") = Object(&Exp, &me);
	me.Attr("Exp10") = Object(&Exp10, &me);
	me.Attr("Exp2") = Object(&Exp2, &me);
	me.Attr("Log") = Object(&Log, &me);
	me.Attr("Log10") = Object(&Log10, &me);
	me.Attr("Log2") = Object(&Log2, &me);
	me.Attr("Acos") = Object(&Acos, &me);
	me.Attr("Asin") = Object(&Asin, &me);
	me.Attr("Atan") = Object(&Atan, &me);
	me.Attr("Acosh") = Object(&Acosh, &me);
	me.Attr("Asinh") = Object(&Asinh, &me);
	me.Attr("Atanh") = Object(&Atanh, &me);
	me.Attr("Cos") = Object(&Cos, &me);
	me.Attr("Sin") = Object(&Sin, &me);
	me.Attr("Tan") = Object(&Tan, &me);
	me.Attr("Cot") = Object(&Cot, &me);
	me.Attr("Cosh") = Object(&Cosh, &me);
	me.Attr("Sinh") = Object(&Sinh, &me);
	me.Attr("Tanh") = Object(&Tanh, &me);
	me.Attr("Coth") = Object(&Coth, &me);
	me.Attr("Hypot") = Object(&Hypot, &me);
	me.Attr("GetPI") = Object(&GetPI, &me);
	me.Attr("GetCatalan") = Object(&GetCatalan, &me);
	me.Attr("GetEuler") = Object(&GetEuler, &me);
	me.Attr("Range") = Object(&Range, &me);
}
