#include "Common.hpp"

short MMF2Func Action(RD *rd, long param1, long param2)
{
	DM("Action(pii", "rd", rd, "param1", param1, "param2", param2);
	return 0;
}

long MMF2Func Condition(RD *rd, long param1, long param2)
{
	DM("Condition(pii", "rd", rd, "param1", param1, "param2", param2);
	return 0;
}

long MMF2Func Expression(RD *rd, long param1)
{
	DM("Expression(pi", "rd", rd, "param1", param1);
	return long("");
}
