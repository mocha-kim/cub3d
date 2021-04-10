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

int		char_to_int_map(t_config *config)
{
	int		i;
	int		j;

	i = -1;

	printf("int map\n");
	if (!(config->map = malloc(sizeof(int*) * config->map_row)))
		return (0);
	while (++i < config->map_row)
	{
		j = -1;
		while (++j < config->map_col)
		{
			if (!(config->map[i] = malloc(sizeof(int) * config->map_col)))
				return (0);
			if (config->map_c[i][j] == ' ')
				config->map[i][j] = 0;
			else
				config->map[i][j] = config->map_c[i][j] - '0';
		}
	}
	printf("done\n");
	return (1);
}