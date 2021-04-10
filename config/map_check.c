#include "config.h"

static int		map_init(t_config *config, char ***visit, int dir[2][4])
{
	int r;
	int c;

	dir[0][0] = 0;
	dir[0][1] = 0;
	dir[0][2] = 1;
	dir[0][3] = -1;
	dir[1][0] = 1;
	dir[1][1] = -1;
	dir[1][2] = 0;
	dir[1][3] = 0;
	r = -1;
	if (!(*visit = malloc(sizeof(char*) * (config->map_row))))
		return (0);
	while (++r < config->map_row)
	{
		if (!((*visit)[r] = malloc(sizeof(char) * (config->map_col))))
			return (0);
		c = -1;
		while (++c < config->map_col)
		{
			(*visit)[r][c] = config->map[r][c];
			if ((*visit)[r][c] == '2')
				(*visit)[r][c] = '1';
		}
	}
	return (1);
}

int				check_map(t_config *config, char **visit, int r, int c, int dir[2][4])
{
	int i;

	i = -1;
	// printf("check map\n");
	if (visit[r][c] == 0 || visit[r][c] == ' ')
		return (0);
	if (visit[r][c] == '1' || visit[r][c] == 'x')
		return (1);
	visit[r][c] = 'x';
	while (++i < 4)
		if (!check_map(config, visit, r + dir[0][i], c + dir[1][i], dir))
			return (0);
	return (1);
}

static void		free_map(char **arr, int r)
{
	int i;

	i = -1;
	if (!arr)
		return ;
	while (++i < r)
		free(arr[i]);
}

int				valid_map_check(t_config *config)
{
	int		r;
	int		c;
	int		is_valid;
	char	**visit;
	int		dir[2][4];

	is_valid = 0;
	visit = 0;
	if (config->map_row <= 2 || config->map_col <= 2
	|| !map_init(config, &visit, dir))
		return (0);
	r = -1;
	while (is_valid >= 0&& ++r < config->map_row)
	{
		c = -1;
		while (++c < config->map_col )
			if (visit[r][c] == '0')
			{
				is_valid = 1;
				if (check_map(config, visit, r, c, dir) == 0)
				{
					is_valid = -1;
					break ;
				}
			}
	}
	free_map(visit, config->map_row);
	if (is_valid == 1)
		return (1);
	else
		return (0);
}