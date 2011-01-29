#include "type.h"

//eventually we'll move this to a script file
const double type[TYPE_END][TYPE_END] = {
				/*defending 	GHOST	NORMAL	FIGHTING	FLYING	FIRE	GRASS	WATER */
	/*attacking*/
		/*GHOST*/				1,		1,		1.5,			1,		1,		1,		1,
		/*NORMAL*/				0,		1,		0.5,			1,		1,		1,		1,
	/*FIGHTING*/				0,		2,		1,				1,		1,		1,		0.5,
		/*FLYING*/				1,		1,		2,				1,		1,		1,		1,
	/*FIRE*/					1,		1,		1,				1,		1,		2,		0,
		/*GRASS*/				1,		1,		1,				1,		0,		0.5,	0.5,
		/*WATER*/				1,		1,		1,				1,		2,		0.5,	0.5
};
