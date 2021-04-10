#include "config.h"

int		element_check(int set[])
{
	int i;

	i = -1;
	while (++i < 9)
		if (set[i] == 0 && i != C_S && i != C_MAP)
			return (0);
	return (1);
}

int		char_to_int_map(t_config *config)
{
	int		i;
	int		j;

	i = -1;
	if (!(config->map = malloc(sizeof(int*) * config->map_row)))
		return (0);
	while (++i < config->map_row)
	{
		if (!(config->map[i] = malloc(sizeof(int) * config->map_col)))
			return (0);
		j = -1;
		while (++j < config->map_col)
		{
			if (config->map_c[i][j] == ' ')
				config->map[i][j] = 0;
			else
				config->map[i][j] = config->map_c[i][j] - '0';
		}
	}
	return (1);
}

// int		player_valid_check(t_config *config)
// {
	// int		r;
	// int		c;

	// r = config->pos_y;
	// c = config->pos_x;
	// while (++r > config->map_row && ft_strrchr(""))
	// 	if (!ft_strrchr("012", config->map[r][c]))
	// 		return (0);
	// r = config->pos_y;
	// while (--r <= 0)
	// 	if (!ft_strrchr("012", config->map[r][c]))
	// 		return (0);
	// while (!ft_strrchr("012"))
	// return (1);
	// player 위치가 유효한가
// }