#include "Common.hpp"

short MMF2Func Action(RD *rd, long param1, long param2)
{
	DM("Action(piii", "rd", rd, "param1", param1, "param2", param2, "hoEventNumber", rd->rHo.hoEventNumber);
	return 0;
}

long MMF2Func Condition(RD *rd, long param1, long param2)
{
	DM("Condition(piii", "rd", rd, "param1", param1, "param2", param2, "hoEventNumber", rd->rHo.hoEventNumber);
	return 0;
}

long MMF2Func Expression(RD *rd, long param1)
{
	DM("Expression(pii", "rd", rd, "param1", param1, "hoEventNumber", rd->rHo.hoEventNumber);
	return long("");
}
