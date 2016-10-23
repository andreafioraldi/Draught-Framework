#include "Dubbel.h"
#include <ctime>

using namespace std;
using namespace dubbel;

NativeDef(Clock) {
	return Int(clock());
}

NativeDef(Date) {
	me.Attr("YearDay") = Int(0);
	me.Attr("WeekDay") = Int(0);
	me.Attr("Day") = Int(0);
	me.Attr("Month") = Int(0);
	me.Attr("Year") = Int(0);
	me.Attr("Hour") = Int(0);
	me.Attr("Min") = Int(0);
	me.Attr("Sec") = Int(0);
	return Var();
}

NativeDef(Date_ToString) {
	tm t;
	t.tm_yday = me.GetObject().parent->Attr("YearDay").GetInt().get_si();
	t.tm_wday = me.GetObject().parent->Attr("WeekDay").GetInt().get_si();
	t.tm_mday = me.GetObject().parent->Attr("Day").GetInt().get_si();
	t.tm_mon = me.GetObject().parent->Attr("Month").GetInt().get_si();
	t.tm_year = Int(me.GetObject().parent->Attr("Year").GetInt() -1900).get_si();
	t.tm_hour = me.GetObject().parent->Attr("Hour").GetInt().get_si();
	t.tm_min = me.GetObject().parent->Attr("Min").GetInt().get_si();
	t.tm_sec = me.GetObject().parent->Attr("Sec").GetInt().get_si();
	return Var(String(asctime(&t)));
}

NativeDef(Now) {
	Var v = me.GetObject().parent->Attr("Date").Copy();
	time_t T = time(NULL);
	tm * t = localtime(&T);
	v.Attr("YearDay") = Int(t->tm_yday);
	v.Attr("WeekDay") = Int(t->tm_wday);
	v.Attr("Day") = Int(t->tm_mday);
	v.Attr("Month") = Int(t->tm_mon);
	v.Attr("Year") = Int(1900 + t->tm_year);
	v.Attr("Hour") = Int(t->tm_hour);
	v.Attr("Min") = Int(t->tm_min);
	v.Attr("Sec") = Int(t->tm_sec);
	return v;
}

LibInit {
	me.Attr("Clock") = Object(&Clock, &me);
	me.Attr("ClocksSecond") = Int(CLOCKS_PER_SEC);
	me.Attr("Date") = Object(&Date, &me);
	me.Attr("Date").Attr("YearDay") = Int(0);
	me.Attr("Date").Attr("WeekDay") = Int(0);
	me.Attr("Date").Attr("Day") = Int(0);
	me.Attr("Date").Attr("Month") = Int(0);
	me.Attr("Date").Attr("Year") = Int(0);
	me.Attr("Date").Attr("Hour") = Int(0);
	me.Attr("Date").Attr("Min") = Int(0);
	me.Attr("Date").Attr("Sec") = Int(0);
	me.Attr("Date").Attr("ToString") = Object(&Date_ToString, &me);
	me.Attr("Now") = Object(&Now, &me);
}
