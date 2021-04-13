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
	if (!(config->map = malloc(sizeof(int*) * config->map_col)))
		return (0);
	while (++i < config->map_col)
		if (!(config->map[i] = malloc(sizeof(int) * config->map_row)))
			return (0);
	// if (!(config->map = malloc(sizeof(int*) * config->map_row)))
	// 	return (0);
	// while (++i < config->map_row)
	// 	if (!(config->map[i] = malloc(sizeof(int) * config->map_col)))
	// 		return (0);
	i = -1;
	// printf("row: %d col: %d\n", config->map_row, config->map_col);
	// while (++i < config->map_row)
	// {
	// 	j = -1;
	// 	while (++j < config->map_col)
	// 	{
	// 		if (config->map_c[i][j] == ' ' || config->map_c[i][j] == 'x')
	// 			config->map[i][j] = 0;
	// 		else
	// 			config->map[i][j] = config->map_c[i][j] - '0';
	// 		printf("%c", config->map_c[i][j]);
	// 	}
	// 	printf("\n");
	// }
	while (++i < config->map_row)
	{
		j = -1;
		while (++j < config->map_col)
		{
			if (config->map_c[i][j] == ' ' || config->map_c[i][j] == 'x')
				config->map[config->map_col - j - 1][config->map_row - i - 1] = 0;
			else
				config->map[config->map_col - j - 1][config->map_row - i - 1] = config->map_c[i][j] - '0';
			printf("%c", config->map_c[i][j]);
		}
		printf("\n");
	}
	i = -1;
	while (++i < config->map_col)
	{
		j = -1;
		while (++j < config->map_row)
			printf("%d", config->map[i][j]);
		printf("\n");
	}
	printf("\n");
	return (1);
}

int		player_valid_check(t_config *config)
{
	int		r;
	int		c;

	r = config->pos_y;
	c = config->pos_x;
	if (r <= 0 || r >= config->map_row - 1 || c <= 0 || c >= config->map_col - 1)
		return (0);
	if (!ft_strrchr("12x", config->map_c[r][c + 1]) || !ft_strrchr("12x", config->map_c[r][c - 1])
	|| !ft_strrchr("12x", config->map_c[r + 1][c]) || !ft_strrchr("12x", config->map_c[r - 1][c]))
		return (0);
	return (1);
}