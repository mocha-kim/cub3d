#include "config.h"

int		element_check(int set[])
{
	int i;

	i = 0;
	while (i < 9)
		if (set[i++] == 0 && i != C_S)
			return (0);
	return (1);
}