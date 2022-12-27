#include <idc.idc>

static parseName(name, str1, str2)
{
	auto nm, end, orig;
	if(strstr(name, str1) == 0)
	{
		end = strstr(name, str2);
		nm = substr(name, 1, end);
//		Message(form("hit: before %s after %s\n", name, nm));
	}
	else
		return name;
	return nm;
}

static getName(ea)
{
	auto nm, ret;
	nm = GetFunctionName(ea);
	if(strlen(nm) == 0)
	{
		nm = NameEx(BADADDR, ea);
		ret = parseName(nm, "_", "__");
	}
	else
		ret = parseName(nm, "?", "@@");
	return ret;
}

static main()
{
	auto x, tst, head, ord, ea, nm, entries, rngcur, rngmax;
	//Message(form("\n Program Entry Points: %d\n \n", GetEntryPointQty()));
	head = 0; rngcur = 0; rngmax = 0x100; tst = 0;
	for (x=0; x < GetEntryPointQty(); x = x+1)
	{
		ord = GetEntryOrdinal(x);
		if((ord & 0xFFFF0000) == 0)
		{
			ea = GetEntryPoint(ord);
			nm = getName(ea);
			if(ord == 1)
				Message(form("\t%s @%d\n", nm, ord));
			else
				Message(form("\t%s @%d\n", nm, ord));
		}
	}
}

